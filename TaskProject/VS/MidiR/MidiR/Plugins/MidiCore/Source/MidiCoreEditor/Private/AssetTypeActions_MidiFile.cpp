#include "AssetTypeActions_MidiFile.h"
#include "MidiFileAsset.h"
#include "MidiAssetPreview.h"
#include "ToolMenus.h"
#include "Textures/SlateIcon.h"

#define LOCTEXT_NAMESPACE "MidiCoreEditor"

FText   FAssetTypeActions_MidiFile::GetName() const        { return LOCTEXT("MidiFileAssetName", "MIDI File"); }
FColor  FAssetTypeActions_MidiFile::GetTypeColor() const   { return FColor(120, 200, 120); }
UClass* FAssetTypeActions_MidiFile::GetSupportedClass() const { return UMidiFileAsset::StaticClass(); }
uint32  FAssetTypeActions_MidiFile::GetCategories()        { return EAssetTypeCategories::Sounds; }

void FAssetTypeActions_MidiFile::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	// 선택된 첫 MIDI 에셋 하나를 미리듣기 대상으로 삼는다.
	TWeakObjectPtr<UMidiFileAsset> First;
	for (UObject* Obj : InObjects)
	{
		if (UMidiFileAsset* A = Cast<UMidiFileAsset>(Obj))
		{
			First = A;
			break;
		}
	}

	Section.AddMenuEntry(
		"MidiFile_Play",
		LOCTEXT("MidiFile_Play", "Play"),
		LOCTEXT("MidiFile_PlayTip", "에디터에서 이 MIDI를 미리듣기(재생)"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([First]()
		{
			if (First.IsValid())
			{
				FMidiAssetPreview::Play(First.Get());
			}
		}))
	);

	Section.AddMenuEntry(
		"MidiFile_Stop",
		LOCTEXT("MidiFile_Stop", "Stop"),
		LOCTEXT("MidiFile_StopTip", "미리듣기 정지"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FMidiAssetPreview::Stop();
		}))
	);
}

#undef LOCTEXT_NAMESPACE
