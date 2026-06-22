#include "MidiAssetPreview.h"
#include "MidiFileAsset.h"
#include "MidiSynthComponent.h"
#include "Editor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

TWeakObjectPtr<AActor>              FMidiAssetPreview::PreviewActor;
TWeakObjectPtr<UMidiSynthComponent> FMidiAssetPreview::PreviewComp;

void FMidiAssetPreview::Play(UMidiFileAsset* Asset)
{
	Stop();   // 이전 미리듣기 정리
	if (!Asset || !GEditor)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	// 아웃라이너에 안 보이는 임시 액터를 에디터 월드에 띄운다.
	FActorSpawnParameters Params;
	Params.ObjectFlags = RF_Transient;
	Params.bHideFromSceneOutliner = true;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* Actor = World->SpawnActor<AActor>(AActor::StaticClass(), FTransform::Identity, Params);
	if (!Actor)
	{
		return;
	}

	// 신스 컴포넌트를 루트로 붙이고 재생 시작(에디터 월드 오디오로 출력).
	UMidiSynthComponent* Comp = NewObject<UMidiSynthComponent>(Actor, TEXT("PreviewSynth"));
	Comp->MidiAsset = Asset;
	Comp->bAutoPlayOnBeginPlay = false;
	Actor->SetRootComponent(Comp);
	Comp->RegisterComponent();
	Comp->PlayMidi();

	PreviewActor = Actor;
	PreviewComp  = Comp;
}

void FMidiAssetPreview::Stop()
{
	if (PreviewComp.IsValid())
	{
		PreviewComp->StopMidi();
	}
	if (PreviewActor.IsValid())
	{
		PreviewActor->Destroy();
	}
	PreviewComp.Reset();
	PreviewActor.Reset();
}
