#include "Serial.h"

using namespace System::Serial;

void System::Serial::setData(byte data) {
	SB = data;
}

byte System::Serial::getData() {
	return SB;
}

void System::Serial::startTransfer() {
	SC |= BIT8;
}

void System::Serial::stopTransfer() {
	SC &= ~BIT8;
}

void System::Serial::setClockSpeed(bool fast) {
	if (fast)
		SC |= BIT2;
	else
		SC &= ~BIT2;
}

void System::Serial::setClockSource(bool internal) {
	if (internal)
		SC |= BIT1;
	else
		SC &= BIT1;
}

void System::Serial::set(bool start, bool fast, bool internal) {
	byte sc;

	if (internal)
		sc |= BIT1;

	if (fast)
		sc |= BIT2;

	if (start)
		sc |= BIT8;

	SC = sc;
}