#pragma once
#include "MidiCoreApi.h"   // MIDICORE_API (dllexport/dllimport)
#include "Util.h"          // CByteReader (메모리 버퍼 리더) + 빅엔디안/VLQ 헬퍼
#include <vector>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <string>

// ──────────────────────────────────────────────────────────────
// 표준 MIDI 파일(SMF) 자료구조 및 파서 선언
//
// 파일 전체 구조:
//   [Header Chunk "MThd"]  [Track Chunk "MTrk"]  [Track Chunk "MTrk"] ...
//
//   모든 청크 = 4바이트 이름 + 4바이트 길이(빅엔디안) + 본문(길이만큼)
//   트랙 본문 = "델타타임(VLQ) + 이벤트"의 반복, EndOfTrack 메타로 종료
//
//   이벤트는 세 종류:
//     - 채널(MIDI) 이벤트 : NoteOn/NoteOff/ControlChange 등 실제 연주
//     - SysEx 이벤트      : 장치 고유 메시지 (보관해 두었다가 재생 시 그대로 전달)
//     - 메타 이벤트       : 템포/트랙명/트랙끝 등 연주 외 정보
//
// 입력은 메모리 버퍼(CByteReader)로 받는다 — stdio(FILE*)에 의존하지 않으므로
// 파일/언리얼 에셋/네트워크 등 어떤 출처의 바이트 배열이든 파싱할 수 있다.
// ──────────────────────────────────────────────────────────────

// 헤더 format 필드 값 — 트랙 구성 방식
enum FileFormat
{
	SingleTrack = 0,               // 단일 트랙
	MultipleTrack = 1,             // 여러 트랙을 동시에 재생(트랙 0에 템포 등 메타가 모임)
	IndependentMultipleTrack = 2,  // 여러 트랙이 서로 독립적/순차적
};

// 이벤트 대분류
enum EventType
{
	MidiEvent = 0,   // 채널 음악 이벤트
	SysExEvent = 1,  // 시스템 익스클루시브
	MetaEvent = 2,   // 메타 이벤트
};

// 채널 이벤트 상태 바이트의 상위 4비트(이벤트 종류). 하위 4비트는 채널 번호(0~15).
enum MidiEventStatus
{
	NoteOff              = 0x80,   // data1=음높이(note), data2=세기(velocity)
	NoteOn               = 0x90,   // data1=음높이, data2=세기 (velocity 0 이면 NoteOff와 동일)
	PolyphonicKeyPressure = 0xA0,  // 건반별 애프터터치
	ControlChange        = 0xB0,   // data1=컨트롤러 번호, data2=값 (예: 7=볼륨, 64=서스테인)
	ProgramChange        = 0xC0,   // data1=악기 번호  ※데이터 1바이트
	ChannelPressure      = 0xD0,   // 채널 전체 애프터터치  ※데이터 1바이트
	PitchBend            = 0xE0,   // data1=LSB, data2=MSB (합쳐서 14비트 피치 휠)
};

// 모든 이벤트의 공통 인터페이스.
// m_iByteLength: 상태/판별 바이트 이후 이 이벤트가 파일에서 소비한 데이터 바이트 수.
//                트랙 잔여 길이를 줄여 나가는 데 쓰인다.
class MIDICORE_API IEvent
{
public:
	virtual ~IEvent() = default;
	virtual EventType GetType() const = 0;
	uint32_t GetByteLength() const { return m_iByteLength; }
protected:
	uint32_t m_iByteLength = 0;
};

// 채널(MIDI) 이벤트 — 실제 연주 데이터.
// 상태 바이트 1개 + 데이터 바이트 1~2개로 구성된다.
class MIDICORE_API CMidiEvent : public IEvent
{
public:
	// statusByte: 호출자가 이미 읽어 둔 상태 바이트(러닝 스테이터스 복원 포함).
	//             생성자 안에서 종류에 따라 데이터 바이트를 마저 읽는다.
	CMidiEvent(CByteReader& reader, uint8_t statusByte);
	EventType GetType() const override { return MidiEvent; }

	MidiEventStatus GetStatus() const { return (MidiEventStatus)(m_iStatus & 0xF0); } // 상위 4비트=종류
	uint8_t GetChannel() const   { return m_iStatus & 0x0F; }   // 하위 4비트=채널
	uint8_t GetStatusByte() const { return m_iStatus; }
	uint8_t GetNote() const      { return m_iData1; }           // NoteOn/Off에서의 음높이
	uint8_t GetVelocity() const  { return m_iData2; }           // NoteOn/Off에서의 세기
	uint8_t GetData1() const     { return m_iData1; }
	uint8_t GetData2() const     { return m_iData2; }

private:
	uint8_t m_iStatus;  // 상태 바이트(종류<<4 | 채널)
	uint8_t m_iData1;
	uint8_t m_iData2;
};

// SysEx 이벤트 — 장치 고유 메시지 (GM/GS/XG 리셋, 마스터 볼륨 같은 초기화가 주로 실려 온다).
// 데이터를 보관해 두었다가 재생 시 출력 장치로 그대로 전달한다.
//  - 0xF0 시작: 일반 SysEx. 데이터 끝에 보통 종료 바이트(0xF7)가 포함된다.
//  - 0xF7 시작: 이스케이프(연속 패킷 등의 원시 바이트). 프레이밍 없이 그대로 보낸다.
//  ※ 여러 패킷으로 쪼개진 SysEx의 재조립은 지원하지 않는다(실제 파일에서는 드묾).
class MIDICORE_API CSysExEvent : public IEvent
{
public:
	CSysExEvent(CByteReader& reader, uint8_t leadByte);  // 0xF0/0xF7 은 호출자가 이미 소비한 상태로 들어온다
	EventType GetType() const override { return SysExEvent; }

	uint8_t GetLeadByte() const { return m_iLeadByte; }               // 0xF0 또는 0xF7
	const std::vector<uint8_t>& GetData() const { return m_aData; }   // 길이 필드 뒤의 원본 데이터

private:
	uint8_t m_iLeadByte = 0xF0;
	std::vector<uint8_t> m_aData;
};

// 메타 이벤트 — 연주 외 정보(템포/트랙명/박자표/가사 등).
// 템포(0x51)는 값을 따로 뽑아 두고, 그 외 모든 메타의 본문도 원본 바이트로 보관한다.
// → 시각화 단계에서 트랙명·박자표·조표·가사 등을 자유롭게 꺼내 쓸 수 있다.
//
// 주요 메타 타입: 0x01 텍스트, 0x02 저작권, 0x03 트랙명, 0x04 악기명,
//                0x05 가사, 0x06 마커, 0x2F 트랙끝, 0x51 템포,
//                0x58 박자표, 0x59 조표
class MIDICORE_API CMetaEvent : public IEvent
{
public:
	CMetaEvent(CByteReader& reader);   // 0xFF 는 호출자가 이미 소비한 상태로 들어온다
	EventType GetType() const override { return MetaEvent; }

	uint8_t  GetMetaType()   const { return m_iMetaType; }
	uint32_t GetTempo()      const { return m_iTempo; }            // 박자당 마이크로초
	const std::vector<uint8_t>& GetData() const { return m_aData; }     // 메타 본문 원본 바이트
	std::string GetText()    const { return std::string(m_aData.begin(), m_aData.end()); } // 텍스트류(0x01~0x07)

	bool IsEndOfTrack()      const { return m_iMetaType == 0x2F; } // 트랙 종료 표시
	bool IsSetTempo()        const { return m_iMetaType == 0x51; } // 템포 변경
	bool IsTrackName()       const { return m_iMetaType == 0x03; } // 트랙 이름
	bool IsTimeSignature()   const { return m_iMetaType == 0x58; } // 박자표
	bool IsKeySignature()    const { return m_iMetaType == 0x59; } // 조표

private:
	uint8_t  m_iMetaType = 0;
	uint32_t m_iTempo    = 0;
	std::vector<uint8_t> m_aData;   // 메타 데이터부(타입/길이 필드 제외)의 원본
};

// 템포 변경 지점 — (틱 위치, 그 시점부터의 템포).
// 틱→시간 변환에 쓰는 "템포 맵"의 한 항목.
struct TempoChange
{
	uint32_t absoluteTick;
	uint32_t tempoUs;     // 4분음표 하나당 마이크로초 (예: 500000 = 120 BPM)
};

// 파싱된 이벤트 1개 + 시간 정보.
struct CEventRecord
{
	uint32_t absoluteTick = 0;   // 트랙 시작부터 누적된 틱 위치
	double   absTimeMs    = 0.0; // 틱을 밀리초로 변환한 절대 시각(나중에 채워짐)
	std::unique_ptr<IEvent>  event;

	bool IsMidiEvent() const { return event && event->GetType() == ::MidiEvent; }
	const CMidiEvent* AsMidi() const
	{
		return IsMidiEvent() ? static_cast<const CMidiEvent*>(event.get()) : nullptr;
	}

	bool IsSysEx() const { return event && event->GetType() == ::SysExEvent; }
	const CSysExEvent* AsSysEx() const
	{
		return IsSysEx() ? static_cast<const CSysExEvent*>(event.get()) : nullptr;
	}

	bool IsMeta() const { return event && event->GetType() == ::MetaEvent; }
	const CMetaEvent* AsMeta() const
	{
		return IsMeta() ? static_cast<const CMetaEvent*>(event.get()) : nullptr;
	}
};

// 청크 공통 헤더("이름 4바이트 + 길이 4바이트")를 담는 기반 클래스.
class MIDICORE_API CChunk
{
public:
	CChunk() = default;
	virtual ~CChunk() = default;
	uint32_t    GetByteLength() const { return m_iByteLength; }
	const char* GetName()       const { return m_sName; }
protected:
	void ParseChunkHeader(CByteReader& reader);   // 이름(4) + 길이(4)를 읽는다
	char     m_sName[5]    = {};       // 청크 이름 "MThd"/"MTrk" + 널 종단
	uint32_t m_iLength     = 0;        // 본문 길이
	uint32_t m_iByteLength = 0;        // 청크 전체 크기 = m_iLength + 8(헤더)
};

// 헤더 청크 "MThd" — 파일 전체의 포맷 정보.
class MIDICORE_API CHeader : public CChunk
{
public:
	CHeader() = default;
	void Parse(CByteReader& reader);

	uint16_t GetFormat()         const { return m_iFormat; }
	uint16_t GetNumberOfTracks() const { return m_iTracks; }
	uint16_t GetDivision()       const { return m_iDivision; }

	// division 최상위 비트: 0 = PPQN(박자 기반), 1 = SMPTE(시간/프레임 기반)
	bool IsSmpte() const { return (m_iDivision & 0x8000) != 0; }
	// SMPTE 프레임 레이트. 상위 바이트에 -24/-25/-29/-30 (2의 보수)으로 저장되며,
	// -29 는 NTSC 드롭 프레임을 뜻하므로 실제 값은 29.97fps 다.
	double GetSmpteFps() const
	{
		int fps = -(int8_t)(m_iDivision >> 8);
		return fps == 29 ? 29.97 : (double)fps;
	}
	// SMPTE 프레임 하나당 틱 수(하위 바이트)
	uint8_t GetTicksPerFrame() const { return (uint8_t)(m_iDivision & 0xFF); }

private:
	uint16_t m_iFormat   = 0;     // FileFormat 값(0/1/2)
	uint16_t m_iTracks   = 0;     // 트랙 청크 개수
	// 시간 단위 정의. 두 방식이 한 필드에 인코딩된다:
	//  - 최상위 비트 0: 하위 15비트 = 4분음표당 틱 수(PPQN) → 템포 이벤트와 조합해 시간 계산
	//  - 최상위 비트 1: 상위 바이트 = -프레임레이트, 하위 바이트 = 프레임당 틱 수(SMPTE)
	uint16_t m_iDivision = 480;
};

// 시각화용 노트 막대 — NoteOn↔NoteOff 를 짝지어 만든 "하나의 음".
// (피아노롤에서 사각형 하나에 해당: 시작/끝 시각 + 음높이 + 채널 + 세기)
struct NoteSegment
{
	uint8_t channel;     // 0~15
	uint8_t note;        // 음높이 0~127
	uint8_t velocity;    // NoteOn 세기 (색/투명도 등에 활용)
	double  startMs;     // 시작 시각
	double  endMs;       // 끝 시각 (NoteOff 시점, 못 닫히면 트랙 마지막 시각)
};

// 트랙 청크 "MTrk" — 시간순 이벤트들의 모음.
class MIDICORE_API CTrack : public CChunk
{
public:
	CTrack() = default;
	CTrack(CTrack&&) = default;             // 이벤트가 unique_ptr이므로 이동만 허용
	CTrack& operator=(CTrack&&) = default;

	void Parse(CByteReader& reader);
	std::vector<CEventRecord>&        GetEvents()       { return m_aEvents; }
	const std::vector<CEventRecord>&  GetEvents()       const { return m_aEvents; }
	const std::vector<TempoChange>&   GetTempoChanges() const { return m_aTempoChanges; }

	// 시각화 보조 ──────────────────────────────────────
	// 이 트랙의 첫 트랙명(0x03) 메타를 돌려준다. 없으면 빈 문자열.
	std::string GetTrackName() const;
	// NoteOn/NoteOff 를 짝지어 피아노롤용 노트 막대 목록으로 만든다.
	// (absTimeMs 가 채워진 뒤 = 파싱 완료 후에 호출해야 한다)
	std::vector<NoteSegment> BuildNoteSegments() const;

private:
	std::vector<CEventRecord> m_aEvents;        // 이 트랙의 연주/SysEx/메타 이벤트들
	std::vector<TempoChange>  m_aTempoChanges;  // 이 트랙에서 발견된 템포 변경들
};

// MIDI 파일 전체 — 헤더 + 트랙들을 파싱하고, 각 이벤트의 절대 시각을 계산한다.
class MIDICORE_API CMidi
{
public:
	explicit CMidi(const char* filePath);          // 파일을 통째로 읽어 파싱(편의용, 데스크톱/콘솔)
	CMidi(const uint8_t* data, size_t size);       // 메모리 버퍼에서 직접 파싱(언리얼 에셋/pak 등)

	// 트랙/이벤트를 통째로 담는 무거운 객체이고 이동 전용 멤버(CTrack)를 가지므로 복사 금지.
	// (dllexport가 암시적 복사 연산을 강제 생성하다 CTrack 복사 불가로 실패하는 것도 막는다)
	CMidi(const CMidi&) = delete;
	CMidi& operator=(const CMidi&) = delete;

	const CHeader&             GetHeader() const { return m_cHeader; }
	const std::vector<CTrack>& GetTracks() const { return m_aTracks; }

private:
	void ParseBuffer(const uint8_t* data, size_t size);   // 헤더 → 트랙들 → 절대 시각 계산
	void ComputeAbsTimes();   // 전 트랙의 템포를 모아 각 이벤트의 absTimeMs를 채운다
	// 틱 위치를 밀리초로 변환. tempoMap은 틱 오름차순으로 정렬되어 있어야 한다.
	static double TicksToMs(uint32_t absTick, uint16_t division,
	                         const std::vector<TempoChange>& tempoMap);

	CHeader             m_cHeader;
	std::vector<CTrack> m_aTracks;
};
