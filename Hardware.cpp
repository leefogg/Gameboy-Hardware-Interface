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

struct Color {
  	Color(uint16 Data) : data(Data) {}
  	
  	volatile uint16 data;
  
  	static const uint16 componentMask = 0B11111;
  
  	byte setRed(byte red) {
      red &= componentMask;
      
      data &= ~componentMask;
      data |= red;
    }
  	byte setGreen(byte green) {
      green &= componentMask;
      
      data &= ~(componentMask << 5);
      data |= (green << 5);
    }
	byte setBlue(byte blue) {
      blue &= componentMask;
      
      data &= ~(componentMask << 10);
      data |= (blue << 10);
    }
  	
  	byte getRed() {
     	return data & componentMask;
    }
  	byte getGreen() {
     	return (data & (componentMask << 5)) >> 5;
    }
  	byte getBlue() {
     	return (data & (componentMask << 10)) >> 10;
    }
};

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
        static volatile byte& JOYP = *reinterpret_cast<byte *>(0xFF00);
		
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
			const byte 
            width = 160,
			height = 144;
          
            static volatile byte& Control = 	*reinterpret_cast<byte *>(0xFF40);
            static volatile byte& Stats = 		*reinterpret_cast<byte *>(0xFF41);
            static volatile byte& X = 			*reinterpret_cast<byte *>(0xFF43);
            static volatile byte& Y = 			*reinterpret_cast<byte *>(0xFF42);
            static volatile byte& Scanline = 	*reinterpret_cast<byte *>(0xFF44);
            static volatile byte& InterruptY = 	*reinterpret_cast<byte *>(0xFF45);
			
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
			
          	namespace Map {
				static volatile byte& BGPI  = *reinterpret_cast<byte *>(0xFF68); // Background palette index
              	static volatile uint16& BGPD  = *reinterpret_cast<uint16 *>(0xFF69); // Background palette data
              
              	static void setPaletteIndex(byte index) {                	
                  	// Limit to 64 range
                  	index &= 0B00011111; // 64-1, 3F
                  
                  	byte bgpi = BGPI;
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
              
              	static void setPaletteColor(uint16 color) {
                 	 BGPD = color;
                }
              	static void setPaletteColor(Color color) {
                 	 setPaletteColor(color.data);
                }
              
             	 static Color getPaletteColor() {
                 	 return Color(BGPD);
                }
				
				static void setBank(byte bank) {
                  	if (bank > 1)
                      	return;

                  	if (bank == 1)
                  		VBK |= bank;
                  	else
						VBK &= ~BIT1;                      
                }
            }
			
          	namespace Sprites {
              	struct Sprite {
                  private:
                  byte Y;
                  byte X;
                  byte Attributes;
                  
                  public:
                  byte Tile;
                  
                  void setY(byte y) { Y = y+16; }
                  byte getY(){ return Y-16; }
                  
                  void setX(byte x) { X = x+8; }
                  byte getX(){ return X-8; }
                  
                  void hide() { Y = height; }
                  
                  void setPriority(bool above) {
                   	 if (above)
                    	Attributes |= BIT8;
                    else
                    	Attributes &= ~BIT8; 
                  }
                  
                  void yFlip(bool flip) {
                   	  if (flip)
                    	Attributes |= BIT7;
                    else
                    	Attributes &= ~BIT7;
                  }
                  void xFlip(bool flip) {
                   	  if (flip)
                    	Attributes |= BIT6;
                    else
                    	Attributes &= ~BIT6;
                  }
				  
                  void setTileBank(byte bank) {
                   	if (bank > 1)
                      return;
                       
                    if (bank == 1)
                    	Attributes |= BIT3;
                    else
                    	Attributes &= ~BIT3;  
                  }
                  
                  void setPalette(byte palette) {
                  	if (palette > 3)
                      return;
					
                    Attributes &= 0B11111100;
                    Attributes |= palette;
                  }
                };
              
              	static Sprite* OAM = (Sprite *)0xFE00;
              	
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
              	
              	static volatile byte& OBPI  = 	*reinterpret_cast<byte *>(0xFF6A); // Sprite palette index
              	static volatile uint16& OBPD  = *reinterpret_cast<uint16 *>(0xFF6B); // Sprite palette data
              	
              	static void setPaletteIndex(byte index) {                	
                  	// Limit to 64 range
                  	index &= 0B00011111; // 64-1, 3F
                  
                  	byte obpi = OBPI;
                  	obpi &= BIT8; // Preserve the auto increment flag
                  	obpi |= index;
                  	OBPI = obpi;
                }
              	static void setPaletteIndex(byte index, const bool autoincrement) {
                  	byte obpi = index;
                  	// Limit to 64 range
                 	obpi &= 0B00011111; // 64-1, 3F
                  	
                  	if (autoincrement)
                    	obpi |= BIT8;
                 	
                  	OBPI = obpi;
                }
              	
              	static void setPaletteAutoIncrement(const bool autoincrement) {                	
                  	if (autoincrement) 
                      OBPI |= 0B10000000;
                  	else
                      OBPI &= 0B00011111; // Clear auto increment
                }
              
              	static byte getPaletteIndex() {
                 	return OBPI & 0B00011111;
                }
              
              	static void setPaletteColor(uint16 color) {
                 	 OBPD = color;
                }
              	static void setPaletteColor(Color color) {
                 	 setPaletteColor(color.data);
                }
              
             	 static Color getPaletteColor() {
                 	 return Color(OBPD);
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
