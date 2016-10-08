#define BIT1 1
#define BIT2 (1 << 1)
#define BIT3 (1 << 2)
#define BIT4 (1 << 3)
#define BIT5 (1 << 4)
#define BIT6 (1 << 5)
#define BIT7 (1 << 6)
#define BIT8 (1 << 7)

typedef unsigned char uint8;
typedef uint8 byte;
typedef char int8;
typedef unsigned short uint16; 
typedef short int16;

namespace {
  	inline constexpr bool testBit(const byte data, const byte bit) {
      	return (data & (1 << bit)) != 0;
    }
  	
  	inline constexpr byte setBit(const byte bit, byte data) {
      	data |= (1 << (bit-1));
      	return data;
    }
  	
  	inline constexpr byte clearBit(const byte bit, byte data) {
      	data &= ~(1 << (bit-1));
      	return data;
    }
}

namespace System {
    inline volatile byte &memory(const uint16 loc) {
     	return *reinterpret_cast<byte *>(loc);
    }
  
  	namespace Input {
        volatile byte& JOYP = *reinterpret_cast<byte *>(0xFF00);

        static void enableDPad() {
          	JOYP |= BIT5;
        }
        static void enableButtons() {
          	JOYP |= BIT6;
        }

        static byte getControllerBits() {
            byte bits;
            enableDPad();
            bits = JOYP << 4;
            enableButtons();
            bits |= JOYP;
            return bits;
        }

        struct Controller {
            Controller(const byte data) : 
                A(testBit(data, 0)), 
                B(testBit(data, 1)), 
                Select(testBit(data, 2)),
                Start(testBit(data, 3)),
                Left(testBit(data, 4)), 
                Right(testBit(data, 5)), 
                Up(testBit(data, 6)),
                Down(testBit(data, 7)){
            }

            Controller() : 
                Controller(getControllerBits()) {
            }

            bool A, B, Start, Select, Up, Down, Left, Right;
        };
    }
	
  	namespace Output {
        namespace LCD {
            volatile byte& Control = 	*reinterpret_cast<byte *>(0xFF40);
            volatile byte& Stats = 		*reinterpret_cast<byte *>(0xFF41);
            volatile byte& X = 			*reinterpret_cast<byte *>(0xFF43);
            volatile byte& Y = 			*reinterpret_cast<byte *>(0xFF42);
            volatile byte& Scanline = 	*reinterpret_cast<byte *>(0xFF44);
            volatile byte& InterruptY = *reinterpret_cast<byte *>(0xFF45);

            enum RenderMode {
                Hblank,
                Vblank,
                OAM,
                VRAM
            };

           	static RenderMode getRenderMode() {
                return static_cast<RenderMode>(Stats & 0x00000011);
            }
          
          	static bool isRenderingScreen() {
        		return Scanline < 144; 
        	}
      
            static void waitForVblank() {
                while(isRenderingScreen()){;} 
            }
          
          	static void enable() {
            	Control |= BIT8;
            }
          	
          	static void disable() {
            	waitForVblank();
              	Control &= ~BIT8;
            }
          
          	namespace Background {
				volatile byte& BGPI  = *reinterpret_cast<byte *>(0xFF68); // Background palette index
              	volatile byte& BGPD  = *reinterpret_cast<byte *>(0xFF69); // Background palette data
              
              	static void setPaletteIndex(byte index) {
                	byte bgpi = BGPI;
                  	// Limit to 64 range
                  	index &= 0B00011111; // 64-1, 3F
                  	
                  	bgpi &= BIT8; // Preserve the auto increment flag
                  	bgpi |= index;
                  	BGPI = bgpi;
                }
              	static void setPaletteIndex(byte index, const bool autoincrement) {
                  	byte bgpi = index;
                  	// Limit to 64 range
                 	bgpi &= 0B00011111; // 64-1, 3F
                  	
                  	if (autoincrement)
                    	bgpi |= BIT8;
                 	
                  	BGPI = bgpi;
                }
              	
              	static void setPaletteAutoIncrement(const bool autoincrement) {                	
                  	if (autoincrement) 
                      BGPI |= 0B10000000;
                  	else
                      BGPI &= 0B00011111; // Clear auto increment
                }
              
              	static byte getPaletteIndex() {
                 	return BGPI & 0B00011111;
                }
            }
          
          	namespace Sprites {
				static void set8x8Size() {
                  	Control &= ~BIT2;
                }
              
              	static void set8x16Size() {
                  	Control |= BIT2;
                }
              
              	static byte getSpriteWidth() {
                 	return 8 + ((Control & ~BIT2) << 1);
                }
              
              	static void enable() {
                	Control |= BIT2;
                }
              
              	static void disable() {
                  	Control &= ~BIT2;
                }
            }
        }
    }

  	// Interrupts
  	static void enableScanlineInterrput() {
    	Output::LCD::Stats |= BIT6; 
    }
  	static void enableOAMInterrupt() {
    	Output::LCD::Stats |= BIT5; 
    }
  	static void enableVblankInterrput() {
    	Output::LCD::Stats |= BIT4; 
    }
  	static void enableHblankInterrput() {
    	Output::LCD::Stats |= BIT3; 
    }
}

int main() {
    System::Output::LCD::Background::getPaletteIndex();
}
