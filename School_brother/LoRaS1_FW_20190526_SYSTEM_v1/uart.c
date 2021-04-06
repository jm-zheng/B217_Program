// -------------------------------------------------------------------
// uart.c
// -------------------------------------------------------------------
#include "define.h"

#define RTU_MAX_REG		100

__IO uint8_t RS485_TxBuffer[RS485_TX_BUFFER_MAX];
__IO uint8_t RS485_RxBuffer[RS485_RX_BUFFER_MAX];
__IO uint8_t RS485_Flag;
__IO uint8_t RS485_TxLength;
__IO uint8_t RS485_TxIndex;
__IO uint8_t RS485_RxLength;
__IO uint8_t RS485_Count;
uint8_t RS485_Read;

__IO uint8_t CO2_TxBuffer[CO2_TX_BUFFER_MAX];
__IO uint8_t CO2_RxBuffer[CO2_RX_BUFFER_MAX];
__IO uint8_t CO2_Flag;
__IO uint8_t CO2_TxLength;
__IO uint8_t CO2_RxLength;
__IO uint8_t CO2_RxIndex;
__IO uint8_t CO2_TxIndex;
__IO uint8_t CO2_Count;
uint8_t CO2_Read;

__IO uint8_t RF_TxBuffer[RF_TX_BUFFER_MAX];
__IO uint8_t RF_RxBuffer[RF_RX_BUFFER_MAX];
__IO uint8_t RF_Flag;
__IO uint8_t RF_TxLength;
__IO uint8_t RF_RxLength;
__IO uint8_t RF_RxIndex;
__IO uint8_t RF_TxIndex;
__IO uint8_t RF_Count;
uint8_t RF_Read;

__IO uint8_t ISP_TxBuffer[ISP_TX_BUFFER_MAX];
__IO uint8_t ISP_RxBuffer[ISP_RX_BUFFER_MAX];
__IO uint8_t ISP_Flag;
__IO uint8_t ISP_TxLength;
__IO uint8_t ISP_RxLength;
__IO uint8_t ISP_RxIndex;
__IO uint8_t ISP_TxIndex;
__IO uint8_t ISP_Count;
uint8_t ISP_Read;


uint8_t COMM_Slave;
uint8_t *COMM_Buffer;
uint8_t COMM_Flag;
uint8_t COMM_Cmd;
uint8_t COMM_Addr;
uint8_t COMM_Reg;
uint8_t COMM_Len;
uint8_t COMM_Read;
uint8_t COMM_Point;
uint16_t COMM_Crc;
uint8_t COMM_CrcHi;
uint8_t COMM_CrcLo;

uint16_t CRC_Table[] = {
0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,//
0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,//
0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,//
0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,//
0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,//
0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,//
0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,//
0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,//
0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,//
0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,//
0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,//
0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,//
0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,//
0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,//
0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,//
0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,//
0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,//
0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,//
0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,//
0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,//
0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,//
0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,//
0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,//
0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,//
0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,//
0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,//
0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,//
0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,//
0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,//
0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,//
0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,//
0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };//

// -------------------------------------------------------------------
void UART_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	/* RS485 會耗電先不開啟*/
	// USART1
  __HAL_RCC_USART1_CLK_ENABLE();
  // USART1 GPIO Configuration    
  // PA9     ------> USART1_TX
  // PA10     ------> USART1_RX 
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// RS485
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);	

	RS485_Flag = 0;
	RS485_TxIndex = 0x00;
	RS485_TxLength = 0x00;
	RS485_RxLength = 0x00;
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	/**/
	
	// USART2
  __HAL_RCC_USART2_CLK_ENABLE();
  // USART2 GPIO Configuration    
  // PA2     ------> USART2_TX
  // PA3     ------> USART2_RX 
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	// RF (RoLa)
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	RF_Flag = 0;
	RF_TxIndex = 0x00;
	RF_RxIndex = 0x00;
	RF_RxLength = 0x00;
	RF_TxLength = 0x00;
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

	// USART3
  __HAL_RCC_USART3_CLK_ENABLE();
  // USART2 GPIO Configuration    
  // PB10     ------> USART3_TX
  // PB11     ------> USART3_RX 
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_USART3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	// CO2
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart3);

	// USART4
	__HAL_RCC_USART4_CLK_ENABLE();
	// USART4 GPIO Configuration    
  // PC10     ------> USART4_TX
  //  PC11     ------> USART4_RX 
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF0_USART4;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	// ISP
  huart4.Instance = USART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart4);
	HAL_NVIC_SetPriority(USART3_4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART3_4_IRQn);

	CO2_Flag = 0;
	CO2_TxIndex = 0x00;
	CO2_RxIndex = 0x00;
	CO2_RxLength = 0x00;
	CO2_TxLength = 0x00;
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

	ISP_Flag = 0;
	ISP_TxIndex = 0x00;
	ISP_RxIndex = 0x00;
	ISP_RxLength = 0x00;
	ISP_TxLength = 0x00;
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);
}

// -------------------------------------------------------------------
// RS485
// -------------------------------------------------------------------
void USART1_IRQHandler(void)
{
	uint8_t byte;
	if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE) != RESET))
	{
		byte = USART1->RDR;
		RS485_Count = 0;
		if(RS485_Flag == 0)
		{
			if (RS485_RxLength < RS485_RX_BUFFER_MAX)
			{
				RS485_RxBuffer[RS485_RxLength++] = byte;
			}
		}
	}

	// USART in mode Tramitter
	if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_TXE) != RESET))
	{
		USART1->TDR = RS485_TxBuffer[RS485_TxIndex++];
		if (RS485_TxIndex >= RS485_TX_BUFFER_MAX)
		{
			RS485_TxIndex=0;
		}
		if (RS485_TxIndex == RS485_TxLength)
		{
			__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
			RS485_TxLength = 0;
			RS485_TxIndex = 0;
      __HAL_UART_ENABLE_IT(&huart1, UART_IT_TC);
		}
	}
	if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_TC) != RESET))
	{
		RS485_TxLength = 0;
		RS485_TxIndex = 0;
		__HAL_UART_DISABLE_IT(&huart1, UART_IT_TC);
		DELAY_Us(200);
		RS485_RX();
	}
}

// -------------------------------------------------------------------
// RF
// -------------------------------------------------------------------
void USART2_IRQHandler(void)
{
	uint8_t byte;

	if ((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_RXNE) != RESET))
	{
		byte = USART2->RDR;
		RF_Count = 0;
		if(RF_Flag == 0)
		{
			if (RF_RxLength < ISP_RX_BUFFER_MAX)
			{
				RF_RxBuffer[RF_RxLength++] = byte;
			}
		}
	}

	// USART in mode Tramitter
	if ((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_TXE) != RESET))
	{
		USART2->TDR = RF_TxBuffer[RF_TxIndex++];
		if (RF_TxIndex >= RF_TX_BUFFER_MAX)
		{
			RF_TxIndex=0;
		}
		if (RF_TxIndex == RF_TxLength)
		{
			__HAL_UART_DISABLE_IT(&huart2, UART_IT_TXE);
			RF_TxLength = 0;
			RF_TxIndex = 0;
		}
	}
}

// -------------------------------------------------------------------
// CO2 / ISP
// -------------------------------------------------------------------
void USART3_4_IRQHandler(void)
{
	uint8_t byte;

	if ((__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart3, UART_IT_RXNE) != RESET))
	{
		byte = USART3->RDR;
		CO2_Count = 0;
		if(CO2_Flag == 0)
		{
			if (CO2_RxLength < CO2_RX_BUFFER_MAX)
			{
				CO2_RxBuffer[CO2_RxLength++] = byte;
			}
		}
	}
	
	// USART in mode Tramitter
	if ((__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TXE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart3, UART_IT_TXE) != RESET))
	{
		USART3->TDR = CO2_TxBuffer[CO2_TxIndex++];
		if (CO2_TxIndex >= CO2_TX_BUFFER_MAX)
		{
			CO2_TxIndex=0;
		}
		if (CO2_TxIndex == CO2_TxLength)
		{
			__HAL_UART_DISABLE_IT(&huart3, UART_IT_TXE);
			CO2_TxLength = 0;
			CO2_TxIndex = 0;
		}
	}

	if ((__HAL_UART_GET_FLAG(&huart4, UART_FLAG_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart4, UART_IT_RXNE) != RESET))
	{
		byte = USART4->RDR;
		ISP_Count = 0;
		if(ISP_Flag == 0)
		{
			if (ISP_RxLength < ISP_RX_BUFFER_MAX)
			{
				ISP_RxBuffer[ISP_RxLength++] = byte;
			}
		}
	}
	
	// USART in mode Tramitter
	if ((__HAL_UART_GET_FLAG(&huart4, UART_FLAG_TXE) != RESET) && (__HAL_UART_GET_IT_SOURCE(&huart4, UART_IT_TXE) != RESET))
	{
		USART4->TDR = ISP_TxBuffer[ISP_TxIndex++];
		if (ISP_TxIndex >= ISP_TX_BUFFER_MAX)
		{
			ISP_TxIndex=0;
		}
		if (ISP_TxIndex == ISP_TxLength)
		{
			__HAL_UART_DISABLE_IT(&huart4, UART_IT_TXE);
			ISP_TxLength = 0;
			ISP_TxIndex = 0;
		}
	}	
}


// -------------------------------------------------------------------
void RS485_PutU8(uint8_t ch)
{
	RS485_TxBuffer[RS485_TxLength++] = ch;
}

// -------------------------------------------------------------------
void RS485_PutByte(uint8_t ch)
{
	RS485_TxBuffer[RS485_TxLength++] = ch;
}

//-------------------------------------------------------------------
void RS485_PutEnd(void)
{
	RS485_TX();	
	DELAY_Us(200);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
}

// -------------------------------------------------------------------
uint8_t RS485_GetByte(void)
{
	uint8_t ch;
	ch = RS485_RxBuffer[RS485_Read++];
	return ch;
}

// -------------------------------------------------------------------
void RF_PutByte(uint8_t ch)
{
	RF_TxBuffer[RF_TxLength++] = ch;
}

//-------------------------------------------------------------------
void RF_PutEnd(void)
{
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_TXE);
}

// -------------------------------------------------------------------
uint8_t RF_GetByte(void)
{
	uint8_t ch;
	ch = RF_RxBuffer[RF_Read++];
	return ch;
}


// -------------------------------------------------------------------
void CO2_PutByte(uint8_t ch)
{
	CO2_TxBuffer[CO2_TxLength++] = ch;
}

//-------------------------------------------------------------------
void CO2_PutEnd(void)
{
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_TXE);
}

// -------------------------------------------------------------------
uint8_t CO2_GetByte(void)
{
	uint8_t ch;
	ch = CO2_RxBuffer[CO2_Read++];
	return ch;
}


// -------------------------------------------------------------------
void ISP_PutByte(uint8_t ch)
{
	ISP_TxBuffer[ISP_TxLength++] = ch;
}

//-------------------------------------------------------------------
void ISP_PutEnd(void)
{
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_TXE);
}

// -------------------------------------------------------------------
uint8_t ISP_GetByte(void)
{
	uint8_t ch;
	ch = ISP_RxBuffer[ISP_Read++];
	return ch;
}

//-------------------------------------------------------------------
void COMM_PutByte(uint8_t ch)
{
	ISP_PutByte(ch);
	COMM_CrcCal(ch);
}
//-------------------------------------------------------------------
void COMM_PutStart(void)
{
	COMM_CrcStart();
	COMM_PutByte(COMM_Slave);
	COMM_PutByte(COMM_Cmd);
}

//-------------------------------------------------------------------
void COMM_PutEnd(void)
{
	COMM_CrcEnd();
	COMM_PutByte(COMM_CrcLo);
	COMM_PutByte(COMM_CrcHi);
	
	// ISP
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_TXE);
}

//-------------------------------------------------------------------
void COMM_CrcStart(void)
{
	COMM_Crc = 0xFFFF;
}

//-------------------------------------------------------------------
void COMM_CrcCal(uint8_t ch)
{
  COMM_Crc = (COMM_Crc >> 8) ^ CRC_Table[(COMM_Crc ^ ch) & 0xFF];
}

//-------------------------------------------------------------------
void COMM_CrcEnd(void)
{
	COMM_CrcHi = (uint8_t)(COMM_Crc >> 8);
	COMM_CrcLo = (uint8_t)(COMM_Crc);
}

//-------------------------------------------------------------------
void COMM_CrcCheck(void)
{
	uint16_t i;

	COMM_CrcStart();
	for (i = 0; i < (COMM_Point - 2); i++)
	{
		COMM_CrcCal(COMM_Buffer[i]);
	}
	COMM_CrcEnd();
}

//-------------------------------------------------------------------
void COMM_PutWord(uint16_t ch)
{
	COMM_PutByte((uint8_t)(ch >> 8));
	COMM_PutByte((uint8_t)(ch));
}

//-------------------------------------------------------------------
void COMM_PutDWord(uint32_t ch)
{
	COMM_PutWord((uint16_t)(ch >> 16));
	COMM_PutWord((uint16_t)(ch));
}

//-------------------------------------------------------------------
uint8_t COMM_GetByte(void)
{
	return (COMM_Buffer[COMM_Read++]);
}

//-------------------------------------------------------------------
uint16_t COMM_GetWord(void)
{
	uint16_t ch;
	ch = (uint16_t)(COMM_Buffer[COMM_Read++]);
	ch = (ch << 8) + (uint16_t)(COMM_Buffer[COMM_Read++]);
	return ch;
}

//-------------------------------------------------------------------
uint32_t COMM_GetDWord(void)
{
	uint32_t ch;
	ch = (uint32_t)(COMM_GetWord());
	ch = (ch << 16) + (uint32_t)(COMM_GetWord());
	return ch;
}

//-------------------------------------------------------------------
void COMM_ReadHoldingRegisters(void)
{
	uint8_t i,len;
	//uint32_t addr;
	uint32_t val;

	if(COMM_Reg>RTU_MAX_REG)
	{
		COMM_Reg=0;
	}
	len=COMM_Len;
	if(len>64)
	{
		len=64;
	}		
	COMM_PutStart();
	COMM_PutByte(len*2);
	for(i=0;i<(len/2);i++)
	{
		//addr=RS485_Addr_Table[COMM_Reg+i];
		//val=FMC_Read(PARAMETER_ADDR + addr);
		COMM_PutDWord(val);
	}
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void COMM_PresetSingleRegister(void)
{
	//uint32_t addr;

	if(COMM_Reg>RTU_MAX_REG)
	{
		COMM_Reg=0;
	}

	//addr=RS485_Addr_Table[COMM_Reg];
	//FMC_Write(PARAMETER_ADDR + addr, COMM_Len);

	COMM_PutStart();
	COMM_PutWord(COMM_Reg);
	COMM_PutWord(COMM_Len);
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void COMM_PresetMultipleRegisters(void)
{
	//uint32_t addr;
	uint8_t nbyte,len,i;
	
	if(COMM_Reg>RTU_MAX_REG)
	{
		COMM_Reg=0;
	}
	len=COMM_Len;
	if(len>64)
	{
		len=64;
	}		
	nbyte=COMM_GetByte();
	if(nbyte==(len*2))
	{
		for(i=0;i<len;i++)
		{
			//addr=RS485_Addr_Table[COMM_Reg+i];
			//FMC_Write(PARAMETER_ADDR + addr, COMM_GetWord());
		}
		COMM_PutStart();
		COMM_PutWord(COMM_Reg);
		COMM_PutWord(COMM_Len);
		COMM_PutEnd();
	}
}

//-------------------------------------------------------------------
void COMM_GetSlave(void)
{
	COMM_Addr = COMM_Slave;
	COMM_PutStart();
	COMM_PutWord(DEVICE_MODEL);
	COMM_PutWord(2);
	COMM_PutWord(COMM_Slave);
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void COMM_GetSnVersion(void)
{
	if (COMM_Len == 8)
	{
		if(COMM_GetDWord()==0x33423596)
		{
			DEVICE_Sn = COMM_GetDWord();
			//FRAM_WriteU32(FRAM_SN_ADDR, DEVICE_Sn);
		}
	}

	COMM_PutStart();
	COMM_PutWord(COMM_Len);
	COMM_PutWord(8);
	COMM_PutWord(DEVICE_MODEL);
	COMM_PutWord(DEVICE_VERSION);
	COMM_PutDWord(DEVICE_Sn);
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void COMM_SetSlave(void)
{
	uint16_t slave;

	if (COMM_Len == 2)
	{
		slave = COMM_GetWord();
		if(slave==0)
		{
			slave=1;
		}
		if (slave != COMM_Slave)
		{
			COMM_Slave = slave;
			//FRAM_WriteU8(FRAM_SLAVE_ADDR, COMM_Slave);
		}
	}
	COMM_PutStart();
	COMM_PutWord(DEVICE_MODEL);
	COMM_PutWord(2);
	COMM_PutWord(COMM_Slave);
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void COMM_SetSlaveBySN(void)
{
	uint16_t slave;
	uint32_t uid;

	if (COMM_Len == 6)
	{
		uid = COMM_GetDWord();
		slave = COMM_GetWord();
		if (uid == DEVICE_Sn)
		{
			if(slave==0)
			{
				slave=1;
			}
			if (slave != COMM_Slave)
			{
				COMM_Slave = slave;
				//FRAM_WriteU8(FRAM_SLAVE_ADDR, COMM_Slave);
			}
		}
	}
	COMM_PutStart();
	COMM_PutWord(DEVICE_MODEL);
	COMM_PutWord(6);
	COMM_PutDWord(DEVICE_Sn);
	COMM_PutWord(COMM_Slave);
	COMM_PutEnd();
}


//-------------------------------------------------------------------
void COMM_SetReset(void)
{
	uint16_t chk,cmd;

	if (COMM_Len == 4)
	{
		chk = COMM_GetWord();
		cmd = COMM_GetWord();
		if(chk==0x55AA)
		{
			if(cmd==0x0001)
			{
				DEVICE_ResetFlag=1; // REBOOT
      }
			if(cmd==0x0002)
			{
				DEVICE_ResetFlag=2; // INITIAL
				//PARAMETER_Initial();
			}
			if(cmd==0x0003)
			{
				COMM_PutStart();
				COMM_PutWord(DEVICE_MODEL);
				COMM_PutWord(0);
				COMM_PutEnd();
				BEEP_Ok();
				DEVICE_ResetFlag=1; // REBOOT
				return;
			}
		}
	}
	COMM_PutStart();
	COMM_PutWord(DEVICE_MODEL);
	COMM_PutWord(0);
	COMM_PutEnd();
}

//-------------------------------------------------------------------
void UART_Proc(void)
{
	COMM_Flag=0;
	if (ISP_Count >= 10) // 10ms
	{
		ISP_Count=0;
		if(ISP_RxLength>=8)
		{
			COMM_Flag=1;
		}
		else
		{
			ISP_RxLength=0;
		}
	}	
	if(COMM_Flag>0)
	{
		COMM_Buffer=(uint8_t *)ISP_RxBuffer;
		COMM_Point=ISP_RxLength;
		
		COMM_Read = 0;
		COMM_Addr = COMM_GetByte();
		if (COMM_Addr == 0 || COMM_Addr == COMM_Slave)
		{
			COMM_CrcCheck();
			if (COMM_CrcLo == COMM_Buffer[COMM_Point - 2] && COMM_CrcHi == COMM_Buffer[COMM_Point - 1])
			{
				if (COMM_Flag==1)
				{
					ISP_Flag = 1;
				}				
				COMM_Read = 1;
				COMM_Cmd = COMM_GetByte();
				COMM_Reg = COMM_GetWord();
				COMM_Len = COMM_GetWord();
				switch (COMM_Cmd)
				{
					case COMM_CMD_READ_HOLDING_REGISTER:
						COMM_ReadHoldingRegisters();
						break;
					case COMM_CMD_PRESET_SINGLE_REGISTER:
						COMM_PresetSingleRegister();
						break;
					case COMM_CMD_PRESET_MULTIPLE_REGISTER:
						COMM_PresetMultipleRegisters();
						break;
					case COMM_CMD_GET_SLAVE:
						COMM_GetSlave();
						break;
					case COMM_CMD_GET_SN_VERSION:
						COMM_GetSnVersion();
						break;

					case COMM_CMD_SET_SLAVE_BY_SN:
						COMM_SetSlaveBySN();
						break;
					case COMM_CMD_SET_SLAVE:
						COMM_SetSlave();
						break;
						
					case COMM_CMD_SET_RESET:
						COMM_SetReset();
						break;
					
					case COMM_CMD_FLASH_ENTER:
						COMM_PutStart();
						COMM_PutWord(DEVICE_MODEL);
						COMM_PutWord(0);
						COMM_PutEnd();
						DELAY_Ms(30);
						JUMP_ToIspProgram();
						break;
				}
			}
		}
	}
	if (COMM_Flag==1)
	{
		ISP_RxLength = 0;
		ISP_Count = 0;
		ISP_Flag = 0;
	}	
}

uint16_t CO2_GetValue(void)
{
		uint16_t CO2_Val = 0;
		uint8_t *CO2_Buffer;
		if (CO2_Count >= 10) // 10ms
		{
			CO2_Count=0;
				if(CO2_RxLength>=17)
				{
						CO2_Flag = 1;
						CO2_Buffer = (uint8_t *)CO2_RxBuffer;
				}
				else
				{
						CO2_RxLength=0;
				}
		}
		
		if(CO2_Flag)
		{
				uint8_t co2_flagr = 0;
				for(int i=0;i<5;i++)
				{
						if(CO2_Buffer[10*i+1] == 'Z')
						{
								for(int j=3;j<8;j++)
								{
										if(CO2_Buffer[10*i+j] >= 0x30 && CO2_Buffer[10*i+j] <= 0x39)
										{
												co2_flagr ++;
										}
								}	
						}
						if(co2_flagr ==5)
						{
								CO2_Val = (uint16_t)(CO2_Buffer[10*i+4]-0x30)*1000 + (uint16_t)(CO2_Buffer[10*i+5]-0x30)*100 + (uint16_t)(CO2_Buffer[10*i+6]-0x30)*10 + (uint16_t)(CO2_Buffer[10*i+7]-0x30);
								break;
						}
						else
						{
								co2_flagr = 0;
						}
				}
				CO2_Flag = 0;
				CO2_RxLength=0;
		}
		return CO2_Val;
}

uint16_t RS485_GetValue(uint8_t *RS485_Buffer)
{
		RS485_Count=0;
		for(int i=0; i<RS485_RxLength ; i++)
		{
				RS485_Buffer[i] = RS485_RxBuffer[i];
		}
		

		RS485_RxLength = 0;
		return 1;
}
uint8_t RS485_RxLen(void)
{
		return RS485_RxLength;
}

uint16_t RF_GetValue(uint8_t *RF_Buffer)
{
		RF_Count=0;
		for(int i=0; i<RF_RxLength ; i++)
		{
				RF_Buffer[i] = RF_RxBuffer[i];
		}
		

		RF_RxLength = 0;
		return 1;
}
uint8_t RF_RxLen(void)
{
		return RF_RxLength;
}
