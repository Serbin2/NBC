#pragma once
#include "Util.h"

using namespace std;

enum FileFormat
{
	SingleTrack = 0,
	MultipleTrack = 1,
	IndependentlyMultupleTrack = 2,
};

enum EventType
{
	MidiEvent = 0,
	SysExEvent = 1,
	MetaEvent = 2,
};

enum MidiEventStatus
{
	NoteOff = 0x80,
	NoteOn = 0x90,
	PolyphonicKeyPressure = 0xA0,
	ControlChange = 0xB0,
	ProgramChange = 0xC0,
	ChannelPressure = 0xD0,
	PitchBend = 0xE0,
};

enum SysExEventStatus
{
	SOX = 0xF0,	//	start of SysExEvent
	EOX = 0xF7,	//	end of SysExEvent
};

enum MetaEventStatus
{
	SequenceNumber = 0x00,
	TextEvent = 0x01, 
	CopyrightNotice = 0x02,
	SequenceName = 0x03,
	InstrumentName = 0x04, 
	Lyric = 0x05,
	Marker = 0x06,
	CuePoint = 0x07, 
	MidiChannelPrefix = 0x20,
	EndOfTrack = 0x2F,
	SetTempo = 0x51,
	SMTPEOffset = 0x54,
	TimeSignature = 0x58,
	KeySignature = 0x59,
	SequencerSpecific = 0x7F  
} ;

class IEvent
{	//	이벤트의 기본 인터페이스
public:

	virtual ~IEvent() = 0;

	virtual EventType GetType() const = 0;

	uint8_t GetByteLength() const {	return m_iByteLength; }

protected:

	uint8_t m_iByteLength;
};

class CMidiEvent : public IEvent
{
public:
	CMidiEvent(const char* filePath, int addr);
	virtual ~CMidiEvent() {};

	EventType GetType() const override;
	MidiEventStatus GetStatus() const;
	uint8_t GetChannel() const;
	uint8_t GetNote() const;
	uint8_t GetVelocity() const;
	uint8_t GetData() const;

protected:
	static uint8_t runningStatus;

	uint8_t m_iStatus;	//	state + channel
	uint16_t m_iData;
};

class CSysExEvent : public IEvent
{
public:
	CSysExEvent(const char* filePath, int addr);
	virtual ~CSysExEvent() {};

	EventType GetType() const override;
	SysExEventStatus GetStatus() const;
	uint8_t GetLength() const;
	uint8_t* GetData() const;

protected:
	uint8_t m_iStatus;
	uint8_t m_iLength;
	uint8_t* m_aData;
};

class CMetaEvent : public IEvent
{
public:
	CMetaEvent(const char* filePath, int addr);
	virtual ~CMetaEvent() {};

protected:

};

class CEvent
{
public:
	CEvent(const char* filePath, int addr);


protected:

};

class CChunk
{
public:
	CChunk(const char* filePath, int addr);
	virtual ~CChunk();

	int GetByteLength();

protected:
	char* m_sName;
	uint32_t m_iLength;
	int m_iByteLength;
};

class CTrack : public CChunk
{
public:
	CTrack(const char* filePath, int addr);

	[[nodiscard]] const deque<CEvent>& getEvents() const;

private:
	deque<CEvent> m_aEvents;
};

class CHeader : public CChunk
{
public:
	explicit CHeader(const char* filePath);

	uint16_t GetNumberOfTracks();

private:
	uint32_t m_iLength;
	uint16_t m_iFormat;
	uint16_t m_iTracks;
	uint16_t m_iDivision;
};

class CMidi
{
public:
	explicit CMidi(const char* filePath);

	[[nodiscard]] const CHeader& getHeader() const;
	[[nodiscard]] const deque<CTrack>& getTracks() const;
private:
	
	CHeader m_cHeader;
	deque<CTrack> m_aTracks;
};


