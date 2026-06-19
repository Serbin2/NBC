#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

// ──────────────────────────────────────────────────────────────
// MIDI 파일 바이너리 읽기 헬퍼
// 표준 MIDI 파일(SMF)은 헤더/트랙의 모든 멀티바이트 정수를
// 빅엔디안(상위 바이트 우선)으로 저장한다.
//
// 입력은 FILE* 가 아니라 "메모리 버퍼"다(CByteReader). 파일을 통째로 읽어
// 두든, 언리얼 에셋/pak/네트워크에서 받은 바이트든, 배열로만 만들면 파싱할 수 있다.
// → 파서가 특정 입력 방식(stdio)에 묶이지 않아 어디서든 재사용 가능하다.
// ──────────────────────────────────────────────────────────────

// 메모리 버퍼 위를 앞에서부터 순차적으로 읽는 경량 리더.
//  - 범위를 벗어난 읽기는 0을 돌려준다(범위 밖 메모리 접근 방지 — 손상된 파일 방어).
//  - 위치(position)는 끝을 넘어도 계속 전진시켜 길이 계산의 일관성을 유지한다.
class CByteReader
{
public:
	CByteReader(const uint8_t* data, size_t size)
		: m_pData(data), m_iSize(size), m_iPos(0) {}

	// 한 바이트를 읽고 전진. 버퍼 끝을 넘으면 0을 돌려준다.
	uint8_t ReadByte()
	{
		uint8_t b = (m_iPos < m_iSize) ? m_pData[m_iPos] : (uint8_t)0;
		m_iPos++;
		return b;
	}

	// n바이트를 dst로 복사하고 전진. 버퍼가 모자라면 가능한 만큼만 복사하고
	// 나머지는 0으로 채운다(부분 손상 파일에서도 안전).
	void ReadBytes(void* dst, size_t n)
	{
		size_t avail = (m_iPos < m_iSize) ? (m_iSize - m_iPos) : 0;
		size_t copy  = (n < avail) ? n : avail;
		if (copy > 0)
			memcpy(dst, m_pData + m_iPos, copy);
		if (copy < n)
			memset((uint8_t*)dst + copy, 0, n - copy);   // 부족분은 0
		m_iPos += n;
	}

	// 직전에 읽은 한 바이트를 되돌린다(러닝 스테이터스 복원용).
	void Unget() { if (m_iPos > 0) m_iPos--; }

	size_t Position() const { return m_iPos; }
	bool   Eof()      const { return m_iPos >= m_iSize; }

private:
	const uint8_t* m_pData;
	size_t         m_iSize;
	size_t         m_iPos;
};

// VLQ(Variable Length Quantity) 디코딩.
// MIDI에서 "델타 타임"과 "이벤트 데이터 길이"를 표현하는 가변 길이 정수 형식.
//  - 각 바이트의 하위 7비트(0x7F)만 실제 값으로 사용한다.
//  - 최상위 비트(0x80)가 1이면 "다음 바이트로 이어짐", 0이면 마지막 바이트.
//  - 따라서 0~127은 1바이트, 그 이상은 여러 바이트로 표현된다.
//    예) 0x81 0x00 → (0b0000001 << 7) | 0b0000000 = 128
// readedLen: 이 값을 읽는 데 소비한 바이트 수를 돌려준다(트랙 잔여 길이 계산용).
inline uint32_t ReadVLQ(CByteReader& reader, uint32_t& readedLen)
{
	uint32_t value = 0;
	readedLen = 0;

	while (true)
	{
		uint8_t c = reader.ReadByte();
		readedLen++;

		value = (value << 7) | (c & 0x7F);	// 하위 7비트를 누적

		if (!(c & 0x80))	// 최상위 비트가 0이면 마지막 바이트
			break;
		if (readedLen >= 4)	// VLQ는 최대 4바이트 — 손상된 파일에서 무한 루프 방지
			break;
	}

	return value;
}

// 빅엔디안 2바이트(uint16) 읽기. 예) 헤더의 format / tracks / division 필드.
inline uint16_t ReadBE16(CByteReader& reader)
{
	uint8_t b1 = reader.ReadByte();	// 상위 바이트가 먼저 온다
	uint8_t b2 = reader.ReadByte();

	return (uint16_t)((b1 << 8) | b2);
}

// 빅엔디안 4바이트(uint32) 읽기. 예) 청크 길이 필드.
inline uint32_t ReadBE32(CByteReader& reader)
{
	uint8_t b1 = reader.ReadByte();	// 상위 바이트부터 차례대로
	uint8_t b2 = reader.ReadByte();
	uint8_t b3 = reader.ReadByte();
	uint8_t b4 = reader.ReadByte();

	return ((uint32_t)b1 << 24) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 8) | (uint32_t)b4;
}
