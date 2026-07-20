# MidiCore — 사용 설명서

**MidiCore** 언리얼 엔진 5.5 플러그인의 블루프린트 노출 API 레퍼런스입니다.
레벨에 직접 배치하는 두 클래스 — **Midi Synth Component**(오디오)와
**Midi Piano Roll Actor**(시각화) — 를 중심으로, 보조 에셋과 블루프린트
라이브러리까지 다룹니다.

설치와 빠른 시작은 `README.md`, 서드파티 라이선스는
`Resources/THIRD_PARTY_NOTICES.md` 를 참고하세요. 재생이 내부적으로 어떻게
이뤄지는지(파싱 → 스케줄 → 오디오 믹서 pull → 블록 디스패치 → 합성 → 시각화
동기화)는 브라우저에서 `Documentation/PlaybackFlow.html` 을 열어 그림으로 볼 수
있습니다.

> **플랫폼:** Windows(Win64) 전용. 동봉된 네이티브 라이브러리는 Windows DLL입니다.

---

## 목차
1. [개념](#개념)
2. [Midi Synth Component](#midi-synth-component)
3. [Midi Piano Roll Actor](#midi-piano-roll-actor)
4. [MIDI File Asset](#midi-file-asset)
5. [Midi Blueprint Library](#midi-blueprint-library)
6. [대표 사용 흐름](#대표-사용-흐름)
7. [리소스 경로 해석](#리소스-경로-해석)
8. [런타임 주의사항 및 한계](#런타임-주의사항-및-한계)

---

## 개념

- **MIDI 데이터 출처.** 신스 컴포넌트와 피아노롤 액터 모두, 임포트한
  **`MidiAsset`**(`UMidiFileAsset`) 또는 **`MidiFilePath`** 문자열에서 MIDI를
  읽을 수 있습니다. `MidiAsset`이 지정되면 항상 우선하며, `MidiFilePath`는
  `MidiAsset`이 비어 있을 때만 사용됩니다.
- **채널.** MIDI 채널은 `0~15`입니다. 채널 `10`(인덱스 9)은 GM 드럼 채널이며
  조옮김에서 제외됩니다.
- **오디오 vs 시각화.** 신스 컴포넌트는 소리를 내고, 피아노롤 액터는 노트를
  3D 막대로 그립니다. 둘은 독립이지만, 한 액터에 함께 두면 재생바가 오디오
  시계를 따라가도록 묶을 수 있습니다(`bSyncToSynth` 참고).

---

## Midi Synth Component

`UMidiSynthComponent`(`MidiSynthComponent.h`) — 파싱된 MIDI 이벤트를 평탄화해
두고, UE 오디오 스레드에서 FluidSynth + 사운드폰트로 직접 합성하는
`USynthComponent`입니다.

클래스 그룹 **Audio**, 블루프린트에서 스폰 가능. 아무 액터에나 붙이고 MIDI
출처와 사운드폰트를 지정한 뒤 `PlayMidi`를 호출하면 됩니다.

### 프로퍼티

모두 `EditAnywhere, BlueprintReadWrite`, 카테고리 **Midi**.

| 프로퍼티 | 타입 | 기본값 | 설명 |
|---|---|---|---|
| `MidiAsset` | `UMidiFileAsset*` | 없음 | 임포트한 `.mid` 에셋. `MidiFilePath`보다 우선. |
| `MidiFilePath` | `FString` | `"goit.mid"` | 상대경로는 프로젝트 `Content/` 기준으로 해석([해석 규칙](#리소스-경로-해석)). `MidiAsset`이 비었을 때만 사용. |
| `SoundFontPath` | `FString` | `"GeneralUser-GS.sf2"` | `.sf2` 사운드폰트. 상대경로는 위와 동일하게 해석. |
| `Gain` | `float` | `0.2` | 마스터 게인, `0.0~1.0`로 클램프. |
| `PlaybackSpeed` | `float` | `1.0` | 재생 배속, `0.25~4.0`로 클램프. |
| `Transpose` | `int32` | `0` | 반음 단위, `-24~24`로 클램프. 드럼 채널 제외. |
| `bLoop` | `bool` | `false` | 곡 끝에서 처음부터 반복. |
| `bAutoPlayOnBeginPlay` | `bool` | `true` | `BeginPlay`에서 자동 재생. |

### 재생 컨트롤 (블루프린트 호출)

| 함수 | 설명 |
|---|---|
| `PlayMidi()` | 처음부터 재생. |
| `StopMidi()` | 정지 및 초기화. |
| `PauseMidi()` | 현재 위치에서 일시정지. |
| `ResumeMidi()` | 일시정지에서 재개. |
| `SeekSeconds(float Seconds)` | 해당 시각으로 점프. MIDI "체이스"로 컨트롤러/프로그램 체인지를 정확히 맞춤. |
| `SetPlaybackSpeed(float Speed)` | 배속 변경(프로퍼티와 동일 범위). |
| `SetGainLevel(float InGain)` | 마스터 게인 변경(`0.0~1.0`). |
| `SetTranspose(int32 Semitones)` | `-24~24` 반음 조옮김(드럼 채널은 영향 없음). |
| `SetLoop(bool bInLoop)` | 반복 켜기/끄기. |
| `SetChannelMute(int32 Channel, bool bMute)` | 채널 음소거/해제(`0~15`). 음소거 시 울리던 노트를 즉시 끄고 새 노트온을 차단. |
| `ToggleChannelMute(int32 Channel)` | 채널 음소거 상태 토글. |

### 에디터 미리듣기 (디테일 패널 버튼)

PIE 진입 없이 에디터에서 바로 실행 — 세팅을 청취 확인할 때 유용합니다.

| 함수 | 설명 |
|---|---|
| `PreviewPlay()` | 에디터 월드에서 재생. |
| `PreviewStop()` | 에디터 미리듣기 정지. |

### 조회 (블루프린트 Pure)

| 함수 | 반환 | 설명 |
|---|---|---|
| `GetPlayPositionSeconds()` | `float` | 현재 재생 위치(초). 시각화 동기화에 사용. |
| `GetDurationSeconds()` | `float` | 곡 전체 길이(초). |
| `IsPlayingMidi()` | `bool` | 재생 중이면 `true`(정지 상태가 아님). |
| `IsChannelMuted(int32 Channel)` | `bool` | 채널 음소거 상태. |

> **스레딩.** 컨트롤 호출은 게임 스레드에서 들어와 atomic으로 오디오 렌더
> 스레드에 전달되므로, 컴포넌트가 활성화된 뒤에는 언제든 안전하게 호출할 수
> 있습니다. 각 컴포넌트는 자기 FluidSynth 인스턴스와 사운드폰트를 독립적으로
> 소유합니다([런타임 주의사항](#런타임-주의사항-및-한계) 참고).

---

## Midi Piano Roll Actor

`AMidiPianoRollActor`(`MidiPianoRollActor.h`) — MIDI 파일을 파싱해 노트를 3D
막대로 배치하는 액터입니다.

- **X축** = 시간(막대 위치 = 시작 초, 길이 = 지속 시간)
- **Z축** = 음높이(`0~127`)
- **색** = 채널
- 재생 중 세로 **재생바**가 시간축을 따라 이동합니다.

노트는 채널별 `UInstancedStaticMeshComponent`에 인스턴스로 추가되어 대량
파일도 가볍습니다. 레벨에 끌어다 놓으면 `OnConstruction`에서 막대가 즉시
생성됩니다.

### 프로퍼티

모두 `EditAnywhere, BlueprintReadWrite`, 카테고리 **Midi**.

| 프로퍼티 | 타입 | 기본값 | 설명 |
|---|---|---|---|
| `MidiAsset` | `UMidiFileAsset*` | 없음 | 임포트한 `.mid` 에셋. `MidiFilePath`보다 우선. |
| `MidiFilePath` | `FString` | `"goit.mid"` | 상대경로는 신스 컴포넌트와 동일하게 해석. `MidiAsset`이 비었을 때만 사용. |
| `TimeScale` | `float` | `100` | 1초당 월드 길이(uu) — 가로(시간) 스케일. |
| `PitchScale` | `float` | `15` | 반음 1당 월드 높이(uu) — 세로(음높이) 스케일. |
| `NoteHeight` | `float` | `10` | 노트 막대 두께(Z, uu). |
| `NoteDepth` | `float` | `8` | 노트 막대 깊이(Y, uu). |
| `bAnimatePlayhead` | `bool` | `true` | 재생 중 재생바를 자동으로 이동. |
| `PlaybackSpeed` | `float` | `1` | 재생바 배속 — 동기화가 꺼졌거나 신스 컴포넌트가 없을 때**만** 사용. |
| `bSyncToSynth` | `bool` | `true` | **같은 액터**에 붙은 Midi Synth Component의 재생 위치에 재생바를 맞춤(오디오·시각 드리프트 제거). 컴포넌트가 없으면 `PlaybackSpeed`로 폴백. |
| `PlaybackOffsetSeconds` | `float` | `0` | 재생바 시간 미세 보정(초). 양수 = 오디오보다 앞당김, 음수 = 늦춤. |

### 함수

| 함수 | 설명 |
|---|---|
| `Rebuild()` | 출처를 다시 파싱해 모든 막대를 다시 그림. 디테일 패널 버튼이자 블루프린트 호출 가능. 에셋/경로나 레이아웃 스케일을 바꾼 뒤 호출. |

---

## MIDI File Asset

`UMidiFileAsset`(`MidiFileAsset.h`) — 표준 MIDI 파일의 원본 바이트와 표시용
메타데이터를 담는 `BlueprintType` 컨테이너입니다.

**임포트:** `.mid` / `.midi` 파일을 콘텐츠 브라우저로 드래그하면, 에디터 모듈의
팩토리가 `UMidiFileAsset`을 만들고 바이트를 저장한 뒤 메타데이터를 채웁니다.
에셋을 우클릭하면 **Play / Stop** 미리듣기가 가능합니다.

| 멤버 | 타입 | 설명 |
|---|---|---|
| `RawData` | `TArray<uint8>` | `.mid` 원본 바이트. 런타임에 파서로 그대로 전달. |
| `Format` | `int32` | SMF 포맷(0/1/2). 읽기 전용. |
| `TrackCount` | `int32` | 트랙 수. 읽기 전용. |
| `EventCount` | `int32` | 전체 MIDI 이벤트 수. 읽기 전용. |
| `NoteCount` | `int32` | 전체 노트 세그먼트 수. 읽기 전용. |
| `DurationSeconds` | `float` | 곡 길이(초). 읽기 전용. |
| `SourceFilePath` | `FString` | 임포트 출처 경로(참고용). 읽기 전용. |
| `RefreshInfo()` | — | `RawData`를 다시 파싱해 위 메타데이터를 재계산. 임포트 시 자동 호출. |

---

## Midi Blueprint Library

`UMidiBlueprintLibrary`(`MidiBlueprintLibrary.h`) — 컴포넌트 없이 MIDI를
파싱하는 정적 헬퍼. 커스텀 시각화나 툴에 쓸 수 있습니다.

| 함수 | 표시 이름 | 설명 |
|---|---|---|
| `LoadMidiInfo(FilePath, OutFormat, OutTrackCount, OutEventCount, OutNoteCount, OutDurationSeconds)` → `bool` | **Load MIDI Info** | `.mid` 경로를 파싱해 요약 수치와 길이를 반환. 성공 시 `true`. |
| `LoadMidiNotes(FilePath, OutNotes)` → `bool` | **Load MIDI Notes** | `.mid` 경로를 파싱해 모든 노트 세그먼트를 반환. |
| `LoadMidiNotesFromAsset(Asset, OutNotes)` → `bool` | **Load MIDI Notes (Asset)** | 위와 동일하되 임포트한 `UMidiFileAsset`에서 읽음. |

`ResolveMidiResourcePath(In, PluginSubDir)`는 C++ 전용 정적 헬퍼
(블루프린트 비노출)로, 상대 리소스 경로 해석에 내부적으로 쓰입니다 —
[리소스 경로 해석](#리소스-경로-해석) 참고.

### `FMidiNoteSegment`

라이브러리가 반환하는 노트 구조체(피아노롤 사각형 하나):

| 필드 | 타입 | 범위 | 의미 |
|---|---|---|---|
| `Channel` | `int32` | `0~15` | MIDI 채널. |
| `Note` | `int32` | `0~127` | 음높이. |
| `Velocity` | `int32` | `0~127` | 노트온 세기. |
| `StartSeconds` | `float` | — | 시작 시각. |
| `EndSeconds` | `float` | — | 종료 시각. |

---

## 대표 사용 흐름

**오디오만**
1. 액터에 **Midi Synth Component**를 추가.
2. `MidiAsset`을 지정(또는 `MidiFilePath` 기본값 유지).
3. `bAutoPlayOnBeginPlay = true`로 두거나, 블루프린트에서 `PlayMidi` 호출.

**시각화만**
1. 레벨에 **AMidiPianoRollActor**를 드롭.
2. `MidiAsset` / `MidiFilePath`를 파일로 지정. 막대가 즉시 표시됨.
3. `TimeScale` / `PitchScale`를 조정했으면 **Rebuild**를 누름.

**오디오 + 시각화 동기(권장)**
1. 같은 콘텐츠에 대해 **Midi Synth Component**와 **AMidiPianoRollActor**를
   함께 사용.
2. Midi Synth Component를 피아노롤과 **같은 액터**에 붙임.
3. `bSyncToSynth = true` 유지 — 재생바가 `GetPlayPositionSeconds()`를 따라가
   오디오와 시각이 어긋나지 않음.
4. 필요하면 `PlaybackOffsetSeconds`로 미세 정렬.

---

## 리소스 경로 해석

상대경로 `SoundFontPath` / `MidiFilePath`(및 라이브러리의 경로 함수)는 다음
순서로 해석됩니다.

1. `<Project>/Content/<경로>` — 프로젝트가 동봉 기본값을 오버라이드 가능.
2. `<Plugin>/Content/SoundFonts|Midi/<파일명>` — 동봉본 폴백.

절대경로는 그대로 사용합니다. 어디서도 못 찾으면 프로젝트 경로를 반환하고
로드 실패를 로그로 남깁니다. 그래서 플러그인은 별도 설정 없이 동작하지만,
프로젝트 `Content/`에 자신의 `.sf2`를 넣어 사운드폰트를 바꿀 수 있습니다.

---

## 런타임 주의사항 및 한계

- **독립 인스턴스.** 각 `UMidiSynthComponent`는 자기 FluidSynth 인스턴스를
  소유하고 **사운드폰트 사본을 각자 로드**합니다(동봉본 기준 약 30MB). 컴포넌트
  사이에 공유되는 가변 상태는 없습니다.
- **여러 곡 동시 재생**이 지원되며 안전합니다 — 신스 컴포넌트를 여러 개 두고
  서로 다른 파일을 동시에 재생할 수 있습니다. 다만 개수에 비례해 비용이 늘어
  납니다.
  - **메모리:** N개 컴포넌트 ≈ N × 사운드폰트 크기.
  - **시작 지연:** 컴포넌트가 시작될 때 게임 스레드에서 사운드폰트를 블로킹
    로드하므로, 여러 개를 한꺼번에 시작하면 히치가 생길 수 있음.
  - **CPU/오디오:** 인스턴스마다 매 오디오 블록을 합성하므로 DSP 비용과 보이스
    수가 N에 비례해 증가.
- **에디터 미리듣기는 설계상 단일 인스턴스.** 에셋 우클릭 미리듣기와 컴포넌트의
  `PreviewPlay`는 공유 에디터 미리듣기 슬롯 하나를 쓰므로, 새 미리듣기는 이전
  것을 멈춥니다. 이 제한은 에디터 미리듣기에만 해당하며 런타임 컴포넌트와는
  무관합니다.
- **수명.** 오디오 렌더와 게임 스레드 정리가 내부적으로 직렬화되므로, 재생 중
  액터를 삭제하거나 에디터를 종료해도 안전합니다.
