#pragma once

#include "types.h"

namespace System {
	namespace Output {
		namespace Sound {
			static volatile byte& NR50 = *reinterpret_cast<byte *>(0xFF24);
			static volatile byte& NR51 = *reinterpret_cast<byte *>(0xFF25);
			static volatile byte& NR52 = *reinterpret_cast<byte *>(0xFF26);

			void addChannelToSO1(byte channel);

			void addChannelToSO2(byte channel);

			void removeChannelFromSO1(byte channel);

			void removeChannelFromSO2(byte channel);

			void setSO1Volume(byte volume);

			void setSO2Volume(byte volume);

			void enable();

			void disable();
		}
	}
}