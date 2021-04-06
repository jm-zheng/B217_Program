//-------------------------------------------------------------------
// library.c
//-------------------------------------------------------------------
#include "define.h"

//-------------------------------------------------------------------
uint8_t LIB_AscToDec(uint8_t ch)
{
	if (ch >= '0' && ch <= '9')
	{
		ch -= '0';
	}
	else
	{
		ch = 10;
	}
	return ch;
}

//-------------------------------------------------------------------
uint8_t LIB_AscToHex(uint8_t ch)
{
	if (ch >= '0' && ch <= '9')
	{
		ch -= '0';
	}
	else if (ch >= 'A' && ch <= 'F')
	{
		ch = ch - 'A' + 10;
	}
	else if (ch >= 'a' && ch <= 'f')
	{
		ch = ch - 'a' + 10;
	}
	else
	{
		ch = 0;
	}
	return ch;
}

//-------------------------------------------------------------------
TYPE_AscHex LIB_HexToAsc(uint8_t uch)
{
	TYPE_AscHex asc;

	asc.High = ((uch &0xF0) >> 4);
	if (asc.High > 9)
	{
		asc.High = (asc.High - 10+'A');
	}
	else
	{
		asc.High = asc.High + '0';
	}

	asc.Low = uch &0x0F;
	if (asc.Low > 9)
	{
		asc.Low = (asc.Low - 10+'A');
	}
	else
	{
		asc.Low = asc.Low + '0';
	}
	return asc;
}

//-------------------------------------------------------------------
uint8_t LIB_StrLen(char ucDataStr[])
{
	uint8_t j;

	for ( j = 0; j<255; j++ )
	{
		if(ucDataStr[j] == '\0')
		{
			return j;
		}
	}
	return 0;
}


//-------------------------------------------------------------------
void LIB_MemCpy(uint8_t mtag[],uint8_t msrc[],uint8_t len)
{
	uint8_t i;

	for ( i = 0; i<len; i++ )
	{
		mtag[i] = msrc[i];
	}
}

