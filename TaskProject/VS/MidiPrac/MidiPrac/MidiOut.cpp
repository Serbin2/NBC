#include "MidiOut.h"
#include <cstdio>
#include <algorithm>

using namespace std;

// ════════════════════════════════════════════════════════════
// 사운드폰트 탐색 (백엔드와 무관한 공용 헬퍼)
// ════════════════════════════════════════════════════════════
vector<string> ScanSoundFonts()
{
	vector<string> result;
	vector<string> seen;   // 중복 제거용: 정규화한 절대경로(소문자)

	// 상대/단축 경로를 절대경로로 정규화 (같은 파일을 여러 폴더에서 찾는 중복 방지)
	auto normalize = [](const string& p) -> string
	{
		char full[MAX_PATH] = {};
		if (GetFullPathNameA(p.c_str(), MAX_PATH, full, NULL))
		{
			string s = full;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			return s;
		}
		return p;
	};

	auto addSf2InDir = [&](const string& dir)
	{
		WIN32_FIND_DATAA fd{};
		HANDLE h = FindFirstFileA((dir + "*.sf2").c_str(), &fd);
		if (h == INVALID_HANDLE_VALUE) return;
		vector<string> found;
		do { found.push_back(dir + fd.cFileName); } while (FindNextFileA(h, &fd));
		FindClose(h);
		sort(found.begin(), found.end());
		for (const string& f : found)
		{
			string key = normalize(f);
			if (find(seen.begin(), seen.end(), key) != seen.end()) continue;
			seen.push_back(key);
			result.push_back(f);
		}
	};

	addSf2InDir("");   // 작업 폴더

	// 실행 파일 폴더와 그 상위 프로젝트 폴더(x64\Debug 기준 ..\..)도 찾아본다
	char exePath[MAX_PATH] = {};
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	string exeDir = exePath;
	size_t slash = exeDir.find_last_of('\\');
	if (slash != string::npos)
	{
		exeDir = exeDir.substr(0, slash + 1);
		addSf2InDir(exeDir);
		addSf2InDir(exeDir + "..\\..\\");
	}
	return result;
}

// ════════════════════════════════════════════════════════════
// WinmmOut
// ════════════════════════════════════════════════════════════

unique_ptr<WinmmOut> WinmmOut::Create(int deviceIndex)
{
	UINT id = (deviceIndex < 0) ? MIDI_MAPPER : (UINT)deviceIndex;

	HMIDIOUT dev = NULL;
	if (midiOutOpen(&dev, id, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return nullptr;

	auto out = unique_ptr<WinmmOut>(new WinmmOut());
	out->m_dev = dev;

	MIDIOUTCAPSA caps{};
	if (midiOutGetDevCapsA((UINT_PTR)id, &caps, sizeof(caps)) == MMSYSERR_NOERROR)
	{
		out->m_name = string("winmm: ") + caps.szPname;
		out->m_volumeSupported = (caps.dwSupport & MIDICAPS_VOLUME) != 0;
	}
	else
		out->m_name = "winmm";
	return out;
}

vector<string> WinmmOut::DeviceNames()
{
	vector<string> names;
	UINT n = midiOutGetNumDevs();
	for (UINT i = 0; i < n; i++)
	{
		MIDIOUTCAPSA caps{};
		if (midiOutGetDevCapsA(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR)
			names.push_back(caps.szPname);
		else
			names.push_back("(알 수 없는 장치)");
	}
	return names;
}

void WinmmOut::ListDevices()
{
	vector<string> names = DeviceNames();
	printf("MIDI 출력 장치 %zu개:\n", names.size());
	for (size_t i = 0; i < names.size(); i++)
		printf("  [%zu] %s\n", i, names[i].c_str());
}

WinmmOut::~WinmmOut()
{
	if (m_dev)
	{
		AllSoundOff();          // 닫기 전에 울리는 음을 모두 정리
		midiOutClose(m_dev);
	}
}

void WinmmOut::NoteOn(int ch, int key, int vel)        { Short((0x90 | ch) | (key << 8) | (vel << 16)); }
void WinmmOut::NoteOff(int ch, int key)                { Short((0x80 | ch) | (key << 8)); }
void WinmmOut::ControlChange(int ch, int num, int val) { Short((0xB0 | ch) | (num << 8) | (val << 16)); }
void WinmmOut::ProgramChange(int ch, int prog)         { Short((0xC0 | ch) | (prog << 8)); }
void WinmmOut::ChannelPressure(int ch, int val)        { Short((0xD0 | ch) | (val << 8)); }
void WinmmOut::KeyPressure(int ch, int key, int val)   { Short((0xA0 | ch) | (key << 8) | (val << 16)); }

void WinmmOut::PitchBend(int ch, int value)
{
	// 14비트 값을 LSB(하위 7비트) / MSB(상위 7비트)로 분해해서 보낸다
	Short((0xE0 | ch) | ((value & 0x7F) << 8) | (((value >> 7) & 0x7F) << 16));
}

// SysEx는 길이가 가변이라 midiOutShortMsg로 보낼 수 없고
// midiOutLongMsg + MIDIHDR 절차가 필요하다:
//   버퍼 등록(Prepare) → 전송 → 완료 대기 → 등록 해제(Unprepare)
void WinmmOut::SysEx(const uint8_t* msg, size_t len)
{
	if (!m_dev || !msg || len == 0) return;

	MIDIHDR hdr{};
	hdr.lpData          = (LPSTR)msg;
	hdr.dwBufferLength  = (DWORD)len;
	hdr.dwBytesRecorded = (DWORD)len;

	if (midiOutPrepareHeader(m_dev, &hdr, sizeof(hdr)) != MMSYSERR_NOERROR)
		return;
	if (midiOutLongMsg(m_dev, &hdr, sizeof(hdr)) == MMSYSERR_NOERROR)
	{
		// 드라이버가 비동기로 전송할 수 있으므로 완료 플래그를 기다린다 (최대 1초)
		for (int i = 0; i < 1000 && !(hdr.dwFlags & MHDR_DONE); i++)
			Sleep(1);
	}
	midiOutUnprepareHeader(m_dev, &hdr, sizeof(hdr));
}

void WinmmOut::NotesOff(int ch)  { ControlChange(ch, 123, 0); }
void WinmmOut::SoundsOff(int ch) { ControlChange(ch, 120, 0); }

void WinmmOut::SetVolume(int percent)
{
	if (!m_dev || !m_volumeSupported) return;
	if (percent < 0)   percent = 0;
	if (percent > 100) percent = 100;
	DWORD v = (DWORD)(0xFFFF * percent / 100);
	midiOutSetVolume(m_dev, MAKELONG(v, v));   // 좌/우 채널 동일하게
}

// ════════════════════════════════════════════════════════════
// FluidSynthOut
// ════════════════════════════════════════════════════════════

// fluidsynth.h 가 동봉되어 있지 않으므로 필요한 함수만 직접 선언해서
// GetProcAddress 로 가져온다. fluid_*_t 타입은 전부 불투명 포인터 → void*.
struct FluidApi
{
	void* (*new_settings)();
	int   (*settings_setstr)(void*, const char*, const char*);
	void* (*new_synth)(void*);
	int   (*sfload)(void*, const char*, int);
	void* (*new_driver)(void*, void*);
	int   (*noteon)(void*, int, int, int);
	int   (*noteoff)(void*, int, int);
	int   (*cc)(void*, int, int, int);
	int   (*program_change)(void*, int, int);
	int   (*pitch_bend)(void*, int, int);
	int   (*channel_pressure)(void*, int, int);
	int   (*key_pressure)(void*, int, int, int);
	int   (*sysex)(void*, const char*, int, char*, int*, int*, int);
	void  (*set_gain)(void*, float);
	int   (*all_notes_off)(void*, int);
	int   (*all_sounds_off)(void*, int);
	void  (*del_driver)(void*);
	void  (*del_synth)(void*);
	void  (*del_settings)(void*);
};

// DLL 후보 이름을 기본 검색 경로 → 실행 파일 기준 상대 폴더 순으로 시도한다.
// LOAD_WITH_ALTERED_SEARCH_PATH: 그 DLL이 의존하는 다른 DLL(SDL3, sndfile 등)도
// 같은 폴더에서 함께 찾을 수 있게 한다.
static HMODULE TryLoadFluidDll()
{
	const char* names[] = { "libfluidsynth-3.dll", "fluidsynth-3.dll", "libfluidsynth.dll", "fluidsynth.dll" };

	// 1) 기본 검색 경로 (실행 파일 폴더 → 시스템 폴더 → 작업 폴더 → PATH)
	for (const char* n : names)
	{
		if (HMODULE h = LoadLibraryA(n)) return h;
	}

	// 2) 실행 파일 기준 상대 폴더 — x64\Debug 에서 실행해도 프로젝트 폴더의 DLL을 찾도록
	char exePath[MAX_PATH] = {};
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	string exeDir = exePath;
	size_t slash = exeDir.find_last_of('\\');
	exeDir = (slash == string::npos) ? "." : exeDir.substr(0, slash);

	const string dirs[] = { exeDir + "\\", exeDir + "\\..\\..\\" };
	for (const string& d : dirs)
	{
		for (const char* n : names)
		{
			string full = d + n;
			if (HMODULE h = LoadLibraryExA(full.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH))
				return h;
		}
	}
	return NULL;
}

static bool LoadFluidApi(HMODULE dll, FluidApi* api)
{
	// 하나라도 없으면 버전이 맞지 않는 것으로 보고 실패 처리
#define FLUID_LOAD(field, name) \
	api->field = (decltype(api->field))GetProcAddress(dll, name); \
	if (!api->field) return false;

	FLUID_LOAD(new_settings,     "new_fluid_settings")
	FLUID_LOAD(settings_setstr,  "fluid_settings_setstr")
	FLUID_LOAD(new_synth,        "new_fluid_synth")
	FLUID_LOAD(sfload,           "fluid_synth_sfload")
	FLUID_LOAD(new_driver,       "new_fluid_audio_driver")
	FLUID_LOAD(noteon,           "fluid_synth_noteon")
	FLUID_LOAD(noteoff,          "fluid_synth_noteoff")
	FLUID_LOAD(cc,               "fluid_synth_cc")
	FLUID_LOAD(program_change,   "fluid_synth_program_change")
	FLUID_LOAD(pitch_bend,       "fluid_synth_pitch_bend")
	FLUID_LOAD(channel_pressure, "fluid_synth_channel_pressure")
	FLUID_LOAD(key_pressure,     "fluid_synth_key_pressure")
	FLUID_LOAD(sysex,            "fluid_synth_sysex")
	FLUID_LOAD(set_gain,         "fluid_synth_set_gain")
	FLUID_LOAD(all_notes_off,    "fluid_synth_all_notes_off")
	FLUID_LOAD(all_sounds_off,   "fluid_synth_all_sounds_off")
	FLUID_LOAD(del_driver,       "delete_fluid_audio_driver")
	FLUID_LOAD(del_synth,        "delete_fluid_synth")
	FLUID_LOAD(del_settings,     "delete_fluid_settings")
#undef FLUID_LOAD
	return true;
}

FluidSynthOut::FluidSynthOut() = default;

FluidSynthOut::~FluidSynthOut()
{
	// 생성의 역순으로 정리한다 (드라이버가 신스를 참조하므로 드라이버부터)
	if (m_api)
	{
		if (m_driver)   m_api->del_driver(m_driver);
		if (m_synth)    m_api->del_synth(m_synth);
		if (m_settings) m_api->del_settings(m_settings);
	}
	if (m_dll) FreeLibrary(m_dll);
}

unique_ptr<FluidSynthOut> FluidSynthOut::Create(const string& soundfontPath)
{
	HMODULE dll = TryLoadFluidDll();
	if (!dll) return nullptr;

	auto api = make_unique<FluidApi>();
	if (!LoadFluidApi(dll, api.get()))
	{
		FreeLibrary(dll);
		return nullptr;
	}

	// FluidSynth 자체 로그가 콘솔 상태 표시를 어지럽히지 않도록 끈다.
	// (예: gm.dls는 SF2 로더가 먼저 실패한 뒤 DLS 로더로 성공하는데,
	//  그 과정의 에러까지 찍힌다. 실패 안내는 우리 쪽 메시지로 충분하다)
	typedef void (*SetLogFn)(int, void*, void*);
	if (auto setLog = (SetLogFn)GetProcAddress(dll, "fluid_set_log_function"))
	{
		setLog(1, NULL, NULL);   // FLUID_ERR
		setLog(2, NULL, NULL);   // FLUID_WARN
		setLog(3, NULL, NULL);   // FLUID_INFO
		setLog(4, NULL, NULL);   // FLUID_DBG
	}

	// 이후 실패하더라도 소멸자가 (생성된 데까지만) 정리해 준다
	unique_ptr<FluidSynthOut> out(new FluidSynthOut());
	out->m_dll = dll;
	out->m_api = std::move(api);

	out->m_settings = out->m_api->new_settings();
	if (!out->m_settings) return nullptr;

	out->m_synth = out->m_api->new_synth(out->m_settings);
	if (!out->m_synth) return nullptr;

	// 사운드폰트 로드. 빌드에 따라 .sf2 외에 .sf3/.dls 를 지원하기도 한다.
	// 실패(-1)하면 이 백엔드는 포기 → 호출자가 다음 후보/winmm으로 넘어간다.
	if (out->m_api->sfload(out->m_synth, soundfontPath.c_str(), 1) < 0)
		return nullptr;

	// 오디오 드라이버 시작 — 기본 드라이버가 실패하면 후보를 차례로 시도
	out->m_driver = out->m_api->new_driver(out->m_settings, out->m_synth);
	if (!out->m_driver)
	{
		const char* drivers[] = { "sdl3", "sdl2", "wasapi", "dsound", "waveout" };
		for (const char* d : drivers)
		{
			out->m_api->settings_setstr(out->m_settings, "audio.driver", d);
			out->m_driver = out->m_api->new_driver(out->m_settings, out->m_synth);
			if (out->m_driver) break;
		}
	}
	if (!out->m_driver) return nullptr;

	// 표시용 이름: "FluidSynth (사운드폰트 파일명)"
	size_t slash = soundfontPath.find_last_of("\\/");
	string sfName = (slash == string::npos) ? soundfontPath : soundfontPath.substr(slash + 1);
	out->m_name = "FluidSynth (" + sfName + ")";
	return out;
}

void FluidSynthOut::NoteOn(int ch, int key, int vel)        { m_api->noteon(m_synth, ch, key, vel); }
void FluidSynthOut::NoteOff(int ch, int key)                { m_api->noteoff(m_synth, ch, key); }
void FluidSynthOut::ControlChange(int ch, int num, int val) { m_api->cc(m_synth, ch, num, val); }
void FluidSynthOut::ProgramChange(int ch, int prog)         { m_api->program_change(m_synth, ch, prog); }
void FluidSynthOut::PitchBend(int ch, int value)            { m_api->pitch_bend(m_synth, ch, value); }
void FluidSynthOut::ChannelPressure(int ch, int val)        { m_api->channel_pressure(m_synth, ch, val); }
void FluidSynthOut::KeyPressure(int ch, int key, int val)   { m_api->key_pressure(m_synth, ch, key, val); }

// FluidSynth는 0xF0/0xF7 프레이밍을 뺀 본문만 받는다
void FluidSynthOut::SysEx(const uint8_t* msg, size_t len)
{
	if (len < 2 || msg[0] != 0xF0 || msg[len - 1] != 0xF7)
		return;   // 프레이밍이 없는 이스케이프 패킷은 신스 합성에 의미가 없어 무시
	m_api->sysex(m_synth, (const char*)(msg + 1), (int)(len - 2), NULL, NULL, NULL, 0);
}

void FluidSynthOut::NotesOff(int ch)  { m_api->all_notes_off(m_synth, ch); }
void FluidSynthOut::SoundsOff(int ch) { m_api->all_sounds_off(m_synth, ch); }

// FluidSynth 기본 게인 0.2 를 100% 기준으로 보고 비례 조절한다
void FluidSynthOut::SetVolume(int percent)
{
	if (percent < 0)   percent = 0;
	if (percent > 100) percent = 100;
	m_api->set_gain(m_synth, 0.2f * percent / 100.0f);
}
