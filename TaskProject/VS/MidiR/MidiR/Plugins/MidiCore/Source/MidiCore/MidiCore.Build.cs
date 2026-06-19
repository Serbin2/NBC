using UnrealBuildTool;

public class MidiCore : ModuleRules
{
	public MidiCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 파서가 std::vector / std::string 을 쓰므로 예외를 허용한다(할당 실패 등 대비).
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",        // FFileHelper, TArray 등
			"CoreUObject", // UObject / 리플렉션
			"Engine",      // UBlueprintFunctionLibrary
			"AudioMixer",  // USynthComponent (오디오 합성 컴포넌트)
			"Projects"     // IPluginManager (플러그인 Binaries 경로 → DLL 동적 로드)
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"FluidSynth"   // 서드파티(External): libfluidsynth-3/SDL3/sndfile DLL 스테이징
		});
	}
}
