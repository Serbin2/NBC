#include "MidiPianoRollActor.h"
#include "MidiBlueprintLibrary.h"
#include "MidiSynthComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AMidiPianoRollActor::AMidiPianoRollActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 엔진 기본 큐브(100uu, 중심 피벗)와 색을 바꿀 수 있는 기본 머티리얼
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeFinder.Succeeded()) CubeMesh = CubeFinder.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFinder(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (MatFinder.Succeeded()) BarMaterial = MatFinder.Object;

	// 채널별 인스턴스 메시 컴포넌트 16개
	ChannelISMs.SetNum(16);
	for (int32 ch = 0; ch < 16; ch++)
	{
		UInstancedStaticMeshComponent* Ism =
			CreateDefaultSubobject<UInstancedStaticMeshComponent>(*FString::Printf(TEXT("ChannelISM_%d"), ch));
		Ism->SetupAttachment(SceneRoot);
		if (CubeMesh) Ism->SetStaticMesh(CubeMesh);
		Ism->SetMobility(EComponentMobility::Movable);
		Ism->SetCastShadow(false);
		ChannelISMs[ch] = Ism;
	}

	// 재생 헤드
	Playhead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Playhead"));
	Playhead->SetupAttachment(SceneRoot);
	if (CubeMesh) Playhead->SetStaticMesh(CubeMesh);
	Playhead->SetMobility(EComponentMobility::Movable);
	Playhead->SetCastShadow(false);
}

void AMidiPianoRollActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	PlayTime = 0.f;
	BuildBars();   // 에디터에 배치/수정하면 즉시 재생성
}

void AMidiPianoRollActor::BeginPlay()
{
	Super::BeginPlay();
	PlayTime = 0.f;
	BuildBars();
}

void AMidiPianoRollActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bAnimatePlayhead || TotalDuration <= 0.f)
		return;

	// 1순위: 같은 액터의 Midi Synth Component 오디오 시계에 종속(드리프트 제거).
	if (bSyncToSynth)
	{
		if (!SynthComp)
			SynthComp = FindComponentByClass<UMidiSynthComponent>();   // 캐시(같은 액터)
		if (SynthComp)
		{
			// 오디오가 보고한 재생 위치 + 수동 미세보정. 오디오가 0/정지면 재생바도 그대로 따라감.
			PlayTime = FMath::Clamp(SynthComp->GetPlayPositionSeconds() + PlaybackOffsetSeconds,
			                        0.f, TotalDuration);
			UpdatePlayheadTransform();
			return;
		}
	}

	// 폴백: 신스가 없거나 동기화를 끈 경우 — 자체 시계로 진행(루프).
	PlayTime += DeltaSeconds * PlaybackSpeed;
	if (PlayTime > TotalDuration) PlayTime = 0.f;
	UpdatePlayheadTransform();
}

void AMidiPianoRollActor::Rebuild()
{
	PlayTime = 0.f;
	BuildBars();
}

void AMidiPianoRollActor::BuildBars()
{
	TotalDuration = 0.f;
	for (UInstancedStaticMeshComponent* Ism : ChannelISMs)
		if (Ism) Ism->ClearInstances();

	if (!MidiAsset && MidiFilePath.IsEmpty()) return;

	// 파싱 → 노트 막대 데이터 (에셋이 있으면 우선)
	TArray<FMidiNoteSegment> Notes;
	const bool bOk = MidiAsset
		? UMidiBlueprintLibrary::LoadMidiNotesFromAsset(MidiAsset, Notes)
		: UMidiBlueprintLibrary::LoadMidiNotes(MidiFilePath, Notes);
	if (!bOk)
		return;

	// 채널별 색 머티리얼(동적 인스턴스). BasicShapeMaterial 의 "Color" 파라미터를 바꾼다.
	for (int32 ch = 0; ch < 16; ch++)
	{
		UInstancedStaticMeshComponent* Ism = ChannelISMs[ch];
		if (!Ism || !BarMaterial) continue;

		UMaterialInstanceDynamic* Mid = UMaterialInstanceDynamic::Create(BarMaterial, this);
		FLinearColor Color = (ch == 9)
			? FLinearColor(0.5f, 0.5f, 0.5f)                       // 채널 10(드럼)은 회색
			: FLinearColor::MakeFromHSV8((uint8)(ch * 16), 220, 255);
		Mid->SetVectorParameterValue(TEXT("Color"), Color);
		Ism->SetMaterial(0, Mid);
	}

	// 노트 → 인스턴스
	const float MinDur = 0.03f;   // 너무 짧은 음도 보이게 최소 길이 보장
	for (const FMidiNoteSegment& N : Notes)
	{
		const float Start = N.StartSeconds;
		const float End   = FMath::Max(N.EndSeconds, Start + MinDur);
		const float Dur   = End - Start;
		TotalDuration = FMath::Max(TotalDuration, End);

		// 큐브(100uu, 중심 피벗) → 막대 중심에 배치하고 길이만큼 X 스케일
		const FVector Loc((Start + End) * 0.5f * TimeScale, 0.f, N.Note * PitchScale);
		const FVector Scale(Dur * TimeScale / 100.f, NoteDepth / 100.f, NoteHeight / 100.f);

		const int32 ch = FMath::Clamp((int32)N.Channel, 0, 15);
		ChannelISMs[ch]->AddInstance(FTransform(FRotator::ZeroRotator, Loc, Scale));
	}

	UpdatePlayheadTransform();
}

void AMidiPianoRollActor::UpdatePlayheadTransform()
{
	if (!Playhead) return;

	const float FullHeight = 128.f * PitchScale;                 // 음역 전체 높이
	const FVector Loc(PlayTime * TimeScale, 0.f, FullHeight * 0.5f);
	const FVector Scale(6.f / 100.f, (NoteDepth * 1.5f) / 100.f, FullHeight / 100.f);
	Playhead->SetRelativeTransform(FTransform(FRotator::ZeroRotator, Loc, Scale));
}
