#include "MidiPlayer.h"
#include <deque>
#include <algorithm>


//char font[64] = "./SGM-V2.01.sf2";
char font[64] = "./gm.dls";

bool Compare(MidiEvent a, MidiEvent b)
{
	if (a.accuTime < b.accuTime)
	{
		return true;
	}
	else if (a.accuTime == b.accuTime)
	{
		if (a.eEvent == MetaEvent)
		{
			return true;
		}
	}
	return false;
}

bool CompareAbs(MidiEvent a, MidiEvent b)
{
	return a.absTime < b.absTime;
}

MidiPlayer::MidiPlayer(string filePath)
{
	tickToMs = (double)500000 / (double)480;
	File.FileOpen(filePath);
	m_device = NULL;

	m_Settings = new_fluid_settings();
	m_Synth = new_fluid_synth(m_Settings);

	m_AudioDriver =	new_fluid_audio_driver(m_Settings, m_Synth);

	// SoundFont 로드
	fluid_synth_sfload(m_Synth, font, 1);
	//fluid_synth_sfload(m_Synth, "C:\Windows\system32\drivers\gm.dls", 1);

}

MidiPlayer::~MidiPlayer()
{
	delete_fluid_audio_driver(m_AudioDriver);
	delete_fluid_synth(m_Synth);
	delete_fluid_settings(m_Settings);
}

void MidiPlayer::PlayAllTrack2()
{
	midiOutOpen(&m_device, 0, 0, 0, 0);

	vector<MidiTrack> tracks = File.GetTrack();
	vector<MidiEvent> events;
	for (auto& t : tracks)
	{
		for (auto& e : t.events)
		{
			events.push_back(e);
		}
	}

	sort(events.begin(), events.end(), Compare);
	uint16_t div = File.GetHeader().division;
	uint32_t tempo = 500000;
	tickToMs = ((double)tempo / (double)1000.0) / (double)div;
	//double gOffset = File.GetGlobalOffset();
	double gOffset = 0;
	double prevTempoTime = 0;	//	직전에 템포가 변경된 시간
	double accuTempoTime = 0;		//	템포 변경 기준으로 누적된 시간
	//	절대시간값을 계산합니다
	for (auto& e : events)
	{
		if (e.eEvent == MetaEvent)
		{	//	템포를 변경합니다
			//	직전 템포타임부터 이번 템포타임 까지는 직전템포로 계산되어야 함
			double calcTime = e.accuTime - prevTempoTime;
			double calcedTime = calcTime * tickToMs;
			accuTempoTime += calcedTime;

			prevTempoTime = e.accuTime;
			tempo = e.longData;
			tickToMs = ((double)tempo / (double)1000.0) / (double)div;
			printf("tickToMs : %f\n", tickToMs);
		}
		double calcTime = e.accuTime - prevTempoTime;	//	현재 템포로 계산해야되는 시간
		double calcedTime = calcTime * tickToMs;
		e.absTime = accuTempoTime + calcedTime + gOffset;
	}

	auto start = chrono::high_resolution_clock::now();

	for (auto& e : events)
	{
		//if (e.eEvent == MetaEvent)	continue;
		auto now = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

		while (true)
		{
			auto now = chrono::high_resolution_clock::now();
			auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

			if (elapsed >= e.absTime)
				break;
		}

		SendMidi(e);
	}

	Sleep(1000);
	midiOutClose(m_device);
}

void MidiPlayer::PlayAllTrack3()
{
	vector<MidiTrack> tracks = File.GetTrack();
	vector<MidiEvent> events;
	for (auto& t : tracks)
	{
		for (auto& e : t.events)
		{
			events.push_back(e);
		}
	}

	sort(events.begin(), events.end(), Compare);
	//uint16_t div = File.GetHeader().division;
	uint16_t div = 480;
	uint32_t tempo = 500000;
	tickToMs = ((double)tempo / (double)1000.0) / (double)div;
	double gOffset = File.GetGlobalOffset();
	double prevTempoTime = 0;	//	직전에 템포가 변경된 시간
	double accuTempoTime = 0;		//	템포 변경 기준으로 누적된 시간
	//	절대시간값을 계산합니다
	for (auto& e : events)
	{
		if (e.eEvent == MetaEvent)
		{	//	템포를 변경합니다
			//	직전 템포타임부터 이번 템포타임 까지는 직전템포로 계산되어야 함
			double calcTime = e.accuTime - prevTempoTime;
			double calcedTime = calcTime * tickToMs;
			accuTempoTime += calcedTime;

			prevTempoTime = e.accuTime;
			tempo = e.longData;
			tickToMs = ((double)tempo / (double)1000.0) / (double)div;
			printf("tickToMs : %f\n", tickToMs);
		}
		double calcTime = e.accuTime - prevTempoTime;	//	현재 템포로 계산해야되는 시간
		double calcedTime = calcTime * tickToMs;
		e.absTime = accuTempoTime + calcedTime + gOffset;
	}

	auto start = chrono::high_resolution_clock::now();

	for (auto& e : events)
	{
		//if (e.eEvent == MetaEvent)	continue;
		auto now = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

		while (true)
		{
			auto now = chrono::high_resolution_clock::now();
			auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

			if (elapsed >= e.absTime)
				break;
		}

		SendMidi2(e);
	}
}

void MidiPlayer::SendMidi(MidiEvent event)
{
	bool note = false;
	DWORD msg;

	switch (event.eEvent)
	{
	case ControlChange:
		if (event.data1 == 7)
		{
			printf("channel %d volume %d\n",event.channel, event.data2);
		}
	case NoteOn:
	case NoteOff:
	case PolyphonicKeyPressure:
	case PitchBend:
		note = true;
		msg = event.type | (event.data1 << 8) | (event.data2 << 16);
		break;
	case ProgramChange:
	case ChannelPressure:
		if (event.channel == 9)	return;
		note = true;
		msg = event.type | (event.data1 << 8);
		break;
	case MetaEvent:
		// tempo
		printf("Tempo changed to %d\n", event.longData);
		break;
	case SystemExclusive:
	{
		MIDIHDR hdr;
		hdr.lpData = event.sysex;
		hdr.dwBufferLength = event.longData;
		hdr.dwFlags = 0;

		if (midiOutPrepareHeader(m_device, &hdr, sizeof(MIDIHDR)) == MMSYSERR_NOERROR)
		{
			if (midiOutLongMsg(m_device, &hdr, sizeof(MIDIHDR)) == MMSYSERR_NOERROR)
			{
				printf("sysex data successed\n");
				return;
			}
		}
		printf("sysex Failure\n");
	}
		return;
	default:
		break;
	}

	if (!note)	return;

	midiOutShortMsg(m_device, msg);
}

void MidiPlayer::SendMidi2(MidiEvent event)
{
	switch (event.eEvent)
	{
	case ControlChange:
		if (event.longData == 1)
		{//bank
			banked = true;
			if (bankMSB == 0)
			{
				bankMSB = event.data1;
			}
			else
			{
				bankLSB = event.data1;
			}
			break;
		}
		fluid_synth_cc(m_Synth, event.channel, event.data1, event.data2);
		break;
	case NoteOn:
		fluid_synth_noteon(m_Synth, event.channel, event.data1, event.data2);
		break;
	case NoteOff:
		fluid_synth_noteoff(m_Synth, event.channel, event.data1);
		break;
	case PolyphonicKeyPressure:
		fluid_synth_key_pressure(m_Synth, event.channel, event.data1, event.data2);
		break;
	case PitchBend:
	{
		int val = (event.data1 << 7) | event.data2;
		fluid_synth_pitch_bend(m_Synth, event.channel, val);
	}
	break;
	case ProgramChange:
	{
		if (banked)
		{
			int val = (bankLSB << 8) | bankMSB;
			fluid_synth_bank_select(m_Synth, event.channel, val);
			banked = false;
			bankMSB = 0;
			bankLSB = 0;
		}
		fluid_synth_program_change(m_Synth, event.channel, event.data1);
	}
	break;
	case ChannelPressure:
		fluid_synth_channel_pressure(m_Synth, event.channel, event.data1);
		break;
	case MetaEvent:
		// tempo
		printf("Tempo changed to %d\n", event.longData);
		break;
	case SystemExclusive:
	{
		int response = 0;
		fluid_synth_sysex(m_Synth, event.sysex, event.longData, NULL, &response, FALSE, FALSE);
	}
	break;
	default:
		break;
	}


}