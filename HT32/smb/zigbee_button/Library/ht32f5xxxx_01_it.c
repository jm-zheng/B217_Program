//-------------------------------------------------------------------
// ht32f5xxxx_01_it.c
//-------------------------------------------------------------------
#include "ht32.h"
#include "HT32IO.h"

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

//-------------------------------------------------------------------
extern vu32 DelayTime;
extern vu32 TimerMillis;

//-------------------------------------------------------------------
// 1ms
//-------------------------------------------------------------------
void SysTick_Handler(void)
{	
  if(DelayTime != 0)
  {
    DelayTime--;
  }
	TimerMillis++;
}

//-------------------------------------------------------------------
extern u32 CH0_DeltaCCR;
extern __IO uint8_t pwmcount;
extern __IO uint8_t pwmtotal;
extern __IO uint8_t pwmvalue[];
extern __IO uint8_t pwmport[];
extern __IO uint16_t pwmpin[];

//-------------------------------------------------------------------
void GPTM0_IRQHandler(void)
{
  if (TM_GetIntStatus(HT_GPTM0, TM_INT_CH0CC) != RESET)
  {
		//10K
		pwmcount++;
		for (uint8_t pwmch = 0; pwmch < pwmtotal; pwmch++)
		{
			if (pwmcount >= pwmvalue[pwmch])
			{
				switch (pwmport[pwmch])
				{
					case PA:
						GPIO_WriteOutBits(HT_GPIOA, pwmpin[pwmch], RESET);
						break;
					case PB:
						GPIO_WriteOutBits(HT_GPIOB, pwmpin[pwmch], RESET);
						break;
					case PC:
						GPIO_WriteOutBits(HT_GPIOC, pwmpin[pwmch], RESET);
						break;
					case PD:
						GPIO_WriteOutBits(HT_GPIOD, pwmpin[pwmch], RESET);
						break;
				}
			}
			else
			{
				switch (pwmport[pwmch])
				{
					case PA:
						GPIO_WriteOutBits(HT_GPIOA, pwmpin[pwmch], SET);
						break;
					case PB:
						GPIO_WriteOutBits(HT_GPIOB, pwmpin[pwmch], SET);
						break;
					case PC:
						GPIO_WriteOutBits(HT_GPIOC, pwmpin[pwmch], SET);
						break;
					case PD:
						GPIO_WriteOutBits(HT_GPIOD, pwmpin[pwmch], SET);
						break;
				}
			}
		}		
    TM_ClearIntPendingBit(HT_GPTM0, TM_INT_CH0CC);
    TM_SetCaptureCompare0(HT_GPTM0, TM_GetCaptureCompare0(HT_GPTM0) + CH0_DeltaCCR);
  }	
}
//-------------------------------------------------------------------

extern __IO uint8_t aicount;
extern __IO uint8_t aiflag;
extern __IO uint16_t aivalue[];
//-------------------------------------------------------------------
void ADC_IRQHandler(void)
{
  ADC_ClearIntPendingBit(HT_ADC, ADC_FLAG_SINGLE_EOC);
  aivalue[aicount] = (HT_ADC->DR[0]&0x0FFF);
	aiflag = 1;
}

//-------------------------------------------------------------------

extern uint8_t inttotal;
extern uint8_t intpin[];
extern uint16_t intgpio[];
extern void(*intrun[])(void);
//-------------------------------------------------------------------
void EXTIO_IRQHandler(void)
{
	uint8_t i;
	
	for(i=0;i<inttotal;i++)
	{
		if (EXTI_GetEdgeFlag(intgpio[i]))
		{
			intrun[i]();
			EXTI_ClearEdgeFlag(intgpio[i]);
			return;
		}
	}
}

//-------------------------------------------------------------------
void EXTI0_1_IRQHandler(void)
{
	EXTIO_IRQHandler();
}

//-------------------------------------------------------------------
void EXTI2_3_IRQHandler(void)
{
	EXTIO_IRQHandler();
}

//-------------------------------------------------------------------
void EXTI4_15_IRQHandler(void)
{
	EXTIO_IRQHandler();
}
