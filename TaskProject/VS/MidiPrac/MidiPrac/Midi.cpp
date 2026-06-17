#include "Midi.h"
#include <algorithm>
#include <cstring>

// ──────────────────────────────────────────────
// CMidiEvent — 채널(연주) 이벤트
// 상태 바이트는 호출자(CTrack::Parse)가 이미 결정해서 넘겨준다.
// 종류에 따라 뒤따르는 데이터 바이트 수(1개 또는 2개)가 달라진다.
// ──────────────────────────────────────────────
CMidiEvent::CMidiEvent(FILE* fp, uint8_t statusByte)
	: m_iStatus(statusByte), m_iData1(0), m_iData2(0)
{
	switch (statusByte & 0xF0)
	{
	case 0xC0:  // ProgramChange  – 데이터 1바이트
	case 0xD0:  // ChannelPressure – 데이터 1바이트
		m_iData1 = (uint8_t)fgetc(fp);
		m_iByteLength = 1;
		break;
	default:    // 그 외 모든 채널 이벤트 – 데이터 2바이트
		m_iData1 = (uint8_t)fgetc(fp);
		m_iData2 = (uint8_t)fgetc(fp);
		m_iByteLength = 2;
		break;
	}
}

// ──────────────────────────────────────────────
// CSysExEvent — 시스템 익스클루시브 (0xF0 / 0xF7 은 호출자가 이미 소비)
// "VLQ 길이 + 그 길이만큼의 데이터" 구조.
// GM/GS/XG 리셋 같은 초기화 메시지가 실려 오므로 데이터를 보관해 두고,
// 재생 시 출력 장치로 그대로 전달한다.
// ──────────────────────────────────────────────
CSysExEvent::CSysExEvent(FILE* fp, uint8_t leadByte)
	: m_iLeadByte(leadByte)
{
	uint32_t vlqLen = 0;
	uint32_t length = ReadVLQ(fp, vlqLen);
	m_iByteLength = vlqLen + length;            // 길이 필드(VLQ) + 데이터부

	m_aData.resize(length);
	if (length > 0)
		fread(m_aData.data(), 1, length, fp);   // 데이터 보관 (0xF0형이면 보통 끝에 0xF7 포함)
}

// ──────────────────────────────────────────────
// CMetaEvent — 메타 이벤트 (0xFF 는 호출자가 이미 소비)
// 구조: 타입 1바이트 + VLQ 길이 + 길이만큼의 데이터.
// 모든 메타의 본문을 m_aData 에 보관한다(트랙명/박자표/가사 등 시각화에 활용).
// 템포(0x51)는 추가로 값을 뽑아 둔다.
// ──────────────────────────────────────────────
CMetaEvent::CMetaEvent(FILE* fp)
{
	m_iMetaType = (uint8_t)fgetc(fp);   // 메타 타입 (0x2F=트랙끝, 0x51=템포 등)

	uint32_t vlqLen = 0;
	uint32_t length = ReadVLQ(fp, vlqLen);
	m_iByteLength = 1 + vlqLen + length;  // 타입(1) + 길이 필드(VLQ) + 데이터부

	m_aData.resize(length);
	if (length > 0)
		fread(m_aData.data(), 1, length, fp);   // 본문 보관

	// Set Tempo: 보관한 3바이트(빅엔디안)에서 4분음표 하나당 마이크로초를 뽑는다
	if (m_iMetaType == 0x51 && length == 3)
		m_iTempo = ((uint32_t)m_aData[0] << 16)
		         | ((uint32_t)m_aData[1] << 8)
		         |  (uint32_t)m_aData[2];
}

// ──────────────────────────────────────────────
// CChunk — 청크 공통 헤더 파싱
// 모든 청크는 "이름 4바이트 + 길이 4바이트(빅엔디안)"로 시작한다.
// ──────────────────────────────────────────────
void CChunk::ParseChunkHeader(FILE* fp)
{
	fread(m_sName, 1, 4, fp);          // "MThd" 또는 "MTrk"
	m_sName[4]     = '\0';
	m_iLength      = ReadBE32(fp);     // 본문 길이
	m_iByteLength  = m_iLength + 8;    // 청크 전체 = 헤더 8바이트 + 본문
}

// ──────────────────────────────────────────────
// CHeader — "MThd" 헤더 청크 파싱
// ──────────────────────────────────────────────
void CHeader::Parse(FILE* fp)
{
	ParseChunkHeader(fp);            // 이름 + 길이
	m_iFormat   = ReadBE16(fp);     // 0/1/2 (트랙 구성 방식)
	m_iTracks   = ReadBE16(fp);     // 트랙 청크 개수
	m_iDivision = ReadBE16(fp);     // 시간 단위: PPQN 또는 SMPTE (해석은 CHeader::IsSmpte() 참고)
}

// ──────────────────────────────────────────────
// CTrack — "MTrk" 트랙 청크 파싱 (파서의 핵심)
//
// 본문은 "델타타임(VLQ) + 이벤트"의 반복이다.
// 각 이벤트의 absoluteTick(누적 틱)만 여기서 기록하고,
// 실제 시간(absTimeMs)은 모든 트랙을 읽은 뒤 CMidi::ComputeAbsTimes()에서 채운다.
// ──────────────────────────────────────────────
void CTrack::Parse(FILE* fp)
{
	ParseChunkHeader(fp);

	uint32_t bytesRead      = 0;   // 본문에서 읽은 바이트 수(m_iLength에 도달하면 끝)
	uint8_t  runningStatus  = 0;   // 러닝 스테이터스: 직전 채널 이벤트의 종류(상위 4비트)
	uint8_t  runningChannel = 0;   //                 직전 채널 이벤트의 채널(하위 4비트)
	uint32_t absTick        = 0;   // 트랙 시작부터 누적된 틱

	while (bytesRead < m_iLength)
	{
		// 1) 델타타임: 직전 이벤트로부터 떨어진 틱 수
		uint32_t vlqLen = 0;
		uint32_t delta  = ReadVLQ(fp, vlqLen);
		bytesRead += vlqLen;
		absTick   += delta;

		// 2) 다음 바이트로 이벤트 종류 판별
		uint8_t bt = (uint8_t)fgetc(fp);
		bytesRead++;

		if (bt == 0xFF)
		{
			// 메타 이벤트
			auto pEvent = make_unique<CMetaEvent>(fp);
			bytesRead += pEvent->GetByteLength();
			if (pEvent->IsSetTempo())
				m_aTempoChanges.push_back({ absTick, pEvent->GetTempo() }); // 템포 맵에 기록
			bool isEnd = pEvent->IsEndOfTrack();

			// 시각화(트랙명/박자표/가사 등)를 위해 시간과 함께 저장한다
			CEventRecord record;
			record.absoluteTick = absTick;
			record.absTimeMs    = 0.0;
			record.event        = std::move(pEvent);
			m_aEvents.push_back(std::move(record));

			if (isEnd)
				break;  // 트랙 종료
		}
		else if (bt == 0xF0 || bt == 0xF7)
		{
			// SysEx 이벤트 — 재생 시 전달할 수 있도록 시간 정보와 함께 저장
			auto pEvent = make_unique<CSysExEvent>(fp, bt);
			bytesRead += pEvent->GetByteLength();

			CEventRecord record;
			record.absoluteTick = absTick;
			record.absTimeMs    = 0.0;
			record.event        = std::move(pEvent);
			m_aEvents.push_back(std::move(record));
		}
		else
		{
			// 채널(연주) 이벤트
			uint8_t statusByte;
			if (bt & 0x80)
			{
				// 최상위 비트가 1 → 이 바이트 자체가 상태 바이트.
				// 러닝 스테이터스를 갱신해 둔다.
				runningStatus  = bt & 0xF0;
				runningChannel = bt & 0x0F;
				statusByte = bt;
			}
			else
			{
				// 최상위 비트가 0 → 상태 바이트가 생략됨(러닝 스테이터스).
				// 방금 읽은 바이트는 사실 데이터이므로 되돌려 놓고,
				// 직전 상태 바이트를 재사용한다.
				ungetc(bt, fp);
				bytesRead--;
				statusByte = runningStatus | runningChannel;
			}

			auto pEvent = make_unique<CMidiEvent>(fp, statusByte);
			bytesRead += pEvent->GetByteLength();

			// 시간 정보와 함께 이벤트 저장 (absTimeMs 는 나중에 계산)
			CEventRecord record;
			record.absoluteTick = absTick;
			record.absTimeMs    = 0.0;
			record.event        = std::move(pEvent);
			m_aEvents.push_back(std::move(record));
		}
	}
}

// 이 트랙의 첫 트랙명(메타 0x03)을 돌려준다. 없으면 빈 문자열.
string CTrack::GetTrackName() const
{
	for (const auto& rec : m_aEvents)
		if (const CMetaEvent* m = rec.AsMeta())
			if (m->IsTrackName())
				return m->GetText();
	return "";
}

// NoteOn↔NoteOff 를 짝지어 피아노롤용 노트 막대(NoteSegment) 목록을 만든다.
// 같은 (채널, 음높이)가 닫히기 전에 다시 켜지면 현재 시각에서 끊고 새로 시작하며,
// 트랙이 끝날 때까지 닫히지 않은 음은 마지막 이벤트 시각으로 마감한다.
// (absTimeMs 가 채워진 뒤 — 즉 CMidi 파싱 완료 후 — 호출해야 정확하다)
vector<NoteSegment> CTrack::BuildNoteSegments() const
{
	vector<NoteSegment> segments;

	// (채널, 음높이)별로 열려 있는 음 추적
	bool    open[16][128];
	double  startMs[16][128];
	uint8_t startVel[16][128];
	memset(open, 0, sizeof(open));

	double lastMs = 0.0;
	for (const auto& rec : m_aEvents)
	{
		if (rec.absTimeMs > lastMs) lastMs = rec.absTimeMs;

		const CMidiEvent* e = rec.AsMidi();
		if (!e) continue;

		MidiEventStatus st = e->GetStatus();
		int ch   = e->GetChannel();
		int note = e->GetNote();

		bool isOn  = (st == NoteOn) && e->GetVelocity() > 0;          // velocity 0 NoteOn = NoteOff
		bool isOff = (st == NoteOff) || (st == NoteOn && e->GetVelocity() == 0);

		if (isOn)
		{
			if (open[ch][note])   // 안 닫힌 채 다시 켜짐 → 현재 시각에서 끊고 새로 시작
				segments.push_back({ (uint8_t)ch, (uint8_t)note, startVel[ch][note], startMs[ch][note], rec.absTimeMs });
			open[ch][note]     = true;
			startMs[ch][note]  = rec.absTimeMs;
			startVel[ch][note] = e->GetVelocity();
		}
		else if (isOff && open[ch][note])
		{
			segments.push_back({ (uint8_t)ch, (uint8_t)note, startVel[ch][note], startMs[ch][note], rec.absTimeMs });
			open[ch][note] = false;
		}
	}

	// 닫히지 않은 음은 트랙 마지막 시각으로 마감
	for (int ch = 0; ch < 16; ch++)
		for (int n = 0; n < 128; n++)
			if (open[ch][n])
				segments.push_back({ (uint8_t)ch, (uint8_t)n, startVel[ch][n], startMs[ch][n], lastMs });

	// 그리기 편하도록 시작 시각 순으로 정렬
	sort(segments.begin(), segments.end(),
		[](const NoteSegment& a, const NoteSegment& b) { return a.startMs < b.startMs; });
	return segments;
}

// ──────────────────────────────────────────────
// CMidi
// ──────────────────────────────────────────────

// 틱 위치(absTick)를 밀리초로 변환한다.
// 변환 비율은 템포에 따라 달라지므로, 구간별로 누적해서 계산한다.
//   1틱당 ms = (박자당 마이크로초) / (division 틱) / 1000
// tempoMap 은 틱 오름차순으로 정렬되어 있어야 한다.
double CMidi::TicksToMs(uint32_t absTick, uint16_t division,
                         const vector<TempoChange>& tempoMap)
{
	double   ms       = 0.0;
	uint32_t prevTick = 0;
	double   tickToMs = 500000.0 / (division * 1000.0);  // 기본 템포 120 BPM(500000us)

	for (const auto& change : tempoMap)
	{
		if (change.absoluteTick >= absTick) break;       // 목표 틱을 넘어선 템포는 무시
		ms       += (change.absoluteTick - prevTick) * tickToMs;  // 이전 템포 구간 누적
		prevTick  = change.absoluteTick;
		tickToMs  = change.tempoUs / (division * 1000.0);         // 이 지점부터 새 비율
	}
	ms += (absTick - prevTick) * tickToMs;   // 마지막 템포 구간
	return ms;
}

// 각 이벤트의 absTimeMs(절대 시각)를 채운다.
// division 해석 방식(PPQN/SMPTE)에 따라 틱→시간 변환 규칙이 다르다.
void CMidi::ComputeAbsTimes()
{
	// ── SMPTE 방식 (division 최상위 비트 = 1) ──
	// 틱이 박자가 아니라 시간(프레임)에 직접 고정된다.
	//   1틱당 ms = 1000 / (프레임 레이트 × 프레임당 틱 수)
	// 템포 메타 이벤트는 SMPTE 모드의 시간 계산에 영향을 주지 않는다.
	if (m_cHeader.IsSmpte())
	{
		double ticksPerFrame = m_cHeader.GetTicksPerFrame();
		if (ticksPerFrame <= 0.0) ticksPerFrame = 1.0;   // 잘못된 파일 방어 (0 나눗셈 방지)
		double msPerTick = 1000.0 / (m_cHeader.GetSmpteFps() * ticksPerFrame);

		for (auto& track : m_aTracks)
		{
			for (auto& record : track.GetEvents())
				record.absTimeMs = record.absoluteTick * msPerTick;
		}
		return;
	}

	// ── PPQN 방식 (division 최상위 비트 = 0) ──
	// 모든 트랙의 템포 변경을 하나로 모아 전역 템포 맵을 만든 뒤 틱을 시간으로 바꾼다.
	// Format 1 파일에서 템포는 트랙 0에, 음표는 트랙 1+ 에 있는 경우를
	// 올바르게 처리하기 위해 "전역" 템포 맵을 쓴다.

	// 1. 모든 트랙에서 템포 변경을 수집해 틱 순으로 정렬
	vector<TempoChange> tempoMap;
	for (const auto& track : m_aTracks)
	{
		for (const auto& tc : track.GetTempoChanges())
			tempoMap.push_back(tc);
	}
	sort(tempoMap.begin(), tempoMap.end(),
		[](const TempoChange& a, const TempoChange& b) {
			return a.absoluteTick < b.absoluteTick;
		});

	// 2. 모든 이벤트의 틱을 절대 시각(ms)으로 변환
	uint16_t division = m_cHeader.GetDivision();
	if (division == 0) division = 480;   // 잘못된 파일 방어 (0이면 변환 불가)
	for (auto& track : m_aTracks)
	{
		for (auto& record : track.GetEvents())
			record.absTimeMs = TicksToMs(record.absoluteTick, division, tempoMap);
	}
}

// 파일을 열어 헤더 → 트랙들 순서로 파싱하고, 마지막에 절대 시각을 계산한다.
CMidi::CMidi(const char* filePath)
{
	FILE* fp;
	if (fopen_s(&fp, filePath, "rb") != 0 || !fp) return;  // 바이너리 모드로 열기

	m_cHeader.Parse(fp);   // "MThd"

	// 헤더가 알려 준 개수만큼 트랙("MTrk")을 차례로 파싱
	m_aTracks.reserve(m_cHeader.GetNumberOfTracks());
	for (int i = 0; i < m_cHeader.GetNumberOfTracks(); i++)
	{
		CTrack track;
		track.Parse(fp);
		m_aTracks.push_back(std::move(track));
	}

	fclose(fp);

	ComputeAbsTimes();   // 틱 → 밀리초
}
