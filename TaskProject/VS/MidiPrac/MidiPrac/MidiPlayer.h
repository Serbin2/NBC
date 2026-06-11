#pragma once
#define WIN32_LEAN_AND_MEAN   // 자주 쓰지 않는 Windows 헤더 제외 (컴파일 속도 향상)
#include <windows.h>          // winmm 헤더가 의존하는 기본 타입(HMIDIOUT, DWORD 등) 정의
#include <mmsystem.h>         // winmm MIDI 출력 API: midiOutOpen / midiOutShortMsg / midiOutClose
#include "Midi.h"
#include <chrono>
#include <string>

#pragma comment(lib, "winmm.lib")   // winmm.lib 자동 링크

class MidiPlayer
{
public:
	explicit MidiPlayer(const std::string& filePath);
	~MidiPlayer();

	void Play();

private:
	void SendMidi(const CMidiEvent& event);

	HMIDIOUT m_device;
	CMidi    m_midi;
};
