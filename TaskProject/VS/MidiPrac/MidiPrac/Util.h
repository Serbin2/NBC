#pragma once

#include <deque>
#include <cstdio>

uint32_t ReadVLQ(FILE* fp, uint32_t& readedLen)
{
	uint32_t value = 0;
	readedLen = 0;

	while (1)
	{
		uint8_t c = fgetc(fp);
		readedLen++;

		value = (value << 7) | (c & 0x7F);	// 0111 1111

		if (!(c & 0x80))	//	1000 0000
			break;
	}

	return value;
}

uint16_t ReadBE16(FILE* fp)
{
	uint8_t b1 = fgetc(fp);
	uint8_t b2 = fgetc(fp);

	return (b1 << 8) | b2;
}

uint32_t ReadBE32(FILE* fp)
{
	uint8_t b1 = fgetc(fp);
	uint8_t b2 = fgetc(fp);
	uint8_t b3 = fgetc(fp);
	uint8_t b4 = fgetc(fp);

	return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}