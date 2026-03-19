#include "MidiPlayer.h"
#include <deque>
#include <algorithm>

bool Compare(MidiEvent a, MidiEvent b)
{
	return a.absTime < b.absTime;
}

MidiPlayer::MidiPlayer(string filePath)
{
	File.FileOpen(filePath);
	m_device = NULL;
}

MidiPlayer::~MidiPlayer()
{

}

void MidiPlayer::Play()
{
	if (midiOutOpen(&m_device, 0, 0, 0, 0) != MMSYSERR_NOERROR)	return;
	
	vector<MidiTrack> tracks = File.GetTrack();
	vector<MidiEvent> events = tracks[0].events;
	auto start = chrono::high_resolution_clock::now();
	for (auto& e : events)
	{
		while (true)
		{
			auto now = chrono::high_resolution_clock::now();
			auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

			if (elapsed >= e.absTime)
				break;
		}

		SendMidi(e);
	}

	midiOutClose(m_device);
}

void MidiPlayer::PlayAllTrack()
{
	midiOutOpen(&m_device, 0, 0, 0, 0);

	vector<MidiTrack> tracks = File.GetTrack();
	vector<deque<MidiEvent>> queue;
	for (auto& t : tracks)
	{
		deque<MidiEvent> ev;

		for (auto& e : t.events)
		{
			ev.push_back(e);
		}

		queue.push_back(ev);
	}

	int finished = 0;
	int size = tracks.size();
	auto start = chrono::high_resolution_clock::now();

	while (finished < size)
	{
		auto now = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();
		finished = 0;
		for (auto& t : queue)
		{
			if (t.size() == 0)
			{
				finished++;
				continue;
			}

			if (elapsed >= t.front().absTime)
			{
				SendMidi(t.front());
				t.pop_front();
			}
		}
	}

	midiOutClose(m_device);
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

	auto start = chrono::high_resolution_clock::now();

	for (auto& e : events)
	{
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

	midiOutClose(m_device);
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
	default:
		break;
	}

	if (!note)	return;

	midiOutShortMsg(m_device, msg);
}

bool MidiPlayer::CompareEvent(MidiEvent a, MidiEvent b)
{
	return a.absTime < b.absTime;
}