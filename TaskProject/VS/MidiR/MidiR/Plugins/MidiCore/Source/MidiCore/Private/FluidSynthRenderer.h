#pragma once
#include "CoreMinimal.h"

// ──────────────────────────────────────────────────────────────
// FluidSynth 블록 렌더러 (언리얼용)
//
// 콘솔판 FluidSynthOut(MidiOut.cpp)을 "오디오 드라이버 없이" 쓰는 버전으로 옮긴 것.
//  - new_fluid_audio_driver 를 만들지 않는다. 대신 fluid_synth_write_float 로
//    UE 오디오 스레드가 요청한 블록만큼만 PCM 을 직접 렌더한다.
//  - fluidsynth.h / import lib 없이 DLL 을 런타임 동적 로드(GetProcAddress)한다.
//    DLL 은 플러그인 Binaries/Win64 에 스테이징된 것을 쓴다.
// 모든 채널 송출 메서드는 UMidiSynthComponent 가 오디오 스레드에서 호출한다.
// (fluid_synth_* 공개 API 는 내부적으로 락이 있어 스레드 안전하다)
// ──────────────────────────────────────────────────────────────

struct FFluidApi;   // 함수 포인터 테이블 (FluidSynthRenderer.cpp 내부 정의)

class FFluidSynthRenderer
{
public:
	FFluidSynthRenderer() = default;
	~FFluidSynthRenderer();

	// DLL 로드 → settings(샘플레이트 지정) → synth 생성 → 사운드폰트 로드.
	// 하나라도 실패하면 false (그 자리까지 정리됨).
	bool Init(int32 SampleRate, const FString& SoundFontPath);
	bool IsValid() const { return Synth != nullptr; }

	// 채널(연주) 이벤트
	void NoteOn(int32 Ch, int32 Key, int32 Vel);
	void NoteOff(int32 Ch, int32 Key);
	void ControlChange(int32 Ch, int32 Num, int32 Val);
	void ProgramChange(int32 Ch, int32 Prog);
	void PitchBend(int32 Ch, int32 Value14);     // 14비트(0~16383), 중앙 8192
	void ChannelPressure(int32 Ch, int32 Val);
	void KeyPressure(int32 Ch, int32 Key, int32 Val);
	void SysEx(const uint8* Data, int32 Len);    // 0xF0...0xF7 프레이밍 포함 완전 메시지

	void AllNotesOff(int32 Ch);
	void AllSoundOff(int32 Ch);
	void AllNotesOffEveryChannel();              // 16채널 일괄
	void AllSoundOffEveryChannel();

	void SetGain(float Gain);                    // 0~1 마스터 게인(기본 0.2 권장)

	// 블록 렌더 — Interleaved 스테레오 버퍼(L,R,L,R...)에 Frames 프레임을 채운다.
	void RenderFloat(float* Interleaved, int32 Frames);

private:
	void Shutdown();

	void* DllFluid   = nullptr;
	void* DllSdl     = nullptr;
	void* DllSndfile = nullptr;
	FFluidApi* Api   = nullptr;
	void* Settings   = nullptr;   // fluid_settings_t*
	void* Synth      = nullptr;   // fluid_synth_t*
};
