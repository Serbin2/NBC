#pragma once

#include "framework.h"
#include <mmsystem.h>
#include <string>
#include <vector>

#pragma comment(lib, "winmm.lib")

using namespace std;

struct MidiHeader
{
	//	파일의 포맷
	//	0 : 파일이 하나의 multi-channel track을 가진다.
	//	1 : 파일이 하나 이상의 simultaneous track을 가진다.
	//	2 : 파일이 하나 이상의 sequentially independent single-track 패턴을 가진다.
	uint32_t length;
	uint16_t format;
	//	트랙의 수
	//	포맷이 0이라면 트랙의 수는 반드시 1이다
	uint16_t tracks;
	//	Tick 해상도
	uint16_t division = 480;
};

/*
MIDI 파일은 반드시 템포와 박자표를 지정해야 한다. 
기본값은 박자는 4/4, 템포는 120비트이고, 이는 트랙별로 저장된다. 
형식 0, 1의 경우 항상 박자와 템포가 같기 때문에 첫 트랙에 박자표와 템포를 저장하는 메타 이벤트를 포함시킨다. 
트랙별로 템포, 박자표가 저장되기 때문에 형식 2인 MIDI 파일의 경우 템포가 달라지는 Chunk마다 박자, 템포를 다르게 지정할 수 있다.
*/


typedef enum MidiEventStatus
{
	None = 0,

	//	Channel Event 0x80~ 0xEF
	//	상위 바이트 = 이벤트 종류, 하위 바이트 = 채널 번호
	//	Status는 항상 0x80 이상이므로 그 이하의 값을 받았으면 running status로
	NoteOff	= 0b10000000,	//	data1 : 0kkkkkkk NoteNumber, data2 : 0vvvvvvv velocity
	NoteOn	= 0b10010000,	//	data1 : 0kkkkkkk NoteNumber, data2 : 0vvvvvvv velocity  *velocity = 0 은 NoteOff와 같습니다
	PolyphonicKeyPressure = 0b10100000,	//	data1 : pitch		data2 : pressure	//	AfterTouch	키별 압력
	ControlChange = 0b10110000,	//	data1 : controller, data2 : value
	//	대표적인 controller 목록 : 
	//	1 : modulation		7 : volume		10 : pan		64 : sustain pedal

	ProgramChange = 0b11000000,	//	악기 변경	data1 : program
	ChannelPressure = 0b11010000,	//	data1 : pressure		//	채널별 압력
	PitchBend = 0b11100000,		//	data1 : LSB, data2 : MSB	,	14bit 값입니다(각 7bit씩 읽음)

	SystemExclusive = 0b11110000,	//	특정 장치용 데이터입니다	-	대부분 skip
	EndofSysEx = 0b11110111,
	MetaEvent = 0b11111111,	//	type length data
	//0x2F	End of Track
	//0x51	Tempo
	//0x03	Track Name
	//0x58	Time Signature
	//0x59	Key Signature

}eStatus;

struct MidiEvent
{
	double absTime;
	uint32_t time = 0;
	uint8_t type = 0;	//	Event | channel
	eStatus eEvent = None;
	uint8_t channel = 0;

	uint8_t data1 = 0;
	uint8_t data2 = 0;
};

struct MidiTrack
{
	uint16_t trackNumber = 0;
	uint32_t length = 0;
	vector<MidiEvent> events;
	uint32_t tempo = 500000;
};

class CMidi
{
public:
	CMidi();
	~CMidi();

	void FileOpen(string fileName);
	vector<MidiTrack> GetTrack() { return tracks; };
	MidiHeader GetHeader() { return m_sMidiHeader; };


protected:
	uint16_t ReadBE16(FILE* fp);	//	빅엔디안 2바이트 읽기
	uint32_t ReadBE32(FILE* fp);	//	빅엔디안 4바이트 읽기
	void ParseTracks(FILE* fp, int trackCount);
	uint32_t GetLastVLQlen();
	uint32_t ReadVLQ(FILE* fp);		//	이벤트 읽기
	MidiTrack ParseEvents(FILE* fp, uint32_t trackLength, uint16_t trackNumber);

private:

	double tickToMs;
	uint32_t LastVLQlen;
	MidiHeader m_sMidiHeader;
	vector<MidiTrack> tracks;
};