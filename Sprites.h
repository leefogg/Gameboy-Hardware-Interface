#pragma once

#include "Color.h"
#include "Sprite.h"

namespace System {
	namespace Output {
		namespace LCD {
			namespace Sprites {
				static Sprite* OAM = (Sprite *)0xFE00;

				void set8x8Size();

				void set8x16Size();

				byte getSpriteWidth();

				void enable();

				void disable();

				volatile byte& OBPI = *reinterpret_cast<byte *>(0xFF6A); // Sprite palette index
				volatile uint16& OBPD = *reinterpret_cast<uint16 *>(0xFF6B); // Sprite palette data

				void setPaletteIndex(byte index);
				void setPaletteIndex(byte index, const bool autoincrement);

				void setPaletteAutoIncrement(const bool autoincrement);

				byte getPaletteIndex();

				void setPaletteColor(uint16 color);
				void setPaletteColor(Color color);

				Color getPaletteColor();
			}
		}
	}
}