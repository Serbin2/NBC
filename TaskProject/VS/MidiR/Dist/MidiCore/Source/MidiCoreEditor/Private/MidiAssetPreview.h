#pragma once
#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"

class UMidiFileAsset;
class UMidiSynthComponent;
class AActor;

// 에디터 월드에 임시(transient) 액터 + 신스 컴포넌트를 띄워 .mid 를 PIE 없이 미리듣기한다.
// (한 번에 하나만 재생: Play 가 이전 미리듣기를 먼저 정리한다)
class FMidiAssetPreview
{
public:
	static void Play(UMidiFileAsset* Asset);
	static void Stop();

private:
	static TWeakObjectPtr<AActor>              PreviewActor;
	static TWeakObjectPtr<UMidiSynthComponent> PreviewComp;
};
