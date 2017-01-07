#include "types.h"
#include "Sound.h"

void System::Output::Sound::addChannelToSO1(byte channel) {
	if (channel > 4)
		return;

	NR51 |= BIT1 << channel;
}

void System::Output::Sound::addChannelToSO2(byte channel) {
	if (channel > 4)
		return;

	NR51 |= BIT5 << channel;
}

void System::Output::Sound::removeChannelFromSO1(byte channel) {
	if (channel > 3)
		return;

	NR51 &= ~(BIT1 << channel);
}

void System::Output::Sound::removeChannelFromSO2(byte channel) {
	if (channel > 3)
		return;

	NR51 &= ~(BIT5 << channel);
}

void System::Output::Sound::setSO1Volume(byte volume) {
	if (volume > 7)
		return;

	byte nr50 = NR50;
	nr50 &= 0B11111000;
	nr50 |= volume << 4;
	NR50 = nr50;
}

void System::Output::Sound::setSO2Volume(byte volume) {
	if (volume > 7)
		return;

	byte nr50 = NR50;
	nr50 &= 0B10001111;
	nr50 |= volume << 4;
	NR50 = nr50;
}

void System::Output::Sound::enable() {
	NR52 |= BIT8;
}

void System::Output::Sound::disable() {
	NR52 &= ~BIT8;
}