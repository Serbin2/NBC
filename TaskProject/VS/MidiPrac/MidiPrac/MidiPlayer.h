#pragma once

#include "MStruct.h"
#include <chrono>


class MidiPlayer
{
public:
	MidiPlayer(string FilePath);
	~MidiPlayer();

	CMidi GetMidi() { return File; };
	void Play();
	void PlayAllTrack();
	void PlayAllTrack2();

protected:
	void SendMidi(MidiEvent evnet);
	bool CompareEvent(MidiEvent a, MidiEvent b);

private:
	
	HMIDIOUT m_device;
	CMidi File;
};

