#include "types.h"

#include "LCD.h"

using namespace System::Output::LCD;

RenderMode System::Output::LCD::getRenderMode() {
	return static_cast<RenderMode>(Stats & 0x00000011);
}

bool System::Output::LCD::isRenderingScreen() {
	return Scanline < height;
}

void System::Output::LCD::waitForVblank() {
	while (isRenderingScreen()) { ; }
}

void System::Output::LCD::enable() {
	Control |= BIT8;
}

void System::Output::LCD::disable() {
	waitForVblank();
	Control &= ~BIT8;
}