#pragma once
#include "MidiOut.h"   // windows.h / mmsystem.h 포함 + 출력 백엔드(IMidiOut)
#include "Midi.h"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

// 재생 옵션 — 명령행 인수로 채워진다 (MidiPrac.cpp 참고)
struct PlayerOptions
{
	std::string midiPath;          // 재생할 SMF 파일
	std::string soundfont;         // 사운드폰트 경로 (비어 있으면 자동 탐색)
	int  winmmDevice = -1;         // winmm 출력 장치 번호 (-1 = 시스템 기본)
	bool forceWinmm  = false;      // true면 FluidSynth를 시도하지 않음
};

// 파싱된 이벤트를 시간 순으로 송출하는 재생기.
//  - 출력: FluidSynth(사운드폰트) 우선, 실패 시 winmm 폴백
//  - 조작: 일시정지 / 탐색 / 배속 / 음량 / 조옮김 / 채널 음소거 / 반복
class MidiPlayer
{
public:
	explicit MidiPlayer(const PlayerOptions& opt);

	void Play();

private:
	// 준비
	bool OpenBackend();            // FluidSynth → winmm 순으로 출력 백엔드 열기
	void CollectEvents();          // 전 트랙의 채널/SysEx 이벤트를 시각순으로 평탄화

	// 송출
	void Dispatch(const CEventRecord& rec);
	void SendChannelEvent(const CMidiEvent& ev);
	void SendSysEx(const CSysExEvent& ev);
	int  TransposedNote(int ch, int note) const;   // 조옮김 적용 (음역 밖이면 -1)

	// 조작 (키보드)
	void PollKeys();
	void TogglePause();
	void ToggleMute(int ch);
	void SeekTo(double targetMs);  // 탐색 + 컨트롤러 상태 복원(chase)
	void AdjustVolume(int delta);
	void AdjustSpeed(double delta);
	void AdjustTranspose(int delta);

	// 표시
	void DrawStatus(bool force);

	void ClearNoteMap();

	PlayerOptions             m_opt;
	CMidi                     m_midi;
	std::unique_ptr<IMidiOut> m_out;

	std::vector<const CEventRecord*> m_events;   // 시각순으로 정렬된 전체 이벤트
	size_t m_eventIndex = 0;
	double m_durationMs = 0.0;

	// 재생 상태
	double m_posMs     = 0.0;      // 현재 재생 위치 (곡 내 시각, ms)
	double m_speed     = 1.0;      // 배속 (0.25 ~ 4.0)
	int    m_volume    = 100;      // 마스터 볼륨 %
	int    m_transpose = 0;        // 반음 단위 조옮김 (드럼 채널 9 제외)
	bool   m_paused    = false;
	bool   m_loop      = false;
	bool   m_quit      = false;
	bool   m_mute[16]  = {};

	// (채널, 원래 음높이) → 실제로 울리고 있는 음높이. -1 = 안 울림.
	// 조옮김이 연주 도중 바뀌어도 NoteOff가 정확한 음을 끄게 한다.
	int8_t m_noteMap[16][128];

	std::chrono::steady_clock::time_point m_lastTick;   // 위치 적분용 직전 시각
	std::chrono::steady_clock::time_point m_lastDraw;   // 상태 표시 갱신 시각
	bool m_dirty = true;                                // 상태 표시 갱신 필요 플래그
};
