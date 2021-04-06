//-------------------------------------------------------------------
// TFT.cpp
//-------------------------------------------------------------------
#include "TFT.h"

#define TFT_SCL            	PC15 //SCK
#define TFT_SDA            	PC14 //MOSI
#define TFT_RES            	PC13
#define TFT_DC             	PB8
#define TFT_BLK             PB9


#define TFT_DC_LOW     			GPIOB->BRR = GPIO_PIN_8
#define TFT_DC_HIGH    			GPIOB->BSRR = GPIO_PIN_8
#define TFT_COMMAND     		GPIOB->BRR = GPIO_PIN_8
#define TFT_DATA	 					GPIOB->BSRR = GPIO_PIN_8
#define TFT_RES_LOW     		GPIOC->BRR = GPIO_PIN_13
#define TFT_RES_HIGH    		GPIOC->BSRR = GPIO_PIN_13
#define TFT_SCL_LOW     		GPIOC->BRR = GPIO_PIN_15
#define TFT_SCL_HIGH    		GPIOC->BSRR = GPIO_PIN_15
#define TFT_SDA_LOW     		GPIOC->BRR = GPIO_PIN_14
#define TFT_SDA_HIGH    		GPIOC->BSRR = GPIO_PIN_14

#define TFT_BLK_ON     			GPIOB->BSRR = GPIO_PIN_9
#define TFT_BLK_OFF    			GPIOB->BRR = GPIO_PIN_9

//------------------------------------------------------------------------------
void TFT::WriteByte(byte ucData)
{
	byte i = 8;

	TFT_SCL_LOW;
	while (i--)
	{
		if (ucData &0x80)
		{
			TFT_SDA_HIGH;
		}
		else
		{
			TFT_SDA_LOW;
		}
		TFT_SCL_HIGH;
		TFT_SCL_LOW;
		ucData <<= 1;
	}
}
//------------------------------------------------------------------------------
void TFT::WriteData(byte ucData)
{
	TFT_DATA; // D/C high
	WriteByte(ucData);
}

//------------------------------------------------------------------------------
void TFT::WriteIndex(byte ucData)
{
	TFT_COMMAND; // D/C low
	WriteByte(ucData);
}
//------------------------------------------------------------------------------
void TFT::WriteData_16Bit(word ucData)
{
	TFT_DATA; // D/C high
	WriteByte(ucData>>8);
	WriteByte(ucData);
}
//------------------------------------------------------------------------------
void TFT::WriteReg(byte ucIndex,byte ucData)
{
	WriteIndex(ucIndex);
  WriteData(ucData);	
}

//------------------------------------------------------------------------------
void TFT::SendData(byte *data, byte i)
{
	TFT_DATA; // D/C high
	while (i)
	{
		WriteByte(*data);
		data++;
		i--;
	}
}

//------------------------------------------------------------------------------
void TFT::SendCommand(byte *data, byte i)
{
	TFT_COMMAND; // D/C low
	while (i)
	{
		WriteByte(*data);
		data++;
		i--;
	}
}

//------------------------------------------------------------------------------
void TFT::setAddress(byte page, byte column)
{
	byte pageAddress[] = 
	{
		PAGE_START_ADDRESS
	};
	byte columnAddress[] = 
	{
		COLUMNADDRESS, COLUMNADDRESS_MSB, COLUMNADDRESS_LSB
	};

	if (page > MAXROWS)
	{
		page = MAXROWS;
	}
	if (column > LCDWIDTH)
	{
		column = LCDWIDTH;
	}

	pageAddress[0] = PAGE_START_ADDRESS | (MAXROWS - page);

	columnAddress[0] = COLUMNADDRESS;
	columnAddress[1] = COLUMNADDRESS_MSB | column;
	columnAddress[2] = COLUMNADDRESS_LSB;

	SendCommand(pageAddress, 1);
	SendCommand(columnAddress, 3);

}

void TFT::SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	
	
	// 0.96"
#ifdef USE_LANDSCAPE//使用橫屏模式
	WriteIndex(0x2a);
	WriteData(0x00);
	WriteData(x_start+3);
	WriteData(0x00);
	WriteData(x_end+3);

	WriteIndex(0x2b);
	WriteData(0x00);
	WriteData(y_start+2);
	WriteData(0x00);
	WriteData(y_end+2);

#else//豎屏模式	
	WriteIndex(0x2a);
	WriteData(0x00);
	WriteData(x_start);
	WriteData(0x00);
	WriteData(x_end);

	WriteIndex(0x2b);
	WriteData(0x00);
	WriteData(y_start);
	WriteData(0x00);
	WriteData(y_end);
#endif
	WriteIndex(0x2c);
	
	/*
	// 1.8"
#ifdef USE_LANDSCAPE//使用橫屏模式
	WriteIndex(0x2a);
	WriteData(0x02);
	WriteData(x_start+2);
	WriteData(0x02);
	WriteData(x_end+2);

	WriteIndex(0x2b);
	WriteData(0x01);
	WriteData(y_start+1);
	WriteData(0x01);
	WriteData(y_end+1);

#else//豎屏模式	
	WriteIndex(0x2a);
	WriteData(0x02);
	WriteData(x_start+2);
	WriteData(0x02);
	WriteData(x_end+2);

	WriteIndex(0x2b);
	WriteData(0x01);
	WriteData(y_start+1);
	WriteData(0x01);
	WriteData(y_end+1);
#endif
	WriteIndex(0x2c);
	*/
}

void TFT::SetScreenColour(int color)
{
 	byte i,j;
	
	
	// 0.96"
	SetRegion(2,67,129,130);
 	for (i=0;i<128;i++)
    	for (j=0;j<64;j++)
        	WriteData_16Bit(color);
	// 1.8"
	//SetRegion(0,0,128-1,160-1);
 	//for (i=0;i<128;i++)
  //  	for (j=0;j<160;j++)
  //      	WriteData_16Bit(color);
}

void TFT::clearScreen(void)
{
	int i; 
	unsigned char picH,picL;
	unsigned char *p;
	
	SetScreenColour(WHITE); //清屏  
	
	p=(unsigned char *)gImage_qq;
	//SetRegion(2,67,128+1,64+66);		//坐標設置
	SetRegion(2,67,129,130);
	
	//SetRegion(0,0,128-1,64-1);	
  for(i=0;i<(128*64);i++)
	{	
	 	picL=*(p+i*2);	//數據低位在前
		picH=*(p+i*2+1);				
		WriteData_16Bit(picH<<8|picL);  						
	}		
	/*
	SetRegion(0,95,128-1,(64+95)-1);	
  for(i=0;i<(128*64);i++)
	{	
	 	picL=*(p+i*2);	//數據低位在前
		picH=*(p+i*2+1);				
		WriteData_16Bit(picH<<8|picL);  						
	}		
	*/
}

/*
//------------------------------------------------------------------------------
void TFT::clearScreen(void)
{
	byte ramData[] = 
	{
		0x00
	};

	byte i, j;

	for (i = 0; i < 8; i++)
	{
		setAddress(i, 0);

		for (j = 0; j < LCDWIDTH; j++)
		{
			SendData(ramData, 1);
		}
	}
	curRow = 0;
	curCol = 0;
	curClsLine = 0;
}
*/
//------------------------------------------------------------------------------
void TFT::setBrightness(byte Brightness)
{
	byte ramData[] = 
	{
		SETCONTRAST
	};
	byte BrightnessData[] = 
	{
		Brightness
	};
	SendCommand(ramData, sizeof ramData);
	SendCommand(BrightnessData, sizeof BrightnessData);
}

//------------------------------------------------------------------------------
void TFT::clearLine(byte row)
{
	byte ramData[] = 
	{
		0x00
	};
	byte j;

	//setAddress(row - 1, 0);
	setAddress(row, 0);
	for (j = 0; j < LCDWIDTH; j++)
	{
		SendData(ramData, 1);
	}

}

//------------------------------------------------------------------------------
void TFT::ScharDraw(byte row, byte column, byte data)
{
	int h;
	byte i;

	if (row > MAXROWS)
	{
		row = MAXROWS;
	}
	if (column > LCDWIDTH)
	{
		column = LCDWIDTH;
	}
	if (data < 32 || data > 129)
	{
		data = '.';
	}
	h = (data - 32) *6;
	setAddress(row, column);
	/OLED_DATA; // D/C high
	for (i = 0; i < 6; i++)
	{
		WriteByte(FONT6x8[h++]);
	}
}

//------------------------------------------------------------------------------
void TFT::Sprint(byte row, byte column, byte *word)
{
	byte a = 0;

	if (row > MAXROWS)
	{
		row = MAXROWS;
	}

	if (column > LCDWIDTH)
	{
		column = LCDWIDTH;
	}

	while (word[a] != 0)
	{
		if (word[a] != 0x0A)
		{
			if (word[a] != 0x0D)
			{
				ScharDraw(row, column, word[a]);

				column += 6;

				if (column >= (LCDWIDTH - 6))
				{
					column = 0;
					if (row < MAXROWS)
					{
						row++;
					}
					else
					{
						row = 0;
					}
				}
			}
			else
			{
				if (row < MAXROWS)
				{
					row++;
				}
				else
				{
					row = 0;
				}
				column = 0;
			}
			a++;
		}
	}
}

//------------------------------------------------------------------------------
void TFT::LcharDraw(byte row, byte column, byte data)
{
	int h;
	byte i;
	if (row > MAXROWS)
	{
		row = MAXROWS;
	}
	if (column > LCDWIDTH)
	{
		column = LCDWIDTH;
	}
	if (data < 32 || data > 129)
	{
		data = '.';
	}
	h = (int)(data - 32) *16;
	setAddress(row, column);
	//OLED_DATA; // D/C high
	for (i = 0; i < 8; i++)
	{
		WriteByte(FONT8x16[h++]);
	}
	setAddress(row + 1, column);
	//OLED_DATA; // D/C high
	for (i = 0; i < 8; i++)
	{
		WriteByte(FONT8x16[h++]);
	}
}

//------------------------------------------------------------------------------
void TFT::Lprint(byte row, byte column, byte *word)
{
	byte a = 0;

	if (row > MAXROWS)
	{
		row = MAXROWS;
	}

	if (column > LCDWIDTH)
	{
		column = LCDWIDTH;
	}

	while (word[a] != 0)
	{
		if (word[a] != 0x0A)
		{
			if (word[a] != 0x0D)
			{
				LcharDraw(row, column, word[a]);

				column += 8;

				if (column >= (LCDWIDTH - 8))
				{
					column = 0;
					if (row < MAXROWS)
					{
						row++;
					}
					else
					{
						row = 0;
					}
				}

			}
			else
			{
				if (row < MAXROWS)
				{
					row++;
				}
				else
				{
					row = 0;
				}
				column = 0;
			}
			a++;
		}
	}
}

//------------------------------------------------------------------------------
void TFT::pixelDraw(byte x, byte y)
{
	byte page, temp;
	byte coordinate[] = 
	{
		0x00
	};

	if (x > LCDWIDTH - 1)
	{
		x = LCDWIDTH - 1;
	}

	if (y > LCDHEIGHT - 1)
	{
		y = LCDHEIGHT - 1;
	}

	page = y / 8;
	temp = 0x80 >> (y % 8);
	coordinate[0] = temp;

	setAddress(page, x);
	SendData(coordinate, 1);

}

//------------------------------------------------------------------------------
// Function		: horizontalLine(byte xStart, byte xStop, byte y)
// Description          : draw horizontal line from xStart to xStop
// Input		: X Start & Stop coordinate, Y
// Output		: display horizontal line
//------------------------------------------------------------------------------
void TFT::horizontalLine(byte xStart, byte xStop, byte y)
{
	byte temp = 0;
	byte page, a;
	byte ramData[] = 
	{
		0x00
	};

	if (xStart > LCDWIDTH - 1)
	{
		xStart = LCDWIDTH - 1;
	}

	if (xStop > LCDWIDTH - 1)
	{
		xStop = LCDWIDTH - 1;
	}

	if (y > LCDHEIGHT - 1)
	{
		y = LCDHEIGHT - 1;
	}

	if (xStart > xStop)
	{
		temp = xStart;
		xStart = xStop;
		xStop = temp;
	}

	page = y / 8;
	temp = 0x80 >> (y % 8);

	a = xStart;
	ramData[0] = temp;

	setAddress(page, xStart);

	while (a <= xStop)
	{
		SendData(ramData, 1);
		a++;
	}
}

//------------------------------------------------------------------------------
// Function		: verticalLine(byte x, byte yStart, byte yStop)
// Description          : draw vertical line from yStart to yStop
// Input		: Y Start & Stop coordinate, X
// Output		: display vertical line
//------------------------------------------------------------------------------
void TFT::verticalLine(byte x, byte yStart, byte yStop)
{
	byte temp1 = 0, temp2 = 0;
	byte page1, page2, pageStart;
	byte a;
	byte ramData1[] = 
	{
		0x00
	};
	byte ramData2[] = 
	{
		0x00
	};

	if (x > LCDWIDTH - 1)
	{
		x = LCDWIDTH - 1;
	}

	if (yStart > LCDHEIGHT - 1)
	{
		yStart = LCDHEIGHT - 1;
	}

	if (yStop > LCDHEIGHT - 1)
	{
		yStop = LCDHEIGHT - 1;
	}

	if (yStart > yStop)
	{
		temp1 = yStart;
		yStart = yStop;
		yStop = temp1;
	}

	page1 = yStart / 8;
	page2 = yStop / 8;
	pageStart = yStart % 8;

	if (page1 != page2)
	{
		if (pageStart > 0)
		{
			temp1 = 0xFF00 >> pageStart;
			temp1 = temp1 ^ 0xFF;
		}
		else
		{
			temp1 = 0xFF;
		}
	}
	else
	{
		temp1 = 0;

		a = yStart - (page1 *8);
		a = 0xFF00 >> a;
		temp2 = temp2 ^ a;
	}

	ramData1[0] = temp1;

	setAddress(page1, x);
	SendData(ramData1, 1);

	a = page1 + 1;
	ramData1[0] = 0xFF;

	while (a < page2)
	{
		setAddress(a, x);
		SendData(ramData1, 1);
		a++;
	}

	temp2 = 8-(yStop % 8);
	temp2--;
	temp2 = 0xFF << temp2;

	ramData2[0] = temp2;

	setAddress(page2, x);
	SendData(ramData2, 1);
}

//------------------------------------------------------------------------------
// Function		: imageDraw(const byte IMAGE[], byte row, byte column)
// Description          : draw image at row, column
// Input		: image, row, column
// Output		: display image
//------------------------------------------------------------------------------
void TFT::imageDraw(const byte IMAGE[], byte row, byte column)
{
	byte a, height, width;

	width = IMAGE[0];
	height = IMAGE[1];

	for (a = 0; a < height; a++)
	{
		setAddress(row + a, column);
		SendData((byte*)IMAGE + 2+a * width, width);
	}
}

//------------------------------------------------------------------------------
// circleDraw function is not complete. needs checks for page surround x-axis for proper column fill
// Function		: circleDraw(register int x, register int y, int r)
// Description          : draw circle at x,y of radius r
// Input		: x,y, radius
// Output		: display circle
//------------------------------------------------------------------------------
void TFT::circleDraw(int x, int y, int r)
{
	int xx =  - r;
	int yy = 0;
	int e = 2-(2 *r);
	do
	{
		pixelDraw(x - xx, y + yy);
		pixelDraw(x - yy, y - xx);
		pixelDraw(x + xx, y - yy);
		pixelDraw(x + yy, y + xx);
		if (e > xx)
		{
			e += ((++xx << 1) + 1);
		}
		if (e <= yy)
		{
			e += ((++yy << 1) + 1);
		}
	}
	while (xx < 0);
}


//------------------------------------------------------------------------------
// Function    : Fill_RAM( unsigned byte c )
// Description : Fills the OLED with one particular data
// Input       : Data
// Output      : None
//------------------------------------------------------------------------------
void TFT::Fill_RAM(byte data)
{
	byte i, j;

	byte ramData[] = 
	{
		0x00
	};

	ramData[0] = data;

	for (i = 0; i < 8; i++)
	{
		setAddress(i, 0);

		for (j = 0; j < LCDWIDTH; j++)
		{
			SendData(ramData, 1);
		}
	}
}

//------------------------------------------------------------------------------
void TFT::Swap(byte *x, byte *y)
{
	int t;
	t =  *x;
	*x =  *y;
	*y = t;
}

//------------------------------------------------------------------------------
// Function		: boxDraw(byte x, byte y, byte w, byte h)
// Description          : draw bow at x,y ,width , height
// Input		: x,y, w,h
// Output		: display box
//------------------------------------------------------------------------------
void TFT::boxDraw(byte x, byte y, byte w, byte h)
{
	//        C
	//   +---------+
	//   |         |
	// B |         | D
	//   |         |
	//   +---------+
	//        A
	if (x > w)
	{
		Swap(&x, &w);
	}
	if (y > h)
	{
		Swap(&y, &h);
	}

	horizontalLine(x + 1, w - 1, h); //A
	verticalLine(x, y + 1, h - 1); //B
	horizontalLine(x + 1, w - 1, y); //C
	verticalLine(w, y + 1, h - 1); //D
}

//------------------------------------------------------------------------------
void TFT::Fill_RAM_PAGE(byte page, byte data)
{
	byte j;

	byte ramData[] = 
	{
		0x00
	};

	ramData[0] = data;

	setAddress(page, 0);

	for (j = 0; j < LCDWIDTH; j++)
	{
		SendData(ramData, 1);
	}
}

//------------------------------------------------------------------------------
void TFT::Set_Contrast_Control(byte d)
{
	byte ramData[] = 
	{
		SETCONTRAST, 0x00
	};
	ramData[1] = d;

	SendCommand(ramData, 2);
}

//------------------------------------------------------------------------------
void TFT::Set_Inverse_Display(byte d)
{
	// 0 = normal, 1 = inverted

	byte ramData[] = 
	{
		NORMALDISPLAY
	};
	ramData[0] = ramData[0] + d;

	SendCommand(ramData, 1);
}

//------------------------------------------------------------------------------
void TFT::Set_Display_On_Off(byte d)
{
	// 0 = off, 1 = on

	byte ramData[] = 
	{
		DISPLAYOFF
	};
	ramData[0] = ramData[0] + d;

	SendCommand(ramData, 1);
}


//------------------------------------------------------------------------------
// Function    : Scroll_Display
// Description : OLED Scroll Left or Right
// Input       : Xstart-0x00  Xstop-0x0F
// Output      : Scroll Left or Right
//------------------------------------------------------------------------------
void TFT::Scroll_Display_Left(uint8_t Xstart, uint8_t Xstop)
{
	byte Scroll_Display_Left_init[] = 
	{
		SCROLL_LEFT, 0X00, Xstart, Scroll_2Frames, Xstop, 0X00, 0XFF, ACTIVATE_SCROLL
	};

	SendCommand(Scroll_Display_Left_init, sizeof Scroll_Display_Left_init);
}

//------------------------------------------------------------------------------
void TFT::Scroll_Display_Right(uint8_t Xstart, uint8_t Xstop)
{
	byte Scroll_Display_Right_init[] = 
	{
		SCROLL_RIGHT, 0X00, Xstart, Scroll_2Frames, Xstop, 0X00, 0XFF, ACTIVATE_SCROLL
	};

	SendCommand(Scroll_Display_Right_init, sizeof Scroll_Display_Right_init);
}

//------------------------------------------------------------------------------
void TFT::ScrollStop(void)
{
	byte ramData[] = 
	{
		DEACTIVATE_SCROLL
	};
	SendCommand(ramData, sizeof ramData);
}

//------------------------------------------------------------------------------
void TFT::BlinkON(void)
{
	byte ramData[] = 
	{
		DISPLAYALLON
	};
	SendCommand(ramData, sizeof ramData);
}

//------------------------------------------------------------------------------
void TFT::BlinkOFF(void)
{
	byte ramData[] = 
	{
		DISPLAYALLON_RESUME
	};
	SendCommand(ramData, sizeof ramData);
}

//----------------------------------------------------------------
void TFT::drawLine(byte x0, byte y0, byte x1, byte y1)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);

	if (steep)
	{
		Swap(&x0, &y0);

		Swap(&x1, &y1);

	}
	if (x0 > x1)
	{
		Swap(&x0, &x1);
		Swap(&y0, &y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
	{
		ystep = 1;
	}
	else
	{
		ystep =  - 1;
	}

	for (; x0 <= x1; x0++)
	{
		if (steep)
		{
			pixelDraw(y0, x0);
		}
		else
		{
			pixelDraw(x0, y0);
		}
		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}

//------------------------------------------------------------------------------
void TFT::setFont(uint8_t fontsize)
{
	curFont = fontsize;
	//clearScreen();
}

//------------------------------------------------------------------------------
void TFT::setPosi(uint8_t row, uint8_t column)
{
	curRow = row;
	curCol = column;
}

//------------------------------------------------------------------------------
// The receive routine called by the interrupt handler
//------------------------------------------------------------------------------
void TFT::recv(){

}

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
TFT::TFT(uint8_t type)
{
	curType = type;
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
TFT::~TFT(){

}

//------------------------------------------------------------------------------
void TFT::begin(uint8_t font)
{
	curFont = font;

	pinMode(TFT_RES, OUTPUT);
	pinMode(TFT_DC, OUTPUT);
	pinMode(TFT_SCL, OUTPUT);
	pinMode(TFT_SDA, OUTPUT);
	pinMode(TFT_BLK, OUTPUT);

	TFT_BLK_ON;
	//TFT_BLK_OFF;
	TFT_COMMAND;
	TFT_RES_LOW;
	delay(20);
	TFT_RES_HIGH;
	delay(20);

	//LCD Init For 0.96Inch LCD Panel with ST7735R.
	WriteIndex(0x11);//Sleep exit 
	delay(120);

	//0.96"
	//ST7735R Frame Rate
	WriteIndex(0xB1); 
	WriteData(0x01); 
	WriteData(0x2C); 
	WriteData(0x2D); 

	WriteIndex(0xB2); 
	WriteData(0x01); 
	WriteData(0x2C); 
	WriteData(0x2D); 

	WriteIndex(0xB3); 
	WriteData(0x01); 
	WriteData(0x2C); 
	WriteData(0x2D); 
	WriteData(0x01); 
	WriteData(0x2C); 
	WriteData(0x2D); 
	
	WriteIndex(0xB4); //Column inversion 
	WriteData(0x07); 
	
	//ST7735R Power Sequence
	WriteIndex(0xC0); 
	WriteData(0xA2); 
	WriteData(0x02); 
	WriteData(0x84); 
	WriteIndex(0xC1); 
	WriteData(0xC5); 
	
	WriteIndex(0xC2); 
	WriteData(0x0A); 
	WriteData(0x00); 

	WriteIndex(0xC3); 
	WriteData(0x8A); 
	WriteData(0x2A); 
	WriteIndex(0xC4); 
	WriteData(0x8A); 
	WriteData(0xEE); 
	
	WriteIndex(0xC5); //VCOM 
	WriteData(0x0E); 
	
	WriteIndex(0x36); //MX, MY, RGB mode 
#ifdef USE_LANDSCAPE//使用橫屏模式
	WriteData(0xA8);
#else//豎屏模式	
	WriteData(0xC8); 
#endif
	
	//ST7735R Gamma Sequence
	WriteIndex(0xe0); 
	WriteData(0x0f); 
	WriteData(0x1a); 
	WriteData(0x0f); 
	WriteData(0x18); 
	WriteData(0x2f); 
	WriteData(0x28); 
	WriteData(0x20); 
	WriteData(0x22); 
	WriteData(0x1f); 
	WriteData(0x1b); 
	WriteData(0x23); 
	WriteData(0x37); 
	WriteData(0x00); 	
	WriteData(0x07); 
	WriteData(0x02); 
	WriteData(0x10); 

	WriteIndex(0xe1); 
	WriteData(0x0f); 
	WriteData(0x1b); 
	WriteData(0x0f); 
	WriteData(0x17); 
	WriteData(0x33); 
	WriteData(0x2c); 
	WriteData(0x29); 
	WriteData(0x2e); 
	WriteData(0x30); 
	WriteData(0x30); 
	WriteData(0x39); 
	WriteData(0x3f); 
	WriteData(0x00); 
	WriteData(0x07); 
	WriteData(0x03); 
	WriteData(0x10);  
	
	WriteIndex(0x2a);
	WriteData(0x00);
	WriteData(0x00+2);
	WriteData(0x00);
	WriteData(0x80+2);

	WriteIndex(0x2b);
	WriteData(0x00);
	WriteData(0x00+3);
	WriteData(0x00);
	WriteData(0x80+3);
	
	WriteIndex(0xF0); //Enable test command  
	WriteData(0x01); 
	WriteIndex(0xF6); //Disable ram power save mode 
	WriteData(0x00); 
	
	/*
	// 1.8"
//------------------------------------ST7735S Frame Rate-----------------------------------------// 
WriteIndex(0xB1); 
WriteData(0x05); 
WriteData(0x3C); 
WriteData(0x3C); 
WriteIndex(0xB2); 
WriteData(0x05); 
WriteData(0x3C); 
WriteData(0x3C); 
WriteIndex(0xB3); 
WriteData(0x05); 
WriteData(0x3C); 
WriteData(0x3C); 
WriteData(0x05); 
WriteData(0x3C); 
WriteData(0x3C); 
//------------------------------------End ST7735S Frame Rate---------------------------------// 
WriteIndex(0xB4); //Dot inversion 
WriteData(0x03); 
//------------------------------------ST7735S Power Sequence---------------------------------// 
WriteIndex(0xC0); 
WriteData(0x28); 
WriteData(0x08); 
WriteData(0x04); 
WriteIndex(0xC1); 
WriteData(0XC0); 
WriteIndex(0xC2); 
WriteData(0x0D); 
WriteData(0x00); 
WriteIndex(0xC3); 
WriteData(0x8D); 
WriteData(0x2A); 
WriteIndex(0xC4); 
WriteData(0x8D); 
WriteData(0xEE); 
//---------------------------------End ST7735S Power Sequence-------------------------------------// 
WriteIndex(0xC5); //VCOM 
WriteData(0x1A); 
WriteIndex(0x36); //MX, MY, RGB mode 
WriteData(0xC0); 
//------------------------------------ST7735S Gamma Sequence---------------------------------// 
WriteIndex(0xE0); 
WriteData(0x04); 
WriteData(0x22); 
WriteData(0x07); 
WriteData(0x0A); 
WriteData(0x2E); 
WriteData(0x30); 
WriteData(0x25); 
WriteData(0x2A); 
WriteData(0x28); 
WriteData(0x26); 
WriteData(0x2E); 
WriteData(0x3A); 
WriteData(0x00); 
WriteData(0x01); 
WriteData(0x03); 
WriteData(0x13); 
WriteIndex(0xE1); 
WriteData(0x04); 
WriteData(0x16); 
WriteData(0x06); 
WriteData(0x0D); 
WriteData(0x2D); 
WriteData(0x26); 
WriteData(0x23); 
WriteData(0x27); 
WriteData(0x27); 
WriteData(0x25); 
WriteData(0x2D); 
WriteData(0x3B); 
WriteData(0x00); 
WriteData(0x01); 
WriteData(0x04); 
WriteData(0x13); 
//------------------------------------End ST7735S Gamma Sequence-----------------------------// 	
	*/
	
	WriteIndex(0x3A); //65k mode 
	WriteData(0x05); 
	
	
	WriteIndex(0x29);//Display on	 
	//	clearScreen();
}

//------------------------------------------------------------------------------
int TFT::read()
{
	return 0;
}

//------------------------------------------------------------------------------
int TFT::available()
{
	return 0;
}

//------------------------------------------------------------------------------
size_t TFT::write(uint8_t b)
{
	if (curFont == FONT_6x8)
	// FONT_6x8 => 8*21
	{
		if (curClsLine != 0)
		{
			//clearLine(curRow);
			curClsLine = 0;
		}
		if (b >= 32)
		{
			if (curCol <= 120)
			{
				ScharDraw(curRow, curCol, b);
				curCol += 6;
			}
			else
			{
				curRow++;
				if (curRow >= 8)
				{
					curRow = 0;
				}
				curCol = 0;
				ScharDraw(curRow, curCol, b);
				curCol += 6;
			}
		}
		if (b == 0x0A)
		{
			while (curCol <= 120)
			{
				ScharDraw(curRow, curCol, ' ');
				curCol += 6;
			}
			curRow++;
			if (curRow >= 8)
			{
				curRow = 0;
			}
			curCol = 0;
			curClsLine = 1;
		}
	}
	else
	// FONT_8x16 = 4*16
	{
		if (curClsLine != 0)
		{
			//clearLine(curRow);
			//clearLine(curRow+1);
			curClsLine = 0;
		}
		if (b >= 32)
		{
			if (curCol <= 120)
			{
				LcharDraw(curRow, curCol, b);
				curCol += 8;
			}
			else
			{
				curRow += 2;
				if (curRow >= 8)
				{
					curRow = 0;
				}
				curCol = 0;
				LcharDraw(curRow, curCol, b);
				curCol += 8;
			}
		}

		if (b == 0x0A)
		{
			while (curCol <= 120)
			{
				LcharDraw(curRow, curCol, ' ');
				curCol += 8;
			}
			curRow += 2;
			if (curRow >= 8)
			{
				curRow = 0;
			}
			curCol = 0;
			curClsLine = 1;
		}
	}
	return 1;
}

//------------------------------------------------------------------------------
void TFT::flush()
{
	//
}

//------------------------------------------------------------------------------
int TFT::peek()
{
	return 0;
}
