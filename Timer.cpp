#include "Timer.h"

using namespace System::Timer;

void System::Timer::set(byte value) {
	TIMA = value;
}

void System::Timer::setResetValue(byte value) {
	TMA = value;
}

void System::Timer::start() {
	TAC |= BIT3;
}

void System::Timer::stop() {
	TAC &= ~BIT3;
}

void System::Timer::setClock(byte clock) {
	if (clock > 3)
		return;

	byte tac = TAC;
	tac &= 0B11111000;
	tac |= clock;
	TAC = tac;
}