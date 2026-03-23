#include "MStruct.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <math.h>

CMidi::CMidi()
{
	LastVLQlen = 0;
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
	printf("FileOpen\n");

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
	printf("length : %d\n", length);
	header.format = ReadBE16(fp);
	printf("format : %d\n", header.format);
	header.tracks = ReadBE16(fp);
	printf("tracks : %d\n", header.tracks);
	header.division = ReadBE16(fp);
	printf("div : %d\n", header.division);

	if ((header.division & 0x8000) == 0) 
	{	//	tick per quater note
		uint16_t ticks_per_qn = header.division & 0x7FFF;  // 96
		printf("tpqn\n");
	}
	else
	{	//	SMPTE
		 // 상위 바이트의 하위 7비트 = 음수 SMPTE fps
		int8_t smpte_fps = (int8_t)((header.division >> 8) & 0x7F);
		uint8_t ticks_per_frame = header.division & 0x00FF;
		printf("SMPTE\n");
	}


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
		//Sleep(1000);
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

//void CMidi::ParseTracks(FILE* fp, int trackCount)
//{
//	for (int i = 0; i < trackCount; i++)
//	{
//		char id[4];
//		fread(id, 1, 4, fp);	//	MTrk
//
//		uint32_t length = ReadBE32(fp);
//
//		ParseEvents(fp, length, i);
//	}
//}

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
	track.length = trackLength;

	printf("parsing track : %d\n", trackNumber);

	uint32_t time = 0;
	uint32_t accuTime = 0;
	uint8_t running = None;
	uint8_t runningChannel = 0;
	while (trackLength > 0)
	{
		//printf("remain length : %d\n", trackLength);
		bool meta = false;
		MidiEvent mEvent;
		uint32_t delta = ReadVLQ(fp);
		trackLength -= GetLastVLQlen();
		time = delta;
		accuTime += time;
		uint8_t bt = fgetc(fp);	//	여기서 running status 체크를 해야함
		trackLength--;
		uint8_t status;
		uint8_t channel;
		uint8_t data1 = 0;
		uint8_t data2 = 0;
		if (bt < eStatus::NoteOff)
		{	//	data를 받고있으므로 running status임
			switch (running)
			{
			case ControlChange:
			case NoteOff:
			case NoteOn:
			case PolyphonicKeyPressure:
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
			status = running;
			channel = runningChannel;
			if (status == NoteOn)
			{
				if (data2 == 0)
				{
					status = NoteOff;
				}
			}
		}
		else
		{
			status = bt & 0xF0;
			channel = bt & 0x0F;

			switch (status)
			{
			case ControlChange:
				data1 = fgetc(fp);
				data2 = fgetc(fp);
				if (data1 == 0 || data1 == 32)
				{	//	control change bank select MSB	/	LSB
					data1 = data2;
					data2 = 0;
					mEvent.longData = 1;
				}
				trackLength -= 2;
				break;
			case NoteOff:
			case NoteOn:
			case PolyphonicKeyPressure:		
			case PitchBend:
				//	데이터 두개
				data1 = fgetc(fp);
				data2 = fgetc(fp);
				running = status;
				if (status == NoteOn)
				{
					if (data2 == 0)
					{
						status = NoteOff;
					}
				}
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
					//printf("skip sysex...\n");
					printf("read sysex...\n");
					uint32_t length = ReadVLQ(fp);
					trackLength -= GetLastVLQlen();
					for (uint32_t i = 0; i < length; i++)
					{
						uint8_t c = fgetc(fp);
						if (i < 20)
						{
							mEvent.sysex[i] = c;
						}	
						trackLength--;
					}
					mEvent.accuTime = (double)accuTime;
					mEvent.time = delta;
					mEvent.eEvent = SystemExclusive;
					mEvent.longData = min(length,20);
					track.events.push_back(mEvent);
					//printf("%u Byte skiped\n", length);
				}
				else if (bt == MetaEvent)
				{
					uint8_t type = fgetc(fp);
					trackLength--;
					uint32_t length = ReadVLQ(fp);
					trackLength -= GetLastVLQlen();
					
					switch (type)
					{
					case 0x01:
					{	//	text
						char text[101];
						for (uint32_t i = 0; i < length; i++)
						{
							if (i > 99)
							{
								fgetc(fp);
								trackLength--;
								continue;
							}
							text[i] = fgetc(fp);
							trackLength--;
						}
						if (length > 100)	length = 100;
						text[length] = '\0';
						printf("MetaEvent Text : %s\n", text);
					}
						break;
					case 0x03:
					{
						//	Track name
						char text[101];
						for (uint32_t i = 0; i < length; i++)
						{
							if (i > 99)
							{
								fgetc(fp);
								trackLength--;
								continue;
							}
							text[i] = fgetc(fp);
							trackLength--;
						}
						if (length > 100)	length = 100;
						text[length] = '\0';
						printf("track name : %s\n", text);
					}
						break;
					case 0x02:
					{
						//	Copyright
						char text[101];
						for (uint32_t i = 0; i < length; i++)
						{
							if (i > 99)
							{
								fgetc(fp);
								trackLength--;
								continue;
							}
							text[i] = fgetc(fp);
							trackLength--;
						}
						if (length > 100)	length = 100;
						text[length] = '\0';
						printf("Copyright : %s\n", text);
					}
					break;
					case 0x04:
					{
						//	Instrument name
						char text[101];
						for (uint32_t i = 0; i < length; i++)
						{
							if (i > 99)
							{
								fgetc(fp);
								trackLength--;
								continue;
							}
							text[i] = fgetc(fp);
							trackLength--;
						}
						if (length > 100)	length = 100;
						text[length] = '\0';
						printf("Instrument name : %s\n", text);
					}
					break;
					case 0x58:
					{
						//	Time Signature
						//	nn dd cc bb
						uint8_t nn = fgetc(fp);
						uint8_t dd = fgetc(fp);
						uint8_t cc = fgetc(fp);
						uint8_t bb = fgetc(fp);
						trackLength -= 4;
						printf("%d / %d, metronome click : %d, 32nd : %d\n", nn, (int)pow(2, dd), cc, bb);
					}
						break;
					case 0x59:
					{
						//	Key Signature
						//	sf(-7 ~ 7) mi ( 0 or 1 )
						//	조표는 숫자 값인 sf Key로 지정되며,
						//	이 값은 C장조일 경우 0, C 위의 각 샵(♯)마다 양수 값,	
						//	C 아래의 각 플랫(♭)마다 음수 값(7~7)을 갖습니다. 
						//	Major/Minor mi 필드는 숫자 값으로, 장조일 경우 0, 단조일 경우 1입니다.
						uint8_t sf = fgetc(fp);
						uint8_t mi = fgetc(fp);
						trackLength -= 2;
						printf("Key Signature\n");
					}
						break;
					case 0x51:
					{
						// tempo 처리
						uint32_t tempo = 0;
						tempo |= fgetc(fp) << 16;
						tempo |= fgetc(fp) << 8;
						tempo |= fgetc(fp);
						trackLength -= 3;
						printf("Meta Event Tempo: %u, delta : %u, accuTime : %u\n", tempo, delta, accuTime);
						mEvent.accuTime = (double)accuTime;
						mEvent.time = delta;
						mEvent.eEvent = MetaEvent;
						mEvent.longData = tempo;
						track.events.push_back(mEvent);
					}
						break;
					case 0x2F:
					{
						printf("End of track\n");
						// End of Track
						if (trackLength > 0)
						{
							assert(0);
						}
						return track;
					}
					break;
					case 0x54:
					{	//	SMPTE offset
						//	hr mn se fr ff
						uint8_t hr = fgetc(fp);
						uint8_t mn = fgetc(fp);
						uint8_t se = fgetc(fp);
						uint8_t fr = fgetc(fp);
						uint8_t ff = fgetc(fp);
						trackLength -= 5;
						int rate = (hr >> 5) & 0x03;
						int hh = hr & 0x1F;
						int fps;
						switch (rate)
						{
						case 0:	fps = 24;	break;
						case 1:	fps = 25;	break;
						case 2:	fps = 30;	break;	//29.97
						case 3:	fps = 30;	break;
						}

						double totalSec = hh * 3600 + mn * 60 + se + (double)fr / fps + (double)ff / (fps * 100);
						globalOffset = totalSec * 1000.0;
					}
					break;
					default:
					{
						printf("Meta Event skip : %d\n", type);
						// 나머지는 skip
						for (uint32_t i = 0; i < length; i++)
						{
							fgetc(fp);
							trackLength--;
						}
					}
					break;
					}
				}
			}
		}

		if (meta)	continue;

		mEvent.accuTime = (double)accuTime;
		mEvent.time = delta;
		mEvent.type = status | channel;
		mEvent.eEvent = (eStatus)status;
		mEvent.channel = runningChannel;
		mEvent.data1 = data1;
		mEvent.data2 = data2;
		track.events.push_back(mEvent);
	}

	return track;
}