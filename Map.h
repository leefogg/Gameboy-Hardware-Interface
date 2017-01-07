#pragma once

#include "types.h"
#include "Color.h"

namespace System {
	namespace Output {
		namespace LCD {
			namespace Map {
				static volatile byte& BGPI = *reinterpret_cast<byte *>(0xFF68); // Background palette index
				static volatile uint16& BGPD = *reinterpret_cast<uint16 *>(0xFF69); // Background palette data
				static volatile byte& VBK = *reinterpret_cast<byte *>(0xFF4F); // VRAM Bank (0 or 1)

				void setPaletteIndex(byte index);
				void setPaletteIndex(byte index, const bool autoincrement);

				void setPaletteAutoIncrement(const bool autoincrement);

				byte getPaletteIndex();

				void setPaletteColor(uint16 color);
				void setPaletteColor(Color color);

				Color getPaletteColor();

				void setBank(byte bank);
			}
		}
	}
}