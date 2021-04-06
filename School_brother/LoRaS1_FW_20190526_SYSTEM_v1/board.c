// -------------------------------------------------------------------
// board.c
// -------------------------------------------------------------------
#include "define.h"

__IO uint8_t ADC_Count;
__IO uint32_t ADC_VDEC_Total;
__IO uint16_t VDEC_Value;

// -------------------------------------------------------------------
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14
                              |RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);	
}

// -------------------------------------------------------------------
void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();

 /* GPIOA->MODER = 0xFFFFFFFF;
  GPIOB->MODER = 0xFFFFFFFF;
  GPIOC->MODER = 0xFFFFFFFF;
  GPIOF->MODER = 0xFFFFFFFF;*/
	
	// -------------------------------------------------------------------
	// BEEP
	GPIO_InitStruct.Pin = BEEP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStruct);
	BEEP_OFF();

	// LED_R
	GPIO_InitStruct.Pin = LED_R_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);
	LED_R_OFF();

	// LED_G
	GPIO_InitStruct.Pin = LED_G_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);
	LED_G_OFF();
	
	// -------------------------------------------------------------------
	// KEY MODE
	GPIO_InitStruct.Pin = KEY_MODE_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEY_MODE_GPIO_PORT, &GPIO_InitStruct);
	// Enable and set EXTI lines Interrupt to the lowest priority
	HAL_NVIC_SetPriority(KEY_MODE_EXTI_IRQ, 2, 0);
	HAL_NVIC_EnableIRQ(KEY_MODE_EXTI_IRQ);

	// KEY ENTER
	GPIO_InitStruct.Pin = KEY_ENTER_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(KEY_ENTER_GPIO_PORT, &GPIO_InitStruct);

	// -------------------------------------------------------------------
	// EN_E5V
	GPIO_InitStruct.Pin = EN_E5V_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(EN_E5V_GPIO_PORT, &GPIO_InitStruct);
	EN_E5V_OFF();

	// -------------------------------------------------------------------
	// EN_E12V
	GPIO_InitStruct.Pin = EN_E12V_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(EN_E12V_GPIO_PORT, &GPIO_InitStruct);
	EN_E12V_OFF();

	// -------------------------------------------------------------------
	// EN_R5V
	GPIO_InitStruct.Pin = EN_R5V_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(EN_R5V_GPIO_PORT, &GPIO_InitStruct);
	EN_R5V_OFF();

	// -------------------------------------------------------------------
	// EN_R12V
	GPIO_InitStruct.Pin = EN_R12V_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(EN_R12V_GPIO_PORT, &GPIO_InitStruct);
	EN_R12V_OFF();


	// -------------------------------------------------------------------
	// EN_RF
	GPIO_InitStruct.Pin = EN_RF_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(EN_RF_GPIO_PORT, &GPIO_InitStruct);
	EN_RF_OFF();
	
	// RF_M0
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(RF_M0_GPIO_PORT, &GPIO_InitStruct);
	RF_M0_LO();
	
	// RF_M1
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(RF_M1_GPIO_PORT, &GPIO_InitStruct);
	RF_M1_LO();
	
	// RF_AUX
	GPIO_InitStruct.Pin = RF_AUX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(RF_AUX_GPIO_PORT, &GPIO_InitStruct);
	RF_AUX_LO();

	// -------------------------------------------------------------------
	// VDEC
  GPIO_InitStruct.Pin = VDEC_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VDEC_GPIO_PORT, &GPIO_InitStruct);

	// AIN_1
  GPIO_InitStruct.Pin = AIN_1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AIN_1_GPIO_PORT, &GPIO_InitStruct);

	// AIN_2
  GPIO_InitStruct.Pin = AIN_2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AIN_2_GPIO_PORT, &GPIO_InitStruct);
	
		// RS485_Select
	GPIO_InitStruct.Pin = RS485_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(RS485_GPIO_PORT, &GPIO_InitStruct);
	RS485_RX();
}

static TIM_HandleTypeDef  htim;
// -------------------------------------------------------------------
void ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	__HAL_RCC_TIM1_CLK_ENABLE();		
  // Time Base configuration = 5ms
  htim.Instance = TIM1;
  htim.Init.Period            = 2400;
  htim.Init.Prescaler         = 100;
  htim.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim.Init.RepetitionCounter = 0x0;
  HAL_TIM_Base_Init(&htim);

  // Timer TRGO selection 
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig);

	
	__HAL_RCC_ADC1_CLK_ENABLE();
  hadc.Instance = ADC1;  
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait      = DISABLE;
  hadc.Init.LowPowerAutoPowerOff  = DISABLE;
  hadc.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  hadc.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_TRGO;       /* Conversion start trigged at each external event */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
	
	HAL_ADC_Init(&hadc);
  HAL_ADCEx_Calibration_Start(&hadc);

	sConfig.Channel = VDEC_ADC_CHANNEL;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);	

  HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);

	ADC_Count=0;
	ADC_VDEC_Total=0;
	VDEC_Value=50;
	ADC_Status=1;
	ADC1->CHSELR=1<<VDEC_ADC_CHANNEL;
	HAL_ADC_Start_IT(&hadc);
  HAL_TIM_Base_Start(&htim);	
}

// -------------------------------------------------------------------
void ADC1_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc);
}

// -------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
  ADC_VDEC_Total+= HAL_ADC_GetValue(AdcHandle);
	ADC_Count++;
	if(ADC_Count>=11)
	{
		VDEC_Value=(ADC_VDEC_Total>>9);
		ADC_VDEC_Total=0;
		ADC_Count=0;
	}
}

// -------------------------------------------------------------------
void IWDG_Init(void)
{
	#ifdef WATCHDOG_ENABLE
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	//hiwdg.Init.Reload = (LSE_VALUE / 8); // 1.6 Sec;
	hiwdg.Init.Reload = (LSE_VALUE / 16); // 1.6 Sec;
	//hiwdg.Init.Reload = (LSE_VALUE / 32); // 0.8 Sec;
	hiwdg.Init.Window = IWDG_WINDOW_DISABLE;
	HAL_IWDG_Init(&hiwdg);
	//HAL_IWDG_Start(&hiwdg);
	#endif 
}

//------------------------------------------------------------------
void IWDG_Reset(void)
{
	#ifdef WATCHDOG_ENABLE
		HAL_IWDG_Refresh(&hiwdg);
	#endif 
}


//------------------------------------------------------------------
void RTC_Init(void)
{
  RTC_DateTypeDef  sdatestructure;
  RTC_TimeTypeDef  stimestructure;
  RTC_AlarmTypeDef salarmstructure;
 	
  __HAL_RCC_PWR_CLK_ENABLE();
  //HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_RTC_ENABLE();
	
	HAL_NVIC_SetPriority(RTC_IRQn, TICK_INT_PRIORITY, 0);
  HAL_NVIC_EnableIRQ(RTC_IRQn);	
	
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	hrtc.Instance = RTC;
	HAL_RTC_Init(&hrtc);
	
	// Disable Calibration 
	//HAL_RTCEx_DeactivateCalibrationOutPut(&hrtc);
	
	// Enable Calibration => PC13
	//HAL_RTCEx_SetCalibrationOutPut(&RTC_Handle, RTC_CALIBOUTPUT_512HZ);

  sdatestructure.Year = 17;
  sdatestructure.Month = RTC_MONTH_JANUARY;
  sdatestructure.Date = 1;
  sdatestructure.WeekDay = RTC_WEEKDAY_SUNDAY;
  HAL_RTC_SetDate(&hrtc,&sdatestructure,FORMAT_BIN);
	
  stimestructure.Hours = 0;
  stimestructure.Minutes = 0;
  stimestructure.Seconds = 0;
  stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
  HAL_RTC_SetTime(&hrtc,&stimestructure,FORMAT_BIN);
  
  salarmstructure.Alarm = RTC_ALARM_A;
  salarmstructure.AlarmMask = RTC_ALARMMASK_ALL;
  //salarmstructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_5;// 125 ms
  //salarmstructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_6;// 250 ms
  //salarmstructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_7;// 500 ms
  salarmstructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_8;// 1Sec
  salarmstructure.AlarmTime.SubSeconds = 0xFF;
  HAL_RTC_SetAlarm_IT(&hrtc,&salarmstructure,FORMAT_BIN);  
	
	__HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_ALRA);
}

//-------------------------------------------------------------------
void STOP_Mode(void)
{
	if(ADC_Status>0)
	{
		ADC_Status=0;
		HAL_ADC_DeInit(&hadc);
	}
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  IWDG_Reset();
}

//-------------------------------------------------------------------
typedef void(*pFunction)(void);

#define ApplicationAddress    FLASH_ISP_START_ADDR // Firmware Upgrade Address
pFunction Jump_To_Application;
uint32_t JumpAddress;

//-------------------------------------------------------------------
void JUMP_ToIspProgram(void)
{
	__disable_irq();
	// Jump to user application 
	JumpAddress = *(__IO uint32_t*)(ApplicationAddress + 4);
	Jump_To_Application = (pFunction)JumpAddress;
	// Initialize user application's Stack Pointer 
	__set_MSP(*(__IO uint32_t*)ApplicationAddress);
	Jump_To_Application();
}

// -------------------------------------------------------------------
// wait us
// -------------------------------------------------------------------
void DELAY_Us(uint16_t us)
{
	uint16_t i;

	for (i = 0; i < us; i++)
	{
		__NOP();
		__NOP();
	}
}

// -------------------------------------------------------------------
void BEEP_On(uint8_t delay)
{
	BEEP_ON();
	BEEP_Delay = delay;
}

// -------------------------------------------------------------------
void LED_R_On(uint8_t delay)
{
	LED_R_ON();
	LED_R_Delay = delay;
}

// -------------------------------------------------------------------
void LED_G_On(uint8_t delay)
{
	LED_G_ON();
	LED_G_Delay = delay;
}

// -------------------------------------------------------------------
void BEEP_Ok(void)	
{
	BEEP_On(50);
	LED_G_On(50);
}

// -------------------------------------------------------------------
void BEEP_Key(void)	
{
	BEEP_On(20);
	LED_G_On(20);
}
