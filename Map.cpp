#include "types.h"
#include "Map.h"
#include "Color.h"

using namespace System::Output::LCD;
using namespace System::Output::LCD::Map;

void System::Output::LCD::Map::setPaletteIndex(byte index) {
	// Limit to 64 range
	index &= 0B00011111; // 64-1, 3F

	byte bgpi = BGPI;
	bgpi &= BIT8; // Preserve the auto increment flag
	bgpi |= index;
	BGPI = bgpi;
}
void System::Output::LCD::Map::setPaletteIndex(byte index, const bool autoincrement) {
	byte bgpi = index;
	// Limit to 64 range
	bgpi &= 0B00011111; // 64-1, 3F

	if (autoincrement)
		bgpi |= BIT8;

	BGPI = bgpi;
}

void System::Output::LCD::Map::setPaletteAutoIncrement(const bool autoincrement) {
	if (autoincrement)
		BGPI |= 0B10000000;
	else
		BGPI &= 0B00011111; // Clear auto increment
}

byte System::Output::LCD::Map::getPaletteIndex() {
	return BGPI & 0B00011111;
}

void System::Output::LCD::Map::setPaletteColor(uint16 color) {
	BGPD = color;
}
void setPaletteColor(Color color) {
	setPaletteColor(color.data);
}

Color System::Output::LCD::Map::getPaletteColor() {
	return Color(BGPD);
}

void System::Output::LCD::Map::setBank(byte bank) {
	if (bank > 1)
		return;

	if (bank == 1)
		VBK |= bank;
	else
		VBK &= ~BIT1;
}