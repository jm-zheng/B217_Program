//-------------------------------------------------------------------
// Nano030.cpp
//-------------------------------------------------------------------

#include "HT32IO.h"

USART_InitTypeDef huart1;
USART_InitTypeDef huart2;

#define PWM_MAX					8
__IO uint8_t pwmcount;
__IO uint8_t pwmtotal;
__IO uint8_t pwmvalue[PWM_MAX];
__IO uint8_t pwmport[PWM_MAX];
__IO uint16_t pwmpin[PWM_MAX];

#define AI_MAX					8
uint8_t aitotal;
__IO uint8_t aicount;
__IO uint8_t aiflag;
uint8_t aipin[AI_MAX];
uint8_t aich[AI_MAX];
__IO uint16_t aivalue[AI_MAX];

#define INT_MAX					8
uint8_t inttotal;
uint8_t intpin[INT_MAX];
uint16_t intgpio[INT_MAX];
void(*intrun[INT_MAX])(void);

vu32 DelayTime;
vu32 TimerMillis;

//-------------------------------------------------------------------
u32 millis(void)
{
	return TimerMillis;
}

//-------------------------------------------------------------------
uint16_t micros(void)
{
	return (TimerMillis*1000);
}

//-------------------------------------------------------------------
void delayMicroseconds(uint16_t us)
{
	u16 i,j;
	for(i=0;i<us;i++)
	{
		for(j=0;j<9;j++)
		{
		}
	}
}

//-------------------------------------------------------------------
void delay(u32 nTime)
{
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

  DelayTime = nTime;

  while(DelayTime != 0);

  SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
}

//-------------------------------------------------------------------
u32 CH0_Frequency;
u32 CH0_DeltaCCR;

//-------------------------------------------------------------------
void SystemClock_Config(void)
{
  TM_TimeBaseInitTypeDef TimeBaseInit;
  TM_OutputInitTypeDef OutInit;
	
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.HTPA=1;
	CKCUClock.Bit.HTPB=1;
	CKCUClock.Bit.HTPC=1;
	CKCUClock.Bit.HTPD=1;
	
  // Enable peripheral clock of AFIO, UART0
  CKCUClock.Bit.AFIO=1;
	CKCUClock.Bit.UART0=1;
	CKCUClock.Bit.USART1=1;
	CKCUClock.Bit.GPTM0=1;
	CKCUClock.Bit.ADC=1;
	CKCUClock.Bit.BKP=1;
	CKCUClock.Bit.EXTI=1;

  SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       // Default : CK_SYS/8
  SYSTICK_SetReloadValue(SystemCoreClock / 8 / 1000); // (CK_SYS/8/1000) = 1ms on chip
  SYSTICK_IntConfig(ENABLE);                          // Enable SYSTICK Interrupt

  CKCU_PeripClockConfig(CKCUClock, ENABLE);

	pwmtotal = 0;
	aitotal = 0;
	inttotal = 0;

	//pwm
  // Time base configuration
  TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
  TimeBaseInit.CounterReload = 65535;
  TimeBaseInit.Prescaler = 1999;
  TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  TM_TimeBaseInit(HT_GPTM0, &TimeBaseInit);

	CH0_Frequency = 10000;//10K
  CH0_DeltaCCR = SystemCoreClock / (CH0_Frequency * (TimeBaseInit.Prescaler + 1));

  // GPTM0 Match Output Toggle Mode configuration: Channel0 ~ 3
  OutInit.OutputMode = TM_OM_MATCH_TOGGLE;
  OutInit.Control = TM_CHCTL_ENABLE;
  OutInit.Polarity = TM_CHP_NONINVERTED;

  OutInit.Channel = TM_CH_0;
  OutInit.Compare = CH0_DeltaCCR;
  TM_OutputInit(HT_GPTM0, &OutInit);

  // Enable GPTM0 channel0 ~ channel3 compare match interrupts 
  TM_IntConfig(HT_GPTM0, TM_INT_CH0CC, ENABLE);
  NVIC_EnableIRQ(GPTM0_IRQn);

  // Enable GPTM
  TM_Cmd(HT_GPTM0, ENABLE);
}

//-------------------------------------------------------------------
void pinMode(uint8_t pin, uint8_t mode)
{
	HT_GPIO_TypeDef *htport;
	u16 gpio_bit;
	gpio_bit = (0x0001 << (pin &0x0F));
	switch (pin &0xF0)
	{
		case PA:
			htport=HT_GPIOA;
			AFIO_GPxConfig(GPIO_PA, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PB:
			htport=HT_GPIOB;
			AFIO_GPxConfig(GPIO_PB, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PC:
			htport=HT_GPIOC;
			AFIO_GPxConfig(GPIO_PC, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PD:
			htport=HT_GPIOD;
			AFIO_GPxConfig(GPIO_PD, gpio_bit, AFIO_FUN_GPIO);
			break;
	}
	switch (mode)
	{
		case INPUT:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			GPIO_PullResistorConfig(htport, gpio_bit,GPIO_PR_DISABLE);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case OUTPUT:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_OUT);
			//GPIO_PullResistorConfig(htport, gpio_bit,GPIO_PR_DISABLE);
			break;
		case INPUT_PULLUP:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			GPIO_PullResistorConfig(htport, gpio_bit,GPIO_PR_UP);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case INPUT_PULLDOWN:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			GPIO_PullResistorConfig(htport, gpio_bit,GPIO_PR_DOWN);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case OUTPUT_OD:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_OUT);
			GPIO_OpenDrainConfig(htport, gpio_bit, ENABLE);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case OUTPUT_OD_PULLUP:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_OUT);
			GPIO_OpenDrainConfig(htport, gpio_bit, ENABLE);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case ANALOG:
			//GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			break;
		case IT_FALLING:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
		case IT_RISING:
			GPIO_DirectionConfig(htport, gpio_bit, GPIO_DIR_IN);
			GPIO_InputConfig(htport, gpio_bit, ENABLE);
			break;
	}
}

//-------------------------------------------------------------------
void digitalWrite(uint8_t pin, uint8_t val)
{
	if (val == HIGH)
	{
		switch (pin &0xF0)
		{
			case PA:
				GPIO_WriteOutBits(HT_GPIOA, (0x0001 << (pin &0x0F)), SET);
				break;
			case PB:
				GPIO_WriteOutBits(HT_GPIOB, (0x0001 << (pin &0x0F)), SET);
				break;
			case PC:
				GPIO_WriteOutBits(HT_GPIOC, (0x0001 << (pin &0x0F)), SET);
				break;
			case PD:
				GPIO_WriteOutBits(HT_GPIOD, (0x0001 << (pin &0x0F)), SET);
				break;
		}
	}
	else
	{
		switch (pin &0xF0)
		{
			case PA:
				GPIO_WriteOutBits(HT_GPIOA, (0x0001 << (pin &0x0F)), RESET);
				break;
			case PB:
				GPIO_WriteOutBits(HT_GPIOB, (0x0001 << (pin &0x0F)), RESET);
				break;
			case PC:
				GPIO_WriteOutBits(HT_GPIOC, (0x0001 << (pin &0x0F)), RESET);
				break;
			case PD:
				GPIO_WriteOutBits(HT_GPIOD, (0x0001 << (pin &0x0F)), RESET);
				break;
		}
	}
}

//-------------------------------------------------------------------
int digitalRead(uint8_t pin)
{
	switch (pin &0xF0)
	{
		case PA:
			if (GPIO_ReadInBit(HT_GPIOA, (0x0001 << (pin &0x0F))) == SET)
			{
				return 1;
			}
			break;
		case PB:
			if (GPIO_ReadInBit(HT_GPIOB, (0x0001 << (pin &0x0F))) == SET)
			{
				return 1;
			}
			break;
		case PC:
			if (GPIO_ReadInBit(HT_GPIOC, (0x0001 << (pin &0x0F))) == SET)
			{
				return 1;
			}
			break;
		case PD:
			if (GPIO_ReadInBit(HT_GPIOD, (0x0001 << (pin &0x0F))) == SET)
			{
				return 1;
			}
			break;
	}
	return 0;
}

//-------------------------------------------------------------------
int analogRead12(uint8_t pin)
{
	uint8_t ch;

	for (ch = 0; ch < aitotal; ch++)
	{
		if (aipin[ch] == pin)
		{
			aicount = ch;
			aiflag = 0;
			switch (pin)
			{
			case PA0:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_0, 0);
				ch = 0;
				break;
			case PA1:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_1, 0);
				ch = 1;
				break;
			case PA2:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_2, 0);
				ch = 2;
				break;
			case PA3:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_3, 0);
				ch = 3;
				break;
			case PA4:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_4, 0);
				ch = 4;
				break;
			case PA5:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_5, 0);
				ch = 5;
				break;
			case PA6:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_6, 0);
				ch = 6;
				break;
			case PA7:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_7, 0);
				ch = 7;
				break;
			case AI_TEMP:
				ch = 16;
				break;
			case AI_VREF:
				ch = 17;
				break;
			}		
			ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
			while (aiflag == 0)
				;
			return aivalue[aicount];
		}
	}

	if (aitotal < AI_MAX)
	{
		if (pin != PA0 && pin != PA1 && pin != PA2 && pin != PA3 && pin != PA4 && pin != PA5 && pin != PA6 && pin != PA7 && pin != PB0 && pin != PB1 && pin != AI_TEMP && pin != AI_VREF && pin != AI_VBAT)
		{
			return 0;
		}
		aipin[aitotal] = pin;
		if (pin != AI_TEMP && pin != AI_VREF && pin != AI_VBAT)
		{
			pinMode(pin, ANALOG);
		}
		switch (pin)
		{
			case PA0:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_0, AFIO_FUN_ADC);
				ch = 0;
				break;
			case PA1:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_FUN_ADC);
				ch = 1;
				break;
			case PA2:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2, AFIO_FUN_ADC);
				ch = 2;
				break;
			case PA3:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3, AFIO_FUN_ADC);
				ch = 3;
				break;
			case PA4:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_4, AFIO_FUN_ADC);
				ch = 4;
				break;
			case PA5:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_5, AFIO_FUN_ADC);
				ch = 5;
				break;
			case PA6:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_6, AFIO_FUN_ADC);
				ch = 6;
				break;
			case PA7:
				AFIO_GPxConfig(GPIO_PA, AFIO_PIN_7, AFIO_FUN_ADC);
				ch = 7;
				break;
			case AI_TEMP:
				ch = 16;
				break;
			case AI_VREF:
				ch = 17;
				break;
		}
		aich[aitotal] = ch;
		if (aitotal == 0)
		{
			CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV3);
	
			//ADC_RegularGroupConfig(HT_ADC, CONTINUOUS_MODE, 1, 1);
			ADC_RegularGroupConfig(HT_ADC, ONE_SHOT_MODE, 1, 0);

			// Use Software Trigger as ADC trigger source
			ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_SOFTWARE);

			ADC_SamplingTimeConfig(HT_ADC, 36);
	
			ADC_IntConfig(HT_ADC, ADC_INT_SINGLE_EOC, ENABLE);
			//ADC_IntConfig(HT_ADC, ADC_INT_CYCLE_EOC, ENABLE);

			ADC_Cmd(HT_ADC, ENABLE);

			NVIC_EnableIRQ(ADC_IRQn);
		}

		aicount = aitotal;
		aitotal++;
		aiflag = 0;
		switch (pin)
		{
			case PA0:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_0, 0);
				ch = 0;
				break;
			case PA1:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_1, 0);
				ch = 1;
				break;
			case PA2:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_2, 0);
				ch = 2;
				break;
			case PA3:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_3, 0);
				ch = 3;
				break;
			case PA4:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_4, 0);
				ch = 4;
				break;
			case PA5:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_5, 0);
				ch = 5;
				break;
			case PA6:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_6, 0);
				ch = 6;
				break;
			case PA7:
				ADC_RegularChannelConfig(HT_ADC, ADC_CH_7, 0);
				ch = 7;
				break;
			case AI_TEMP:
				ch = 16;
				break;
			case AI_VREF:
				ch = 17;
				break;
		}		
		ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
		while (aiflag == 0)
			;
		return aivalue[aicount];
	}
	return 0;
}

//-------------------------------------------------------------------
int analogRead(uint8_t pin)
{
	return (analogRead12(pin) >> 2);
}

//-------------------------------------------------------------------
void analogReference(uint8_t mode)
{
	//
}

//-------------------------------------------------------------------
void analogWrite(uint8_t pin, int val)
{
	uint8_t ch;
	uint8_t pport;
	uint16_t ppin;

	pport = (pin &0xF0);
	ppin = (0x0001 << (pin &0x0F));
	for (ch = 0; ch < pwmtotal; ch++)
	{
		if (pwmport[ch] == pport && pwmpin[ch] == ppin)
		{
			pwmvalue[ch] = val;
			return ;
		}
	}
	if (pwmtotal < PWM_MAX)
	{
		pinMode(pin, OUTPUT);
		pwmport[pwmtotal] = pport;
		pwmpin[pwmtotal] = ppin;
		pwmvalue[pwmtotal] = val;
		pwmtotal++;
	}
}

/*
//-------------------------------------------------------------------
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
	//
	return 0;
}

//-------------------------------------------------------------------
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
	//
	return 0;
}

//-------------------------------------------------------------------
uint8_t shiftIn(uint8_t ulDataPin, uint8_t ulClockPin, uint8_t ulBitOrder)
{
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i)
	{
		digitalWrite(ulClockPin, HIGH);

		if (ulBitOrder == LSBFIRST)
		{
			value |= digitalRead(ulDataPin) << i;
		}
		else
		{
			value |= digitalRead(ulDataPin) << (7-i);
		}

		digitalWrite(ulClockPin, LOW);
	}

	return value;
}

//-------------------------------------------------------------------
void shiftOut(uint8_t ulDataPin, uint8_t ulClockPin, uint8_t ulBitOrder, uint8_t ulVal)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		if (ulBitOrder == LSBFIRST)
		{
			digitalWrite(ulDataPin, !!(ulVal &(1 << i)));
		}
		else
		{
			digitalWrite(ulDataPin, !!(ulVal &(1 << (7-i))));
		}

		digitalWrite(ulClockPin, HIGH);
		digitalWrite(ulClockPin, LOW);
	}
}
*/

//-------------------------------------------------------------------
void attachInterrupt(uint8_t pin, void(*run)(void), int mode)
{
  EXTI_InitTypeDef EXTI_InitStruct = {0};
	uint8_t ch, cpin;
	u16 gpio_bit;
	
	gpio_bit = (0x0001 << (pin &0x0F));
	cpin = (pin &0x0F);
	switch (pin &0xF0)
	{
		case PA:
			AFIO_EXTISourceConfig((AFIO_EXTI_CH_Enum)cpin, (AFIO_ESS_Enum)GPIO_PA);
			AFIO_GPxConfig(GPIO_PA, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PB:
			AFIO_EXTISourceConfig((AFIO_EXTI_CH_Enum)cpin, (AFIO_ESS_Enum)GPIO_PB);
			AFIO_GPxConfig(GPIO_PB, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PC:
			AFIO_EXTISourceConfig((AFIO_EXTI_CH_Enum)cpin, (AFIO_ESS_Enum)GPIO_PC);
			AFIO_GPxConfig(GPIO_PC, gpio_bit, AFIO_FUN_GPIO);
			break;
		case PD:
			AFIO_EXTISourceConfig((AFIO_EXTI_CH_Enum)cpin, (AFIO_ESS_Enum)GPIO_PD);
			AFIO_GPxConfig(GPIO_PD, gpio_bit, AFIO_FUN_GPIO);
			break;
	}
	EXTI_InitStruct.EXTI_Channel = cpin;
	EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
	EXTI_InitStruct.EXTI_DebounceCnt = 0;
	switch (mode)
	{
		case IT_RISING:
			// Configure button EXTI Line on falling edge
			EXTI_InitStruct.EXTI_IntType = EXTI_POSITIVE_EDGE;
			break;
		case IT_FALLING:
			EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
			break;
		case IT_RISING_FALLING:
			EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
			break;
		case IT_RISING_PULLUP:
			pinMode(pin, INPUT_PULLUP);
			EXTI_InitStruct.EXTI_IntType = EXTI_POSITIVE_EDGE;
			break;
		case IT_FALLING_PULLUP:
			pinMode(pin, INPUT_PULLUP);
			EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
			break;
		case IT_RISING_FALLING_PULLUP:
			pinMode(pin, INPUT_PULLUP);
			EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
			break;
		case IT_RISING_PULLDOWN:
			pinMode(pin, INPUT_PULLDOWN);
			EXTI_InitStruct.EXTI_IntType = EXTI_POSITIVE_EDGE;
			break;
		case IT_FALLING_PULLDOWN:
			pinMode(pin, INPUT_PULLDOWN);
			EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
			break;
		case IT_RISING_FALLING_PULLDOWN:
			pinMode(pin, INPUT_PULLDOWN);
			EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
			break;
	}
	EXTI_Init(&EXTI_InitStruct);
	EXTI_IntConfig(cpin, ENABLE);

	for (ch = 0; ch < inttotal; ch++)
	{
		if (intpin[ch] == pin)
		{
			intrun[ch] = run;
			return ;
		}
	}
	if (inttotal < INT_MAX)
	{
		if (cpin <= 1)
		{
			NVIC_SetPriority(EXTI0_1_IRQn, 0x4);
			NVIC_EnableIRQ(EXTI0_1_IRQn);
		}
		else if (cpin >= 4)
		{
			NVIC_SetPriority(EXTI4_15_IRQn, 0x4);
			NVIC_EnableIRQ(EXTI4_15_IRQn);
		}
		else
		{
			NVIC_SetPriority(EXTI2_3_IRQn, 0x4);
			NVIC_EnableIRQ(EXTI2_3_IRQn);
		}
		intpin[inttotal] = pin;
		intgpio[inttotal] = cpin ;
		intrun[inttotal] = run;
		inttotal++;
	}
}

//-------------------------------------------------------------------
void detachInterrupt(uint8_t pin)
{
  EXTI_InitTypeDef EXTI_InitStruct = {0};
	uint8_t ch, cpin;

	cpin = (pin &0x0F);

	EXTI_InitStruct.EXTI_Channel = cpin;
	EXTI_Init(&EXTI_InitStruct);
	EXTI_IntConfig(cpin, DISABLE);

	for (ch = 0; ch < inttotal; ch++)
	{
		if (intpin[ch] == pin)
		{
			return ;
		}
	}
	if (inttotal < INT_MAX)
	{
		cpin = (pin &0x0F);
		if (cpin <= 1)
		{
			NVIC_DisableIRQ(EXTI0_1_IRQn);
		}
		else if (cpin >= 4)
		{
			NVIC_DisableIRQ(EXTI4_15_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(EXTI2_3_IRQn);
		}
		intpin[inttotal] = pin;
		inttotal++;
	}

}


//-------------------------------------------------------------------
void randomSeed( uint32_t dwSeed )
{
  if ( dwSeed != 0 )
  {
    srand( dwSeed ) ;
  }
}

//-------------------------------------------------------------------
long random( long howbig )
{
  if ( howbig == 0 )
  {
    return 0 ;
  }

  return rand() % howbig;
}

//-------------------------------------------------------------------
long random2( long howsmall, long howbig )
{
  if (howsmall >= howbig)
  {
    return howsmall;
  }

  long diff = howbig - howsmall;

  return random(diff) + howsmall;
}

//-------------------------------------------------------------------
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//-------------------------------------------------------------------
uint16_t makeWord( uint8_t h, uint8_t l )
{
  return (h << 8) | l ;
}

/*
//-------------------------------------------------------------------
// return: 0=not find; 1:int/float; 2:string
//-------------------------------------------------------------------
int jsonGet(char *str,char *sname,char *sval)
{
  int i;
	char *pch,ch;
	
  pch=strstr(str,sname);
  if(pch!=NULL)
  {
		pch=strchr(pch,':');
		if(pch!=NULL)
		{
			if(*(pch+1)=='"')
			{
				for(i=0;i<20;i++)
				{
					ch=*(pch+i+2);
					if(ch=='"' || ch=='}' || ch==',')	
					{
						sval[i]=0;
						return 2;
					}
					sval[i]=ch;
				}
			}
			else
			{
				for(i=0;i<10;i++)
				{
					ch=*(pch+i+1);
					if(ch=='}' || ch==',')	
					{
						sval[i]=0;
						return 1;
					}
					sval[i]=ch;
				}
			}
		}
  }
	return 0;	
}	
*/
