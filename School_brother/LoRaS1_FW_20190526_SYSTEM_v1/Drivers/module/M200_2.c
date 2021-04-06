//-------------------------------------------------------------------
// Filename: M200.c
// Description: hal M200 module library ·ÅÀã«×°»´ú(I2C)½d¨Ò
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "define.h"
#include "M200_2.h"


uint16_t M200_Humi;
uint16_t M200_Temp;

#define INPUT													1
#define OUTPUT												2

void SDA_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SDA_1_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SDA_1_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SDA_1_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SDA_1_GPIO_PORT, &GPIO_InitStruct);
		}
		DELAY_Us(1);
}

void SCL_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SCL_1_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SCL_1_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SCL_1_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SCL_1_GPIO_PORT, &GPIO_InitStruct);
		}
}




//-------------------------------------------------------------------
void SHT_Start(void)
{
SDA_PIN_MODE(OUTPUT);
SCL_PIN_MODE(OUTPUT);
    SCL_1_LO();
    SDA_1_HI();
    DELAY_Us(5);
    SCL_1_HI();
    DELAY_Us(5);
    SDA_1_LO();
    DELAY_Us(5);
    SCL_1_LO();
    DELAY_Us(20);
    SCL_1_HI();
    DELAY_Us(5);
    SDA_1_HI();
    DELAY_Us(5);
    SCL_1_LO();
    DELAY_Us(5);
}

//-------------------------------------------------------------------
uint8_t SHT_WriteByte(uint8_t dat)
{
SDA_PIN_MODE(OUTPUT);
SCL_PIN_MODE(OUTPUT);
    uint8_t i, err = 0;

    for (i = 0; i <8; i++)
    {
        if (dat &0x80)
        {
            SDA_1_HI();
        }
        else
        {
            SDA_1_LO();
        }
        dat = dat << 1;
        SCL_1_HI();
        DELAY_Us(20);
        SCL_1_LO();
        DELAY_Us(20);
    }
    SDA_1_HI();
SDA_PIN_MODE(INPUT);
    //HAL_I2C_SDA_DIR_IN();
    //MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN, 0);
    SCL_1_HI();
    DELAY_Us(5);
    if (SDA_1_IN())
    {
        err = 1;
    }
    //HAL_SPI_CS_DIS();
    SCL_1_LO();
SDA_PIN_MODE(OUTPUT);
    SDA_1_HI();
    return err;
}

//-------------------------------------------------------------------
uint8_t SHT_ReadByte(uint8_t ack)
{
    uint8_t res = 0;
    uint8_t cnt;

    SDA_1_HI();
SDA_PIN_MODE(INPUT);
    SCL_1_LO();
    for (cnt = 0; cnt < 8; cnt++)
    {
        SCL_1_HI();
        DELAY_Us(5);
        res <<= 1;
        if (SDA_1_IN())
        {
            res |= 0x01;
        }
        SCL_1_LO();
        DELAY_Us(5);
    }
SDA_PIN_MODE(OUTPUT);
    DELAY_Us(5);
    if (ack == 1)
    {
        SDA_1_LO();
    }
    SCL_1_HI();
    DELAY_Us(20);
    SCL_1_LO();
    SDA_1_HI();
    return res;
}

//-------------------------------------------------------------------
void SHT_ConnectReset(void)
{
    uint8_t i;

    SDA_1_HI();
    SCL_1_LO();
    DELAY_Us(20);
    for (i = 0; i < 9; i++)
    {
        SCL_1_HI();
        DELAY_Us(5);
        SCL_1_LO();
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
void M200_Init(void)
{
    SDA_PIN_MODE(OUTPUT);
    SCL_PIN_MODE(OUTPUT);
    SHT_ConnectReset();
    SHT_Start();
    SHT_WriteByte(0x1E);
		DELAY_Ms(100);
}

//-------------------------------------------------------------------
void M200_GetValue(void)
{
    uint8_t count, err = 0;
		M200_Temp = M200_Humi = 0;
    while (1)
    {
        SHT_Start();
        err += SHT_WriteByte(0x05); //  Converter H
        if (err > 0)
        {
            break;
        }
        //55ms
        SDA_PIN_MODE(INPUT);
        for (count = 0; count < 75; count++)
        {
            DELAY_Ms(1);
            if (SDA_1_IN() == 0)
            {
                SDA_PIN_MODE(OUTPUT);
                M200_Humi = SHT_ReadByte(1);
                if (M200_Humi > 0x3F)
                {
                    M200_Humi = 0x3F;
                }
                M200_Humi = (M200_Humi << 8) + (uint16_t)SHT_ReadByte(1);
                SHT_ReadByte(0);
                break;
            }
        }
        SDA_1_HI();
        SDA_PIN_MODE(OUTPUT);
        
        DELAY_Ms(10);
        SHT_Start();
        err += SHT_WriteByte(0x03); // Converter T
        if (err > 0)
        {
            break;
        }
        //210ms
        SDA_PIN_MODE(INPUT);
        for (count = 0; count < 250; count++)
        {
            DELAY_Ms(1);
            if (SDA_1_IN() == 0)
            {
                SDA_PIN_MODE(OUTPUT);
                M200_Temp = SHT_ReadByte(1);
                if (M200_Temp > 0x3F)
                {
                    M200_Temp = 0x3F;
                }
                M200_Temp = (M200_Temp << 8) + (uint16_t)SHT_ReadByte(1);
                SHT_ReadByte(0);
                break;
            }
        }
        SDA_1_HI();
        SDA_PIN_MODE(OUTPUT);
				M200_Temp = (uint16_t)(((((float)M200_Temp) *0.01) - 40.0) *10.0);
				M200_Humi = (uint16_t)(((((float)M200_Humi) *0.0405) - (((float)M200_Humi)*((float)M200_Humi) *0.0000028) - 4.0) *10.0);				
        break;
    }
    
		
		
    if (err > 0)
    {
        SHT_ConnectReset();
    }
}
