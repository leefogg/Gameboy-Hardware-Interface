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
#define register volatile byte&

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
            register Control = 		*reinterpret_cast<byte *>(0xFF40);
            register Stats = 		*reinterpret_cast<byte *>(0xFF41);
            register X = 			*reinterpret_cast<byte *>(0xFF43);
            register Y = 			*reinterpret_cast<byte *>(0xFF42);
            register Scanline = 	*reinterpret_cast<byte *>(0xFF44);
            register InterruptY = 	*reinterpret_cast<byte *>(0xFF45);

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
    System::Output::LCD::enable();
  	System::Output::LCD::X++;
    return System::Output::LCD::getRenderMode();
}
