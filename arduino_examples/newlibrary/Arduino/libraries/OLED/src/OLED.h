
#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <inttypes.h>
#include <Stream.h>
#include "FontPack.h"

/******************************************************************************
* Definitions
******************************************************************************/
//SoftwareSPI Setting Pin
#define OLED_SCL            9 //SCK
#define OLED_SDA            8 //MOSI
#define OLED_RST            7
#define OLED_DC             4

#define OLED_096            0

#define FONT_6x8            0
#define FONT_8x16           1

// OLED GPIO MACROS
#define OLED_COMMAND     		digitalWrite(OLED_DC,LOW)
#define OLED_DATA	 					digitalWrite(OLED_DC,HIGH)
#define OLED_RES_LOW     		digitalWrite(OLED_RST,LOW)
#define OLED_RES_HIGH    		digitalWrite(OLED_RST,HIGH)
#define OLED_SCL_LOW     		digitalWrite(OLED_SCL,LOW)
#define OLED_SCL_HIGH    		digitalWrite(OLED_SCL,HIGH)
#define OLED_SDA_LOW     		digitalWrite(OLED_SDA,LOW)
#define OLED_SDA_HIGH    		digitalWrite(OLED_SDA,HIGH)

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


class OLED : public Stream
{
private:

	uint8_t curType;
	uint8_t curFont;
	uint8_t curRow;
	uint8_t curCol;
	uint8_t curClsLine;

  // private methods
  inline void recv() __attribute__((__always_inline__));

public:
  // public methods
  OLED(uint8_t type=OLED_096);
  ~OLED();
  void begin(uint8_t font);
  int peek();

	void WriteByte(byte ucData);
	void SendCommand(byte *data, byte i);
	void SendData(byte *data, byte i);
	void setAddress(byte page, byte column);
	void clearScreen(void);
	void clearLine(byte row);
	void setBrightness(byte Brightness);

	void ScharDraw(byte row, byte column, byte data);
	void Sprint(byte row, byte column, byte *word);
	void LcharDraw(byte row, byte column, byte data);
	void Lprint(byte row, byte column, byte *word);

	void pixelDraw(byte x, byte y);
	void horizontalLine(byte xStart, byte xStop, byte y);
	void verticalLine(byte x, byte yStart, byte yStop);
	void imageDraw(const byte IMAGE[], byte row, byte column);

	void circleDraw(int x, int y, int r);
	void boxDraw(byte x, byte y, byte w, byte h);
	void drawLine(byte x0, byte y0, byte x1, byte y1);

	void BlinkON(void);
	void BlinkOFF(void);

	void Scroll_Display_Left(uint8_t Xstart, uint8_t Xstop);
	void Scroll_Display_Right(uint8_t Xstart, uint8_t Xstop);
	void ScrollStop(void);

	void Set_Contrast_Control(byte d);
	void Set_Inverse_Display(byte d);
	void Set_Display_On_Off(byte d);


	void Fill_RAM(byte data);
	void Fill_RAM_PAGE(byte page, byte data);

	void setFont(uint8_t fontsize);
	void setPosi(uint8_t row, uint8_t column);
	void Swap(byte *x, byte *y);

  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();
  operator bool() { return true; }
  
  using Print::write;

};

#endif
