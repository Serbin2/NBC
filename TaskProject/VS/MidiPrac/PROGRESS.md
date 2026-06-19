# 진행 상황 (MIDI → 언리얼 플러그인)

최종 목표: MidiPrac의 MIDI 파서/재생을 **언리얼 엔진(UE5) 플러그인**으로 만들기
(트랙별 피아노롤 시각화 + FluidSynth 사운드폰트 재생).

마지막 업데이트: **2026-06-20**

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

---

## ▶ 다음 세션 시작점

1. **(사용자) 청취 확인**: 에디터에서 아무 액터에 `Midi Synth Component` 추가(또는 빈 액터 배치 후 컴포넌트 부착) → `MidiFilePath=goit.mid` → **Play**로 소리 확인. BP에서 `SeekSeconds`/`PauseMidi`/`SetPlaybackSpeed` 동작 확인.
   - 소리가 없으면 Output Log에서 `[MidiSynth]` 로그 확인(사운드폰트/DLL 로드 실패 여부).
2. **(사용자) 동기화 확인**: 피아노롤 액터 + 신스 컴포넌트 같이 두고 Play → 재생바가 소리와 맞는지. 어긋나면 디테일에서 `PlaybackOffsetSeconds`로 미세 조정(+면 앞당김).
3. **(사용자) 컨트롤 확인**: BP에서 `SetTranspose`/`SetChannelMute`/`SetLoop` 호출(또는 디테일 `Transpose`/`bLoop`)로 조옮김·음소거·반복 동작 청취 확인.
4. **(사용자) 에셋/미리듣기 확인**: Content Browser로 `.mid` 드래그 → `MIDI File` 에셋 생성(디테일에 트랙/노트/길이) → 에셋 **우클릭 Play/Stop** 청취. 신스 컴포넌트/피아노롤 액터에 `MidiAsset` 지정. 컴포넌트 디테일 **Preview Play/Stop** 버튼도 확인. (우클릭이 무음이면 컴포넌트 버튼으로 폴백 + Output Log `[MidiSynth]`)
5. 그다음 후보:
   - **정밀 타이밍**: `OnGenerateAudio` 블록 내 샘플오프셋 세분화.
   - **패키징**: 사운드폰트/DLL/에셋이 Shipping 빌드에 스테이징/쿠킹되는지 검증, FluidSynth LGPL 고지.
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
