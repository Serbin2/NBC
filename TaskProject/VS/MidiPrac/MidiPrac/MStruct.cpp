#include "MStruct.h"

CMidi::CMidi()
{
	tickToMs = (double)500000 / (double)480;
}

CMidi::~CMidi()
{

}


void CMidi::FileOpen(string fileName)
{
	//	파일 열기
	FILE* fp;
	int err = fopen_s(&fp, fileName.c_str(), "rb");

	if (err != 0 || !fp)
	{//	파일 열기 실패
		return;
	}

	//	헤더 읽기
	//"MThd"	(4byte)
	//length	(4byte)	//	헤더의 크기
	//format	(2byte)
	//tracks	(2byte)
	//division	(2byte)
	char chunk[5];
	fread(chunk, 1, 4, fp); // MThd
	chunk[4] = '\n';
	if (!strncmp(chunk, "Mthd", 4))
	{	
		//	midi 파일이 아님
		fclose(fp);
		return;
	}

	uint32_t length = ReadBE32(fp);

	MidiHeader header;

	header.length = length;
	header.format = ReadBE16(fp);
	header.tracks = ReadBE16(fp);
	header.division = ReadBE16(fp);

	m_sMidiHeader = header;

	for (uint16_t i = 0; i < header.tracks; i++)
	{
		//	Track Chunk
		//"MTrk"	(4byte)
		//length	(4byte)
		//event data
		char trackID[4];
		fread(trackID, 1, 4, fp);

		uint32_t length = ReadBE32(fp);

		MidiTrack track = ParseEvents(fp, length, i);
		tracks.push_back(track);
	}
	
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

		ParseEvents(fp, length, i);
	}
}

//	상위 비트 1 -> 다음 바이트 있음 / 상위 비트 0 -> 마지막 바이트임
//	데이터를 7비트 단위로 끝어서 저장함
uint32_t CMidi::ReadVLQ(FILE* fp)
{
	uint32_t value = 0;
	LastVLQlen = 0;

	while (1)
	{
		uint8_t c = fgetc(fp);
		LastVLQlen++;

		value = (value << 7) | (c & 0x7F);	// 0111 1111

		if (!(c & 0x80))	//	1000 0000
			break;
	}

	return value;
}

uint32_t CMidi::GetLastVLQlen()
{
	uint32_t retVal = LastVLQlen;
	LastVLQlen = 0;
	return retVal;
}

MidiTrack CMidi::ParseEvents(FILE* fp, uint32_t trackLength, uint16_t trackNumber)
{
	MidiTrack track;
	track.trackNumber = trackNumber;

	uint32_t time = 0;
	unsigned long long absTime = 0;
	uint8_t running = None;
	uint8_t runningChannel = 0;
	while (trackLength > 0)
	{
		bool meta = false;
		MidiEvent mEvent;
		uint32_t delta = ReadVLQ(fp);
		trackLength -= GetLastVLQlen();
		time = delta;
		absTime += time;
		uint8_t bt = fgetc(fp);	//	여기서 running status 체크를 해야함
		trackLength--;
		uint8_t data1 = 0;
		uint8_t data2 = 0;
		if (bt < eStatus::NoteOff)
		{	//	data를 받고있으므로 running status임
			switch (running)
			{
			case NoteOff:
			case NoteOn:
			case PolyphonicKeyPressure:
			case ControlChange:
			case PitchBend:
				//	데이터 두개
				data1 = bt;
				data2 = fgetc(fp);
				trackLength--;
				break;
			case ProgramChange:
			case ChannelPressure:
				//	데이터 한개
				data1 = bt;
				break;
			default:
				//	running status에선 SysEx나 MetaEvent가 나오지 않음.
				break;
			}
		}
		else
		{
			uint8_t status = bt & 0xF0;
			uint8_t channel = bt & 0x0F;

			switch (status)
			{
			case NoteOff:
			case NoteOn:
			case PolyphonicKeyPressure:
			case ControlChange:
			case PitchBend:
				//	데이터 두개
				data1 = fgetc(fp);
				data2 = fgetc(fp);
				running = status;
				runningChannel = channel;
				trackLength -= 2;
				break;
			case ProgramChange:
			case ChannelPressure:
				//	데이터 한개
				data1 = fgetc(fp);
				running = status;
				runningChannel = channel;
				trackLength--;
				break;
			default:
				//	Sysex or Meta event
				meta = true;
				if (bt == SystemExclusive)
				{	//	처리하지 않습니다
					uint32_t length = ReadVLQ(fp);
					trackLength -= GetLastVLQlen();
					for (uint32_t i = 0; i < length; i++)
					{
						fgetc(fp);
						trackLength--;
					}
				}
				else if (bt == MetaEvent)
				{
					uint8_t type = fgetc(fp);
					trackLength--;
					uint32_t length = ReadVLQ(fp);
					trackLength -= GetLastVLQlen();
					if (type == 0x51)
					{
						// tempo 처리
						uint32_t tempo = 0;
						tempo |= fgetc(fp) << 16;
						tempo |= fgetc(fp) << 8;
						tempo |= fgetc(fp);
						trackLength -= 3;
						track.tempo = tempo;
						tickToMs = ((double)tempo / (double)1000.0) / (double)m_sMidiHeader.division;
					}
					else if (type == 0x2F)
					{
						// End of Track
						return track;
					}
					else
					{
						// 나머지는 skip
						for (uint32_t i = 0; i < length; i++)
						{
							fgetc(fp);
							trackLength--;
						}
					}
				}
			}
		}

		if (meta)	continue;

		mEvent.absTime = (double)absTime * tickToMs;
		mEvent.time = delta;
		mEvent.type = running | runningChannel;
		mEvent.eEvent = (eStatus)running;
		mEvent.channel = runningChannel;
		mEvent.data1 = data1;
		mEvent.data2 = data2;
		track.events.push_back(mEvent);
	}

	return track;
}