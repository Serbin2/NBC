#pragma once

#include <cstdio>
#include <cstdint>

// ──────────────────────────────────────────────────────────────
// MIDI 파일 바이너리 읽기 헬퍼
// 표준 MIDI 파일(SMF)은 헤더/트랙의 모든 멀티바이트 정수를
// 빅엔디안(상위 바이트 우선)으로 저장한다.
// ──────────────────────────────────────────────────────────────

// VLQ(Variable Length Quantity) 디코딩.
// MIDI에서 "델타 타임"과 "이벤트 데이터 길이"를 표현하는 가변 길이 정수 형식.
//  - 각 바이트의 하위 7비트(0x7F)만 실제 값으로 사용한다.
//  - 최상위 비트(0x80)가 1이면 "다음 바이트로 이어짐", 0이면 마지막 바이트.
//  - 따라서 0~127은 1바이트, 그 이상은 여러 바이트로 표현된다.
//    예) 0x81 0x00 → (0b0000001 << 7) | 0b0000000 = 128
// readedLen: 이 값을 읽는 데 소비한 바이트 수를 돌려준다(트랙 잔여 길이 계산용).
inline uint32_t ReadVLQ(FILE* fp, uint32_t& readedLen)
{
	uint32_t value = 0;
	readedLen = 0;

	while (1)
	{
		uint8_t c = fgetc(fp);
		readedLen++;

		value = (value << 7) | (c & 0x7F);	// 하위 7비트를 누적

		if (!(c & 0x80))	// 최상위 비트가 0이면 마지막 바이트
			break;
	}

	return value;
}

// 빅엔디안 2바이트(uint16) 읽기. 예) 헤더의 format / tracks / division 필드.
inline uint16_t ReadBE16(FILE* fp)
{
	uint8_t b1 = fgetc(fp);	// 상위 바이트가 먼저 온다
	uint8_t b2 = fgetc(fp);

	return (b1 << 8) | b2;
}

// 빅엔디안 4바이트(uint32) 읽기. 예) 청크 길이 필드.
inline uint32_t ReadBE32(FILE* fp)
{
	uint8_t b1 = fgetc(fp);	// 상위 바이트부터 차례대로
	uint8_t b2 = fgetc(fp);
	uint8_t b3 = fgetc(fp);
	uint8_t b4 = fgetc(fp);

	return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}
