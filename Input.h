#pragma once

#include "types.h"

namespace System {
	namespace Input {
		static volatile byte& JOYP = *reinterpret_cast<byte *>(0xFF00);

		void enableDPad() {
			JOYP |= BIT5;
		}
		void enableButtons() {
			JOYP |= BIT6;
		}

		byte getControllerBits() {
			byte bits;
			enableDPad();
			bits = JOYP << 4;
			enableButtons();
			bits |= JOYP;
			return bits;
		}
	}
}