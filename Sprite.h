#pragma once
namespace System {
	namespace Output {
		namespace LCD {
			namespace Sprites {
				struct Sprite {
				private:
					byte Y;
					byte X;
					byte Attributes;

				public:
					byte Tile;

					void setY(byte y);
					byte getY();

					void setX(byte x);
					byte getX();

					void hide();

					void setPriority(bool above);

					void yFlip(bool flip);
					void xFlip(bool flip);

					void setTileBank(byte bank);

					void setPalette(byte palette);
				};
			}
		}
	}
}