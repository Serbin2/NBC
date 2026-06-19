#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MidiPianoRollActor.generated.h"

class USceneComponent;
class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
class UStaticMesh;
class UMaterialInterface;
class UMidiSynthComponent;
class UMidiFileAsset;

// 미디 파일을 파싱해 노트를 3D 막대로 배치하는 피아노롤 액터.
//  - X축 = 시간(막대 위치=시작초, 길이=지속시간), Z축 = 음높이(0~127), 색 = 채널
//  - 노트는 채널별 UInstancedStaticMeshComponent 에 인스턴스로 추가(대량도 가볍게)
//  - 재생 헤드(세로 막대)가 Play 중 시간축을 따라 이동
// 레벨에 끌어다 놓으면 OnConstruction 에서 즉시 생성된다.
UCLASS()
class MIDICORE_API AMidiPianoRollActor : public AActor
{
	GENERATED_BODY()

public:
	AMidiPianoRollActor();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// 임포트된 MIDI 에셋(지정되면 아래 MidiFilePath 보다 우선)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	TObjectPtr<UMidiFileAsset> MidiAsset = nullptr;

	// 재생할 .mid 경로 (상대경로면 프로젝트 Content 폴더 기준). MidiAsset 이 없을 때만 사용.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	FString MidiFilePath = TEXT("goit.mid");

	// 시간 1초당 월드 길이(uu) — 가로(시간) 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float TimeScale = 100.f;

	// 반음 1당 월드 높이(uu) — 세로(음높이) 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float PitchScale = 15.f;

	// 노트 막대 두께(Z, uu)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float NoteHeight = 10.f;

	// 노트 막대 깊이(Y, uu)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float NoteDepth = 8.f;

	// Play 중 재생 헤드를 자동으로 이동시킨다
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	bool bAnimatePlayhead = true;

	// 재생 헤드 배속 (아래 동기화가 꺼져 있거나 신스 컴포넌트가 없을 때만 사용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float PlaybackSpeed = 1.f;

	// 같은 액터에 붙은 Midi Synth Component 의 재생 위치에 재생바를 맞춘다(오디오·시각 드리프트 제거).
	// 컴포넌트가 없으면 위 PlaybackSpeed 로 자체 진행(폴백)한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	bool bSyncToSynth = true;

	// 재생바 시간 미세 보정(초). 오디오보다 재생바를 앞당기려면 +, 늦추려면 -.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Midi")
	float PlaybackOffsetSeconds = 0.f;

	// 디테일 패널 버튼 / 블루프린트에서 다시 그리기
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Midi")
	void Rebuild();

private:
	UPROPERTY() USceneComponent* SceneRoot = nullptr;
	UPROPERTY() TArray<UInstancedStaticMeshComponent*> ChannelISMs;  // 채널별(16개)
	UPROPERTY() UStaticMeshComponent* Playhead = nullptr;
	UPROPERTY() UStaticMesh* CubeMesh = nullptr;
	UPROPERTY() UMaterialInterface* BarMaterial = nullptr;
	UPROPERTY(Transient) UMidiSynthComponent* SynthComp = nullptr;   // 동기화 대상(같은 액터, 캐시)

	float TotalDuration = 0.f;   // 곡 길이(초)
	float PlayTime = 0.f;        // 재생 헤드 위치(초)

	void BuildBars();                  // 노트 → 인스턴스 막대 생성
	void UpdatePlayheadTransform();    // 재생 헤드 위치 갱신
};
