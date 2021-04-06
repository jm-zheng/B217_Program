// -------------------------------------------------------------------
// task.c
// -------------------------------------------------------------------
#include "define.h"

// -------------------------------------------------------------------
// 1ms
// -------------------------------------------------------------------
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
	
	CO2_Count++;
	RF_Count++;
	RS485_Count++;
	ISP_Count++;
	TIMER_Count++;
	if (TIMER_Count >= 10)
	// 10 ms
	{
		TIMER_Count = 0;
		TIMER_MsCount++;
		TIMER_10MsCount++;

		if (BEEP_Delay > 0)
		{
			BEEP_Delay--;
			if (BEEP_Delay == 0)
			{
				BEEP_OFF();
			}
		}
		if (LED_R_Delay > 0)
		{
			LED_R_Delay--;
			if (LED_R_Delay == 0)
			{
				LED_R_OFF();
			}
		}
		if (LED_G_Delay > 0)
		{
			LED_G_Delay--;
			if (LED_G_Delay == 0)
			{
				LED_G_OFF();
			}
		}
	}
}

//-------------------------------------------------------------------
void RTC_IRQHandler(void)
{
	if (__HAL_RTC_ALARM_GET_IT_SOURCE(&hrtc, RTC_IT_ALRA) != RESET)
	{
		if (__HAL_RTC_ALARM_GET_FLAG(&hrtc, RTC_FLAG_ALRAF) != RESET)
		{
			TIMER_SecCount++;
			SC_Sleep_Time_Count++;
			__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc, RTC_FLAG_ALRAF);
		}
	}
	__HAL_RTC_ALARM_EXTI_CLEAR_FLAG();
}


//-------------------------------------------------------------------
void EXTI4_15_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(KEY_MODE_PIN) != RESET)
	{
		TIMER_SleepCount=10;
		__HAL_GPIO_EXTI_CLEAR_IT(KEY_MODE_PIN);
	}
	
	if (__HAL_GPIO_EXTI_GET_IT(KEY_ENTER_PIN) != RESET)
	{
		TIMER_SleepCount=10;
		__HAL_GPIO_EXTI_CLEAR_IT(KEY_ENTER_PIN);
	}
}
