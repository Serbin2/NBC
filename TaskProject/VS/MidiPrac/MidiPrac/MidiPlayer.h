#pragma once

#include "MStruct.h"
#include <chrono>


class MidiPlayer
{
public:
	MidiPlayer(string FilePath);
	~MidiPlayer();

	CMidi GetMidi() { return File; };

	void PlayAllTrack2();
	void PlayAllTrack3();

protected:
	void SendMidi(MidiEvent evnet);
	void SendMidi2(MidiEvent event);

private:
	
	double tickToMs;
	HMIDIOUT m_device;
	CMidi File;

	bool banked = false;
	int bankMSB = 0;
	int bankLSB = 0;
	
	fluid_settings_t* m_Settings;
	fluid_synth_t* m_Synth;
	fluid_audio_driver_t* m_AudioDriver;
	//fluid_synth_program_change
	//fluid_synth_noteon
	//fluid_synth_noteoff
};

