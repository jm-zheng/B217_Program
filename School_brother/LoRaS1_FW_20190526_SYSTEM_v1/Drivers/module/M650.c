//-------------------------------------------------------------------
// Filename: M200.c
// Description: hal M200 module library ·ÅÀã«×°»´ú(I2C)½d¨Ò
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "define.h"
#include "M650.h"

uint32_t M650_Lux;

#define INPUT													1
#define OUTPUT												2

void Lux_SDA_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SDA_3_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SDA_3_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SDA_3_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SDA_3_GPIO_PORT, &GPIO_InitStruct);
		}
		DELAY_Us(1);
}

void Lux_SCL_PIN_MODE(uint8_t sw)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		if(sw == INPUT)
		{
				GPIO_InitStruct.Pin = SCL_3_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull = GPIO_PULLUP;
				HAL_GPIO_Init(SCL_3_GPIO_PORT, &GPIO_InitStruct);
		}
		else if(sw == OUTPUT)
		{
				GPIO_InitStruct.Pin = SCL_3_PIN;
				GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				HAL_GPIO_Init(SCL_3_GPIO_PORT, &GPIO_InitStruct);
		}
}

//-------------------------------------------------------------------
void M650_Start(void)
{
      SDA_3_LO();
      SCL_3_LO();
      DELAY_Us(20);
      SCL_3_HI();
      DELAY_Us(20);
      SDA_3_HI();
      DELAY_Us(200);
      
      SDA_3_LO();
      DELAY_Us(20);
      SCL_3_LO();
      DELAY_Us(20);
      
}

void M650_R_Start(void)
{

      SCL_3_HI();
      DELAY_Us(20);
      
      SDA_3_LO();
      DELAY_Us(20);
      SCL_3_LO();
      DELAY_Us(20);
      
}


void M650_Stop(void)
{

      SCL_3_LO();
      SDA_3_LO();
      DELAY_Us(100);
      SCL_3_HI();
      DELAY_Us(100);
      SDA_3_HI();
      DELAY_Us(100);
}

//-------------------------------------------------------------------
uint8_t M650_WriteByte(uint8_t dat)
{
    uint8_t i, err = 0;
    Lux_SDA_PIN_MODE(OUTPUT);
    for (i = 0; i <8; i++)
    {
        if (dat &0x80)
        {
            SDA_3_HI();
        }
        else
        {
            SDA_3_LO();
        }
        DELAY_Us(1);
        dat = dat << 1;
        SCL_3_HI();
        DELAY_Us(20);
        SCL_3_LO();
        DELAY_Us(20);
    }
    SDA_3_HI();
    Lux_SDA_PIN_MODE(INPUT);
    //MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN, 0);
    SCL_3_HI();
    DELAY_Us(20);
    if (SDA_3_IN())
    {
        err = 1;
    }
    SCL_3_LO();
    Lux_SDA_PIN_MODE(OUTPUT);
    SDA_3_HI();
    return err;
}

//-------------------------------------------------------------------
uint8_t M650_ReadByte(uint8_t ack)
{
    uint8_t res = 0;
    uint8_t cnt;

    //HAL_I2C_SDA_SET();
    Lux_SDA_PIN_MODE(INPUT);
    SCL_3_LO();
    for (cnt = 0; cnt < 8; cnt++)
    {
        SCL_3_HI();
        DELAY_Us(20);

        res <<= 1;
        if (SDA_3_IN())
        {
            res |= 0x01;
        }
        SCL_3_LO();
        DELAY_Us(20);
    }
    Lux_SDA_PIN_MODE(OUTPUT);
    DELAY_Us(20);
    if (ack == 1)
    {
        SDA_3_LO();
    }
    SCL_3_HI();
    DELAY_Us(20);
    SCL_3_LO();
    SDA_3_HI();
    return res;
}

//-------------------------------------------------------------------
void M650_ConnectReset(void)
{
    uint8_t i;

    SDA_3_HI();
    SCL_3_LO();
    DELAY_Us(20);
    for (i = 0; i < 9; i++)
    {
        SCL_3_HI();
        DELAY_Us(5);
        SCL_3_LO();
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
void M650_Init(void)
{
    Lux_SCL_PIN_MODE(OUTPUT);
    Lux_SDA_PIN_MODE(OUTPUT);
    //SHT_ConnectReset();
    //SHT_Start();
    //SHT_WriteByte(0x1E);
	DELAY_Ms(100);
}

uint8_t count, err = 0;
    uint8_t M650_exponent;
    uint32_t M650_Mantissa;
    uint32_t M650_exponentFor2;
		uint32_t val;
void M650_GetValue(void)
{
    
    while (1)
    {
        M650_Start();
        err += M650_WriteByte(0x94);
        DELAY_Us(200);
        err += M650_WriteByte(0x03); //  Converter H
        DELAY_Us(200);
        M650_R_Start();
        DELAY_Us(200);
        err += M650_WriteByte(0x95);
        DELAY_Us(200);
        if (err > 0)
        {
            break;
        }

        M650_Mantissa = M650_ReadByte(0);
        M650_exponent = (M650_Mantissa &0xf0)>>4;
        DELAY_Us(200);
        
        M650_R_Start();
        err += M650_WriteByte(0x94);
        DELAY_Us(200);
        err += M650_WriteByte(0x04); //  Converter H
        DELAY_Us(200);
        M650_R_Start();
        DELAY_Us(200);
        err += M650_WriteByte(0x95);
        DELAY_Us(200);
        if (err > 0)
        {
            break;
        }
        //(luxHigh&0xf0)>>4;
        M650_Mantissa = (M650_Mantissa&0x0f)<<4 | M650_ReadByte(0);

        SDA_3_HI();
        Lux_SDA_PIN_MODE(OUTPUT);
        
        DELAY_Ms(10);
        M650_exponentFor2 = 1;
        for(count=0 ;count<M650_exponent ;count++)
        {
            M650_exponentFor2 = M650_exponentFor2 * 2;
        }
				if(M650_exponentFor2 <223)
				{
						val = ((float)M650_exponentFor2*0.045)* M650_Mantissa;
						M650_Lux = val ; 
				}
				else
				{
						val = ((float)M650_exponentFor2*0.045);
						M650_Lux = val * M650_Mantissa;   
				}
             
        SDA_3_HI();
        Lux_SDA_PIN_MODE(OUTPUT);       
        break;
    }
    
    if (err > 0)
    {
        M650_ConnectReset();
    }
}

void M650_DisableInit(void)
{
    Lux_SCL_PIN_MODE(INPUT);
    Lux_SDA_PIN_MODE(INPUT);
}
