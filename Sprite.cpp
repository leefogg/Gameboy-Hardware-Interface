#i#include "types.h"
#include "Sprite.h"
#include "LCD.h"

using namespace System::Output::LCD;
using namespace System::Output::LCD::Sprites;

void Sprite::setY(byte y) { Y = y + 16; }
byte Sprite::getY() { return Y - 16; }

void Sprite::setX(byte x) { X = x + 8; }
byte Sprite::getX() { return X - 8; }

void Sprite::hide() { Y = height; }

void Sprite::setPriority(bool above) {
	if (above)
		Attributes |= BIT8;
	else
		Attributes &= ~BIT8;
}

void Sprite::yFlip(bool flip) {
	if (flip)
		Attributes |= BIT7;
	else
		Attributes &= ~BIT7;
}
void Sprite::xFlip(bool flip) {
	if (flip)
		Attributes |= BIT6;
	else
		Attributes &= ~BIT6;
}

void Sprite::setTileBank(byte bank) {
	if (bank > 1)
		return;

	if (bank == 1)
		Attributes |= BIT3;
	else
		Attributes &= ~BIT3;
}

void Sprite::setPalette(byte palette) {
	if (palette > 3)
		return;

	Attributes &= 0B11111100;
	Attributes |= palette;
}