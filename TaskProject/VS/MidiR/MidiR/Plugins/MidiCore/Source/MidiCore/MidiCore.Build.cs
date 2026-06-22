using System.IO;
using UnrealBuildTool;

public class MidiCore : ModuleRules
{
	public MidiCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 파서가 std::vector / std::string 을 쓰므로 예외를 허용한다(할당 실패 등 대비).
		bEnableExceptions = true;

		// 플러그인 동봉 리소스(기본 사운드폰트 + 예제 미디)를 쿠킹/패키지 빌드에 loose 파일로
		// 포함한다. FluidSynth sfload·파서는 디스크 파일을 직접 읽으므로 .uasset 쿠킹 대상이
		// 아니며, 런타임에 IPluginManager BaseDir 기준으로 찾는다(ResolveMidiResourcePath).
		string PluginContent = Path.Combine(PluginDirectory, "Content");
		RuntimeDependencies.Add(Path.Combine(PluginContent, "SoundFonts", "GeneralUser-GS.sf2"), StagedFileType.NonUFS);
		foreach (string Mid in new string[] { "goit.mid", "rocky_1.mid", "take5.mid" })
		{
			RuntimeDependencies.Add(Path.Combine(PluginContent, "Midi", Mid), StagedFileType.NonUFS);
		}

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
