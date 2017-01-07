#pragma once

#include "types.h"

namespace System {
	namespace Serial {
		static volatile byte& SB = *reinterpret_cast<byte *>(0xFF01);
		static volatile byte& SC = *reinterpret_cast<byte *>(0xFF02);

		void setData(byte data);

		byte getData();

		void startTransfer();

		void stopTransfer();

		void setClockSpeed(bool fast);

		void setClockSource(bool internal);

		void set(bool start, bool fast, bool internal);
	}
}