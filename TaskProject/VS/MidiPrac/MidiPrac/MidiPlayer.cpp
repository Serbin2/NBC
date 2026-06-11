#include "MidiPlayer.h"
#include <algorithm>
#include <vector>

using namespace std;

// 생성자: 파일 경로로 CMidi를 구성하면 그 자리에서 파일 파싱이 끝난다.
MidiPlayer::MidiPlayer(const string& filePath)
	: m_midi(filePath.c_str()), m_device(NULL)
{}

MidiPlayer::~MidiPlayer()
{
	if (m_device) midiOutClose(m_device);
}

// 파싱된 모든 채널 이벤트를 절대 시각(ms) 순서대로 MIDI 출력 장치로 송출한다.
void MidiPlayer::Play()
{
	if (midiOutOpen(&m_device, 0, 0, 0, 0) != MMSYSERR_NOERROR) return;  // 기본 출력 장치 열기

	// 트랙별로 흩어져 있는 채널 이벤트를 (시각, 이벤트) 쌍으로 모아 시각순으로 정렬한다.
	vector<pair<double, const CMidiEvent*>> allEvents;
	for (const auto& track : m_midi.GetTracks())
	{
		for (const auto& record : track.GetEvents())
		{
			if (record.IsMidiEvent())
				allEvents.emplace_back(record.absTimeMs, record.AsMidi());
		}
	}
	sort(allEvents.begin(), allEvents.end(),
		[](const auto& a, const auto& b) { return a.first < b.first; });

	auto start    = chrono::high_resolution_clock::now();
	auto fpsTimer = start;
	int  frameCount = 0;
	int  eventIndex = 0;
	int  totalEvents = (int)allEvents.size();

	// 실제 경과 시간을 따라가며, 재생 시각에 도달한 이벤트들을 차례로 내보낸다.
	while (eventIndex < totalEvents)
	{
		auto   now     = chrono::high_resolution_clock::now();
		double elapsed = chrono::duration_cast<chrono::duration<double, milli>>(now - start).count();

		// 현재 경과 시간 이전에 일어나야 할 이벤트를 모두 송출
		while (eventIndex < totalEvents && elapsed >= allEvents[eventIndex].first)
		{
			SendMidi(*allEvents[eventIndex].second);
			eventIndex++;
		}

		// FPS 측정: 루프 횟수를 세어 1초마다 출력
		frameCount++;
		double fpsElapsed = chrono::duration_cast<chrono::duration<double>>(now - fpsTimer).count();
		if (fpsElapsed >= 1.0)
		{
			printf("\rFPS: %d  ", (int)(frameCount / fpsElapsed));
			fpsTimer   = now;
			frameCount = 0;
		}
	}
	printf("\n");

	midiOutClose(m_device);
	m_device = NULL;
}

// CMidiEvent 하나를 winmm이 요구하는 32비트 메시지로 만들어 송출한다.
// 메시지 바이트 배치: [상태바이트] | [데이터1 << 8] | [데이터2 << 16]
void MidiPlayer::SendMidi(const CMidiEvent& event)
{
	DWORD msg  = 0;
	bool  send = false;

	switch (event.GetStatus())
	{
	case NoteOn:
	case NoteOff:
	case PolyphonicKeyPressure:
	case ControlChange:
	case PitchBend:
		// 데이터 2바이트짜리 이벤트
		msg  = event.GetStatusByte() | (event.GetData1() << 8) | (event.GetData2() << 16);
		send = true;
		break;
	case ProgramChange:
	case ChannelPressure:
		// 데이터 1바이트짜리 이벤트
		if (event.GetChannel() == 9) return;  // 채널 9는 타악기(드럼) — 악기 변경은 건너뜀
		msg  = event.GetStatusByte() | (event.GetData1() << 8);
		send = true;
		break;
	default:
		break;
	}

	if (send) midiOutShortMsg(m_device, msg);
}
