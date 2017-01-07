#pragma once

#include "types.h"

namespace System {
	namespace Timer {
		static volatile byte& DIV = *reinterpret_cast<byte *>(0xFF04);
		static volatile byte& TIMA =*reinterpret_cast<byte *>(0xFF05);
		static volatile byte& TMA = *reinterpret_cast<byte *>(0xFF06);
		static volatile byte& TAC = *reinterpret_cast<byte *>(0xFF07);

		void set(byte value);

		void setResetValue(byte value);

		void start();

		void stop();

		void setClock(byte clock);
	}
}