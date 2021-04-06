//-------------------------------------------------------------------
// Filename: M200.c
// Description: hal M200 module library ·ÅÀã«×°»´ú(I2C)½d¨Ò
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "define.h"
#include "M200_1.h"


uint16_t GND_M200_Humi;
uint16_t GND_M200_Temp;

#define INPUT													1
#define OUTPUT												2

void GND_SDA_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SDA_2_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SDA_2_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SDA_2_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SDA_2_GPIO_PORT, &GPIO_InitStruct);
		}
		DELAY_Us(1);
}

void GND_SCL_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SCL_2_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SCL_2_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SCL_2_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SCL_2_GPIO_PORT, &GPIO_InitStruct);
		}
}




//-------------------------------------------------------------------
void GND_SHT_Start(void)
{
GND_SDA_PIN_MODE(OUTPUT);
GND_SCL_PIN_MODE(OUTPUT);
    SCL_2_LO();
    SDA_2_HI();
    DELAY_Us(5);
    SCL_2_HI();
    DELAY_Us(5);
    SDA_2_LO();
    DELAY_Us(5);
    SCL_2_LO();
    DELAY_Us(20);
    SCL_2_HI();
    DELAY_Us(5);
    SDA_2_HI();
    DELAY_Us(5);
    SCL_2_LO();
    DELAY_Us(5);
}

//-------------------------------------------------------------------
uint8_t GND_SHT_WriteByte(uint8_t dat)
{
GND_SDA_PIN_MODE(OUTPUT);
GND_SCL_PIN_MODE(OUTPUT);
    uint8_t i, err = 0;

    for (i = 0; i <8; i++)
    {
        if (dat &0x80)
        {
            SDA_2_HI();
        }
        else
        {
            SDA_2_LO();
        }
        dat = dat << 1;
        SCL_2_HI();
        DELAY_Us(20);
        SCL_2_LO();
        DELAY_Us(20);
    }
    SDA_2_HI();
GND_SDA_PIN_MODE(INPUT);
    //HAL_I2C_SDA_DIR_IN();
    //MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN, 0);
    SCL_2_HI();
    DELAY_Us(5);
    if (SDA_2_IN())
    {
        err = 1;
    }
    //HAL_SPI_CS_DIS();
    SCL_2_LO();
GND_SDA_PIN_MODE(OUTPUT);
    SDA_2_HI();
    return err;
}

//-------------------------------------------------------------------
uint8_t GND_SHT_ReadByte(uint8_t ack)
{
    uint8_t res = 0;
    uint8_t cnt;

    SDA_2_HI();
GND_SDA_PIN_MODE(INPUT);
    SCL_2_LO();
    for (cnt = 0; cnt < 8; cnt++)
    {
        SCL_2_HI();
        DELAY_Us(5);
        res <<= 1;
        if (SDA_2_IN())
        {
            res |= 0x01;
        }
        SCL_2_LO();
        DELAY_Us(5);
    }
GND_SDA_PIN_MODE(OUTPUT);
    DELAY_Us(5);
    if (ack == 1)
    {
        SDA_2_LO();
    }
    SCL_2_HI();
    DELAY_Us(20);
    SCL_2_LO();
    SDA_2_HI();
    return res;
}

//-------------------------------------------------------------------
void GND_SHT_ConnectReset(void)
{
    uint8_t i;

    SDA_2_HI();
    SCL_2_LO();
    DELAY_Us(20);
    for (i = 0; i < 9; i++)
    {
        SCL_2_HI();
        DELAY_Us(5);
        SCL_2_LO();
        DELAY_Us(5);
    }
	DELAY_Ms(100);
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
// @fn      M200_Init
// @return  none
//-------------------------------------------------------------------
void GND_M200_Init(void)
{
    GND_SDA_PIN_MODE(OUTPUT);
    GND_SCL_PIN_MODE(OUTPUT);
    GND_SHT_ConnectReset();
    GND_SHT_Start();
    GND_SHT_WriteByte(0x1E);
		DELAY_Ms(100);
}

//-------------------------------------------------------------------
void GND_M200_GetValue(void)
{
    uint8_t count, err = 0;
		GND_M200_Temp = GND_M200_Humi = 0;
    while (1)
    {
        GND_SHT_Start();
        err += GND_SHT_WriteByte(0x05); //  Converter H
        if (err > 0)
        {
            break;
        }
        //55ms
        GND_SDA_PIN_MODE(INPUT);
        for (count = 0; count < 75; count++)
        {
            DELAY_Ms(1);
            if (SDA_2_IN() == 0)
            {
                GND_SDA_PIN_MODE(OUTPUT);
                GND_M200_Humi = GND_SHT_ReadByte(1);
                if (GND_M200_Humi > 0x3F)
                {
                    GND_M200_Humi = 0x3F;
                }
                GND_M200_Humi = (GND_M200_Humi << 8) + (uint16_t)GND_SHT_ReadByte(1);
                GND_SHT_ReadByte(0);
                break;
            }
        }
        SDA_2_HI();
        GND_SDA_PIN_MODE(OUTPUT);
        
        DELAY_Ms(10);
        GND_SHT_Start();
        err += GND_SHT_WriteByte(0x03); // Converter T
        if (err > 0)
        {
            break;
        }
        //210ms
        GND_SDA_PIN_MODE(INPUT);
        for (count = 0; count < 250; count++)
        {
            DELAY_Ms(1);
            if (SDA_2_IN() == 0)
            {
                GND_SDA_PIN_MODE(OUTPUT);
                GND_M200_Temp = GND_SHT_ReadByte(1);
                if (GND_M200_Temp > 0x3F)
                {
                    GND_M200_Temp = 0x3F;
                }
                GND_M200_Temp = (GND_M200_Temp << 8) + (uint16_t)GND_SHT_ReadByte(1);
                GND_SHT_ReadByte(0);
                break;
            }
        }
        SDA_2_HI();
        GND_SDA_PIN_MODE(OUTPUT);
				GND_M200_Temp = (uint16_t)(((((float)GND_M200_Temp) *0.01) - 40.0) *10.0);
				GND_M200_Humi = (uint16_t)(((((float)GND_M200_Humi) *0.0405) - (((float)GND_M200_Humi)*((float)GND_M200_Humi) *0.0000028) - 4.0) *10.0);
						
        break;
    }
    
    if (err > 0)
    {
        GND_SHT_ConnectReset();
    }
}
