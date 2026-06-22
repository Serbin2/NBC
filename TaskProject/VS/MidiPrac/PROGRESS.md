# 진행 상황 (MIDI → 언리얼 플러그인)

최종 목표: MidiPrac의 MIDI 파서/재생을 **언리얼 엔진(UE5) 플러그인**으로 만들기
(트랙별 피아노롤 시각화 + FluidSynth 사운드폰트 재생).

마지막 업데이트: **2026-06-22**

---

## 두 개의 프로젝트

| 위치 | 역할 |
|------|------|
| `…\VS\MidiPrac` (이 repo) | **원본 + 빠른 테스트장**. 콘솔 파서/플레이어. 파서 리팩터링을 여기서 먼저 검증. |
| `…\VS\MidiR\MidiR` | **언리얼 5.5 프로젝트**. 여기 `Plugins/MidiCore` 에 파서를 이식. |

> `.sln/.vcxproj/x64` 같은 VS 빌드 파일은 UE로 옮기지 않음. 넘어가는 건 파서 **소스**뿐.

---

## 완료된 것 ✅

### Phase 1 — 파서 포터블화 (MidiPrac repo)
- 입력을 `FILE*` → **메모리 버퍼(`CByteReader`, `Util.h`)** 로 변경.
- `CMidi(const uint8_t* data, size_t size)` 생성자 추가(언리얼용). 기존 `CMidi(const char*)`는 파일을 읽어 같은 `ParseBuffer`로 위임(콘솔 호환 유지).
- `Midi.h` 의 `using namespace std;` 제거 → 전부 `std::` 한정.
- 검증: 솔루션 빌드 0경고/0에러, 콘솔 재생 정상, 소스컴파일 테스트로 goit.mid = **18트랙 / 20030이벤트 / 9860노트 / 269.3초** 확인.

### Phase 2 — 파서를 UE 플러그인으로 이식 (MidiR 프로젝트)
- `Plugins/MidiCore/` 생성 (모듈명 `MidiCore` → UBT가 `MIDICORE_API` 자동 정의).
  - `MidiCoreApi.h` 는 `#ifndef MIDICORE_API` 가드로 원본 VS 빌드와 겸용.
  - 파서 복사: `Util.h`/`Midi.h` → Public, `Midi.cpp` → Private.
  - `MidiCoreModule.cpp` (IMPLEMENT_MODULE).
  - **`UMidiBlueprintLibrary`** — BlueprintCallable `LoadMidiInfo`, `LoadMidiNotes` (+ `FMidiNoteSegment` USTRUCT). 입력은 `FFileHelper::LoadFileToArray` → `CMidi(버퍼,크기)`.
- `MidiREditor` 빌드 성공 → `UnrealEditor-MidiCore.dll`. 테스트용 `goit.mid` 를 `MidiR/Content/` 에 복사.

### 시각화 v1 — 피아노롤 액터
- **`AMidiPianoRollActor`** (MidiCore 플러그인): `LoadMidiNotes` 결과를 채널별 `UInstancedStaticMeshComponent`(엔진 Cube + BasicShapeMaterial `Color`)로 배치.
  - X=시간, Z=음높이, 색=채널(드럼=회색), 재생 헤드가 Tick에서 시간축 스윕(루프).
  - `OnConstruction`에서 즉시 생성 → 레벨에 드롭만 해도 보임.
  - 디테일: `MidiFilePath`(기본 goit.mid) · `TimeScale` · `PitchScale` · `PlaybackSpeed` · `Rebuild` 버튼.
- `MidiREditor` 빌드 성공.

### Phase 2 오디오 — FluidSynth → USynthComponent (2026-06-20)
- **서드파티(External) 모듈** `Plugins/MidiCore/Source/ThirdParty/FluidSynth/` 신설: `FluidSynth.Build.cs`가 DLL 3종(`libfluidsynth-3.dll`/`SDL3.dll`/`sndfile.dll`)을 `RuntimeDependencies`로 빌드 산출물(`Binaries/Win64`) 옆에 스테이징. import lib/헤더 없음(동적 로딩).
- **`FFluidSynthRenderer`**(Private): 콘솔 `FluidSynthOut`을 "드라이버 없이" 쓰는 버전. `FPlatformProcess::GetDllHandle`로 SDL3→sndfile→libfluidsynth 순 로드, `FluidApi` 함수포인터 테이블. **드라이버 함수 제거**, `fluid_synth_write_float`(블록 렌더) + `fluid_settings_setnum`(샘플레이트) 추가. `Init(SR, sf2)` / 송출(NoteOn/Off/CC/Program/Bend/Pressure/SysEx/AllSoundOff) / `RenderFloat`.
- **`UMidiSynthComponent : USynthComponent`**(Public): `Init`에서 렌더러 생성+사운드폰트 로드+이벤트 평탄화(콘솔 `CollectEvents` 이식, `{초, 패킹메시지}` 불변 배열). `OnGenerateAudio`(오디오스레드)에서 누적샘플로 시간 전진→도달 이벤트 드레인→`RenderFloat`. 제어는 atomic 전달(배속/일시정지/게인/탐색). 탐색은 `SeekTo`의 chase(채널별 마지막 CC/Program/Bend/Pressure 재전송) 이식.
  - BlueprintCallable: `PlayMidi`/`StopMidi`/`PauseMidi`/`ResumeMidi`/`SeekSeconds`/`SetPlaybackSpeed`/`SetGainLevel`/`GetPlayPositionSeconds`/`GetDurationSeconds`/`IsPlayingMidi`. 디테일: `MidiFilePath`(기본 goit.mid)·`SoundFontPath`(기본 GeneralUser-GS.sf2)·`Gain`·`PlaybackSpeed`·`bAutoPlayOnBeginPlay`.
- `MidiCore.Build.cs`: `AudioMixer`(USynthComponent)·`Projects`(IPluginManager) 공개 의존 + `FluidSynth`(ThirdParty) 비공개 의존. `GeneralUser-GS.sf2`를 `MidiR/Content/`에 복사.
- **`MidiREditor` 빌드 성공(0 에러)**, 3개 DLL이 `Plugins/MidiCore/Binaries/Win64/`에 스테이징 확인. (소스 컴파일/링크까지 검증, **실제 소리는 사용자 청취 필요**)
- 주의: USynthComponent는 `FObjectInitializer` 생성자 필요. UObject가 불완전 타입 PIMPL을 들 땐(예외 활성) `TUniquePtr` 대신 **원시 포인터**로 둬야 UHT 생성 생성자/소멸자가 완전 타입을 요구하지 않음.

### 시각 동기화 — 재생바 ↔ 오디오 시계 (2026-06-20)
- 사용자 검증 중 발견: 피아노롤 액터를 신스와 같이 쓰면 재생바가 오디오보다 약간 빠름(두 시계가 독립 + 사운드폰트 로딩 시작 지연).
- `AMidiPianoRollActor::Tick` 수정: `bSyncToSynth`(기본 true)면 같은 액터의 `UMidiSynthComponent`를 `FindComponentByClass`로 찾아(캐시) 매 Tick `PlayTime = GetPlayPositionSeconds() + PlaybackOffsetSeconds`로 맞춤(클램프). 신스 없거나 동기화 끄면 기존 자체 시계(`DeltaSeconds*PlaybackSpeed`, 루프)로 폴백.
- 새 EditAnywhere 변수: `bSyncToSynth`(오디오 시계 종속), `PlaybackOffsetSeconds`(수동 미세보정, +면 재생바 앞당김). 빌드 0에러.

### Phase 3 — 재생 컨트롤 풀세트 (2026-06-20)
콘솔 `MidiPlayer`의 조옮김/음소거/반복 로직을 `UMidiSynthComponent` 오디오 스레드 모델로 이식. 빌드 0에러.
- **조옮김(transpose)**: `int8 NoteMap[16][128]`로 (채널,원음)→실제 울리는 음높이를 추적 → 도중에 조옮김이 바뀌어도 NoteOff가 정확한 음을 끔. 드럼 채널(9) 제외, 범위 -24~24, 음역 밖이면 그 음만 생략. PolyKeyPressure도 NoteMap으로 매핑.
- **채널 음소거(mute)**: `TAtomic<uint32> MuteMask`(채널당 1비트). `OnGenerateAudio` 블록 시작에서 엣지 감지 → 새로 음소거된 채널은 `AllNotesOff`+NoteMap 클리어로 즉시 소거. NoteOn 송출 시 음소거 채널은 건너뜀(CC/program은 통과).
- **반복(loop)**: 끝 도달 시 `bLoopAtomic`이면 `AllSoundOff`+NoteMap 클리어 후 커서/시간 0으로(정지 대신).
- 일시정지/탐색 시에도 NoteMap 클리어. 새 변수/함수: `Transpose`·`bLoop`(EditAnywhere) + `SetTranspose`/`SetLoop`/`SetChannelMute`/`ToggleChannelMute`/`IsChannelMuted`(BlueprintCallable).

### .mid 에셋 임포트 + 에디터 미리듣기 (2026-06-20)
`.mid`를 문자열 경로 대신 Content Browser 에셋으로 다루고 에디터에서 청취. 빌드 0에러(`UnrealEditor-MidiCoreEditor.dll` 생성).
- **`UMidiFileAsset`**(런타임): `RawData`(원본 바이트) + 임포트 시 계산한 Format/Track/Event/Note/Duration/SourceFilePath(`RefreshInfo()`). `MIDICORE_API`.
- **소비(경로 폴백 유지)**: `UMidiSynthComponent`·`AMidiPianoRollActor`에 `TObjectPtr<UMidiFileAsset> MidiAsset` 추가(에셋 우선, 없으면 기존 경로). 컴포넌트는 `BuildSchedule`을 `BuildScheduleFromBytes`로 분리. `UMidiBlueprintLibrary`에 `LoadMidiNotesFromAsset` + 내부 `ParseBytes`/`CollectNotes` 공용화.
- **신설 에디터 모듈 `MidiCoreEditor`**(uplugin에 Type=Editor/PostEngineInit 추가): `UMidiFileFactory`(.mid/.midi 임포트, 드래그&드롭) · `FAssetTypeActions_MidiFile`(카테고리 Sounds, 우클릭 **Play/Stop** = `FToolMenuSection::GetActions`) · `FMidiAssetPreview`(에디터 월드에 transient 액터+신스 컴포넌트 스폰해 PIE 없이 재생/정지).
- **컴포넌트 디테일 미리듣기 버튼**: `UMidiSynthComponent`에 `PreviewPlay`/`PreviewStop`(CallInEditor) — 배치된 컴포넌트를 에디터에서 바로 청취(가장 확실한 경로).

### 에디터 미리듣기 무음 + 크래시 2종 수정 (2026-06-22) — 모두 사용자 검증 완료
미리듣기/삭제/종료 과정에서 드러난 버그 3개를 잡음. 빌드 0에러.
- **에디터 미리듣기 무음**: 비게임(에디터) 월드에선 오디오 디바이스가 `bGameTicking==false`라 **`bIsUISound` 보이스만 렌더**(엔진 `AudioDevice.cpp`: `bGameTicking || WaveInstance->bIsUISound`). 일반 `USynthComponent`는 `bIsUISound=false`라 PIE에선 들리고 에디터에선 무음. → `PlayMidi()`에서 `Start()` 전에 **비게임 월드면** `bIsUISound=true`/`bIsPreviewSound=true`/`bAllowSpatialization=false` 설정(게임 월드/PIE는 그대로). `Init`/`OnGenerateAudio`가 도는데도 무음이면 이 케이스.
- **재생 중 액터 삭제 크래시(AV)**: 콜스택 `~UMidiSynthComponent → ~FFluidSynthRenderer → Shutdown → delete_fluid_*`. 오디오 렌더 스레드가 `OnGenerateAudio`에서 `fluid_synth_write_float`를 도는 중 게임 스레드 GC 소멸자가 `delete Renderer`로 같은 fluid 객체를 해제 → **use-after-free**. → `FCriticalSection RendererCS`로 Renderer **생성(`Init`)·사용(`OnGenerateAudio`)·해제(소멸자)** 직렬화 + **`BeginDestroy()`** 오버라이드에서 먼저 `Stop()`으로 렌더 콜백 차단(경합 창 최소화).
- **엔진 종료 시 크래시(AV)**: 종료 시 GC 일괄 purge가 소멸자→`Shutdown`→`delete_fluid_settings` 호출 → 종료 시점엔 FluidSynth DLL/내부 전역 정리 순서가 깨져 무효 메모리 접근. (런타임 중 삭제에선 정상이라 종료 특이 문제로 확정) → `Shutdown()` 진입 시 **`IsEngineExitRequested()`면 정리를 통째로 스킵**(프로세스 종료로 OS가 메모리·DLL 회수). 런타임 중 정상 파괴에선 기존대로 정리.
- 교훈: **`USynthComponent` 파생이 외부 네이티브 리소스를 들 때**, 오디오 렌더 스레드와 GC 소멸자 수명을 반드시 상호배제하고(락 또는 `ISoundGenerator` 패턴), **종료 시 외부 DLL 정리는 건너뛴다**.

### 배포 가능한 자급자족 플러그인 패키징 (2026-06-22) — 타 프로젝트 동작 검증 완료
플러그인만 넣으면 추가 설정 없이 동작하도록 자급자족화 + 배포본 산출.
- **자급자족 경로 해석**: `UMidiBlueprintLibrary::ResolveMidiResourcePath(In, PluginSubDir)` 신설 — 상대경로를 ①프로젝트 `Content/<In>` → ②플러그인 동봉본 `<Plugin>/Content/<SubDir>/<파일명>`(`IPluginManager` BaseDir) 순으로 해석. 컴포넌트/액터/`LoadMidiNotes`가 모두 경유 → **플러그인만 넣어도 동봉 사운드폰트로 소리**, 프로젝트에 `.sf2` 두면 오버라이드. 기존 `ResolveContentPath`(컴포넌트)·`ResolveMidiPath`(라이브러리) 중복 제거하고 이 함수로 통일.
- **동봉**: `GeneralUser-GS.sf2`(32MB)·예제 `.mid` 3종을 `Plugins/MidiCore/Content/{SoundFonts,Midi}/`로 복사(비에셋 raw; FluidSynth `sfload`·파서가 디스크 파일을 직접 읽어 `.uasset` 쿠킹 대상 아님). `MidiCore.Build.cs`에서 `RuntimeDependencies.Add(..., StagedFileType.NonUFS)`로 스테이징(`PluginDirectory` 기준).
- **라이선스/문서**: `Resources/THIRD_PARTY_NOTICES.md`(FluidSynth·sndfile LGPL-2.1 / SDL3 zlib / GeneralUser-GS; 동적 로드+미수정 DLL이라 LGPL 동적링크 충족), `LICENSE`(MIT, 저작권자 placeholder), `README.md`. uplugin: VersionName 1.0·설명·`CanContainContent:true`.
- **⚠️ `RunUAT BuildPlugin` 실패(엔진 버그)**: 설치형 UE 5.5 UBT 회귀 — `AddAllValidModulesToTarget`에서 `GetModuleRulesType()`가 null인데 null-forgiving(`!`)으로 통과 → `IsValidForTarget(null)` `ArgumentNullException`. 우리 코드 무관(코드 빌드는 0에러, EngineVersion 제거 후에도 동일), RiderLink 등 타 플러그인도 같은 스택. **→ 수동 패키징으로 동등 산출**: `Dist/MidiCore`(Source+Binaries/Win64[DLL5종+.modules]+Content+Resources+LICENSE/README/uplugin, Intermediate 제외) + `Dist/MidiCore-1.0-UE5.5-Win64.zip`(33MB). Source 포함이라 타 엔진 마이너버전은 리빌드, 동일 5.5는 동봉 바이너리로 무컴파일 로드. **빈 프로젝트 압축해제 → 정상 동작 사용자 확인.**

---

## ▶ 다음 세션 시작점

- ✅ **청취/동기화/컨트롤 검증 완료**: 신스 컴포넌트 Play 소리, 피아노롤 재생바 동기화, 조옮김/음소거/반복 모두 확인.
- ✅ **에셋/미리듣기 검증 완료**: `.mid` 드래그 임포트, 에셋 우클릭 Play/Stop, 컴포넌트 Preview 버튼 청취 확인.
- ✅ **크래시/무음 수정 검증 완료(2026-06-22)**: 에디터 미리듣기 소리 남, 재생 중 액터 삭제·에디터 종료 모두 크래시 없음.
- ✅ **배포 패키징 검증 완료(2026-06-22)**: 자급자족화 + `Dist/MidiCore`(+zip) 산출, 빈 프로젝트에서 정상 동작 확인.

다음 후보(미착수):
   - **정밀 타이밍**: `OnGenerateAudio` 블록 내 샘플오프셋 세분화.
   - **패키징 마감**: 정식 `RunUAT BuildPlugin`(엔진 버그 우회: 소스빌드 엔진/엔진 Verify 후 재시도), 배포 전 `LICENSE` 저작권자 기입, sf2 Git LFS, Shipping 풀 쿠킹·Mac/Linux 타깃.
   - **에셋 마감**: 정식 Reimport(`UAssetImportData`)·썸네일·전용 에디터.
   - **시각화 강화**: 현재 울리는 노트 하이라이트 / 2D UMG 피아노롤.

---

## 빌드 명령 (UE 플러그인)
```
"C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\Build.bat" ^
  MidiREditor Win64 Development ^
  -Project="…\VS\MidiR\MidiR\MidiR.uproject" -WaitMutex -NoHotReload
```
> 빌드 전 언리얼 에디터를 닫을 것(DLL 잠김 방지). 한글 주석 소스는 **UTF-8 BOM 유지**(C4819 방지).

## 참고 문서 (이 repo 루트)
- `MidiCore-DLL-API.md` — DLL/파서 API 정리
- `UnrealPlugin-Roadmap.md` — UE 플러그인 마이그레이션 로드맵(Phase 0~3, 오디오/라이선스 상세)
