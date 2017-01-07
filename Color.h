#pragma once

#include "types.h"
namespace System {
	namespace Output {
		namespace LCD {
			struct Color {
				Color(uint16 Data) : data(Data) {}

				volatile uint16 data;

				// Each component is 5-bit. This is used to mask and erase data.
				static const uint16 componentMask = 0B11111;

				void setRed(byte red);
				void setGreen(byte green);
				void setBlue(byte blue);

				byte getRed();
				byte getGreen();
				byte getBlue();
			};
		}
	}
}
