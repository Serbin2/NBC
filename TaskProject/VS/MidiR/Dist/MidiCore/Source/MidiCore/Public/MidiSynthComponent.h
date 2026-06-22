#pragma once
#include "CoreMinimal.h"
#include "Templates/Atomic.h"
#include "HAL/CriticalSection.h"
#include "Components/SynthComponent.h"
#include "MidiSynthComponent.generated.h"

class FFluidSynthRenderer;
class UMidiFileAsset;

// ──────────────────────────────────────────────────────────────
// MIDI 신디사이저 컴포넌트
//
// 파서(CMidi)가 만든 이벤트를 시각순으로 평탄화해 두고, UE 오디오 렌더 스레드에서
// FluidSynth(사운드폰트)로 직접 합성해 USynthComponent 로 출력한다.
//  - 콘솔판 MidiPlayer 의 평탄화/디스패치/탐색(chase) 로직을 오디오 스레드 모델로 옮김.
//  - 재생 위치/배속/일시정지/탐색은 게임스레드 → 오디오스레드를 atomic 으로 전달.
//
// 사용: 액터에 이 컴포넌트를 붙이고 MidiFilePath/SoundFontPath 를 지정 → PlayMidi().
// ──────────────────────────────────────────────────────────────
UCLASS(ClassGroup = (Audio), meta = (BlueprintSpawnableComponent))
class MIDICORE_API UMidiSynthComponent : public USynthComponent
{
	GENERATED_BODY()

public:
	UMidiSynthComponent(const FObjectInitializer& ObjectInitializer);
	virtual ~UMidiSynthComponent();

	// 임포트된 MIDI 에셋(지정되면 아래 MidiFilePath 보다 우선)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	TObjectPtr<UMidiFileAsset> MidiAsset = nullptr;

	// 재생할 .mid 경로 (상대경로면 프로젝트 Content 폴더 기준). MidiAsset 이 없을 때만 사용.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	FString MidiFilePath = TEXT("goit.mid");

	// 사운드폰트 .sf2 경로 (상대경로면 프로젝트 Content 폴더 기준)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	FString SoundFontPath = TEXT("GeneralUser-GS.sf2");

	// 마스터 게인 0~1 (FluidSynth 기본 0.2)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Gain = 0.2f;

	// 재생 배속 (0.25 ~ 4.0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi", meta = (ClampMin = "0.25", ClampMax = "4.0"))
	float PlaybackSpeed = 1.0f;

	// 조옮김(반음 단위, -24~24). 드럼 채널(10)은 제외된다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi", meta = (ClampMin = "-24", ClampMax = "24"))
	int32 Transpose = 0;

	// 곡 끝에서 처음부터 반복
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	bool bLoop = false;

	// BeginPlay 에서 자동 재생
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	bool bAutoPlayOnBeginPlay = true;

	// ── 컨트롤(블루프린트) ──────────────────────────────
	UFUNCTION(BlueprintCallable, Category = "Midi") void PlayMidi();        // 처음부터 재생
	UFUNCTION(BlueprintCallable, Category = "Midi") void StopMidi();        // 정지
	UFUNCTION(BlueprintCallable, Category = "Midi") void PauseMidi();       // 일시정지
	UFUNCTION(BlueprintCallable, Category = "Midi") void ResumeMidi();      // 재개
	UFUNCTION(BlueprintCallable, Category = "Midi") void SeekSeconds(float Seconds);
	UFUNCTION(BlueprintCallable, Category = "Midi") void SetPlaybackSpeed(float Speed);
	UFUNCTION(BlueprintCallable, Category = "Midi") void SetGainLevel(float InGain);
	UFUNCTION(BlueprintCallable, Category = "Midi") void SetTranspose(int32 Semitones);   // 반음 -24~24
	UFUNCTION(BlueprintCallable, Category = "Midi") void SetLoop(bool bInLoop);
	UFUNCTION(BlueprintCallable, Category = "Midi") void SetChannelMute(int32 Channel, bool bMute);   // Channel 0~15
	UFUNCTION(BlueprintCallable, Category = "Midi") void ToggleChannelMute(int32 Channel);

	// 디테일 패널 버튼 — 에디터에서 PIE 없이 미리듣기
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Midi|Preview") void PreviewPlay();
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Midi|Preview") void PreviewStop();

	// 현재 재생 위치(초) — 시각화(피아노롤) 동기화용
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Midi") float GetPlayPositionSeconds() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Midi") float GetDurationSeconds() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Midi") bool  IsPlayingMidi() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Midi") bool  IsChannelMuted(int32 Channel) const;

protected:
	// USynthComponent
	virtual bool  Init(int32& SampleRate) override;
	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;

	// UActorComponent
	virtual void BeginPlay() override;

	// UObject — 파괴 시 오디오를 먼저 멈춰 렌더 스레드 경합을 끊는다.
	virtual void BeginDestroy() override;

private:
	// 평탄화된 스케줄 이벤트 (로드 후 불변 → 오디오 스레드에서 락 없이 읽음)
	struct FSchedEvent
	{
		double TimeSeconds = 0.0;
		uint8  Type        = 0;   // 0 = 채널 이벤트, 1 = SysEx
		uint8  Status      = 0;   // 채널 이벤트 상태 상위니블(0x80~0xE0)
		uint8  Ch          = 0;
		uint8  D1          = 0;
		uint8  D2          = 0;
		int32  SysExIndex  = -1;  // Type==1 일 때 SysExBlobs 인덱스
	};

	void BuildSchedule();                                       // 에셋/경로 → 바이트 선택(게임스레드)
	void BuildScheduleFromBytes(const uint8* Data, int32 Size); // CMidi → FSchedEvent 배열
	void SendSchedEvent(const FSchedEvent& Ev);    // 신스로 송출(오디오스레드)
	void DoSeek(double TargetSeconds);             // chase + 커서 점프(오디오스레드)
	int32 TransposeNote(int32 Ch, int32 Note) const;   // 조옮김 적용(음역 밖이면 -1). 드럼 채널 제외

	// 불완전 타입 PIMPL — 원시 포인터로 수동 관리(UHT 생성 생성자/소멸자가 완전 타입을
	// 요구하지 않도록). 생성/해제는 .cpp(완전 타입 가시)에서만 한다.
	FFluidSynthRenderer* Renderer = nullptr;

	// Renderer 는 오디오 렌더 스레드(OnGenerateAudio)와 게임 스레드(Init/소멸자)가 함께
	// 만진다. 객체 자체의 use-after-free 를 막기 위해 생성·사용·해제를 직렬화한다.
	FCriticalSection RendererCS;
	TArray<FSchedEvent>   Schedule;
	TArray<TArray<uint8>> SysExBlobs;
	double DurationSeconds = 0.0;
	int32  SampleRateHz    = 48000;

	// 오디오 스레드 전용 상태
	int32  Cursor          = 0;
	double PlayTimeSeconds = 0.0;
	bool   bPrevPaused     = false;   // 일시정지 진입(엣지) 감지용
	uint32 PrevMuteMask    = 0;       // 음소거 변경(엣지) 감지용
	int32  AudioTranspose  = 0;       // 이번 블록의 조옮김 스냅샷
	uint32 AudioMuteMask   = 0;       // 이번 블록의 음소거 스냅샷
	// (채널, 원래 음높이) → 실제로 울리는 음높이. -1 = 안 울림.
	// 조옮김이 도중에 바뀌어도 NoteOff 가 정확한 음을 끄게 한다.
	int8   NoteMap[16][128];

	// 게임 → 오디오 스레드 제어
	TAtomic<bool>   bPaused{ false };
	TAtomic<bool>   bPlaying{ false };
	TAtomic<float>  SpeedAtomic{ 1.0f };
	TAtomic<float>  GainAtomic{ 0.2f };
	TAtomic<bool>   bGainDirty{ true };
	TAtomic<double> PendingSeek{ -1.0 };       // >=0 이면 탐색 요청
	TAtomic<double> ReportedPosition{ 0.0 };   // GetPlayPositionSeconds 가 읽음
	TAtomic<int32>  TransposeAtomic{ 0 };
	TAtomic<bool>   bLoopAtomic{ false };
	TAtomic<uint32> MuteMask{ 0 };             // 채널당 1비트(1=음소거)

	bool bStarted = false;   // (게임스레드) Start() 호출 여부
};
