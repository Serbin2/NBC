using UnrealBuildTool;

// MidiCore 의 에디터 전용 모듈.
//  - .mid 임포트 팩토리(UMidiFileFactory)
//  - Content Browser 에셋 액션(Play/Stop 미리듣기)
public class MidiCoreEditor : ModuleRules
{
	public MidiCoreEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"MidiCore"      // UMidiFileAsset / UMidiSynthComponent
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd",       // UFactory
			"AssetTools",     // IAssetTools / FAssetTypeActions_Base
			"ToolMenus",      // FToolMenuSection (에셋 우클릭 메뉴)
			"Slate",
			"SlateCore"
		});
	}
}
