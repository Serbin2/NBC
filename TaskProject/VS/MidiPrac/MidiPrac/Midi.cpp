#include "Midi.h"

uint8_t CMidiEvent::runningStatus = 0;

CMidiEvent::CMidiEvent(const char* filePath, int addr)
{
	FILE* fp;
	int err = fopen_s(&fp, filePath, "rb");
	if (err != 0 || !fp)
	{	//	file open failed
		fprintf(stderr, "파일을 열지 못했습니다.\n");
		return;
	}
	fseek(fp, addr, SEEK_SET);

	m_iStatus = getc(fp);
	if (m_iStatus & 0x80)	//	running state인지 확인
	{	
		runningStatus = m_iStatus;
		m_iByteLength = 1;
	}
	else
	{	//	running state
		m_iStatus = runningStatus;
		fseek(fp, -1, SEEK_CUR);
	}

	switch (m_iStatus & 0xF0)
	{
	case 0xC0:	//	programChange
	case 0xD0:	//	ChannelPressure
		m_iData = getc(fp);
		m_iByteLength += 1;
		break;
	case 0x80:	//	NoteOff
	case 0x90:	//	NoteOn
	case 0xA0:	//	PolyphonicKeyPressure
	case 0xB0:	//	ControlChange
	case 0xE0:	//	PitchBend
		m_iData = getc(fp) << 8 | getc(fp);
		m_iByteLength += 2;
		break;
	}

	fclose(fp);
}

EventType CMidiEvent::GetType() const
{
	return MidiEvent;
}

MidiEventStatus CMidiEvent::GetStatus() const
{
	return MidiEventStatus(m_iStatus | 0xF0);
}

uint8_t CMidiEvent::GetChannel() const
{
	return m_iStatus | 0x0F;
}

uint8_t CMidiEvent::GetNote() const
{
	if(GetStatus() == NoteOff || GetStatus() == NoteOn)
}

CChunk::CChunk(const char* filePath, int addr) :
	m_sName(nullptr)
{
	FILE* fp;
	int err = fopen_s(&fp, filePath, "rb");
	if (err != 0 || !fp)
	{	//	file open failed
		fprintf(stderr, "파일을 열지 못했습니다.\n");
		return;
	}
	fseek(fp, addr, SEEK_SET);

	m_sName = new char[5];
	fread(m_sName, 1, 4, fp);
	m_sName[4] = 0;

	m_iLength = ReadBE32(fp);
	m_iByteLength = m_iLength + 8;

	fclose(fp);
}

CChunk::~CChunk()
{
	if (m_sName != nullptr)	delete[] m_sName;
}

int CChunk::GetByteLength()
{
	return m_iByteLength;
}

CTrack::CTrack(const char* filePath, int addr):
	CChunk(filePath, addr)
{
	addr += 8;
	int readedBytes = 0;

	while (readedBytes < m_iLength) 
	{
		CEvent event{ filePath, addr };
		events.push_back(event);
		addr += event.getByteLength();
		bytesRead += event.getByteLength();
	}
}

const deque<CEvent>& CTrack::getEvents() const
{
	return m_aEvents;
}


CHeader::CHeader(const char* filePath) :
	CChunk(filePath, 0) {

	FILE* fp;
	int err = fopen_s(&fp, filePath, "rb");
	if (err != 0 || !fp)
	{	//	file open failed
		fprintf(stderr, "파일을 열지 못했습니다.\n");
		return;
	}

	fseek(fp, 8, SEEK_SET);
	m_iFormat = ReadBE16(fp);
	m_iTracks = ReadBE16(fp);
	m_iDivision = ReadBE16(fp);

	fclose(fp);
}

uint16_t CHeader::GetNumberOfTracks()
{
	return m_iTracks;
}

CMidi::CMidi(const char* filePath) : m_cHeader(filePath) {
	int addr = m_cHeader.GetByteLength();

	for (int i{ 0 }; i < m_cHeader.GetNumberOfTracks(); ++i) {
		CTrack track{ filePath, addr };
		m_aTracks.push_back(track);
		addr += track.GetByteLength();
	}
}


const CHeader& CMidi::getHeader() const
{
	return m_cHeader;
}


const deque<CTrack>& CMidi::getTracks() const 
{
	return m_aTracks;
}

