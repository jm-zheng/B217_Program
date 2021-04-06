//-------------------------------------------------------------------
// ht32f5xxxx_uart_it.c
//-------------------------------------------------------------------
#include "ht32.h"
#include "HT32IO.h"

#if !defined(SERIAL_TX_BUFFER_SIZE)
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#define SERIAL_RX_BUFFER_SIZE 64
#endif

extern __IO uint16_t *_rx_buffer_head_u0;
extern __IO uint16_t *_rx_buffer_tail_u0;
extern __IO uint16_t *_tx_buffer_head_u0;
extern __IO uint16_t *_tx_buffer_tail_u0;
extern __IO unsigned char *_rx_buffer_u0;
extern __IO unsigned char *_tx_buffer_u0;

extern __IO uint16_t *_rx_buffer_head_u1;
extern __IO uint16_t *_rx_buffer_tail_u1;
extern __IO uint16_t *_tx_buffer_head_u1;
extern __IO uint16_t *_tx_buffer_tail_u1;
extern __IO unsigned char *_rx_buffer_u1;
extern __IO unsigned char *_tx_buffer_u1;

//-------------------------------------------------------------------
void USART0_IRQHandler(void)
{
  // Rx, move data from UART to buffer
  if(USART_GetFlagStatus(HT_USART0,USART_FLAG_RXDR))
  {
		unsigned char ch=USART_ReceiveData(HT_USART0);
		uint16_t i = (unsigned int)(*_rx_buffer_head_u0 + 1) % SERIAL_RX_BUFFER_SIZE;
		if (i != *_rx_buffer_tail_u0)
		{
			_rx_buffer_u0[*_rx_buffer_head_u0] = ch;
			*_rx_buffer_head_u0 = i;
		}
    USART_ClearFlag(HT_USART0,USART_FLAG_RXDR);
		return;
  }
  // Tx, move data from buffer to UART
  if(USART_GetFlagStatus(HT_USART0,USART_FLAG_TXDE)) 
  {
		unsigned char c = _tx_buffer_u0[*_tx_buffer_tail_u0];
		USART_SendData(HT_USART0, c); 
		*_tx_buffer_tail_u0 = (*_tx_buffer_tail_u0 + 1) % SERIAL_TX_BUFFER_SIZE;
		if (*_tx_buffer_head_u0 == *_tx_buffer_tail_u0)
		{
			// Buffer empty, so disable interrupts
			*_tx_buffer_head_u0 = *_tx_buffer_tail_u0 = 0;
			USART_IntConfig(HT_USART0,USART_INT_TXDE,DISABLE);
		}
  }
}

//-------------------------------------------------------------------
void USART1_IRQHandler(void)
{
  // Rx, move data from UART to buffer
  if(USART_GetFlagStatus(HT_USART1,USART_FLAG_RXDR))
  {
		uint16_t i = (unsigned int)(*_rx_buffer_head_u1 + 1) % SERIAL_RX_BUFFER_SIZE;
		unsigned char ch=USART_ReceiveData(HT_USART1);
		if (i != *_rx_buffer_tail_u1)
		{
			_rx_buffer_u1[*_rx_buffer_head_u1] = ch;
			*_rx_buffer_head_u1 = i;
		}
    USART_ClearFlag(HT_USART1,USART_FLAG_RXDR);
		return;
  }
  // Tx, move data from buffer to UART
  if(USART_GetFlagStatus(HT_USART1,USART_FLAG_TXDE)) 
  {
		unsigned char c = _tx_buffer_u1[*_tx_buffer_tail_u1];
		USART_SendData(HT_USART1, c); 
		*_tx_buffer_tail_u1 = (*_tx_buffer_tail_u1 + 1) % SERIAL_TX_BUFFER_SIZE;
		if (*_tx_buffer_head_u1 == *_tx_buffer_tail_u1)
		{
			// Buffer empty, so disable interrupts
			*_tx_buffer_head_u1 = *_tx_buffer_tail_u1 = 0;
			USART_IntConfig(HT_USART1,USART_INT_TXDE,DISABLE);
			return;
		}
  }
}
