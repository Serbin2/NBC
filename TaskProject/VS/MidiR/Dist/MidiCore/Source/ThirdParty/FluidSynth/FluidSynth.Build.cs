using System.IO;
using UnrealBuildTool;

// FluidSynth 서드파티(External) 모듈.
//  - 우리는 fluidsynth.h / import lib 없이 런타임에 GetProcAddress 로 동적 로드하므로
//    헤더/.lib 는 필요 없다. 이 모듈의 역할은 동봉 DLL 3종을 빌드 산출물 폴더로
//    복사(RuntimeDependencies)해 두는 것뿐이다.
//  - 드라이버를 안 쓰더라도 libfluidsynth-3.dll 의 임포트 테이블에 SDL3/sndfile 이
//    걸려 있을 수 있어 3개 모두 스테이징한다.
public class FluidSynth : ModuleRules
{
	public FluidSynth(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string BinDir = Path.Combine(ModuleDirectory, "bin", "Win64");
			foreach (string Dll in new string[] { "libfluidsynth-3.dll", "SDL3.dll", "sndfile.dll" })
			{
				string Src = Path.Combine(BinDir, Dll);
				// 빌드 산출물(모듈 DLL) 옆에 복사 → 런타임에 같은 폴더에서 찾는다.
				RuntimeDependencies.Add("$(BinaryOutputDir)/" + Dll, Src);
			}
		}
	}
}
