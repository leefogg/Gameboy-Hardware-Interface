#include "Sprites.h"
#include "Color.h"
#include "LCD.h"

using namespace System::Output::LCD;
using namespace System::Output::LCD::Sprites;

void System::Output::LCD::Sprites::set8x8Size() {
	Control &= ~BIT2;
}

void System::Output::LCD::Sprites::set8x16Size() {
	Control |= BIT2;
}

byte System::Output::LCD::Sprites::getSpriteWidth() {
	return 8 + ((Control & ~BIT2) << 1);
}

void System::Output::LCD::Sprites::enable() {
	Control |= BIT2;
}

void System::Output::LCD::Sprites::disable() {
	Control &= ~BIT2;
}

void System::Output::LCD::Sprites::setPaletteIndex(byte index) {
	// Limit to 64 range
	index &= 0B00011111; // 64-1, 3F

	byte obpi = OBPI;
	obpi &= BIT8; // Preserve the auto increment flag
	obpi |= index;
	OBPI = obpi;
}
void System::Output::LCD::Sprites::setPaletteIndex(byte index, const bool autoincrement) {
	byte obpi = index;
	// Limit to 64 range
	obpi &= 0B00011111; // 64-1, 3F

	if (autoincrement)
		obpi |= BIT8;

	OBPI = obpi;
}

void System::Output::LCD::Sprites::setPaletteAutoIncrement(const bool autoincrement) {
	if (autoincrement)
		OBPI |= 0B10000000;
	else
		OBPI &= 0B00011111; // Clear auto increment
}

byte System::Output::LCD::Sprites::getPaletteIndex() {
	return OBPI & 0B00011111;
}

void System::Output::LCD::Sprites::setPaletteColor(uint16 color) {
	OBPD = color;
}
void System::Output::LCD::Sprites::setPaletteColor(Color color) {
	setPaletteColor(color.data);
}

Color System::Output::LCD::Sprites::getPaletteColor() {
	return Color(OBPD);
}