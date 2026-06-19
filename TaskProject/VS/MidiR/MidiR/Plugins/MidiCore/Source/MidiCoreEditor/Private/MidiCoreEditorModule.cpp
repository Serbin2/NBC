#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetTypeActions_MidiFile.h"

// MidiCore 에디터 모듈 — .mid 에셋 액션을 AssetTools 에 등록한다.
class FMidiCoreEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		Action = MakeShared<FAssetTypeActions_MidiFile>();
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}

	virtual void ShutdownModule() override
	{
		if (Action.IsValid() && FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
		Action.Reset();
	}

private:
	TSharedPtr<FAssetTypeActions_MidiFile> Action;
};

IMPLEMENT_MODULE(FMidiCoreEditorModule, MidiCoreEditor)
