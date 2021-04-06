//-------------------------------------------------------------------
// Serial.cpp
//-------------------------------------------------------------------
#include "Serial.h"

//-------------------------------------------------------------------
HardwareSerial Serial(&huart1);
HardwareSerial Serial1(&huart2);

//-------------------------------------------------------------------
HardwareSerial::HardwareSerial(UART_HandleTypeDef *uart): _uart(uart){}

//-------------------------------------------------------------------
#if defined(HAVE_HWSERIAL0)
void serialEvent()__attribute__((weak));
bool Serial0_available()__attribute__((weak));
#endif 

#if defined(HAVE_HWSERIAL1)
void serialEvent1()__attribute__((weak));
bool Serial1_available()__attribute__((weak));
#endif 

//-------------------------------------------------------------------
void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL0)
	if (Serial0_available && serialEvent && Serial0_available())
	{
		serialEvent();
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (Serial1_available && serialEvent1 && Serial1_available())
	{
		serialEvent1();
	}
#endif 
}

//-------------------------------------------------------------------
// Public Methods
//-------------------------------------------------------------------
void HardwareSerial::begin(unsigned long baud, byte config, bool swap)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	_written = false;

#if defined(HAVE_HWSERIAL0)
	if (_uart->Instance == USART1)
	{
		//UART1
		__HAL_RCC_USART1_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);

		huart1.Instance = USART1;
		huart1.Init.BaudRate = baud;
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		huart1.Init.StopBits = UART_STOPBITS_1;
		huart1.Init.Parity = UART_PARITY_NONE;
		huart1.Init.Mode = UART_MODE_TX_RX;
		huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		if(swap==true)
		{
			huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
			huart1.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;		
		}
		else
		{
			huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		}
		HAL_UART_DeInit(&huart1);
		HAL_UART_Init(&huart1);
		HAL_UART_Receive_IT(&huart1, &_rx_ch, 1);
	}
#endif 

#if defined(HAVE_HWSERIAL1)
	if (_uart->Instance == USART2)
	{
		//UART2
		__HAL_RCC_USART2_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);

		huart2.Instance = USART2;
		huart2.Init.BaudRate = baud;
		huart2.Init.WordLength = UART_WORDLENGTH_8B;
		huart2.Init.StopBits = UART_STOPBITS_1;
		huart2.Init.Parity = UART_PARITY_NONE;
		huart2.Init.Mode = UART_MODE_TX_RX;
		huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		if(swap==true)
		{
			huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
			huart2.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;		
		}
		else
		{
			huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		}
		HAL_UART_DeInit(&huart2);
		HAL_UART_Init(&huart2);
		HAL_UART_Receive_IT(&huart2, &_rx_ch, 1);
	}
#endif 
	_tx_buffer_head = _tx_buffer_tail = 0;
	_rx_buffer_head = _rx_buffer_tail = 0;
}

//-------------------------------------------------------------------
void HardwareSerial::end(void)
{
	// wait for transmission of outgoing data
	flush();

#if defined(HAVE_HWSERIAL0)
	if (_uart->Instance == USART1)
	{
		//UART1
		HAL_UART_AbortReceive_IT(&huart1);
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		HAL_UART_DeInit(&huart1);
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (_uart->Instance == USART2)
	{
		//UART2
		HAL_UART_AbortReceive_IT(&huart2);
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		HAL_UART_DeInit(&huart2);
	}
#endif 
	// clear any received data
	_rx_buffer_head = _rx_buffer_tail = 0;
}

//-------------------------------------------------------------------
int HardwareSerial::available(void)
{
	return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

//-------------------------------------------------------------------
int HardwareSerial::peek(void)
{
	if (_rx_buffer_head == _rx_buffer_tail)
	{
		return  - 1;
	}
	else
	{
		return _rx_buffer[_rx_buffer_tail];
	}
}

//-------------------------------------------------------------------
int HardwareSerial::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer_head == _rx_buffer_tail)
	{
		return  - 1;
	}
	else
	{
		unsigned char c = _rx_buffer[_rx_buffer_tail];
		_rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
		return c;
	}
}

//-------------------------------------------------------------------
int HardwareSerial::availableForWrite(void)
{
	tx_buffer_index_t head = _tx_buffer_head;
	tx_buffer_index_t tail = _tx_buffer_tail;
	if (head >= tail)
	{
		return SERIAL_TX_BUFFER_SIZE - 1-head + tail;
	}
	return tail - head - 1;
}

//-------------------------------------------------------------------
void HardwareSerial::flush(void)
{
	if (!_written)
	{
		return ;
	}
#if defined(HAVE_HWSERIAL0)
	if (_uart->Instance == USART1)
	{
		//UART1
		HAL_UART_AbortTransmit_IT(&huart1);
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (_uart->Instance == USART2)
	{
		//UART2
		HAL_UART_AbortTransmit_IT(&huart2);
	}
#endif 
	_tx_buffer_head = _tx_buffer_tail = 0;
}

//-------------------------------------------------------------------
// Actual interrupt handlers
//-------------------------------------------------------------------
void HardwareSerial::_tx_udr_empty_irq(void)
{
	// If interrupts are enabled, there must be more data in the output
	// buffer. Send the next byte
	_tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;
	if (_tx_buffer_head == _tx_buffer_tail)
	{
		// Buffer empty, so disable interrupts
		_tx_buffer_head = _tx_buffer_tail = 0;
		return ;
	}
	unsigned char c = _tx_buffer[_tx_buffer_tail];

#if defined(HAVE_HWSERIAL0)
	if (_uart->Instance == USART1)
	{
		//UART1
		HAL_UART_Transmit_IT(&huart1, (uint8_t*) &c, 1);
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (_uart->Instance == USART2)
	{
		//UART2
		HAL_UART_Transmit_IT(&huart2, (uint8_t*) &c, 1);
	}
#endif 
}

//-------------------------------------------------------------------
size_t HardwareSerial::write(uint8_t c)
{
	_written = true;
	tx_buffer_index_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
	_tx_buffer[_tx_buffer_head] = c;
	if (_tx_buffer_head == _tx_buffer_tail)
	{
		_tx_buffer_head = i;
#if defined(HAVE_HWSERIAL0)
		if (_uart->Instance == USART1)
		{
			//UART1
			HAL_UART_Transmit_IT(&huart1, (uint8_t*) &c, 1);
		}
#endif 
#if defined(HAVE_HWSERIAL1)
		if (_uart->Instance == USART2)
		{
			//UART2
			HAL_UART_Transmit_IT(&huart2, (uint8_t*) &c, 1);
		}
#endif 
	}
	else
	{
		_tx_buffer_head = i;
	}
	return 1;
}


//-------------------------------------------------------------------
// Actual interrupt handlers
//-------------------------------------------------------------------
void HardwareSerial::_rx_complete_irq(void)
{
	rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
#if defined(HAVE_HWSERIAL0)
	if (_uart->Instance == USART1)
	{
		HAL_UART_Receive_IT(&huart1, &_rx_ch, 1);
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (_uart->Instance == USART2)
	{
		HAL_UART_Receive_IT(&huart2, &_rx_ch, 1);
	}
#endif 

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != _rx_buffer_tail)
	{
		_rx_buffer[_rx_buffer_head] = _rx_ch;
		_rx_buffer_head = i;
	}
}

//-------------------------------------------------------------------
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#if defined(HAVE_HWSERIAL0)
	if (huart->Instance == USART1)
	{
		Serial._tx_udr_empty_irq();
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (huart->Instance == USART2)
	{
		Serial1._tx_udr_empty_irq();
	}
#endif 
}

//-------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if defined(HAVE_HWSERIAL0)
	if (huart->Instance == USART1)
	{
		Serial._rx_complete_irq();
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (huart->Instance == USART2)
	{
		Serial1._rx_complete_irq();
	}
#endif 
}

//-------------------------------------------------------------------
bool Serial0_available(void)
{
	return Serial.available();
}

//-------------------------------------------------------------------
bool Serial1_available(void)
{
	return Serial1.available();
}
