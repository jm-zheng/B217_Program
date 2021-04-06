//-------------------------------------------------------------------
// Irq.cpp
//-------------------------------------------------------------------
#include "Nano030.h"

//-------------------------------------------------------------------
void NMI_Handler(void)
{
	//
}

//-------------------------------------------------------------------
void HardFault_Handler(void)
{
  while (1)
  {
		//
  }
}

//-------------------------------------------------------------------
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

//-------------------------------------------------------------------
// 1us
//-------------------------------------------------------------------
void TIM6_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
}

//-------------------------------------------------------------------
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}

//-------------------------------------------------------------------
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart2);
}

//-------------------------------------------------------------------
void ADC1_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc);
}

//-------------------------------------------------------------------
void EXTI0_1_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(K1_PIN) != RESET) 
  { 
		HAL_GPIO_EXTI_IRQHandler(K1_PIN);
	}
  if(__HAL_GPIO_EXTI_GET_IT(K2_PIN) != RESET) 
  {
		HAL_GPIO_EXTI_IRQHandler(K2_PIN);
	}
}

//-------------------------------------------------------------------
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	//
}
#endif
