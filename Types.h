#pragma once

typedef unsigned char uint8;
typedef uint8 byte;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;

#define BIT1 1
#define BIT2 (1 << 1)
#define BIT3 (1 << 2)
#define BIT4 (1 << 3)
#define BIT5 (1 << 4)
#define BIT6 (1 << 5)
#define BIT7 (1 << 6)
#define BIT8 (1 << 7)

namespace {
	inline constexpr bool testBit(const byte data, const byte bit) {
		return (data & (1 << bit)) != 0;
	}
}