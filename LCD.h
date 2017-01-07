#pragma once

#include "types.h"
#include "RenderMode.h"

namespace System {
	namespace Output {
		namespace LCD {
			static const byte
				width = 160,
				height = 144;

			static volatile byte& Control = *reinterpret_cast<byte *>(0xFF40);
			static volatile byte& Stats = *reinterpret_cast<byte *>(0xFF41);
			static volatile byte& X = *reinterpret_cast<byte *>(0xFF43);
			static volatile byte& Y = *reinterpret_cast<byte *>(0xFF42);
			static volatile byte& Scanline = *reinterpret_cast<byte *>(0xFF44);
			static volatile byte& InterruptY = *reinterpret_cast<byte *>(0xFF45);

			RenderMode getRenderMode();

			bool isRenderingScreen();

			void waitForVblank();

			void enable();

			void disable();
		}
	}
}