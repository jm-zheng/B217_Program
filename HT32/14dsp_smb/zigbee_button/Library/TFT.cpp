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
void TFT::SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	
	// 0.96"
#ifdef USE_LANDSCAPE//使用橫屏模式
	WriteIndex(0x2a);
	WriteData(0x00);
	WriteData(x_start+5);
	WriteData(0x00);
	WriteData(x_end+4);

	WriteIndex(0x2b);
	WriteData(0x00);
	WriteData(y_start+69);
	WriteData(0x00);
	WriteData(y_end+68);

#else//豎屏模式	
	WriteIndex(0x2a);
	WriteData(0x00);
	WriteData(x_start+2);
	WriteData(0x00);
	WriteData(x_end+1);

	WriteIndex(0x2b);
	WriteData(0x00);
	WriteData(y_start+67);
	WriteData(0x00);
	WriteData(y_end+66);
#endif
	WriteIndex(0x2c);
}

//------------------------------------------------------------------------------
void TFT::SetScreenColour(int color)
{
 	byte i,j;
	
	// 0.96"
	//SetRegion(2,67,129,130);
	SetRegion(0,0,128,64);		//坐標設置
 	for (i=0;i<128;i++)
	{
    for (j=0;j<64;j++)
		{
      WriteData_16Bit(color);
		}
	}
}

//------------------------------------------------------------------------------
void TFT::clearScreen(void)
{
	SetScreenColour(BLACK); //清屏  
}

//------------------------------------------------------------------------------
// Function		: imageDraw(const byte IMAGE[], byte row, byte column)
// Description          : draw image at row, column
// Input		: image, row, column
// Output		: display image
//------------------------------------------------------------------------------
void TFT::imageDraw(const byte *p, byte x, byte y, byte width, byte height)
{
	int i; 
	unsigned char picH,picL;
	
	SetRegion(0,0,128,64);		//坐標設置
  for(i=0;i<(width*height);i++)
	{	
	 	picL=*(p+i*2);	//數據低位在前
		picH=*(p+i*2+1);				
		WriteData_16Bit(picH<<8|picL);  						
	}		
}

//------------------------------------------------------------------------------
void TFT::pixelDraw(byte x,byte y,int color)
{
	SetRegion(x,y,x+1,y+1);
	WriteData_16Bit(color);
}    

//------------------------------------------------------------------------------
void TFT::clearLine(byte row)
{
	/*
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
	*/
}

//------------------------------------------------------------------------------
void TFT::LcharDraw(byte row, byte column, byte data)
{
	unsigned char i,j;
	unsigned short xx,yy;
	
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
		data = 0;
	}
	else
	{
		data=(data-32);
	}
	xx=column;
	yy=row*8;
	for(i=0;i<16;i++)
	{
	  for(j=0;j<8;j++) 
		{
	    if(FONT8x16[data*16+i]&(0x80>>j))	
			{
        pixelDraw(xx+j,yy+i,curColor);
			}
			else 
			{
				if (curColor!=bgColor) 
					pixelDraw(xx+j,yy+i,bgColor);
			}
		}	
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
// Function		: horizontalLine(byte xStart, byte xStop, byte y)
// Description          : draw horizontal line from xStart to xStop
// Input		: X Start & Stop coordinate, Y
// Output		: display horizontal line
//------------------------------------------------------------------------------
void TFT::horizontalLine(byte xStart, byte xStop, byte y)
{
	
	byte temp = 0;
	byte a;

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

	a = xStart;
	while (a <= xStop)
	{
	  pixelDraw(a,y,curColor);
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
	byte temp;
	byte a;

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
		temp = yStart;
		yStart = yStop;
		yStop = temp;
	}

	a = yStart;
	while (a <= yStop)
	{
	  pixelDraw(x,a,curColor);
		a++;
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
		pixelDraw(x - xx, y + yy,curColor);
		pixelDraw(x - yy, y - xx,curColor);
		pixelDraw(x + xx, y - yy,curColor);
		pixelDraw(x + yy, y + xx,curColor);
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
			pixelDraw(y0, x0,curColor);
		}
		else
		{
			pixelDraw(x0, y0,curColor);
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
void TFT::setColor(int color,int bgcolor)
{
	curColor = color;
	bgColor = bgcolor;
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
void TFT::recv()
{

}

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
TFT::TFT(void)
{
	
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
TFT::~TFT()
{

}

//------------------------------------------------------------------------------
void TFT::begin(void)
{
	curColor=WHITE;
	bgColor=BLACK;

	pinMode(TFT_RES, OUTPUT);
	pinMode(TFT_DC, OUTPUT);
	pinMode(TFT_SCL, OUTPUT);
	pinMode(TFT_SDA, OUTPUT);
	pinMode(TFT_BLK, OUTPUT);

	TFT_BLK_ON;
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
	
	
	WriteIndex(0x3A); //65k mode 
	WriteData(0x05); 
	
	
	WriteIndex(0x29);//Display on	 
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
		if (curClsLine != 0)
		{
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
