# MidiCore → 언리얼 엔진 플러그인 제작 가이드라인

현재 `MidiCore.dll`(SMF 파서 + 출력 백엔드)을 언리얼 엔진(UE5) **플러그인**으로
옮기기 위한 로드맵입니다. "그대로 옮길 부분"과 "언리얼식으로 다시 쓸 부분"을 구분하는 것이 핵심입니다.

---

## 0. 결론 먼저 — 무엇을 옮기고 무엇을 버리나

| 현재 요소 | 언리얼에서 | 이유 |
|-----------|------------|------|
| **파서** (`Midi.cpp`, `Util.h`, 이벤트/트랙/노트세그먼트) | ✅ **그대로 이식** (소스 직접 컴파일) | 순수 C++. 의존성 없음. 가장 가치 있는 자산 |
| `NoteSegment` / `BuildNoteSegments` / 템포·시각 데이터 | ✅ 이식 → **USTRUCT 노출** | 피아노롤 GUI(목표)의 데이터 소스 |
| `IMidiOut` 추상화 | ✅ 유지 → **언리얼 백엔드 추가** | 백엔드 교체 지점이라 설계가 이미 맞음 |
| **FluidSynth** | △ **렌더 전용**으로 재사용 (오디오 드라이버 제거) | UE 오디오 엔진으로 PCM을 직접 흘려보내야 함 |
| `WinmmOut` (winmm 직접 출력) | △ **에디터/Win64 디버그용**으로만 | OS 전역 MIDI out. 패키지/타 플랫폼·UE 오디오와 안 맞음 |
| FluidSynth의 **SDL3 오디오 드라이버** | ❌ 제거 | UE 오디오 디바이스와 충돌. 블록 렌더 API로 대체 |
| `MidiPlayer` (콘솔 재생 루프) | ❌ **다시 작성** | `_kbhit`/`Sleep`/`timeBeginPeriod`/콘솔 — UE에 안 맞음 |
| `MidiCore.dll`의 **C++ 클래스 export** | ❌ 버림 | STL을 DLL 경계로 넘기는 모델은 UE의 CRT/STL과 ABI 충돌 |

> **한 줄 요약**: 파서는 소스째 UE 모듈로 컴파일하고, 소리는 FluidSynth를 *신디사이저*로만
> 써서 `USynthComponent`로 UE 오디오에 연결한다. 콘솔 플레이어 로직은 컴포넌트 Tick/오디오 콜백으로 재작성한다.

---

## 1. 먼저 정해야 할 3가지 결정

1. **타깃 플랫폼 범위**
   - (A) **Win64 전용** → 현재 코드 재사용 최대. 권장 시작점.
   - (B) 크로스플랫폼(Mac/Android/콘솔) → winmm 불가, FluidSynth 라이브러리를 플랫폼별로 준비해야 함.
   - 👉 **권장: 1차는 Win64 전용으로 완성** 후 필요 시 확장.

2. **오디오 출력 경로**
   - (A) **FluidSynth를 UE 오디오로 렌더**(`USynthComponent`) → 게임에 정상 통합(스페이셜라이즈/믹서/패키징 OK). **권장**.
   - (B) FluidSynth 자체 오디오 드라이버 유지 → 빠르지만 UE 밖에서 소리가 나 통합성 ✗.
   - (C) 시각화만 우선, 소리는 나중 → 피아노롤 목표만이면 **파서만으로 충분**.

3. **코어 라이브러리 통합 방식**
   - (A) **소스 직접 컴파일**(파서) → ABI 문제 없음. **권장**.
   - (B) 프리빌트 `MidiCore.dll` 링크 → UE의 CRT/STL과 충돌 위험. 파서엔 비권장.
   - FluidSynth처럼 **이미 바이너리로만 있는 서드파티**만 (B) 방식(ThirdParty 모듈)으로.

---

## 2. 권장 플러그인 구조

```
Plugins/MidiSynth/
├─ MidiSynth.uplugin
├─ Source/
│  ├─ MidiCore/                     # [Runtime] 순수 파서 (소스 직접 컴파일)
│  │  ├─ MidiCore.Build.cs
│  │  ├─ Public/  Midi.h, MidiTypes.h ...
│  │  └─ Private/ Midi.cpp, Util.h ...
│  ├─ MidiSynthRuntime/             # [Runtime] USynthComponent + 재생 스케줄러 + Blueprint API
│  │  ├─ MidiSynthRuntime.Build.cs
│  │  ├─ Public/  UMidiSynthComponent.h, MidiPlayerTypes.h ...
│  │  └─ Private/ ...
│  └─ ThirdParty/
│     └─ FluidSynth/                # [External] 헤더 + .lib + .dll 스테이징만
│        ├─ FluidSynth.Build.cs
│        ├─ include/                # 직접 동적 로드(GetProcAddress)면 헤더 생략 가능
│        ├─ lib/Win64/fluidsynth.lib
│        └─ bin/Win64/ libfluidsynth-3.dll, SDL3.dll, sndfile.dll
└─ Content/
   └─ SoundFonts/ GeneralUser-GS.sf2   # 또는 별도 에셋/외부 경로
```

모듈을 **MidiCore(파서) / MidiSynthRuntime(소리·BP) / ThirdParty(FluidSynth)** 로 나누면
"파서만 쓰는 사용자"(시각화)와 "소리까지 쓰는 사용자"를 깔끔히 분리할 수 있습니다.

### 2.1 `.uplugin`
```json
{
  "FileVersion": 3,
  "FriendlyName": "MIDI Synth",
  "Version": 1, "VersionName": "0.1",
  "Category": "Audio",
  "Modules": [
    { "Name": "MidiCore",          "Type": "Runtime", "LoadingPhase": "Default" },
    { "Name": "MidiSynthRuntime",  "Type": "Runtime", "LoadingPhase": "Default" }
  ]
}
```

### 2.2 `MidiCore.Build.cs` (파서 모듈)
```csharp
using UnrealBuildTool;
public class MidiCore : ModuleRules
{
    public MidiCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core" });
        // 파일을 메모리로 읽어 파싱하면 CoreUObject/Engine 불필요
        bEnableExceptions = true;        // std 컨테이너 사용 시 안전하게
        // winmm를 에디터 디버그 백엔드로 둘 때만:
        if (Target.Platform == UnrealTargetPlatform.Win64)
            PublicSystemLibraries.Add("winmm.lib");
    }
}
```

### 2.3 `FluidSynth.Build.cs` (서드파티 — 바이너리 스테이징)
```csharp
using System.IO;
using UnrealBuildTool;
public class FluidSynth : ModuleRules
{
    public FluidSynth(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
            // 동적 로드(GetProcAddress) 방식이면 .lib 링크는 생략 가능
            // PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory,"lib","Win64","fluidsynth.lib"));
            foreach (var Dll in new[]{ "libfluidsynth-3.dll", "SDL3.dll", "sndfile.dll" })
            {
                string Src = Path.Combine(ModuleDirectory, "bin", "Win64", Dll);
                RuntimeDependencies.Add("$(BinaryOutputDir)/" + Dll, Src); // 빌드 산출물 옆에 복사
            }
        }
    }
}
```
> 현재 `TryLoadFluidDll()`가 이미 `LoadLibrary`+`GetProcAddress`로 동적 로드하므로 **import lib가 필요 없습니다.**
> 다만 DLL 탐색 경로를 `exe\..\..` 대신 **플러그인 바이너리 폴더**로 바꿔야 합니다(§4.5).

---

## 3. 단계별 마이그레이션 로드맵

### Phase 0 — 플러그인 골격
- 빈 플러그인 생성(`MidiSynth`), 위 3개 모듈/`.uplugin` 작성, 빈 빌드 통과.

### Phase 1 — 파서 이식 (소리 없음, 시각화 목표 달성)
1. `Midi.h/.cpp`, `Util.h`를 `MidiCore` 모듈로 복사.
2. **파일 입력을 `FILE*` → 메모리 버퍼로 리팩터링** (가장 중요, §4.1).
3. UE 코딩 규칙 충돌 제거 (§4.2~4.4).
4. `NoteSegment`/트랙명/템포를 **USTRUCT(BlueprintType)** 로 노출(§5).
5. 테스트: `.mid`를 로드해 노트 개수·길이·트랙명을 로그/위젯에 출력 → **피아노롤 데이터 확보**.

### Phase 2 — 소리 (FluidSynth → USynthComponent)
1. `ThirdParty/FluidSynth` 구성, DLL 스테이징.
2. `FluidSynthOut`에서 **오디오 드라이버 생성 제거**, 대신 `fluid_synth_write_float` 블록 렌더 사용(§6).
3. `UMidiSynthComponent : USynthComponent` 작성 — `OnGenerateAudio`에서 합성(§6.2).
4. 게임스레드 → 오디오스레드로 **이벤트를 락프리 큐**로 전달, 샘플 단위 스케줄(§6.3).

### Phase 3 — 재생 컨트롤 & 마감
- 재생/일시정지/탐색/배속/조옮김/채널 음소거를 **BlueprintCallable**로 재구현
  (콘솔 `MidiPlayer` 로직을 컴포넌트 상태머신으로 이식, `Sleep`/`_kbhit` 제거).
- (선택) `WinmmOut`을 `WITH_EDITOR` 한정 디버그 백엔드로 유지.
- 패키징 테스트(Shipping) — DLL/사운드폰트가 함께 스테이징되는지 확인.

---

## 4. 소스 수정 체크리스트 (UE 규칙 충돌)

### 4.1 ⭐ 파일 입력 → 메모리 버퍼 (필수)
패키지 게임에선 `.mid`가 pak 안에 있어 `fopen`이 실패합니다. 메모리 파싱으로 바꾸세요.
```cpp
// UE 쪽
TArray<uint8> Bytes;
FFileHelper::LoadFileToArray(Bytes, *FullPath);   // 또는 에셋/IFileManager
CMidi Midi(Bytes.GetData(), Bytes.Num());
```
파서 내부의 `fgetc/fread/ungetc(FILE*)`를 **바이트 포인터+오프셋 리더**(예: `struct FByteReader { const uint8* p; size_t n, pos; }`)로 교체합니다. `Util.h`의 `ReadVLQ/ReadBE16/ReadBE32`도 이 리더를 받게 바꾸면 됩니다.

### 4.2 헤더의 `using namespace std;` 제거
`Midi.h` 9행 등. UE 헤더에 섞이면 충돌 → `std::vector`처럼 한정 사용으로.

### 4.3 Windows 헤더 래핑
`windows.h`/`mmsystem.h`는 UE 매크로와 충돌하므로 감싸세요.
```cpp
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include <mmsystem.h>
#include "Windows/HideWindowsPlatformTypes.h"
```
`#pragma comment(lib,"winmm.lib")` 제거 → Build.cs의 `PublicSystemLibraries`로.

### 4.4 기타
- 유니티 빌드에서 `min/max`, 전역 심볼 충돌 주의(`NOMINMAX`는 UE가 관리).
- 한글 주석 소스는 **UTF-8 BOM** 유지(C4819 방지) — 기존 규칙 그대로.
- 예외: UE는 기본 예외 비활성. std 컨테이너 쓰면 `bEnableExceptions=true`.

### 4.5 FluidSynth DLL 탐색 경로 교정
`TryLoadFluidDll()`이 `exe\..\..`를 뒤지는데, UE에선 플러그인 바이너리 폴더에서 찾아야 합니다.
```cpp
FString Base = IPluginManager::Get().FindPlugin(TEXT("MidiSynth"))->GetBaseDir();
FString Dir  = FPaths::Combine(Base, TEXT("Source/ThirdParty/FluidSynth/bin/Win64"));
void* Handle = FPlatformProcess::GetDllHandle(*FPaths::Combine(Dir, TEXT("libfluidsynth-3.dll")));
```

---

## 5. Blueprint 노출 설계

```cpp
USTRUCT(BlueprintType)
struct FMidiNoteSegment
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) int32 Channel = 0;
    UPROPERTY(BlueprintReadOnly) int32 Note = 0;
    UPROPERTY(BlueprintReadOnly) int32 Velocity = 0;
    UPROPERTY(BlueprintReadOnly) float StartSeconds = 0.f;
    UPROPERTY(BlueprintReadOnly) float EndSeconds = 0.f;
};

UCLASS(BlueprintType)
class UMidiSong : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) bool LoadFromFile(const FString& Path);
    UFUNCTION(BlueprintCallable) void GetNoteSegments(TArray<FMidiNoteSegment>& Out) const;
    UFUNCTION(BlueprintCallable) float GetDurationSeconds() const;
    UFUNCTION(BlueprintCallable) void GetTrackNames(TArray<FString>& Out) const;
private:
    TUniquePtr<CMidi> Midi;   // 내부 파서 보관(헤더는 Private 의존)
};
```
- 내부 `CMidi`/`NoteSegment`(`std::` 기반)는 **Private에 숨기고**, 경계에서 UE 타입으로 변환합니다.
- 이렇게 하면 파서의 `std::` 사용이 Blueprint/외부로 새지 않습니다.

---

## 6. 오디오 통합 상세 (핵심)

### 6.1 FluidSynth를 "드라이버 없이" 쓰기
`Create()`에서 **`new_fluid_audio_driver` 호출을 제거**하고, 샘플레이트만 UE에 맞춥니다.
```cpp
fluid_settings_setnum(settings, "synth.sample-rate", (double)SampleRate); // UE는 보통 48000
// 드라이버 생성/SDL3 경로 삭제 → SDL3.dll 런타임 의존도 줄어듦
```
필요한 추가 심볼: `fluid_synth_write_float`, `fluid_settings_setnum`.

### 6.2 `UMidiSynthComponent`
```cpp
UCLASS(ClassGroup=(Audio), meta=(BlueprintSpawnableComponent))
class UMidiSynthComponent : public USynthComponent
{
    GENERATED_BODY()
protected:
    virtual bool  Init(int32& SampleRate) override   // 엔진이 SampleRate 알려줌
    {
        NumChannels = 2;
        // 여기서 FluidSynth 생성 + 사운드폰트 로드 + 위 sample-rate 설정
        return true;
    }
    virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override
    {
        const int32 Frames = NumSamples / 2;        // 스테레오 인터리브
        DrainScheduledEvents(Frames);               // 이번 블록 구간 이벤트 송출(§6.3)
        // 인터리브 출력: L=offset0/incr2, R=offset1/incr2
        fluid_synth_write_float(Synth, Frames, OutAudio, 0, 2, OutAudio, 1, 2);
        return NumSamples;
    }
};
```
`Start()`/`Stop()`(USynthComponent 제공)으로 합성 시작/정지, BP에서 호출 가능.

### 6.3 스레드 안전한 이벤트 스케줄
- `OnGenerateAudio`는 **오디오 렌더 스레드**에서 돌고, 재생 위치 전진·이벤트 송출은 여기서 해야 샘플 정확도가 납니다.
- 게임스레드(BP)에서의 조작(탐색/배속/음소거)은 **락프리 명령 큐**(`TQueue<…, SPSC>` 또는 원자 변수)로 전달.
- 콘솔판 `MidiPlayer`의 "시각순 평탄화 + chase(탐색 시 컨트롤러 상태 복원)" 알고리즘은 그대로 재사용 가치가 큽니다. 타이밍 기준만 `Sleep` → **누적 샘플 카운트**로 교체.

---

## 7. 라이선스 / 배포 주의

- **FluidSynth: LGPL-2.1** — 동적 링크(DLL) 유지 시 비교적 안전하지만, 게임 배포 시 LGPL 고지/교체가능성 의무를 확인하세요. 정적 링크는 지양.
- **libsndfile: LGPL**, **SDL3: zlib**(관대). 오디오 드라이버를 제거하면 SDL3 의존을 줄일 수 있습니다.
- **사운드폰트(GeneralUser-GS 등)**: 자체 라이선스 확인 후 `Content`에 동봉 또는 사용자 지정 경로로.
- 배포 전 `RuntimeDependencies`로 DLL/사운드폰트가 **패키지에 포함**되는지 Shipping 빌드로 검증.

---

## 8. 권장 진행 순서 요약

1. **Phase 1(파서+시각화)** 부터. 소리 없이도 피아노롤 목표 달성 — 위험 가장 낮음.
2. 파서의 **메모리 입력 리팩터링**과 **`std::` 캡슐화**를 이때 끝낸다.
3. 그다음 **FluidSynth 블록 렌더 + USynthComponent**로 소리.
4. 재생 컨트롤(BP) → 패키징 검증 → (선택) 크로스플랫폼.

> 가장 먼저 손볼 한 가지를 꼽으면: **파서의 `FILE*` 입력을 메모리 버퍼로 바꾸는 것**.
> 이거 하나로 UE 어떤 입력 경로(에셋/pak/외부파일)에도 붙일 수 있게 됩니다.
