#include "FluidSynthRenderer.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"

// fluidsynth.h 가 없으므로 필요한 함수만 직접 선언해 GetProcAddress 로 가져온다.
// fluid_*_t 타입은 전부 불투명 포인터이므로 void* 로 다룬다.
// (Win64 에서는 x64 호출 규약이 하나뿐이라 __cdecl 명시는 불필요)
struct FFluidApi
{
	void* (*new_settings)();
	int   (*settings_setstr)(void*, const char*, const char*);
	int   (*settings_setnum)(void*, const char*, double);
	void* (*new_synth)(void*);
	int   (*sfload)(void*, const char*, int);
	int   (*write_float)(void*, int, void*, int, int, void*, int, int);
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
	void  (*del_synth)(void*);
	void  (*del_settings)(void*);
};

namespace
{
	// 스테이징된 DLL 들이 있는 플러그인 Binaries/Win64 폴더.
	FString FluidBinDir()
	{
		TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("MidiCore"));
		if (!Plugin.IsValid())
		{
			return FString();
		}
		return FPaths::Combine(Plugin->GetBaseDir(), TEXT("Binaries"), TEXT("Win64"));
	}
}

bool FFluidSynthRenderer::Init(int32 SampleRate, const FString& SoundFontPath)
{
	const FString BinDir = FluidBinDir();
	if (BinDir.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("[MidiSynth] 플러그인 경로를 찾을 수 없습니다."));
		return false;
	}

	// libfluidsynth-3.dll 의 임포트(SDL3/sndfile)를 먼저 같은 폴더에서 로드해 둔다.
	// (이미 로드된 동일 이름 모듈을 Windows 가 재사용하므로 import 해소가 안전해진다)
	DllSdl     = FPlatformProcess::GetDllHandle(*FPaths::Combine(BinDir, TEXT("SDL3.dll")));
	DllSndfile = FPlatformProcess::GetDllHandle(*FPaths::Combine(BinDir, TEXT("sndfile.dll")));
	DllFluid   = FPlatformProcess::GetDllHandle(*FPaths::Combine(BinDir, TEXT("libfluidsynth-3.dll")));
	if (!DllFluid)
	{
		UE_LOG(LogTemp, Error, TEXT("[MidiSynth] libfluidsynth-3.dll 로드 실패: %s"), *BinDir);
		Shutdown();
		return false;
	}

	Api = new FFluidApi();

	// 하나라도 없으면 버전 불일치로 보고 실패 처리.
#define FLUID_LOAD(Field, Name) \
	Api->Field = (decltype(Api->Field))FPlatformProcess::GetDllExport(DllFluid, TEXT(Name)); \
	if (!Api->Field) { UE_LOG(LogTemp, Error, TEXT("[MidiSynth] 심볼 누락: %s"), TEXT(Name)); Shutdown(); return false; }

	FLUID_LOAD(new_settings,     "new_fluid_settings")
	FLUID_LOAD(settings_setstr,  "fluid_settings_setstr")
	FLUID_LOAD(settings_setnum,  "fluid_settings_setnum")
	FLUID_LOAD(new_synth,        "new_fluid_synth")
	FLUID_LOAD(sfload,           "fluid_synth_sfload")
	FLUID_LOAD(write_float,      "fluid_synth_write_float")
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
	FLUID_LOAD(del_synth,        "delete_fluid_synth")
	FLUID_LOAD(del_settings,     "delete_fluid_settings")
#undef FLUID_LOAD

	// FluidSynth 자체 로그를 끈다(선택 — 심볼 없으면 무시).
	typedef void (*SetLogFn)(int, void*, void*);
	if (SetLogFn SetLog = (SetLogFn)FPlatformProcess::GetDllExport(DllFluid, TEXT("fluid_set_log_function")))
	{
		for (int Level = 1; Level <= 4; ++Level) SetLog(Level, nullptr, nullptr);
	}

	Settings = Api->new_settings();
	if (!Settings) { Shutdown(); return false; }

	// 드라이버를 만들지 않으므로 샘플레이트만 UE 에 맞춰 둔다(반드시 synth 생성 전에).
	Api->settings_setnum(Settings, "synth.sample-rate", (double)SampleRate);

	Synth = Api->new_synth(Settings);
	if (!Synth) { Shutdown(); return false; }

	// 사운드폰트 로드(실패하면 -1) → 소리 없음.
	if (Api->sfload(Synth, TCHAR_TO_UTF8(*SoundFontPath), 1) < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[MidiSynth] 사운드폰트 로드 실패: %s"), *SoundFontPath);
		Shutdown();
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("[MidiSynth] FluidSynth 준비됨 (%d Hz, sf2=%s)"), SampleRate, *SoundFontPath);
	return true;
}

void FFluidSynthRenderer::Shutdown()
{
	if (Api)
	{
		if (Synth)    Api->del_synth(Synth);
		if (Settings) Api->del_settings(Settings);
	}
	Synth = nullptr;
	Settings = nullptr;

	delete Api;
	Api = nullptr;

	// FPlatformProcess::GetDllHandle 로 얻은 핸들은 짝지어 해제한다.
	if (DllFluid)   { FPlatformProcess::FreeDllHandle(DllFluid);   DllFluid = nullptr; }
	if (DllSndfile) { FPlatformProcess::FreeDllHandle(DllSndfile); DllSndfile = nullptr; }
	if (DllSdl)     { FPlatformProcess::FreeDllHandle(DllSdl);     DllSdl = nullptr; }
}

FFluidSynthRenderer::~FFluidSynthRenderer()
{
	Shutdown();
}

void FFluidSynthRenderer::NoteOn(int32 Ch, int32 Key, int32 Vel)        { if (Synth) Api->noteon(Synth, Ch, Key, Vel); }
void FFluidSynthRenderer::NoteOff(int32 Ch, int32 Key)                  { if (Synth) Api->noteoff(Synth, Ch, Key); }
void FFluidSynthRenderer::ControlChange(int32 Ch, int32 Num, int32 Val) { if (Synth) Api->cc(Synth, Ch, Num, Val); }
void FFluidSynthRenderer::ProgramChange(int32 Ch, int32 Prog)           { if (Synth) Api->program_change(Synth, Ch, Prog); }
void FFluidSynthRenderer::PitchBend(int32 Ch, int32 Value14)            { if (Synth) Api->pitch_bend(Synth, Ch, Value14); }
void FFluidSynthRenderer::ChannelPressure(int32 Ch, int32 Val)          { if (Synth) Api->channel_pressure(Synth, Ch, Val); }
void FFluidSynthRenderer::KeyPressure(int32 Ch, int32 Key, int32 Val)   { if (Synth) Api->key_pressure(Synth, Ch, Key, Val); }

// FluidSynth 는 0xF0/0xF7 프레이밍을 뺀 본문만 받는다(콘솔판과 동일).
void FFluidSynthRenderer::SysEx(const uint8* Data, int32 Len)
{
	if (!Synth || Len < 2 || Data[0] != 0xF0 || Data[Len - 1] != 0xF7)
	{
		return;
	}
	Api->sysex(Synth, (const char*)(Data + 1), Len - 2, nullptr, nullptr, nullptr, 0);
}

void FFluidSynthRenderer::AllNotesOff(int32 Ch)  { if (Synth) Api->all_notes_off(Synth, Ch); }
void FFluidSynthRenderer::AllSoundOff(int32 Ch)  { if (Synth) Api->all_sounds_off(Synth, Ch); }

void FFluidSynthRenderer::AllNotesOffEveryChannel()
{
	for (int32 Ch = 0; Ch < 16; ++Ch) AllNotesOff(Ch);
}
void FFluidSynthRenderer::AllSoundOffEveryChannel()
{
	for (int32 Ch = 0; Ch < 16; ++Ch) AllSoundOff(Ch);
}

void FFluidSynthRenderer::SetGain(float Gain)
{
	if (Synth) Api->set_gain(Synth, Gain);
}

void FFluidSynthRenderer::RenderFloat(float* Interleaved, int32 Frames)
{
	if (!Synth || Frames <= 0)
	{
		return;
	}
	// 인터리브 스테레오: L = offset0/incr2, R = offset1/incr2
	Api->write_float(Synth, Frames, Interleaved, 0, 2, Interleaved, 1, 2);
}
