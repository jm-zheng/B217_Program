//-------------------------------------------------------------------
// Nano030.cpp
//-------------------------------------------------------------------
#include "Nano030.h"

ADC_HandleTypeDef hadc;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim16;

#define PWM_MAX					8
__IO uint8_t pwmcount;
__IO uint8_t pwmtotal;
__IO uint8_t pwmvalue[PWM_MAX];
__IO uint8_t pwmport[PWM_MAX];
__IO uint16_t pwmpin[PWM_MAX];

#define AI_MAX			8
uint8_t aitotal;
__IO uint8_t aicount;
__IO uint8_t aiflag;
uint8_t aipin[AI_MAX];
uint8_t aich[AI_MAX];
__IO uint16_t aivalue[AI_MAX];

#define INT_MAX			8
uint8_t inttotal;
uint8_t intpin[INT_MAX];
uint16_t intgpio[INT_MAX];
void(*intrun[INT_MAX])(void);

//-------------------------------------------------------------------
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	#if (PREFETCH_ENABLE != 0)
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
	#endif 
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_HSI;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

	// GPIO Ports Clock Enable 
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	pwmtotal = 0;
	aitotal = 0;
	inttotal = 0;
	
	huart1.Instance = USART1;
	huart2.Instance = USART2;
	
	//pwm
	__HAL_RCC_TIM6_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM6_IRQn);
	//TIM6
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 0;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	//htim6.Init.Period = (SystemCoreClock / 127500) - 1; // PWM 500Hz
	htim6.Init.Period = (SystemCoreClock / 25500) - 1; // PWM 100Hz	
	htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim6.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);

	//micros
	__HAL_RCC_TIM14_CLK_ENABLE();
	htim14.Instance = TIM14;
	htim14.Init.Prescaler = 48-1;
	htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim14.Init.Period = 65535;
	htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim14.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim14);
	__HAL_TIM_SetCounter(&htim14, 0);
	__HAL_TIM_ENABLE(&htim14);

	//delayMicroseconds
	__HAL_RCC_TIM16_CLK_ENABLE();
	htim16.Instance = TIM16;
	htim16.Init.Prescaler = 48-1;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = 65535;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim16);
}

//-------------------------------------------------------------------
void pinMode(uint8_t pin, uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	switch (mode)
	{
		case INPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case OUTPUT:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case INPUT_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case INPUT_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;
		case OUTPUT_OD:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case OUTPUT_OD_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case ANALOG:
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case IT_FALLING:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case IT_RISING:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
	}
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = (0x0001 << (pin &0x0F));
	switch (pin &0xF0)
	{
		case PA:
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			break;
		case PB:
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			break;
		case PC:
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
			break;
		case PD:
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
			break;
		case PF:
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
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
				HAL_GPIO_WritePin(GPIOA, (0x0001 << (pin &0x0F)), GPIO_PIN_SET);
				break;
			case PB:
				HAL_GPIO_WritePin(GPIOB, (0x0001 << (pin &0x0F)), GPIO_PIN_SET);
				break;
			case PC:
				HAL_GPIO_WritePin(GPIOC, (0x0001 << (pin &0x0F)), GPIO_PIN_SET);
				break;
			case PD:
				HAL_GPIO_WritePin(GPIOD, (0x0001 << (pin &0x0F)), GPIO_PIN_SET);
				break;
			case PF:
				HAL_GPIO_WritePin(GPIOF, (0x0001 << (pin &0x0F)), GPIO_PIN_SET);
				break;
		}
	}
	else
	{
		switch (pin &0xF0)
		{
			case PA:
				HAL_GPIO_WritePin(GPIOA, (0x0001 << (pin &0x0F)), GPIO_PIN_RESET);
				break;
			case PB:
				HAL_GPIO_WritePin(GPIOB, (0x0001 << (pin &0x0F)), GPIO_PIN_RESET);
				break;
			case PC:
				HAL_GPIO_WritePin(GPIOC, (0x0001 << (pin &0x0F)), GPIO_PIN_RESET);
				break;
			case PD:
				HAL_GPIO_WritePin(GPIOD, (0x0001 << (pin &0x0F)), GPIO_PIN_RESET);
				break;
			case PF:
				HAL_GPIO_WritePin(GPIOF, (0x0001 << (pin &0x0F)), GPIO_PIN_RESET);
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
			if (HAL_GPIO_ReadPin(GPIOA, (0x0001 << (pin &0x0F))) == GPIO_PIN_SET)
			{
				return 1;
			}
			break;
		case PB:
			if (HAL_GPIO_ReadPin(GPIOB, (0x0001 << (pin &0x0F))) == GPIO_PIN_SET)
			{
				return 1;
			}
			break;
		case PC:
			if (HAL_GPIO_ReadPin(GPIOC, (0x0001 << (pin &0x0F))) == GPIO_PIN_SET)
			{
				return 1;
			}
			break;
		case PD:
			if (HAL_GPIO_ReadPin(GPIOD, (0x0001 << (pin &0x0F))) == GPIO_PIN_SET)
			{
				return 1;
			}
			break;
		case PF:
			if (HAL_GPIO_ReadPin(GPIOF, (0x0001 << (pin &0x0F))) == GPIO_PIN_SET)
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
	ADC_ChannelConfTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	for (ch = 0; ch < aitotal; ch++)
	{
		if (aipin[ch] == pin)
		{
			aicount = ch;
			ADC1->CHSELR = 1 << (aich[aicount]);
			aiflag = 0;
			HAL_ADC_Start_IT(&hadc);
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
		if (aitotal == 0)
		{
			__HAL_RCC_TIM1_CLK_ENABLE();
			htim1.Instance = TIM1;
			htim1.Init.Prescaler = 0;
			//htim1.Init.Period = (SystemCoreClock / 1000000) - 1; // 1us
			htim1.Init.Period = (SystemCoreClock / 100000) - 1; // 10us
			//htim1.Init.Period = (SystemCoreClock / 10000) - 1; // 100us
			//htim1.Init.Period = (SystemCoreClock / 1000) - 1; // 1ms
			htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim1.Init.RepetitionCounter = 0x0;
			HAL_TIM_Base_Init(&htim1);
			HAL_TIM_Base_Start(&htim1);

			// Timer TRGO selection 
			sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
			sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
			HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

			__HAL_RCC_ADC1_CLK_ENABLE();
			hadc.Instance = ADC1;
			hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
			hadc.Init.Resolution = ADC_RESOLUTION_12B;
			hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
			hadc.Init.ScanConvMode = DISABLE;
			hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
			hadc.Init.LowPowerAutoWait = DISABLE;
			hadc.Init.LowPowerAutoPowerOff = DISABLE;
			hadc.Init.ContinuousConvMode = DISABLE;
			hadc.Init.DiscontinuousConvMode = DISABLE;
			hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_TRGO; /* Conversion start trigged at each external event */
			hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
			hadc.Init.DMAContinuousRequests = ENABLE;
			hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

			HAL_ADC_Init(&hadc);
			HAL_ADCEx_Calibration_Start(&hadc);
		}
		aipin[aitotal] = pin;
		if (pin != AI_TEMP && pin != AI_VREF && pin != AI_VBAT)
		{
			pinMode(pin, ANALOG);
		}
		switch (pin)
		{
			case PA0:
				sConfig.Channel = ADC_CHANNEL_0;
				ch = 0;
				break;
			case PA1:
				sConfig.Channel = ADC_CHANNEL_1;
				ch = 1;
				break;
			case PA2:
				sConfig.Channel = ADC_CHANNEL_2;
				ch = 2;
				break;
			case PA3:
				sConfig.Channel = ADC_CHANNEL_3;
				ch = 3;
				break;
			case PA4:
				sConfig.Channel = ADC_CHANNEL_4;
				ch = 4;
				break;
			case PA5:
				sConfig.Channel = ADC_CHANNEL_5;
				ch = 5;
				break;
			case PA6:
				sConfig.Channel = ADC_CHANNEL_6;
				ch = 6;
				break;
			case PA7:
				sConfig.Channel = ADC_CHANNEL_7;
				ch = 7;
				break;
			case PB0:
				sConfig.Channel = ADC_CHANNEL_8;
				ch = 8;
				break;
			case PB1:
				sConfig.Channel = ADC_CHANNEL_9;
				ch = 9;
				break;
			case AI_TEMP:
				sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
				ch = 16;
				break;
			case AI_VREF:
				sConfig.Channel = ADC_CHANNEL_VREFINT;
				ch = 17;
				break;
		}
		aich[aitotal] = ch;
		sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
		sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
		HAL_ADC_ConfigChannel(&hadc, &sConfig);

		HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(ADC1_IRQn);

		aicount = aitotal;
		ADC1->CHSELR = 1 << (aich[aicount]);
		aitotal++;
		aiflag = 0;
		HAL_ADC_Start_IT(&hadc);
		while (aiflag == 0)
			;
		return aivalue[aicount];
	}
	return 0;
}

// -------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
	aivalue[aicount] = HAL_ADC_GetValue(AdcHandle);
	HAL_ADC_Stop_IT(&hadc);
	aiflag = 1;
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

//-------------------------------------------------------------------
void attachInterrupt(uint8_t pin, void(*run)(void), int mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	uint8_t ch, cpin;

	switch (mode)
	{
		case IT_RISING:
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case IT_FALLING:
			GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case IT_RISING_FALLING:
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case IT_RISING_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case IT_FALLING_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case IT_RISING_FALLING_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case IT_RISING_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;
		case IT_FALLING_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;
		case IT_RISING_FALLING_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
	}
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = (0x0001 << (pin &0x0F));
	switch (pin &0xF0)
	{
		case PA:
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			break;
		case PB:
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			break;
		case PC:
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
			break;
		case PD:
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
			break;
		case PF:
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
			break;
	}

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
		cpin = (pin &0x0F);
		if (cpin <= 1)
		{
			HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
			HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
		}
		else if (cpin >= 4)
		{
			HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
			HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
		}
		else
		{
			HAL_NVIC_SetPriority(EXTI2_3_IRQn, 2, 0);
			HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
		}
		intpin[inttotal] = pin;
		intgpio[inttotal] = GPIO_InitStruct.Pin ;
		intrun[inttotal] = run;
		inttotal++;
	}
}

//-------------------------------------------------------------------
void detachInterrupt(uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	uint8_t ch, cpin;

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = (0x0001 << (pin &0x0F));
	switch (pin &0xF0)
	{
		case PA:
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			break;
		case PB:
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			break;
		case PC:
			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
			break;
		case PD:
			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
			break;
		case PF:
			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
			break;
	}

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
			HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
		}
		else if (cpin >= 4)
		{
			HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);
		}
		else
		{
			HAL_NVIC_DisableIRQ(EXTI2_3_IRQn);
		}
		intpin[inttotal] = pin;
		inttotal++;
	}

}

//-------------------------------------------------------------------
// delay us
//-------------------------------------------------------------------
void delayMicroseconds(uint16_t us)
{
	__HAL_TIM_SetCounter(&htim16, 0);
	__HAL_TIM_ENABLE(&htim16);
	while (__HAL_TIM_GetCounter(&htim16) < us)
		;
	__HAL_TIM_DISABLE(&htim16);
}

//-------------------------------------------------------------------
uint16_t micros(void)
{
	return __HAL_TIM_GetCounter(&htim14);
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

//-------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//AO->PWM
	if (htim->Instance == htim6.Instance)
	{
		pwmcount++;
		for (uint8_t pwmch = 0; pwmch < pwmtotal; pwmch++)
		{
			if (pwmcount >= pwmvalue[pwmch])
			{
				switch (pwmport[pwmch])
				{
					case PA:
						HAL_GPIO_WritePin(GPIOA, pwmpin[pwmch], GPIO_PIN_RESET);
						break;
					case PB:
						HAL_GPIO_WritePin(GPIOB, pwmpin[pwmch], GPIO_PIN_RESET);
						break;
					case PC:
						HAL_GPIO_WritePin(GPIOC, pwmpin[pwmch], GPIO_PIN_RESET);
						break;
					case PD:
						HAL_GPIO_WritePin(GPIOD, pwmpin[pwmch], GPIO_PIN_RESET);
						break;
					case PF:
						HAL_GPIO_WritePin(GPIOF, pwmpin[pwmch], GPIO_PIN_RESET);
						break;
				}
			}
			else
			{
				switch (pwmport[pwmch])
				{
					case PA:
						HAL_GPIO_WritePin(GPIOA, pwmpin[pwmch], GPIO_PIN_SET);
						break;
					case PB:
						HAL_GPIO_WritePin(GPIOB, pwmpin[pwmch], GPIO_PIN_SET);
						break;
					case PC:
						HAL_GPIO_WritePin(GPIOC, pwmpin[pwmch], GPIO_PIN_SET);
						break;
					case PD:
						HAL_GPIO_WritePin(GPIOD, pwmpin[pwmch], GPIO_PIN_SET);
						break;
					case PF:
						HAL_GPIO_WritePin(GPIOF, pwmpin[pwmch], GPIO_PIN_SET);
						break;
				}
			}
		}
	}
}

//-------------------------------------------------------------------
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint8_t i;
	for(i=0;i<inttotal;i++)
	{
		if (GPIO_Pin == intgpio[i])
		{
			intrun[i]();			
		}
	}
}
