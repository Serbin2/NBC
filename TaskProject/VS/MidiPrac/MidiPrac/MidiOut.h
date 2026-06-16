#pragma once
// ──────────────────────────────────────────────────────────────
// MIDI 출력 백엔드 추상화
//
// 파서(CMidi)가 만든 이벤트를 MidiPlayer가 이 인터페이스를 통해 송출한다.
//  - WinmmOut      : Windows 기본 winmm API (MS GS Wavetable 등 장치로 출력)
//  - FluidSynthOut : 동봉된 FluidSynth DLL을 런타임에 로드해
//                    사운드폰트(.sf2 등)로 직접 렌더링한다 (음질 ↑)
// ──────────────────────────────────────────────────────────────
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN   // 자주 쓰지 않는 Windows 헤더 제외
#endif
#ifndef NOMINMAX
#define NOMINMAX              // min/max 매크로 차단 (std::min/std::max 사용을 위해)
#endif
#include <windows.h>
#include <mmsystem.h>         // winmm MIDI 출력 API
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#pragma comment(lib, "winmm.lib")   // winmm.lib 자동 링크

// 작업/실행 폴더(및 그 상위 프로젝트 폴더)에서 *.sf2 사운드폰트를 찾아
// 경로 목록으로 돌려준다. 중복 파일은 한 번만 포함한다.
// (출력 선택 메뉴와 자동 탐색 양쪽에서 함께 쓴다)
std::vector<std::string> ScanSoundFonts();

// 모든 백엔드가 구현해야 하는 출력 인터페이스
class IMidiOut
{
public:
	virtual ~IMidiOut() = default;
	virtual const char* Name() const = 0;   // 표시용 이름

	// 채널(연주) 이벤트
	virtual void NoteOn(int ch, int key, int vel) = 0;
	virtual void NoteOff(int ch, int key) = 0;
	virtual void ControlChange(int ch, int num, int val) = 0;
	virtual void ProgramChange(int ch, int prog) = 0;
	virtual void PitchBend(int ch, int value) = 0;          // 14비트(0~16383), 중앙 8192
	virtual void ChannelPressure(int ch, int val) = 0;
	virtual void KeyPressure(int ch, int key, int val) = 0;

	// SysEx — 0xF0 ... 0xF7 프레이밍을 포함한 완전한 메시지를 받는다
	virtual void SysEx(const uint8_t* msg, size_t len) = 0;

	// 소리 끄기 (패닉)
	virtual void NotesOff(int ch) = 0;    // CC123 All Notes Off : 노트를 정상 릴리스로 끔
	virtual void SoundsOff(int ch) = 0;   // CC120 All Sound Off : 잔향까지 즉시 차단
	void AllNotesOff() { for (int c = 0; c < 16; c++) NotesOff(c); }
	void AllSoundOff() { for (int c = 0; c < 16; c++) { NotesOff(c); SoundsOff(c); } }

	virtual void SetVolume(int percent) = 0;   // 마스터 볼륨 0~100
};

// ──────────────────────────────────────────────
// winmm 백엔드 — OS에 설치된 MIDI 출력 장치로 메시지를 보낸다.
// 별도 음원이 없으면 보통 "Microsoft GS Wavetable Synth"가 소리를 낸다.
// ──────────────────────────────────────────────
class WinmmOut : public IMidiOut
{
public:
	// deviceIndex < 0 이면 MIDI_MAPPER(시스템 기본 장치). 실패 시 nullptr.
	static std::unique_ptr<WinmmOut> Create(int deviceIndex);
	static void ListDevices();   // 사용 가능한 출력 장치 목록 출력
	// 출력 장치 이름을 장치 번호(0..n-1) 순서대로 돌려준다 (선택 메뉴용)
	static std::vector<std::string> DeviceNames();
	~WinmmOut() override;

	const char* Name() const override { return m_name.c_str(); }
	void NoteOn(int ch, int key, int vel) override;
	void NoteOff(int ch, int key) override;
	void ControlChange(int ch, int num, int val) override;
	void ProgramChange(int ch, int prog) override;
	void PitchBend(int ch, int value) override;
	void ChannelPressure(int ch, int val) override;
	void KeyPressure(int ch, int key, int val) override;
	void SysEx(const uint8_t* msg, size_t len) override;
	void NotesOff(int ch) override;
	void SoundsOff(int ch) override;
	void SetVolume(int percent) override;

private:
	WinmmOut() = default;
	// 짧은 메시지 패킹: [상태바이트] | [데이터1 << 8] | [데이터2 << 16]
	void Short(DWORD msg) { if (m_dev) midiOutShortMsg(m_dev, msg); }

	HMIDIOUT    m_dev = NULL;
	std::string m_name;
	bool        m_volumeSupported = false;   // 장치가 midiOutSetVolume을 지원하는지
};

// ──────────────────────────────────────────────
// FluidSynth 백엔드 — 사운드폰트 렌더링.
//
// fluidsynth.h / 임포트 라이브러리 없이 LoadLibrary + GetProcAddress 로
// 동적 로드한다. → DLL이나 사운드폰트가 없어도 빌드·실행이 가능하고,
// 실패하면 호출자가 winmm으로 폴백할 수 있다.
// ──────────────────────────────────────────────
struct FluidApi;   // 함수 포인터 테이블 (MidiOut.cpp 내부 정의)

class FluidSynthOut : public IMidiOut
{
public:
	// DLL 로드 → 신스 생성 → 사운드폰트 로드 → 오디오 드라이버 시작.
	// 하나라도 실패하면 nullptr 를 돌려준다.
	static std::unique_ptr<FluidSynthOut> Create(const std::string& soundfontPath);
	~FluidSynthOut() override;

	const char* Name() const override { return m_name.c_str(); }
	void NoteOn(int ch, int key, int vel) override;
	void NoteOff(int ch, int key) override;
	void ControlChange(int ch, int num, int val) override;
	void ProgramChange(int ch, int prog) override;
	void PitchBend(int ch, int value) override;
	void ChannelPressure(int ch, int val) override;
	void KeyPressure(int ch, int key, int val) override;
	void SysEx(const uint8_t* msg, size_t len) override;
	void NotesOff(int ch) override;
	void SoundsOff(int ch) override;
	void SetVolume(int percent) override;

private:
	FluidSynthOut();

	HMODULE m_dll = NULL;
	std::unique_ptr<FluidApi> m_api;
	void* m_settings = nullptr;   // fluid_settings_t*     (불투명 포인터)
	void* m_synth    = nullptr;   // fluid_synth_t*
	void* m_driver   = nullptr;   // fluid_audio_driver_t*
	std::string m_name;
};
