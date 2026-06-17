# MidiCore.dll — 기능 정리 및 API 문서

표준 MIDI 파일(SMF) **파서**와 MIDI **출력 백엔드**를 하나의 동적 라이브러리
(`MidiCore.dll`)로 묶어, 다른 프로그램(콘솔 플레이어, GUI 피아노롤 등)에서
재사용할 수 있게 한 모듈에 대한 문서입니다.

- 대상 솔루션: `MidiPrac.sln`
- 작성 기준 커밋: `437bbba FEAT : 백엔드 추상화, SysEx 처리`

---

## 1. 솔루션 구성

| 프로젝트 | 종류 | 산출물 | 역할 |
|----------|------|--------|------|
| **MidiCore** | DynamicLibrary | `MidiCore.dll` + `MidiCore.lib` | 재사용 가능한 **파서 + 출력 백엔드** (DLL 본체) |
| **MidiPrac** | Application (Console) | `MidiPrac.exe` | DLL을 소비하는 **콘솔 MIDI 플레이어** |

```
MidiPrac.sln
├─ MidiCore  (DLL)  ──┐  Midi.cpp / MidiOut.cpp 를 컴파일,  MIDICORE_EXPORTS 정의
│                     │
└─ MidiPrac  (EXE) ───┘  ProjectReference 로 MidiCore 를 참조 → import lib 자동 링크
       └ MidiPlayer.cpp / MidiPrac.cpp  (재생 엔진 + 진입점, DLL에 포함되지 않음)
```

> **헤더 위치 주의**: 공용 헤더(`Midi.h`, `MidiOut.h`, `Util.h`, `MidiCoreApi.h`)와
> 소스(`Midi.cpp`, `MidiOut.cpp`)는 모두 물리적으로 `MidiPrac\` 폴더에 있습니다.
> MidiCore 프로젝트는 이를 `..\MidiPrac\*` 상대 경로로 참조해 컴파일합니다.

---

## 2. DLL 내보내기(export) 모델

내보내기는 `MidiCoreApi.h`의 `MIDICORE_API` 매크로로 제어합니다.

| 빌드 상황 | 정의할 매크로 | `MIDICORE_API` 결과 |
|-----------|---------------|---------------------|
| **MidiCore.dll 빌드** | `MIDICORE_EXPORTS` | `__declspec(dllexport)` |
| **DLL 소비(헤더 포함)** | (아무것도 정의 안 함) | `__declspec(dllimport)` |
| **정적 라이브러리/단일 프로젝트** | `MIDICORE_STATIC` | (빈 값) |

- MidiCore 프로젝트는 4개 구성 모두 `MIDICORE_EXPORTS`, `_USRDLL`을
  전처리기 정의에 포함합니다. (`MidiCore.vcxproj`)
- C++ **클래스 단위 export** 방식이라 `C4251`(STL 멤버), `C4275`(비 DLL 기반 클래스)
  경고는 `MidiCoreApi.h`에서 의도적으로 끕니다.

### ⚠️ 사용 제약 (C++ 클래스 export의 전제)
DLL과 그것을 쓰는 모든 모듈은 **동일 조건**으로 빌드해야 ABI가 맞습니다.
- **동일한 MSVC 툴셋** (현재 `v143`)
- **동일한 동적 CRT** (`/MD` 또는 `/MDd`)
- **Debug/Release 일치**, **플랫폼(x64/Win32) 일치**

---

## 3. DLL이 제공하는 기능 (한눈에 보기)

| 분류 | 핵심 타입/함수 | 헤더 | 설명 |
|------|----------------|------|------|
| **A. SMF 파싱** | `CMidi` | `Midi.h` | 파일을 열어 헤더·트랙·이벤트를 한 번에 파싱 |
| | `CHeader` / `CTrack` / `CChunk` | | 청크 단위 파싱(MThd/MTrk) |
| | `IEvent` / `CMidiEvent` / `CSysExEvent` / `CMetaEvent` | | 이벤트 3종(채널/SysEx/메타) |
| **B. 시간/시각화 데이터** | `TempoChange`, `CEventRecord` | `Midi.h` | 템포 맵, 절대 시각(ms)이 채워진 이벤트 |
| | `NoteSegment` + `CTrack::BuildNoteSegments()` | | 피아노롤용 노트 막대(시작/끝/음높이/세기) |
| **C. MIDI 출력 백엔드** | `IMidiOut` (인터페이스) | `MidiOut.h` | 모든 백엔드의 공통 출력 API |
| | `WinmmOut` | | Windows winmm(MS GS Wavetable 등) |
| | `FluidSynthOut` | | FluidSynth + 사운드폰트(.sf2) 렌더링 |
| | `ScanSoundFonts()` | | 작업/실행 폴더의 `.sf2` 자동 탐색 |
| **D. 바이너리 읽기 헬퍼** | `ReadVLQ` / `ReadBE16` / `ReadBE32` | `Util.h` | 헤더 전용 inline(※ DLL export 아님) |

> **DLL에 포함되지 않는 것**: 재생 엔진 `MidiPlayer`(일시정지·탐색·배속·조옮김·
> 채널 음소거 등)와 진입점 `main`은 **EXE 쪽(MidiPrac)** 에 있습니다.
> 즉 DLL은 "**파싱 + 송출 원시 기능**"만 제공하고, "재생 루프/조작"은 소비자 몫입니다.

---

## 4. A. SMF 파싱 API (`Midi.h`)

### 4.1 진입 클래스 — `CMidi`
```cpp
class MIDICORE_API CMidi {
public:
    explicit CMidi(const char* filePath);   // 생성과 동시에 파일 전체 파싱
    CMidi(const CMidi&) = delete;            // 복사 금지 (이동 전용 멤버 보유)

    const CHeader&        GetHeader() const;
    const vector<CTrack>& GetTracks() const;
};
```
- 생성자 하나로 **파일 열기 → 헤더 파싱 → 트랙 파싱 → 각 이벤트 절대 시각(ms) 계산**까지 끝납니다.
- 파싱 성공 여부는 `GetHeader().GetName()` 이 `"MThd"` 인지로 확인합니다(파일 없음/형식 오류 시 다름).
- 무거운 객체이므로 **복사 불가**(이동만). DLL의 암시적 복사 연산 생성 실패도 함께 막습니다.

### 4.2 헤더 — `CHeader`
```cpp
uint16_t GetFormat();          // 0=단일, 1=동시 다중, 2=독립 다중 트랙 (enum FileFormat)
uint16_t GetNumberOfTracks();  // MTrk 개수
uint16_t GetDivision();        // 시간 단위(PPQN 또는 SMPTE 인코딩)
bool     IsSmpte();            // division 최상위 비트: 1=SMPTE, 0=PPQN
double   GetSmpteFps();        // SMPTE 프레임레이트 (-29 → 29.97 NTSC 드롭)
uint8_t  GetTicksPerFrame();   // SMPTE 프레임당 틱 수
```

### 4.3 트랙 — `CTrack`
```cpp
class MIDICORE_API CTrack : public CChunk {
public:
    const vector<CEventRecord>& GetEvents() const;        // 시간순 이벤트
    const vector<TempoChange>&  GetTempoChanges() const;  // 이 트랙의 템포 변경
    string                      GetTrackName() const;     // 첫 트랙명(메타 0x03), 없으면 ""
    vector<NoteSegment>         BuildNoteSegments() const;// 피아노롤용 노트 막대
};
```
- 러닝 스테이터스(생략된 상태 바이트) 복원을 포함해 `MTrk` 본문을 완전 파싱합니다.

### 4.4 이벤트 3종
공통 인터페이스 `IEvent`(`GetType()`, `GetByteLength()`)를 상속합니다.

| 클래스 | `GetType()` | 주요 접근자 |
|--------|-------------|-------------|
| `CMidiEvent` | `MidiEvent` | `GetStatus()`(상위 4비트), `GetChannel()`, `GetNote()`, `GetVelocity()`, `GetData1/2()` |
| `CSysExEvent` | `SysExEvent` | `GetLeadByte()`(0xF0/0xF7), `GetData()`(원본 바이트) |
| `CMetaEvent` | `MetaEvent` | `GetMetaType()`, `GetTempo()`(µs/4분음표), `GetText()`, `GetData()`, `IsEndOfTrack/IsSetTempo/IsTrackName/IsTimeSignature/IsKeySignature()` |

채널 이벤트 종류는 `enum MidiEventStatus` 로 제공:
`NoteOff(0x80)`, `NoteOn(0x90)`, `PolyphonicKeyPressure(0xA0)`, `ControlChange(0xB0)`,
`ProgramChange(0xC0)`, `ChannelPressure(0xD0)`, `PitchBend(0xE0)`.

### 4.5 안전한 이벤트 접근 — `CEventRecord`
```cpp
struct CEventRecord {
    uint32_t absoluteTick;   // 트랙 시작부터 누적 틱
    double   absTimeMs;      // 절대 시각(ms) — 파싱 완료 후 채워짐
    unique_ptr<IEvent> event;

    const CMidiEvent*  AsMidi()  const;  // 타입이 아니면 nullptr
    const CSysExEvent* AsSysEx() const;
    const CMetaEvent*  AsMeta()  const;
};
```

---

## 5. B. 시각화/시간 데이터

- **`TempoChange { uint32_t absoluteTick; uint32_t tempoUs; }`** — 틱→시간 변환용 템포 맵 항목.
- **절대 시각 계산**: `CMidi`가 전 트랙 템포를 하나로 모아(PPQN) 또는 프레임 기반(SMPTE)으로
  각 이벤트 `absTimeMs`를 채웁니다. Format 1(템포는 트랙 0, 음표는 트랙 1+)도 올바르게 처리.
- **`NoteSegment { channel, note, velocity, startMs, endMs }`** —
  `CTrack::BuildNoteSegments()` 가 NoteOn↔NoteOff 를 짝지어 만든 **피아노롤 사각형 하나**.
  안 닫힌 음은 트랙 마지막 시각으로 마감하며 시작 시각순 정렬됩니다.
  → **GUI 피아노롤 시각화의 데이터 소스**.

---

## 6. C. MIDI 출력 백엔드 (`MidiOut.h`)

### 6.1 공통 인터페이스 — `IMidiOut`
```cpp
class MIDICORE_API IMidiOut {
public:
    virtual const char* Name() const = 0;

    virtual void NoteOn(int ch, int key, int vel) = 0;
    virtual void NoteOff(int ch, int key) = 0;
    virtual void ControlChange(int ch, int num, int val) = 0;
    virtual void ProgramChange(int ch, int prog) = 0;
    virtual void PitchBend(int ch, int value) = 0;       // 14비트(0~16383), 중앙 8192
    virtual void ChannelPressure(int ch, int val) = 0;
    virtual void KeyPressure(int ch, int key, int val) = 0;
    virtual void SysEx(const uint8_t* msg, size_t len) = 0;  // 0xF0..0xF7 완전한 메시지

    virtual void NotesOff(int ch) = 0;   // CC123 All Notes Off
    virtual void SoundsOff(int ch) = 0;  // CC120 All Sound Off
    void AllNotesOff();                  // 16채널 일괄 (비가상 헬퍼)
    void AllSoundOff();
    virtual void SetVolume(int percent) = 0;   // 0~100
};
```

### 6.2 `WinmmOut` — Windows winmm 백엔드
```cpp
static std::unique_ptr<WinmmOut> Create(int deviceIndex);  // <0 = MIDI_MAPPER(시스템 기본)
static void                       ListDevices();           // 장치 목록 콘솔 출력
static std::vector<std::string>   DeviceNames();           // 장치 이름 목록(선택 메뉴용)
```
- 별도 음원이 없으면 보통 "Microsoft GS Wavetable Synth"로 소리가 납니다.
- `winmm.lib`는 `MidiOut.h`의 `#pragma comment(lib, "winmm.lib")`로 자동 링크.
- 마스터 볼륨은 장치가 `MIDICAPS_VOLUME`를 지원할 때만 적용됩니다.

### 6.3 `FluidSynthOut` — 사운드폰트 렌더링 백엔드
```cpp
static std::unique_ptr<FluidSynthOut> Create(const std::string& soundfontPath);
```
- `libfluidsynth-3.dll`을 **런타임 동적 로드**(`LoadLibrary`+`GetProcAddress`)합니다.
  → import lib/헤더 없이 빌드되며, DLL/사운드폰트가 없으면 `nullptr`을 돌려주어
  소비자가 winmm으로 폴백할 수 있습니다.
- 오디오 드라이버는 기본 → `sdl3/sdl2/wasapi/dsound/waveout` 순으로 시도.
- **런타임 의존 DLL**(EXE/작업 폴더에 동봉 필요):
  `libfluidsynth-3.dll`, `SDL3.dll`, `sndfile.dll` + 사운드폰트(`*.sf2`, 예: `GeneralUser-GS.sf2`).

### 6.4 사운드폰트 탐색 — `ScanSoundFonts()`
```cpp
MIDICORE_API std::vector<std::string> ScanSoundFonts();
```
작업 폴더 → 실행 파일 폴더 → 그 상위(`..\..`) 에서 `*.sf2` 를 찾아 **중복 제거**한 경로 목록 반환.

---

## 7. D. 바이너리 읽기 헬퍼 (`Util.h`) — 참고

`ReadVLQ`, `ReadBE16`, `ReadBE32` 는 **헤더 전용 inline 함수**입니다.
`MIDICORE_API`가 붙지 않아 DLL 심볼로 export되지 않으며, 헤더를 포함한 쪽에서 그대로 인라인됩니다.
파서 내부 구현 세부이므로 일반 소비자가 직접 호출할 일은 드뭅니다.

---

## 8. 소비(consume) 방법

### 8.1 같은 솔루션 내 (현재 MidiPrac 방식 — 권장)
1. 소비 프로젝트에 **ProjectReference** 로 `MidiCore.vcxproj` 추가
   → `MidiCore.lib`(import lib)가 자동 링크됨.
2. 공용 헤더(`Midi.h`/`MidiOut.h`)를 `#include`. (`MIDICORE_EXPORTS`는 **정의하지 않음** → dllimport)
3. 실행 시 `MidiCore.dll`(+ FluidSynth 사용 시 `libfluidsynth-3.dll`, `SDL3.dll`, `sndfile.dll`)을
   EXE 옆에 둡니다.

### 8.2 외부 프로젝트
- 헤더 4종(`Midi.h`, `MidiOut.h`, `Util.h`, `MidiCoreApi.h`)과 `MidiCore.lib`/`MidiCore.dll` 배포.
- 빌드 시 동일 툴셋/CRT/구성(2장 제약) 준수.

### 8.3 최소 사용 예
```cpp
#include "Midi.h"
#include "MidiOut.h"

CMidi midi("song.mid");                          // 파싱
if (std::string(midi.GetHeader().GetName()) != "MThd") return;   // 유효성

// 출력 백엔드: 사운드폰트 우선, 실패 시 winmm 폴백
std::unique_ptr<IMidiOut> out;
for (auto& sf : ScanSoundFonts())
    if ((out = FluidSynthOut::Create(sf))) break;
if (!out) out = WinmmOut::Create(-1);            // 시스템 기본 장치

// 전 트랙 채널 이벤트를 시각순으로 모아 송출하면 재생이 된다 (타이밍 루프는 소비자 구현)
for (auto& track : midi.GetTracks())
    for (auto& rec : track.GetEvents())
        if (const CMidiEvent* e = rec.AsMidi())
            if (e->GetStatus() == NoteOn)
                out->NoteOn(e->GetChannel(), e->GetNote(), e->GetVelocity());

// 피아노롤 시각화용 데이터
for (auto& track : midi.GetTracks())
    std::vector<NoteSegment> bars = track.BuildNoteSegments();
```
> 실제 재생에는 `absTimeMs` 기준 타이밍 루프, 일시정지/탐색/조옮김, SysEx 재조립 등이 필요한데,
> 그 구현 예시는 EXE 쪽 `MidiPlayer.cpp`(`MidiPlayer` 클래스)를 참고하세요.

---

## 9. 한계 / 메모

- 여러 패킷으로 쪼개진 SysEx의 **재조립은 미지원**(실파일에선 드묾).
- `CMidi`는 파일 경로(`const char*`)만 받습니다. 메모리 버퍼/스트림 입력은 없음.
- 파싱 실패가 예외가 아니라 "빈 헤더"로 표현되므로, 소비자가 `GetName()=="MThd"`로 확인해야 합니다.
- 출력 백엔드는 Windows 전용(`winmm` / `FluidSynth` 동적 로드)입니다.
- 재사용성을 더 높이려면 `MidiPlayer`(재생 엔진)도 DLL로 옮기는 것을 고려할 수 있습니다(현재는 EXE 소속).
