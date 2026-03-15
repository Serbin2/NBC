#include "MStruct.h"




void CMidi::FileOpen(string fileName)
{
	//	파일 열기
	FILE* fp = fopen(fileName.c_str(), "rb");

	if (!fp)
	{//	파일 열기 실패
		return;
	}

	//	헤더 읽기
	//"MThd"	(4byte)
	//length	(4byte)	//	헤더의 크기
	//format	(2byte)
	//tracks	(2byte)
	//division	(2byte)
	char chunk[4];
	fread(chunk, 1, 4, fp); // MThd
	if (!strncmp(chunk, "Mthd", 4))
	{
		fclose(fp);
		return;
	}

	uint32_t length = ReadBE32(fp);

	MidiHeader header;

	header.format = ReadBE16(fp);
	header.tracks = ReadBE16(fp);
	header.division = ReadBE16(fp);

	m_sMidiHeader = header;


	//	Track Chunk
	//"MTrk"	(4byte)
	//length	(4byte)
	//event data
	
	char trackID[4];
	fread(trackID, 1, 4, fp);

	uint32_t length = ReadBE32(fp);

	//	MIDI event
	//delta_time	(vlq)
	//event			(0xF?)



	fclose(fp);
	return;
}

uint16_t CMidi::ReadBE16(FILE* fp)
{
	uint8_t b1 = fgetc(fp);
	uint8_t b2 = fgetc(fp);

	return (b1 << 8) | b2;
}

uint32_t CMidi::ReadBE32(FILE* fp)
{
	uint8_t b1 = fgetc(fp);
	uint8_t b2 = fgetc(fp);
	uint8_t b3 = fgetc(fp);
	uint8_t b4 = fgetc(fp);

	return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

void CMidi::ParseTracks(FILE* fp, int trackCount)
{
	for (int i = 0; i < trackCount; i++)
	{
		char id[4];
		fread(id, 1, 4, fp);	//	MTrk

		uint32_t length = ReadBE32(fp);

		ParseEvents(fp, length);
	}
}

//	상위 비트 1 -> 다음 바이트 있음 / 상위 비트 0 -> 마지막 바이트임
//	데이터를 7비트 단위로 끝어서 저장함
uint32_t CMidi::ReadVLQ(FILE* fp)
{
	uint32_t value = 0;

	while (1)
	{
		uint8_t c = fgetc(fp);

		value = (value << 7) | (c & 0x7F);	// 0111 1111

		if (!(c & 0x80))	//	1000 0000
			break;
	}

	return value;
}

void CMidi::ParseEvents(FILE* fp, uint32_t trackLength)
{
	MidiEvent mEvent;
	uint32_t time = 0;
	uint8_t running = None;
	while (trackLength > 0)
	{
		uint32_t delta = ReadVLQ(fp);
		time = delta;

		uint8_t bt = fgetc(fp);	//	여기서 running status 체크를 해야함
		if (bt < eStatus::NoteOff)
		{	//	data를 받고있으므로 running status임

		}
		uint8_t status = bt & 0xF0;
		uint8_t channel = bt & 0x0F;

		eStatus event = (eStatus)status;
		switch (event)
		{
		case NoteOff:
			uint8_t note = fgetc(fp);
			uint8_t velocity = fgetc(fp);
			mEvent.time = delta;
			mEvent.type = bt;
			mEvent.data1 = note;
			mEvent.data2 = velocity;
			events.push_back(mEvent);
			break;
		case NoteOn:
			uint8_t note = fgetc(fp);
			uint8_t velocity = fgetc(fp);
			break;
		}


		if ((status & 0xF0) == 0x90)	//	1111 0000
		{
			uint8_t note = fgetc(fp);
			uint8_t velocity = fgetc(fp);

			//printf("NoteOn %d time %d\n", note, time);
			
		}
	}
}