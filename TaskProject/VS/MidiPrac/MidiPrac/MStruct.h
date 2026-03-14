#pragma once

#include "framework.h"
#include <mmsystem.h>
#include <string>
#include <vector>

using namespace std;

struct MidiHeader
{
	//	파일의 포맷
	//	0 : 파일이 하나의 multi-channel track을 가진다.
	//	1 : 파일이 하나 이상의 simultaneous track을 가진다.
	//	2 : 파일이 하나 이상의 sequentially independent single-track 패턴을 가진다.
	uint16_t format;
	//	트랙의 수
	//	포맷이 0이라면 트랙의 수는 반드시 1이다
	uint16_t tracks;
	//	Tick 해상도
	uint16_t division;
};

/*
MIDI 파일은 반드시 템포와 박자표를 지정해야 한다. 
기본값은 박자는 4/4, 템포는 120비트이고, 이는 트랙별로 저장된다. 
형식 0, 1의 경우 항상 박자와 템포가 같기 때문에 첫 트랙에 박자표와 템포를 저장하는 메타 이벤트를 포함시킨다. 
트랙별로 템포, 박자표가 저장되기 때문에 형식 2인 MIDI 파일의 경우 템포가 달라지는 Chunk마다 박자, 템포를 다르게 지정할 수 있다.
*/

struct MidiEvent
{
	uint32_t time;
	uint8_t type;

	uint8_t data1;
	uint8_t data2;
};

class CMidi
{
public:


	void FileOpen(string fileName);

protected:
	uint16_t ReadBE16(FILE* fp);	//	빅엔디안 2바이트 읽기
	uint32_t ReadBE32(FILE* fp);	//	빅엔디안 4바이트 읽기
	void ParseTracks(FILE* fp, int trackCount);
	uint32_t ReadVLQ(FILE* fp);		//	이벤트 읽기
	void ParseEvents(FILE* fp, uint32_t trackLength);

private:

	FILE* m_pCurrentFile;

	MidiHeader m_sMidiHeader;
	vector<MidiEvent> events;
};