//-------------------------------------------------------------------
#ifndef TFT_H
#define TFT_H

#include "HT32IO.h"
#include "Stream.h"

#define RED  		0xf800
#define GREEN		0x07e0
#define BLUE 		0x001f
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   
#define GRAY1   0x8410      	
#define GRAY2   0x4208   

//#define USE_LANDSCAPE	1

//-------------------------------------------------------------------
//  PARAMETERS
#define LCDWIDTH 						128
#define LCDHEIGHT 					64
#define MAXROWS 						7
#define MAXCONTRAST 				0xFF

// command table
#define SETCONTRAST 				0x81
#define DISPLAYALLON_RESUME	0xA4
#define DISPLAYALLON 				0xA5
#define NORMALDISPLAY 			0xA6
#define INVERTDISPLAY 			0xA7
#define DISPLAYOFF 					0xAE
#define DISPLAYON 					0xAF

// scrolling commands
#define ACTIVATE_SCROLL 		0x2F
#define DEACTIVATE_SCROLL 	0x2E
#define SCROLL_RIGHT				0x26
#define SCROLL_LEFT					0X27
#define SCROLL_VERT_RIGHT		0x29
#define SCROLL_VERT_LEFT		0x2A
#define SET_VERTICAL				0xA3

// speed is in number of frames
#define Scroll_2Frames			0x07
#define Scroll_3Frames			0x04
#define Scroll_4Frames			0x05
#define Scroll_5Frames			0x00
#define Scroll_25Frames			0x06
#define Scroll_64Frames			0x01
#define Scroll_128Frames		0x02
#define Scroll_256Frames		0x03

// address setting
#define SETLOWCOLUMN 				0x00
#define SETHIGHCOLUMN 			0x10
#define MEMORYMODE 					0x20
#define COLUMNADDRESS 			0x21
#define COLUMNADDRESS_MSB 	0x00
#define COLUMNADDRESS_LSB 	0x7F
#define PAGEADDRESS					0x22
#define PAGE_START_ADDRESS 	0xB0

// hardware configuration
#define SETSTARTLINE        0x40
#define SEGREMAP            0xA1
#define SETMULTIPLEX        0xA8
#define COMSCANINC          0xC0
#define COMSCANDEC          0xC8
#define SETDISPLAYOFFSET    0xD3
#define SETCOMPINS          0xDA

// timing and driving
#define SETDISPLAYCLOCKDIV  0xD5
#define SETPRECHARGE        0xD9
#define SETVCOMDETECT       0xDB
#define SETNOP                 0xE3

// power supply configuration
#define CHARGEPUMP          0x8D
#define EXTERNALVCC         0x10
#define SWITCHCAPVCC        0x20

static const unsigned char FONT8x16[] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //" "
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x10,0x10,0x00,0x00, //"!"
0x00,0x00,0x6C,0x6C,0x24,0x24,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00, //"""
0x00,0x24,0x24,0x24,0x24,0xFE,0x48,0x48,0x48,0x48,0xFC,0x90,0x90,0x90,0x90,0x00, //"#"
0x00,0x10,0x3C,0x54,0x92,0x90,0x50,0x38,0x14,0x12,0x12,0x92,0x54,0x78,0x10,0x00, //"$"
0x00,0x00,0x22,0x5C,0x94,0xA8,0x48,0x10,0x10,0x24,0x2A,0x52,0x54,0x88,0x00,0x00, //"%"
0x00,0x00,0x30,0x48,0x48,0x50,0x20,0x6E,0x54,0x94,0x8C,0x88,0x8A,0x74,0x00,0x00, //"&"
0x00,0x00,0x30,0x30,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"'"
0x00,0x04,0x08,0x10,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x08,0x04,0x00, //"("
0x00,0x80,0x40,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x20,0x40,0x80,0x00, //")"
0x00,0x00,0x00,0x00,0x10,0x54,0x38,0x10,0x38,0x54,0x10,0x00,0x00,0x00,0x00,0x00, //"*"
0x00,0x00,0x00,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00, //"+"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x00, //","
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"-"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00, //"."
0x00,0x00,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x80,0x00,0x00, //"/"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"0"
0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00, //"1"
0x00,0x00,0x38,0x44,0x82,0x82,0x04,0x08,0x10,0x20,0x40,0x82,0x84,0xFC,0x00,0x00, //"2"
0x00,0x00,0x38,0x44,0x82,0x02,0x04,0x38,0x04,0x02,0x02,0x82,0x44,0x38,0x00,0x00, //"3"
0x00,0x00,0x04,0x0C,0x14,0x14,0x24,0x24,0x44,0x44,0xFE,0x04,0x04,0x0E,0x00,0x00, //"4"
0x00,0x00,0xFC,0x80,0x80,0x80,0xB8,0xC4,0x82,0x02,0x02,0x82,0x84,0x78,0x00,0x00, //"5"
0x00,0x00,0x3C,0x42,0x82,0x80,0xB8,0xC4,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"6"
0x00,0x00,0x7E,0x42,0x82,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x10,0x00,0x00, //"7"
0x00,0x00,0x38,0x44,0x82,0x82,0x44,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"8"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x46,0x3A,0x02,0x82,0x44,0x38,0x00,0x00, //"9"
0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00, //":"
0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x00,0x00, //";"
0x00,0x00,0x00,0x00,0x06,0x18,0x60,0x80,0x60,0x18,0x06,0x00,0x00,0x00,0x00,0x00, //"<"
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00, //"="
0x00,0x00,0x00,0x00,0xC0,0x30,0x0C,0x02,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00, //">"
0x00,0x38,0x44,0x82,0x82,0x02,0x04,0x08,0x10,0x10,0x10,0x00,0x10,0x10,0x00,0x00, //"?"
0x00,0x00,0x38,0x44,0x82,0x9A,0xAA,0xAA,0xAA,0xAA,0xAA,0x96,0x80,0x42,0x3C,0x00, //"@"
0x00,0x00,0x10,0x10,0x10,0x28,0x28,0x28,0x44,0x44,0x7C,0x44,0x44,0xEE,0x00,0x00, //"A"
0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0x42,0x42,0xFC,0x00,0x00, //"B"
0x00,0x00,0x3C,0x44,0x82,0x80,0x80,0x80,0x80,0x80,0x82,0x82,0x44,0x38,0x00,0x00, //"C"
0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00, //"D"
0x00,0x00,0xFC,0x44,0x42,0x40,0x44,0x7C,0x44,0x40,0x40,0x42,0x44,0xFC,0x00,0x00, //"E"
0x00,0x00,0xFC,0x44,0x42,0x40,0x44,0x7C,0x44,0x40,0x40,0x40,0x40,0xF0,0x00,0x00, //"F"
0x00,0x00,0x34,0x4C,0x82,0x80,0x80,0x80,0x8E,0x84,0x84,0x84,0x4C,0x34,0x00,0x00, //"G"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"H"
0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00, //"I"
0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,0x00, //"J"
0x00,0x00,0xEE,0x44,0x48,0x48,0x50,0x60,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00, //"K"
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x44,0xFC,0x00,0x00, //"L"
0x00,0x00,0xC6,0x44,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x44,0x44,0x44,0xEE,0x00,0x00, //"M"
0x00,0x00,0xCE,0x44,0x64,0x64,0x64,0x54,0x54,0x4C,0x4C,0x4C,0x44,0xE4,0x00,0x00, //"N"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"O"
0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0xE0,0x00,0x00, //"P"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xBA,0x44,0x3C,0x02,0x00, //"Q"
0x00,0x00,0xF0,0x48,0x44,0x44,0x44,0x48,0x70,0x48,0x44,0x44,0x44,0xE6,0x00,0x00, //"R"
0x00,0x00,0x3C,0x44,0x82,0x80,0x40,0x30,0x0C,0x02,0x02,0x82,0x44,0x78,0x00,0x00, //"S"
0x00,0x00,0x7C,0x54,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"T"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x00,0x00, //"U"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x28,0x28,0x28,0x28,0x10,0x10,0x10,0x00,0x00, //"V"
0x00,0x00,0xEE,0x44,0x54,0x54,0x54,0x54,0x54,0x54,0x28,0x28,0x28,0x28,0x00,0x00, //"W"
0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x28,0x28,0x44,0x44,0xEE,0x00,0x00, //"X"
0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"Y"
0x00,0x00,0x7E,0x44,0x84,0x08,0x08,0x10,0x20,0x20,0x40,0x82,0x84,0xFC,0x00,0x00, //"Z"
0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x00, //"["
0x00,0x00,0xEE,0x44,0x54,0x54,0xFE,0x54,0x54,0x54,0x28,0x28,0x28,0x28,0x00,0x00, //"\"
0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00, //"]"
0x00,0x30,0x48,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"^"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00, //"_"
0x00,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"`"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x84,0x04,0x7C,0x84,0x84,0x8C,0x76,0x00,0x00, //"a"
0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x64,0x58,0x00,0x00, //"b"
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x80,0x80,0x80,0x80,0x44,0x38,0x00,0x00, //"c"
0x00,0x00,0x0C,0x04,0x04,0x04,0x34,0x4C,0x84,0x84,0x84,0x84,0x4C,0x36,0x00,0x00, //"d"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x84,0x84,0xFC,0x80,0x80,0x84,0x78,0x00,0x00, //"e"
0x00,0x00,0x18,0x24,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, //"f"
0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0x44,0x44,0x78,0x80,0x7C,0x82,0x82,0x7C,0x00, //"g"
0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"h"
0x00,0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"i"
0x00,0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0x60,0x00, //"j"
0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x48,0x50,0x60,0x50,0x48,0x44,0xEE,0x00,0x00, //"k"
0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x11,0x10,0x10,0x10,0x10,0x10,0x39,0x00,0x00, //"l"
0x00,0x00,0x00,0x00,0x00,0x00,0xAC,0xD2,0x92,0x92,0x92,0x92,0x92,0xD6,0x00,0x00, //"m"
0x00,0x00,0x00,0x00,0x00,0x00,0x58,0xE4,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"n"
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"o"
0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0xE0,0x00, //"p"
0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x4C,0x84,0x84,0x84,0x4C,0x34,0x04,0x0E,0x00, //"q"
0x00,0x00,0x00,0x00,0x00,0x00,0x6C,0x30,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, //"r"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x88,0x84,0x60,0x18,0x84,0x44,0x78,0x00,0x00, //"s"
0x00,0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x24,0x18,0x00,0x00, //"t"
0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00, //"u"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x00,0x00, //"v"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x54,0x54,0x28,0x28,0x28,0x00,0x00, //"w"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x28,0x10,0x10,0x28,0x44,0xEE,0x00,0x00, //"x"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0xA0,0xC0,0x00, //"y"
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x88,0x10,0x20,0x42,0x84,0xFC,0x00,0x00, //"z"
0x00,0x0C,0x10,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0x10,0x10,0x0C,0x00, //"{"
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00, //"|"
0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x18,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00, //"}"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x72,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"~"
};


class TFT: public Stream
{
	private:
		uint8_t curRow;
		uint8_t curCol;
		uint8_t curClsLine;
		int curColor;
		int bgColor;

		// private methods
		inline void recv()__attribute__((__always_inline__));

	public:
		// public methods
		TFT(void);
		~TFT();
		void begin(void);
		void WriteByte(byte ucData);
		void WriteData(byte ucData);
		void WriteIndex(byte ucData);
		void WriteData_16Bit(word ucData);
		void WriteReg(byte ucIndex,byte ucData);
	
		void SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);
		void SetScreenColour(int color);
		void SendCommand(byte *data, byte i);
		void SendData(byte *data, byte i);
		void clearScreen(void);
		void clearLine(byte row);

		void LcharDraw(byte row, byte column, byte data);
		void Lprint(byte row, byte column, byte *word);

		void pixelDraw(byte x,byte y,int color);
		void horizontalLine(byte xStart, byte xStop, byte y);
		void verticalLine(byte x, byte yStart, byte yStop);
		void imageDraw(const byte *p, byte x, byte y, byte width, byte height);

		void circleDraw(int x, int y, int r);
		void boxDraw(byte x, byte y, byte w, byte h);
		void drawLine(byte x0, byte y0, byte x1, byte y1);

		void setPosi(uint8_t row, uint8_t column);
		void Swap(byte *x, byte *y);
		void setColor(int color,int bgcolor);

		virtual size_t write(uint8_t byte);
		virtual int peek();
		virtual int read();
		virtual int available();
		virtual void flush();
		operator bool()
		{
				return true;
		}
		using Print::write;
};

#endif