
// 
// Includes
// 

#include <OLED.h>
#ifdef __AVR__
 #include <avr/pgmspace.h>
#else
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

//
// Statics
//

//
// Private methods
//

//------------------------------------------------------------------------------
void OLED::WriteByte(byte ucData)
{
  byte i = 8;

  OLED_SCL_LOW;
  while (i--)
  {
    if (ucData &0x80)
    {
      OLED_SDA_HIGH;
    }
    else
    {
      OLED_SDA_LOW;
    }
    OLED_SCL_HIGH;
    OLED_SCL_LOW;
    ucData <<= 1;
  }
}

//------------------------------------------------------------------------------
void OLED::SendData(byte *data, byte i)
{
	OLED_DATA; // D/C high
	while (i)
	{
		WriteByte(*data);
		data++;
		i--;
	}
}

//------------------------------------------------------------------------------
void OLED::SendCommand(byte *data, byte i)
{
	OLED_COMMAND; // D/C low
	while (i)
	{
		WriteByte(*data);
		data++;
		i--;
	}
}

//------------------------------------------------------------------------------
void OLED::setAddress(byte page, byte column)
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

//------------------------------------------------------------------------------
void OLED::clearScreen(void)
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

//------------------------------------------------------------------------------
void OLED::setBrightness(byte Brightness)
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
void OLED::clearLine(byte row)
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
void OLED::ScharDraw(byte row, byte column, byte data)
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
	OLED_DATA; // D/C high
  for(i=0;i<6;i++)
  {
		WriteByte(pgm_read_byte(FONT6x8+(h++)));
  }
}

//------------------------------------------------------------------------------
void OLED::Sprint(byte row, byte column, byte *word)
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
void OLED::LcharDraw(byte row, byte column, byte data)
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
	OLED_DATA; // D/C high
  for(i=0;i<8;i++)
  {
		WriteByte(pgm_read_byte(FONT8x16+(h++)));
  }
	setAddress(row + 1, column);
	OLED_DATA; // D/C high
  for(i=0;i<8;i++)
  {
		WriteByte(pgm_read_byte(FONT8x16+(h++)));
  }
}

//------------------------------------------------------------------------------
void OLED::Lprint(byte row, byte column, byte *word)
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

void OLED::pixelDraw(byte x, byte y)
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
/* Function		: horizontalLine(byte xStart, byte xStop, byte y)
* Description          : draw horizontal line from xStart to xStop
* Input		: X Start & Stop coordinate, Y
* Output		: display horizontal line
*/
void OLED::horizontalLine(byte xStart, byte xStop, byte y)
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
/* Function		: verticalLine(byte x, byte yStart, byte yStop)
* Description          : draw vertical line from yStart to yStop
* Input		: Y Start & Stop coordinate, X
* Output		: display vertical line
*/
void OLED::verticalLine(byte x, byte yStart, byte yStop)
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
/* Function		: imageDraw(const byte IMAGE[], byte row, byte column)
* Description          : draw image at row, column
* Input		: image, row, column
* Output		: display image
*/
// from TI_DogsLCD_HAL
void OLED::imageDraw(const byte IMAGE[], byte row, byte column)
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


// circleDraw function is not complete. needs checks for page surround x-axis for proper column fill

/* Function		: circleDraw(register int x, register int y, int r)
* Description          : draw circle at x,y of radius r
* Input		: x,y, radius
* Output		: display circle
*/
//------------------------------------------------------------------------------
void OLED::circleDraw(int x, int y, int r)
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
/* Function    : Fill_RAM( unsigned byte c )
* Description : Fills the OLED with one particular data
* Input       : Data
* Output      : None
*/
void OLED::Fill_RAM(byte data)
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
void OLED::Swap(byte *x, byte *y)
{
	int t;
	t =  *x;
	*x =  *y;
	*y = t;
}

//------------------------------------------------------------------------------
/* Function		: boxDraw(byte x, byte y, byte w, byte h)
* Description          : draw bow at x,y ,width , height
* Input		: x,y, w,h
* Output		: display box
*/
void OLED::boxDraw(byte x, byte y, byte w, byte h)
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
void OLED::Fill_RAM_PAGE(byte page, byte data)
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
void OLED::Set_Contrast_Control(byte d)
{
	byte ramData[] = 
	{
		SETCONTRAST, 0x00
	};
	ramData[1] = d;

	SendCommand(ramData, 2);
}

//------------------------------------------------------------------------------
void OLED::Set_Inverse_Display(byte d)
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
void OLED::Set_Display_On_Off(byte d)
{
	// 0 = off, 1 = on

	byte ramData[] = 
	{
		DISPLAYOFF
	};
	ramData[0] = ramData[0] + d;

	SendCommand(ramData, 1);
}


/* Function    : Scroll_Display
* Description : OLED Scroll Left or Right
* Input       : Xstart-0x00  Xstop-0x0F
* Output      : Scroll Left or Right
*/
//------------------------------------------------------------------------------
void OLED::Scroll_Display_Left(uint8_t Xstart, uint8_t Xstop)
{
	byte Scroll_Display_Left_init[] = 
	{
		SCROLL_LEFT, 0X00, Xstart, Scroll_2Frames, Xstop, 0X00, 0XFF, ACTIVATE_SCROLL
	};

	SendCommand(Scroll_Display_Left_init, sizeof Scroll_Display_Left_init);
}

//------------------------------------------------------------------------------
void OLED::Scroll_Display_Right(uint8_t Xstart, uint8_t Xstop)
{
	byte Scroll_Display_Right_init[] = 
	{
		SCROLL_RIGHT, 0X00, Xstart, Scroll_2Frames, Xstop, 0X00, 0XFF, ACTIVATE_SCROLL
	};

	SendCommand(Scroll_Display_Right_init, sizeof Scroll_Display_Right_init);
}

void OLED::ScrollStop(void)
{
	byte ramData[] = 
	{
		DEACTIVATE_SCROLL
	};
	SendCommand(ramData, sizeof ramData);
}



void OLED::BlinkON(void)
{
	byte ramData[] = 
	{
		DISPLAYALLON
	};
	SendCommand(ramData, sizeof ramData);
}


void OLED::BlinkOFF(void)
{
	byte ramData[] = 
	{
		DISPLAYALLON_RESUME
	};
	SendCommand(ramData, sizeof ramData);
}

//----------------------------------------------------------------
void OLED::drawLine(byte x0, byte y0, byte x1, byte y1)
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
void OLED::setFont(uint8_t fontsize)
{
	curFont = fontsize;
  clearScreen();
}

//------------------------------------------------------------------------------
void OLED::setPosi(uint8_t row, uint8_t column)
{
	curRow= row ;
	curCol= column ;
}

//
// The receive routine called by the interrupt handler
//
void OLED::recv()
{

}

//
// Constructor
//
OLED::OLED(uint8_t type)
{
  curType=type;
}

//
// Destructor
//
OLED::~OLED()
{

}

void OLED::begin(uint8_t font)
{
	curFont = font;
	pinMode(OLED_RST, OUTPUT);
	pinMode(OLED_DC, OUTPUT);
	pinMode(OLED_SCL, OUTPUT);
	pinMode(OLED_SDA, OUTPUT);

  OLED_COMMAND;
	OLED_RES_LOW;
	delay(20);
	OLED_RES_HIGH;
	delay(20);

	byte init[] = 
	{
		DISPLAYOFF,  //
		SETLOWCOLUMN,  //
		SETHIGHCOLUMN,  //
		SETSTARTLINE,  //
		SETCONTRAST,  //
		0xCF,  //
		SEGREMAP,  //
		NORMALDISPLAY,  //
		SETMULTIPLEX,  //
		0x3F,  //
		SETDISPLAYOFFSET,  //
		0x00,  //
		SETDISPLAYCLOCKDIV,  //
		0x80,  //
		SETPRECHARGE,  //
		0xF1,  //
		SETCOMPINS,  //
		0x12,  //
		SETVCOMDETECT,  //
		0x40,  //
		CHARGEPUMP,  //
		0x14,  //
		DISPLAYON  //
	};
	SendCommand(init, sizeof init);
	clearScreen();
}

int OLED::read()
{
  return 0;
}

int OLED::available()
{
  return 0;
}

size_t OLED::write(uint8_t b)
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
				curRow ++;
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
    	while(curCol<=120)
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
    	while(curCol<=120)
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

void OLED::flush()
{
}

int OLED::peek()
{
  return 0;
}
