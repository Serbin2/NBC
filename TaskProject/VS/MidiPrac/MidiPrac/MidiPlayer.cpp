#include "MidiPlayer.h"
#include <algorithm>
#include <conio.h>     // _kbhit / _getch — 키보드 폴링
#include <cstdio>
#include <cstring>

using namespace std;
using namespace std::chrono;

// Ctrl+C / 콘솔 창 닫기 등으로 강제 종료될 때도 패닉을 보내기 위한 전역 포인터.
// (이 경로에서는 소멸자가 불리지 않으므로 핸들러에서 직접 처리해야 한다)
static IMidiOut* s_ctrlOut = nullptr;

static BOOL WINAPI ConsoleCtrlHandler(DWORD)
{
	if (s_ctrlOut) s_ctrlOut->AllSoundOff();
	return FALSE;   // FALSE: 기본 핸들러가 이어서 프로세스를 종료하게 둔다
}

// 생성자: 파일 경로로 CMidi를 구성하면 그 자리에서 파일 파싱이 끝난다.
MidiPlayer::MidiPlayer(const PlayerOptions& opt)
	: m_opt(opt), m_midi(opt.midiPath.c_str())
{
	ClearNoteMap();
}

void MidiPlayer::ClearNoteMap()
{
	memset(m_noteMap, -1, sizeof(m_noteMap));
}

// ──────────────────────────────────────────────
// 준비
// ──────────────────────────────────────────────

// 전 트랙에 흩어져 있는 채널/SysEx 이벤트를 한 줄로 모아 시각순으로 정렬한다.
// stable_sort: 같은 시각이면 파일에 적힌 순서(예: ProgramChange → NoteOn)를 유지한다.
void MidiPlayer::CollectEvents()
{
	for (const auto& track : m_midi.GetTracks())
	{
		for (const auto& record : track.GetEvents())
		{
			if (record.IsMidiEvent() || record.IsSysEx())
				m_events.push_back(&record);
		}
	}
	stable_sort(m_events.begin(), m_events.end(),
		[](const CEventRecord* a, const CEventRecord* b) { return a->absTimeMs < b->absTimeMs; });

	m_durationMs = m_events.empty() ? 0.0 : m_events.back()->absTimeMs;
}

// FluidSynth(사운드폰트) → winmm 순서로 출력 백엔드를 연다.
bool MidiPlayer::OpenBackend()
{
	if (!m_opt.forceWinmm)
	{
		// 사운드폰트 후보 수집: 지정 경로 → 작업/실행 폴더의 *.sf2 → Windows 기본 gm.dls
		vector<string> candidates;
		if (!m_opt.soundfont.empty())
			candidates.push_back(m_opt.soundfont);
		else
		{
			candidates = ScanSoundFonts();   // 작업/실행 폴더의 *.sf2

			// Windows 내장 GM 음원 (FluidSynth 빌드가 DLS를 지원할 때만 성공한다)
			char winDir[MAX_PATH] = {};
			GetWindowsDirectoryA(winDir, MAX_PATH);
			candidates.push_back(string(winDir) + "\\System32\\drivers\\gm.dls");
		}

		for (const string& sf : candidates)
		{
			if ((m_out = FluidSynthOut::Create(sf)))
				return true;
		}
		if (!m_opt.soundfont.empty())
			printf("사운드폰트를 열 수 없습니다: %s → winmm으로 대체합니다\n", m_opt.soundfont.c_str());
	}

	m_out = WinmmOut::Create(m_opt.winmmDevice);
	return m_out != nullptr;
}

// ──────────────────────────────────────────────
// 재생 본체
// ──────────────────────────────────────────────
void MidiPlayer::Play()
{
	// 파싱 실패(파일 없음/형식 오류) 검사: 정상 SMF라면 헤더 이름이 "MThd"다
	if (strcmp(m_midi.GetHeader().GetName(), "MThd") != 0)
	{
		printf("MIDI 파일을 열 수 없습니다: %s\n", m_opt.midiPath.c_str());
		return;
	}

	CollectEvents();
	if (m_events.empty())
	{
		printf("재생할 이벤트가 없습니다: %s\n", m_opt.midiPath.c_str());
		return;
	}

	if (!OpenBackend())
	{
		printf("MIDI 출력 장치를 열 수 없습니다.\n");
		return;
	}

	printf("File   : %s  (%d events, %.1f sec)\n",
		m_opt.midiPath.c_str(), (int)m_events.size(), m_durationMs / 1000.0);
	printf("Output : %s\n", m_out->Name());
	printf("Keys   : Space 일시정지 | ←/→ 5초 이동 | Home 처음 | ↑/↓ 음량 | [ ] 배속 | +/- 조옮김 | 1~0 채널 음소거 | L 반복 | Esc 종료\n");
	fflush(stdout);

	// Ctrl+C로 끊어도 음이 남지 않도록 패닉 핸들러 등록
	s_ctrlOut = m_out.get();
	SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

	timeBeginPeriod(1);   // Sleep 분해능을 1ms로

	ClearNoteMap();
	m_lastTick = steady_clock::now();
	m_lastDraw = m_lastTick;

	while (!m_quit)
	{
		PollKeys();

		// 일시정지가 아니면 실제 경과 시간 × 배속만큼 재생 위치를 전진시킨다
		auto now = steady_clock::now();
		if (!m_paused)
			m_posMs += duration_cast<duration<double, milli>>(now - m_lastTick).count() * m_speed;
		m_lastTick = now;

		// 재생 위치에 도달한 이벤트를 모두 송출
		while (m_eventIndex < m_events.size() && m_events[m_eventIndex]->absTimeMs <= m_posMs)
		{
			Dispatch(*m_events[m_eventIndex]);
			m_eventIndex++;
		}

		// 곡 끝: 반복이면 처음부터, 아니면 종료 (일시정지 중에는 대기 유지 — 뒤로 탐색 가능)
		if (m_eventIndex >= m_events.size())
		{
			if (m_loop) { SeekTo(0.0); continue; }
			if (!m_paused) break;
		}

		DrawStatus(false);

		// 다음 이벤트까지 또는 최대 15ms 대기 — 키 입력 반응성을 위해 길게 자지 않는다
		double waitMs = 15.0;
		if (!m_paused && m_eventIndex < m_events.size())
			waitMs = std::min(waitMs, (m_events[m_eventIndex]->absTimeMs - m_posMs) / m_speed);
		if (waitMs < 1.0) waitMs = 1.0;
		Sleep((DWORD)waitMs);
	}

	timeEndPeriod(1);

	DrawStatus(true);
	printf("\n%s\n", m_quit ? "Stopped." : "Done.");

	// 정리: 패닉 → Ctrl 핸들러 해제 → 백엔드 닫기
	m_out->AllSoundOff();
	SetConsoleCtrlHandler(ConsoleCtrlHandler, FALSE);
	s_ctrlOut = nullptr;
	m_out.reset();
}

// ──────────────────────────────────────────────
// 송출
// ──────────────────────────────────────────────
void MidiPlayer::Dispatch(const CEventRecord& rec)
{
	if (rec.IsMidiEvent())   SendChannelEvent(*rec.AsMidi());
	else if (rec.IsSysEx())  SendSysEx(*rec.AsSysEx());
}

// 조옮김 적용. 드럼 채널(9)은 음높이가 타악기 종류를 뜻하므로 제외한다.
int MidiPlayer::TransposedNote(int ch, int note) const
{
	if (ch == 9 || m_transpose == 0) return note;
	int n = note + m_transpose;
	return (n < 0 || n > 127) ? -1 : n;   // 음역 밖이면 그 음만 연주 생략
}

void MidiPlayer::SendChannelEvent(const CMidiEvent& ev)
{
	int ch = ev.GetChannel();
	int d1 = ev.GetData1();
	int d2 = ev.GetData2();

	switch (ev.GetStatus())
	{
	case NoteOn:
	case NoteOff:
	{
		bool isOn = (ev.GetStatus() == NoteOn) && d2 > 0;   // velocity 0 인 NoteOn은 NoteOff 취급
		if (isOn)
		{
			if (m_mute[ch]) return;            // 음소거 채널: NoteOn만 막으면 음이 새로 나지 않는다
			int n = TransposedNote(ch, d1);
			if (n < 0) return;
			m_noteMap[ch][d1] = (int8_t)n;     // 끌 때를 위해 "실제로 울리는 음높이"를 기록
			m_out->NoteOn(ch, n, d2);
		}
		else
		{
			int n = m_noteMap[ch][d1];
			m_noteMap[ch][d1] = -1;
			m_out->NoteOff(ch, n >= 0 ? n : d1);
		}
		return;
	}
	case ControlChange:   m_out->ControlChange(ch, d1, d2); return;
	case ProgramChange:   m_out->ProgramChange(ch, d1);     return;   // 채널 9(드럼)도 전달 — 드럼 킷 변경 허용
	case ChannelPressure: m_out->ChannelPressure(ch, d1);   return;
	case PolyphonicKeyPressure:
	{
		int n = m_noteMap[ch][d1];
		m_out->KeyPressure(ch, n >= 0 ? n : d1, d2);
		return;
	}
	case PitchBend:       m_out->PitchBend(ch, d1 | (d2 << 7)); return;   // 14비트 = LSB | MSB<<7
	default: return;
	}
}

// SysEx를 0xF0...0xF7 의 완전한 형태로 만들어 백엔드에 넘긴다.
void MidiPlayer::SendSysEx(const CSysExEvent& ev)
{
	const vector<uint8_t>& d = ev.GetData();
	if (d.empty()) return;

	if (ev.GetLeadByte() == 0xF0)
	{
		// SMF에는 선두 0xF0 가 빠진 채 저장되어 있으므로 다시 붙여서 보낸다
		vector<uint8_t> msg;
		msg.reserve(d.size() + 1);
		msg.push_back(0xF0);
		msg.insert(msg.end(), d.begin(), d.end());
		m_out->SysEx(msg.data(), msg.size());
	}
	else
	{
		// 0xF7 이스케이프: 저장된 바이트를 그대로 보낸다
		m_out->SysEx(d.data(), d.size());
	}
}

// ──────────────────────────────────────────────
// 조작
// ──────────────────────────────────────────────
void MidiPlayer::PollKeys()
{
	while (_kbhit())
	{
		int c = _getch();
		if (c == 0 || c == 0xE0)
		{
			// 확장 키(방향키/Home 등)는 두 번째 코드로 구분한다
			int e = _getch();
			switch (e)
			{
			case 75: SeekTo(m_posMs - 5000.0); break;   // ←
			case 77: SeekTo(m_posMs + 5000.0); break;   // →
			case 72: AdjustVolume(+5);         break;   // ↑
			case 80: AdjustVolume(-5);         break;   // ↓
			case 71: SeekTo(0.0);              break;   // Home
			}
			continue;
		}
		switch (c)
		{
		case ' ': TogglePause(); break;
		case 27: case 'q': case 'Q': m_quit = true; break;       // Esc
		case '[': AdjustSpeed(-0.1); break;
		case ']': AdjustSpeed(+0.1); break;
		case '+': case '=': AdjustTranspose(+1); break;
		case '-': case '_': AdjustTranspose(-1); break;
		case 'l': case 'L': m_loop = !m_loop; m_dirty = true; break;
		case '0': ToggleMute(9); break;                          // 0 = 채널 10 (GM 드럼)
		default:
			if (c >= '1' && c <= '9') ToggleMute(c - '1');       // 1~9 = 채널 1~9
			break;
		}
	}
}

void MidiPlayer::TogglePause()
{
	m_paused = !m_paused;
	if (m_paused)
	{
		m_out->AllNotesOff();   // 울리던 음 정리 (재개하면 그 시점의 새 음부터 들린다)
		ClearNoteMap();
	}
	m_dirty = true;
}

void MidiPlayer::ToggleMute(int ch)
{
	m_mute[ch] = !m_mute[ch];
	if (m_mute[ch])
	{
		m_out->NotesOff(ch);
		memset(m_noteMap[ch], -1, sizeof(m_noteMap[ch]));
	}
	m_dirty = true;
}

// 지정 시각으로 이동한다.
// 인덱스만 옮기면 건너뛴 구간의 악기 변경/페달/벤드를 잃어버리므로,
// 목표 지점 이전 이벤트들의 "최종 컨트롤러 상태"를 모아 재전송한다(chase).
void MidiPlayer::SeekTo(double targetMs)
{
	targetMs = std::max(0.0, std::min(m_durationMs, targetMs));

	m_out->AllNotesOff();   // 울리던 음 정리
	ClearNoteMap();

	// 목표 이전 이벤트를 훑으며 채널별 마지막 값만 남긴다 (-1 = 등장 안 함)
	int cc[16][128], prog[16], bend[16], press[16];
	memset(cc,    -1, sizeof(cc));
	memset(prog,  -1, sizeof(prog));
	memset(bend,  -1, sizeof(bend));
	memset(press, -1, sizeof(press));

	size_t idx = 0;
	for (; idx < m_events.size() && m_events[idx]->absTimeMs < targetMs; idx++)
	{
		const CMidiEvent* e = m_events[idx]->AsMidi();
		if (!e) continue;   // SysEx는 chase하지 않는다 (리셋 재전송은 부작용이 더 클 수 있음)
		int ch = e->GetChannel();
		switch (e->GetStatus())
		{
		case ControlChange:   cc[ch][e->GetData1()] = e->GetData2();            break;
		case ProgramChange:   prog[ch]  = e->GetData1();                        break;
		case PitchBend:       bend[ch]  = e->GetData1() | (e->GetData2() << 7); break;
		case ChannelPressure: press[ch] = e->GetData1();                        break;
		default: break;
		}
	}

	// 상태 재전송 — CC(뱅크 셀렉트 0/32 포함)를 먼저 보내고 악기/벤드 순으로
	for (int ch = 0; ch < 16; ch++)
	{
		for (int n = 0; n < 128; n++)
			if (cc[ch][n] >= 0) m_out->ControlChange(ch, n, cc[ch][n]);
		if (prog[ch]  >= 0) m_out->ProgramChange(ch, prog[ch]);
		if (bend[ch]  >= 0) m_out->PitchBend(ch, bend[ch]);
		if (press[ch] >= 0) m_out->ChannelPressure(ch, press[ch]);
	}

	m_eventIndex = idx;
	m_posMs = targetMs;
	m_dirty = true;
}

void MidiPlayer::AdjustVolume(int delta)
{
	m_volume = std::max(0, std::min(100, m_volume + delta));
	m_out->SetVolume(m_volume);
	m_dirty = true;
}

void MidiPlayer::AdjustSpeed(double delta)
{
	m_speed = std::max(0.25, std::min(4.0, m_speed + delta));
	m_dirty = true;
}

void MidiPlayer::AdjustTranspose(int delta)
{
	m_transpose = std::max(-24, std::min(24, m_transpose + delta));
	m_dirty = true;
}

// ──────────────────────────────────────────────
// 표시 — 한 줄짜리 상태를 \r 로 덮어쓴다
// ──────────────────────────────────────────────
void MidiPlayer::DrawStatus(bool force)
{
	auto now = steady_clock::now();
	if (!force && !m_dirty && duration_cast<milliseconds>(now - m_lastDraw).count() < 250)
		return;
	m_lastDraw = now;
	m_dirty = false;

	int pos = (int)(m_posMs / 1000.0);
	int dur = (int)(m_durationMs / 1000.0);

	string flags;
	if (m_loop) flags += "  loop";
	string muted;
	for (int ch = 0; ch < 16; ch++)
		if (m_mute[ch]) muted += (muted.empty() ? "" : ",") + to_string(ch + 1);
	if (!muted.empty()) flags += "  mute:" + muted;

	printf("\r[%s] %02d:%02d / %02d:%02d  x%.2f  vol %3d%%  key %+d%s        ",
		m_paused ? "PAUSE" : "PLAY ",
		pos / 60, pos % 60, dur / 60, dur % 60,
		m_speed, m_volume, m_transpose, flags.c_str());
	fflush(stdout);
}
