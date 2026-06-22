#include "MidiSynthComponent.h"
#include "FluidSynthRenderer.h"
#include "MidiFileAsset.h"
#include "MidiBlueprintLibrary.h"  // ResolveMidiResourcePath (프로젝트 Content → 플러그인 동봉본)
#include "Midi.h"                 // 내부 파서(CMidi 등) — std 기반, 이 .cpp 안에서만 사용
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeLock.h"       // FScopeLock (Renderer 접근 직렬화)
#include "Engine/World.h"         // UWorld::IsGameWorld (에디터 미리듣기 분기)
#include <cstring>                // strcmp

UMidiSynthComponent::UMidiSynthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = false;   // 재생 시점은 PlayMidi()/BeginPlay 로 직접 제어
}

UMidiSynthComponent::~UMidiSynthComponent()
{
	// 오디오 렌더 스레드가 OnGenerateAudio 안에서 Renderer 를 쓰는 중일 수 있으므로
	// 락을 잡고 해제한다(렌더 콜백과 상호배제). BeginDestroy 에서 이미 정지를 시도한다.
	FScopeLock Lock(&RendererCS);
	delete Renderer;
	Renderer = nullptr;
}

// ──────────────────────────────────────────────
// USynthComponent — 준비 / 오디오 생성
// ──────────────────────────────────────────────
bool UMidiSynthComponent::Init(int32& SampleRate)
{
	NumChannels  = 2;                 // 스테레오 인터리브
	SampleRateHz = SampleRate;        // 엔진이 알려주는 디바이스 샘플레이트

	// 오디오 스레드가 시작되기 전(게임스레드)이므로 여기서 상태를 초기화한다.
	Cursor          = 0;
	PlayTimeSeconds = 0.0;
	bPrevPaused     = false;
	PrevMuteMask    = 0;
	FMemory::Memset(NoteMap, 0xFF, sizeof(NoteMap));   // 0xFF = -1 (안 울림)
	ReportedPosition.Store(0.0);
	PendingSeek.Store(-1.0);
	SpeedAtomic.Store(FMath::Clamp(PlaybackSpeed, 0.25f, 4.0f));
	GainAtomic.Store(FMath::Clamp(Gain, 0.0f, 1.0f));
	bGainDirty.Store(true);
	TransposeAtomic.Store(FMath::Clamp(Transpose, -24, 24));
	bLoopAtomic.Store(bLoop);
	MuteMask.Store(0);

	{
		// 이전 인스턴스 정리/생성은 렌더 콜백과 상호배제(포인터 교체 경합 방지).
		FScopeLock Lock(&RendererCS);
		delete Renderer;                      // Start() 재호출 시 이전 인스턴스 정리
		Renderer = new FFluidSynthRenderer();
	}
	const FString SfPath = UMidiBlueprintLibrary::ResolveMidiResourcePath(SoundFontPath, TEXT("SoundFonts"));
	if (!Renderer->Init(SampleRateHz, SfPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("[MidiSynth] FluidSynth 준비 실패 → 무음으로 진행"));
	}
	else
	{
		Renderer->SetGain(GainAtomic.Load());
	}

	BuildSchedule();
	return true;   // 실패해도 컴포넌트는 살려 두고(무음) 크래시를 피한다
}

int32 UMidiSynthComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
	// 이 콜백이 도는 동안 게임 스레드가 Renderer 를 delete 하지 못하도록 잡아 둔다.
	// (정상 재생 중엔 게임 스레드가 락을 잡지 않으므로 항상 즉시 획득 → 글리치 없음)
	FScopeLock Lock(&RendererCS);

	if (!Renderer || !Renderer->IsValid())
	{
		FMemory::Memzero(OutAudio, NumSamples * sizeof(float));
		return NumSamples;
	}

	const int32 Frames = NumSamples / 2;   // 스테레오

	// 게임스레드에서 온 게인 변경 반영
	if (bGainDirty.Exchange(false))
	{
		Renderer->SetGain(GainAtomic.Load());
	}

	// 탐색 요청 반영(chase)
	const double Seek = PendingSeek.Exchange(-1.0);
	if (Seek >= 0.0)
	{
		DoSeek(Seek);
	}

	// 이번 블록의 조옮김/음소거 스냅샷(이벤트 송출이 참조)
	AudioTranspose = TransposeAtomic.Load();
	const uint32 NewMuteMask = MuteMask.Load();

	// 새로 음소거된 채널은 즉시 울리던 음을 끈다(엣지 처리)
	const uint32 NewlyMuted = NewMuteMask & ~PrevMuteMask;
	if (NewlyMuted)
	{
		for (int32 Ch = 0; Ch < 16; ++Ch)
		{
			if (NewlyMuted & (1u << Ch))
			{
				Renderer->AllNotesOff(Ch);
				FMemory::Memset(NoteMap[Ch], 0xFF, sizeof(NoteMap[Ch]));
			}
		}
	}
	PrevMuteMask  = NewMuteMask;
	AudioMuteMask = NewMuteMask;

	// 일시정지 진입 시 한 번만 울리던 음 정리
	const bool bNowPaused = bPaused.Load();
	if (bNowPaused && !bPrevPaused)
	{
		Renderer->AllNotesOffEveryChannel();
		FMemory::Memset(NoteMap, 0xFF, sizeof(NoteMap));
	}
	bPrevPaused = bNowPaused;

	if (bPlaying.Load() && !bNowPaused)
	{
		const double Speed = (double)SpeedAtomic.Load();
		PlayTimeSeconds += (double)Frames / (double)SampleRateHz * Speed;

		while (Cursor < Schedule.Num() && Schedule[Cursor].TimeSeconds <= PlayTimeSeconds)
		{
			SendSchedEvent(Schedule[Cursor]);
			++Cursor;
		}

		if (Cursor >= Schedule.Num())
		{
			if (bLoopAtomic.Load())
			{
				// 반복: 울리던 음 정리 후 처음으로(다음 블록부터 0초 이벤트 재송출)
				Renderer->AllSoundOffEveryChannel();
				FMemory::Memset(NoteMap, 0xFF, sizeof(NoteMap));
				Cursor          = 0;
				PlayTimeSeconds = 0.0;
			}
			else
			{
				bPlaying.Store(false);   // 끝 도달 — 정지(잔향/릴리스는 계속 렌더)
			}
		}
	}

	ReportedPosition.Store(PlayTimeSeconds);

	Renderer->RenderFloat(OutAudio, Frames);
	return NumSamples;
}

// ──────────────────────────────────────────────
// UActorComponent
// ──────────────────────────────────────────────
void UMidiSynthComponent::BeginPlay()
{
	Super::BeginPlay();
	if (bAutoPlayOnBeginPlay)
	{
		PlayMidi();
	}
}

void UMidiSynthComponent::BeginDestroy()
{
	// 액터/컴포넌트가 파괴되기 시작하면 먼저 합성을 멈춰 오디오 렌더 콜백을 끊는다.
	// (소멸자의 Renderer 해제가 렌더 스레드와 겹치지 않도록 경합 창을 최소화)
	bPlaying.Store(false);
	if (bStarted)
	{
		Stop();             // USynthComponent::Stop — 오디오 소스 정지
		bStarted = false;
	}
	Super::BeginDestroy();
}

// ──────────────────────────────────────────────
// 스케줄 구성(게임스레드) / 송출(오디오스레드)
// ──────────────────────────────────────────────
void UMidiSynthComponent::BuildSchedule()
{
	// 에셋이 지정되면 그 바이트를, 아니면 파일 경로에서 읽은 바이트를 쓴다.
	if (MidiAsset && MidiAsset->RawData.Num() > 0)
	{
		BuildScheduleFromBytes(MidiAsset->RawData.GetData(), MidiAsset->RawData.Num());
		return;
	}

	const FString Full = UMidiBlueprintLibrary::ResolveMidiResourcePath(MidiFilePath, TEXT("Midi"));
	TArray<uint8> Bytes;
	if (!FFileHelper::LoadFileToArray(Bytes, *Full))
	{
		UE_LOG(LogTemp, Error, TEXT("[MidiSynth] MIDI 로드 실패: %s"), *Full);
		Schedule.Reset();
		SysExBlobs.Reset();
		DurationSeconds = 0.0;
		return;
	}
	BuildScheduleFromBytes(Bytes.GetData(), Bytes.Num());
}

void UMidiSynthComponent::BuildScheduleFromBytes(const uint8* Data, int32 Size)
{
	Schedule.Reset();
	SysExBlobs.Reset();
	DurationSeconds = 0.0;

	if (!Data || Size <= 0)
		return;

	CMidi Midi(Data, (size_t)Size);
	if (strcmp(Midi.GetHeader().GetName(), "MThd") != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[MidiSynth] MIDI 형식 오류"));
		return;
	}

	// 전 트랙의 채널/SysEx 이벤트를 한 줄로 모은다(콘솔 MidiPlayer::CollectEvents 이식).
	for (const CTrack& Tr : Midi.GetTracks())
	{
		for (const CEventRecord& Rec : Tr.GetEvents())
		{
			if (const CMidiEvent* E = Rec.AsMidi())
			{
				FSchedEvent S;
				S.TimeSeconds = Rec.absTimeMs / 1000.0;
				S.Type   = 0;
				S.Status = (uint8)E->GetStatus();
				S.Ch     = E->GetChannel();
				S.D1     = E->GetData1();
				S.D2     = E->GetData2();
				Schedule.Add(S);
			}
			else if (const CSysExEvent* Sx = Rec.AsSysEx())
			{
				const std::vector<uint8_t>& D = Sx->GetData();
				if (D.empty())
				{
					continue;
				}

				TArray<uint8> Blob;
				if (Sx->GetLeadByte() == 0xF0)
				{
					// SMF 에는 선두 0xF0 가 빠져 저장되므로 다시 붙인다(데이터 끝에 0xF7 포함).
					Blob.Add(0xF0);
					Blob.Append(D.data(), (int32)D.size());
				}
				else
				{
					// 0xF7 이스케이프: 원본 그대로(프레이밍 없는 패킷은 렌더러가 무시).
					Blob.Append(D.data(), (int32)D.size());
				}

				FSchedEvent S;
				S.TimeSeconds = Rec.absTimeMs / 1000.0;
				S.Type        = 1;
				S.SysExIndex  = SysExBlobs.Add(MoveTemp(Blob));
				Schedule.Add(S);
			}
		}
	}

	// 같은 시각이면 파일 순서(예: ProgramChange → NoteOn)를 유지하도록 안정 정렬.
	Schedule.StableSort([](const FSchedEvent& A, const FSchedEvent& B)
	{
		return A.TimeSeconds < B.TimeSeconds;
	});

	DurationSeconds = Schedule.Num() ? Schedule.Last().TimeSeconds : 0.0;
	UE_LOG(LogTemp, Log, TEXT("[MidiSynth] 스케줄 %d 이벤트, %.1f초"),
		Schedule.Num(), DurationSeconds);
}

void UMidiSynthComponent::SendSchedEvent(const FSchedEvent& Ev)
{
	if (Ev.Type == 1)
	{
		if (SysExBlobs.IsValidIndex(Ev.SysExIndex))
		{
			const TArray<uint8>& Blob = SysExBlobs[Ev.SysExIndex];
			Renderer->SysEx(Blob.GetData(), Blob.Num());
		}
		return;
	}

	const int32 Ch = Ev.Ch, D1 = Ev.D1, D2 = Ev.D2;
	switch (Ev.Status)
	{
	case 0x90:   // NoteOn (velocity 0 은 NoteOff 취급)
		if (D2 > 0)
		{
			if (AudioMuteMask & (1u << Ch)) return;       // 음소거 채널: 새 음을 막는다
			const int32 N = TransposeNote(Ch, D1);
			if (N < 0) return;                            // 조옮김으로 음역 밖 → 이 음만 생략
			NoteMap[Ch][D1] = (int8)N;                    // 끌 때를 위해 실제 음높이 기록
			Renderer->NoteOn(Ch, N, D2);
		}
		else
		{
			const int32 N = NoteMap[Ch][D1];
			NoteMap[Ch][D1] = -1;
			Renderer->NoteOff(Ch, N >= 0 ? N : D1);
		}
		break;
	case 0x80:   // NoteOff
	{
		const int32 N = NoteMap[Ch][D1];
		NoteMap[Ch][D1] = -1;
		Renderer->NoteOff(Ch, N >= 0 ? N : D1);
		break;
	}
	case 0xB0: Renderer->ControlChange(Ch, D1, D2);  break;
	case 0xC0: Renderer->ProgramChange(Ch, D1);      break;   // 드럼 채널도 전달(킷 변경 허용)
	case 0xD0: Renderer->ChannelPressure(Ch, D1);    break;
	case 0xA0:   // PolyphonicKeyPressure — 실제 울리는 음높이로 매핑
	{
		const int32 N = NoteMap[Ch][D1];
		Renderer->KeyPressure(Ch, N >= 0 ? N : D1, D2);
		break;
	}
	case 0xE0: Renderer->PitchBend(Ch, D1 | (D2 << 7)); break;
	default: break;
	}
}

// 조옮김 적용. 드럼 채널(9)은 음높이가 타악기 종류를 뜻하므로 제외한다.
int32 UMidiSynthComponent::TransposeNote(int32 Ch, int32 Note) const
{
	if (Ch == 9 || AudioTranspose == 0) return Note;
	const int32 N = Note + AudioTranspose;
	return (N < 0 || N > 127) ? -1 : N;   // 음역 밖이면 그 음만 연주 생략
}

// 콘솔 MidiPlayer::SeekTo 이식: 목표 이전 이벤트의 채널별 마지막 컨트롤러 상태를
// 모아 재전송(chase)한 뒤 커서/시간을 점프시킨다.
void UMidiSynthComponent::DoSeek(double TargetSeconds)
{
	TargetSeconds = FMath::Clamp(TargetSeconds, 0.0, DurationSeconds);

	Renderer->AllSoundOffEveryChannel();   // 울리던 음 즉시 차단
	FMemory::Memset(NoteMap, 0xFF, sizeof(NoteMap));

	int16 CcVal[16][128];
	int16 ProgVal[16];
	int32 BendVal[16];
	int16 PressVal[16];
	FMemory::Memset(CcVal,    0xFF, sizeof(CcVal));     // 0xFFFF = -1 (등장 안 함)
	FMemory::Memset(ProgVal,  0xFF, sizeof(ProgVal));
	FMemory::Memset(BendVal,  0xFF, sizeof(BendVal));
	FMemory::Memset(PressVal, 0xFF, sizeof(PressVal));

	int32 Idx = 0;
	for (; Idx < Schedule.Num() && Schedule[Idx].TimeSeconds < TargetSeconds; ++Idx)
	{
		const FSchedEvent& S = Schedule[Idx];
		if (S.Type != 0) continue;   // SysEx 는 chase 하지 않음
		switch (S.Status)
		{
		case 0xB0: CcVal[S.Ch][S.D1] = (int16)S.D2;                 break;
		case 0xC0: ProgVal[S.Ch]     = (int16)S.D1;                 break;
		case 0xE0: BendVal[S.Ch]     = (int32)(S.D1 | (S.D2 << 7)); break;
		case 0xD0: PressVal[S.Ch]    = (int16)S.D1;                 break;
		default: break;
		}
	}

	for (int32 Ch = 0; Ch < 16; ++Ch)
	{
		for (int32 N = 0; N < 128; ++N)
			if (CcVal[Ch][N] >= 0) Renderer->ControlChange(Ch, N, CcVal[Ch][N]);
		if (ProgVal[Ch]  >= 0) Renderer->ProgramChange(Ch, ProgVal[Ch]);
		if (BendVal[Ch]  >= 0) Renderer->PitchBend(Ch, BendVal[Ch]);
		if (PressVal[Ch] >= 0) Renderer->ChannelPressure(Ch, PressVal[Ch]);
	}

	Cursor          = Idx;
	PlayTimeSeconds = TargetSeconds;
}

// ──────────────────────────────────────────────
// 컨트롤(블루프린트)
// ──────────────────────────────────────────────
void UMidiSynthComponent::PlayMidi()
{
	bPaused.Store(false);
	bPlaying.Store(true);
	if (!bStarted)
	{
		// 에디터(비게임) 월드에서 미리듣기할 때:
		// PIE가 아니면 오디오 디바이스가 'game ticking'이 아니라서, UI 사운드로
		// 표시된 보이스만 렌더된다(엔진 AudioDevice.cpp: bGameTicking || bIsUISound).
		// 따라서 미리듣기는 UI/프리뷰 2D 사운드로 만들어 리스너 위치·PIE 여부와
		// 무관하게 들리도록 한다. (Start() 가 이 플래그들을 내부 오디오 컴포넌트로 복사)
		if (UWorld* W = GetWorld())
		{
			if (!W->IsGameWorld())
			{
				bIsUISound           = true;
				bIsPreviewSound      = true;
				bAllowSpatialization = false;
			}
		}
		Start();          // → Init() → 오디오 생성 시작
		bStarted = true;
	}
	else
	{
		PendingSeek.Store(0.0);   // 이미 재생 중이면 처음으로 되감기
	}
}

void UMidiSynthComponent::StopMidi()
{
	bPlaying.Store(false);
	if (bStarted)
	{
		Stop();
		bStarted = false;
	}
}

void UMidiSynthComponent::PauseMidi()  { bPaused.Store(true); }
void UMidiSynthComponent::ResumeMidi() { bPaused.Store(false); }

void UMidiSynthComponent::SeekSeconds(float Seconds)
{
	PendingSeek.Store((double)FMath::Max(0.0f, Seconds));
}

void UMidiSynthComponent::SetPlaybackSpeed(float Speed)
{
	PlaybackSpeed = FMath::Clamp(Speed, 0.25f, 4.0f);
	SpeedAtomic.Store(PlaybackSpeed);
}

void UMidiSynthComponent::SetGainLevel(float InGain)
{
	Gain = FMath::Clamp(InGain, 0.0f, 1.0f);
	GainAtomic.Store(Gain);
	bGainDirty.Store(true);
}

void UMidiSynthComponent::SetTranspose(int32 Semitones)
{
	Transpose = FMath::Clamp(Semitones, -24, 24);
	TransposeAtomic.Store(Transpose);
}

void UMidiSynthComponent::SetLoop(bool bInLoop)
{
	bLoop = bInLoop;
	bLoopAtomic.Store(bInLoop);
}

void UMidiSynthComponent::SetChannelMute(int32 Channel, bool bMute)
{
	if (Channel < 0 || Channel > 15) return;
	const uint32 Bit = 1u << Channel;
	uint32 Mask = MuteMask.Load();
	Mask = bMute ? (Mask | Bit) : (Mask & ~Bit);
	MuteMask.Store(Mask);
}

void UMidiSynthComponent::ToggleChannelMute(int32 Channel)
{
	if (Channel < 0 || Channel > 15) return;
	SetChannelMute(Channel, !IsChannelMuted(Channel));
}

// 디테일 패널 버튼 — 배치된 컴포넌트를 에디터 월드 오디오로 PIE 없이 재생/정지
void UMidiSynthComponent::PreviewPlay() { PlayMidi(); }
void UMidiSynthComponent::PreviewStop() { StopMidi(); }

float UMidiSynthComponent::GetPlayPositionSeconds() const { return (float)ReportedPosition.Load(); }
float UMidiSynthComponent::GetDurationSeconds() const     { return (float)DurationSeconds; }
bool  UMidiSynthComponent::IsPlayingMidi() const          { return bPlaying.Load(); }

bool UMidiSynthComponent::IsChannelMuted(int32 Channel) const
{
	if (Channel < 0 || Channel > 15) return false;
	return (MuteMask.Load() & (1u << Channel)) != 0;
}
