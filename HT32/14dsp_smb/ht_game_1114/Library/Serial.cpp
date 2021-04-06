//-------------------------------------------------------------------
// Serial.cpp
//-------------------------------------------------------------------
#include "Serial.h"


//-------------------------------------------------------------------
HardwareSerial Serial(&huart1);
HardwareSerial Serial1(&huart2);
__IO uint16_t *_rx_buffer_head_u0;
__IO uint16_t *_rx_buffer_tail_u0;
__IO uint16_t *_tx_buffer_head_u0;
__IO uint16_t *_tx_buffer_tail_u0;
__IO unsigned char *_rx_buffer_u0;
__IO unsigned char *_tx_buffer_u0;

__IO uint16_t *_rx_buffer_head_u1;
__IO uint16_t *_rx_buffer_tail_u1;
__IO uint16_t *_tx_buffer_head_u1;
__IO uint16_t *_tx_buffer_tail_u1;
__IO unsigned char *_rx_buffer_u1;
__IO unsigned char *_tx_buffer_u1;
//-------------------------------------------------------------------
HardwareSerial::HardwareSerial(USART_InitTypeDef *uart): _uart(uart){}

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
	_written = false;
#if defined(HAVE_HWSERIAL0)
	if (_uart == &huart1)
	{
		_rx_buffer_head_u0=&_rx_buffer_head;
		_rx_buffer_tail_u0=&_rx_buffer_tail;
		_tx_buffer_head_u0=&_tx_buffer_head;
		_tx_buffer_tail_u0=&_tx_buffer_tail;
		_rx_buffer_u0=_rx_buffer;
		_tx_buffer_u0=_tx_buffer;

		// Config AFIO mode as Rx and Tx function.
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2, AFIO_FUN_USART_UART);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3, AFIO_FUN_USART_UART);
		huart1.USART_BaudRate = baud;
		huart1.USART_WordLength = USART_WORDLENGTH_8B;
		huart1.USART_StopBits = USART_STOPBITS_1;
		huart1.USART_Parity = USART_PARITY_NO;
		huart1.USART_Mode = USART_MODE_NORMAL;
		USART_Init(HT_USART0  , &huart1);
		// Seting UART0 interrupt-flag
		USART_IntConfig(HT_USART0, USART_INT_RXDR, ENABLE);
		// Enable UART0
		USART_TxCmd(HT_USART0, ENABLE);
		USART_RxCmd(HT_USART0, ENABLE);
		// Configure USART0 interrupt
		NVIC_EnableIRQ(USART0_IRQn);
	}
#endif 

#if defined(HAVE_HWSERIAL1)
	if (_uart == &huart2)
	{
		_rx_buffer_head_u1=&_rx_buffer_head;
		_rx_buffer_tail_u1=&_rx_buffer_tail;
		_tx_buffer_head_u1=&_tx_buffer_head;
		_tx_buffer_tail_u1=&_tx_buffer_tail;
		_rx_buffer_u1=_rx_buffer;
		_tx_buffer_u1=_tx_buffer;
		
		// Config AFIO mode as Rx and Tx function.
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_4, AFIO_FUN_USART_UART);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_5, AFIO_FUN_USART_UART);
		/*
		huart2.USART_BaudRate = baud;
		huart2.USART_WordLength = USART_WORDLENGTH_8B;
		huart2.USART_StopBits = USART_STOPBITS_1;
		huart2.USART_Parity = USART_PARITY_NO;
		huart2.USART_Mode = USART_MODE_NORMAL;
		USART_Init(HT_USART1  , &huart2);
    */
		huart2.USART_BaudRate = baud;
		huart2.USART_WordLength = USART_WORDLENGTH_7B;
		huart2.USART_StopBits = USART_STOPBITS_1;
		huart2.USART_Parity = USART_PARITY_EVEN;
		huart2.USART_Mode = USART_MODE_NORMAL;
		USART_Init(HT_USART1  , &huart2);
		// Seting USART1 interrupt-flag
		USART_IntConfig(HT_USART1, USART_INT_RXDR, ENABLE);
		// Enable USART1
		USART_TxCmd(HT_USART1, ENABLE);
		USART_RxCmd(HT_USART1, ENABLE);
		// Configure USART1 interrupt
		NVIC_EnableIRQ(USART1_IRQn);
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
	if (_uart == &huart1)
	{
		NVIC_DisableIRQ(USART0_IRQn);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2, AFIO_FUN_GPIO);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3, AFIO_FUN_GPIO);
	}
#endif
#if defined(HAVE_HWSERIAL1)
	if (_uart == &huart2)
	{
		NVIC_DisableIRQ(USART1_IRQn);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_4, AFIO_FUN_GPIO);
		AFIO_GPxConfig(GPIO_PA, AFIO_PIN_5, AFIO_FUN_GPIO);
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
		_rx_buffer_tail = (uint16_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
		return c;
	}
}

//-------------------------------------------------------------------
int HardwareSerial::availableForWrite(void)
{
	uint16_t head = _tx_buffer_head;
	uint16_t tail = _tx_buffer_tail;
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
	if (_uart == &huart1)
	{
		USART_IntConfig(HT_USART0,USART_INT_TXDE,DISABLE);
	}
#endif 
#if defined(HAVE_HWSERIAL1)
	if (_uart == &huart2)
	{
		USART_IntConfig(HT_USART1,USART_INT_TXDE,DISABLE);
	}
#endif 
	_tx_buffer_head = _tx_buffer_tail = 0;
}

//-------------------------------------------------------------------
size_t HardwareSerial::write(uint8_t c)
{
	_written = true;
	uint16_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
	_tx_buffer[_tx_buffer_head] = c;
	if (_tx_buffer_head == _tx_buffer_tail)
	{
		_tx_buffer_head = i;
#if defined(HAVE_HWSERIAL0)
		if (_uart == &huart1)
		{
			USART_IntConfig(HT_USART0, USART_INT_TXDE, ENABLE);			
		}
#endif 
#if defined(HAVE_HWSERIAL1)
		if (_uart == &huart2)
		{
			USART_IntConfig(HT_USART1, USART_INT_TXDE, ENABLE);			
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
bool Serial0_available(void)
{
	return Serial.available();
}

//-------------------------------------------------------------------
bool Serial1_available(void)
{
	return Serial1.available();
}
