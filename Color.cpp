#include "types.h"
#include "Color.h"

using namespace System::Output::LCD;

void System::Output::LCD::Color::setRed(byte red) {
	red &= componentMask; // Limit to 5-bit

	data &= ~componentMask; // Erase previous value
	data |= red; // Set new value
}
void System::Output::LCD::Color::setGreen(byte green) {
	green &= componentMask; // Limit to 5-bit

	data &= ~(componentMask << 5);  // Erase previous value
	data |= (green << 5); // Set new value
}
void System::Output::LCD::Color::setBlue(byte blue) {
	blue &= componentMask; // Limit to 5-bit

	data &= ~(componentMask << 10);  // Erase previous value
	data |= (blue << 10); // Set new value
}

byte System::Output::LCD::Color::getRed() {
	return data & componentMask;
}
byte System::Output::LCD::Color::getGreen() {
	return (data & (componentMask << 5)) >> 5;
}
byte System::Output::LCD::Color::getBlue() {
	return (data & (componentMask << 10)) >> 10;
}