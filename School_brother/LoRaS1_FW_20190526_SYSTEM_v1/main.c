//-------------------------------------------------------------------
// main.c
//-------------------------------------------------------------------
#include "define.h"
#include "M200_1.h"
#include "M200_2.h"
#include "M650.h"
//-------------------------------------------------------------------
RTC_HandleTypeDef hrtc;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
IWDG_HandleTypeDef hiwdg;
ADC_HandleTypeDef hadc;

// -------------------------------------------------------------------
__IO uint8_t TIMER_Count;
__IO uint8_t TIMER_MsCount;
__IO uint8_t TIMER_10MsCount;
__IO uint8_t TIMER_SecCount;
uint8_t TIMER_SleepCount;

__IO uint8_t BEEP_Delay;
__IO uint8_t LED_R_Delay;
__IO uint8_t LED_G_Delay;
__IO uint8_t LED_Y_Delay;

uint32_t DEVICE_Sn;
uint8_t DEVICE_ResetFlag;

uint8_t KEY_MODE_Tag;
uint8_t KEY_ENTER_Tag;

#define SENSORS_ADDR												'1'

uint16_t SC_Sleep_Time;
uint16_t SC_Sleep_Time_Count;
uint8_t SC_Move_Flag;

uint8_t POWER_Flag;
uint8_t ADC_Status;
uint16_t AIR_Temp, AIR_Humi;
uint16_t GND_Temp, GND_Humi;
uint32_t AIR_Lux;
uint16_t AIR_CO2;
uint16_t GND_EC;
uint16_t GND_PH;
double do_value, ec_value ,ph_value ,temp_value;
uint16_t Water_do,Water_ec,Water_ph,Water_temp;


uint8_t RF_TX_Flag = 0;

#define Zigbee_Number_ADDR                        0

#define Zigbee_Number_AIR_TEMP                        1
#define Zigbee_Number_AIR_TEMP_HUNDREDS                        Zigbee_Number_AIR_TEMP + 1
#define Zigbee_Number_AIR_TEMP_TENS                        Zigbee_Number_AIR_TEMP + 2
#define Zigbee_Number_AIR_TEMP_UNITS                        Zigbee_Number_AIR_TEMP + 3
#define Zigbee_Number_AIR_TEMP_ONES                        Zigbee_Number_AIR_TEMP + 4
#define Zigbee_Number_AIR_TEMP_TENTHS                        Zigbee_Number_AIR_TEMP + 5

#define Zigbee_Number_GND_TEMP                        7
#define Zigbee_Number_GND_TEMP_HUNDREDS                        Zigbee_Number_GND_TEMP + 1
#define Zigbee_Number_GND_TEMP_TENS                        Zigbee_Number_GND_TEMP + 2
#define Zigbee_Number_GND_TEMP_UNITS                        Zigbee_Number_GND_TEMP + 3
#define Zigbee_Number_GND_TEMP_ONES                        Zigbee_Number_GND_TEMP + 4
#define Zigbee_Number_GND_TEMP_TENTHS                        Zigbee_Number_GND_TEMP + 5

#define Zigbee_Number_AIR_HUMI                        13
#define Zigbee_Number_AIR_HUMI_HUNDREDS                        Zigbee_Number_AIR_HUMI + 1
#define Zigbee_Number_AIR_HUMI_TENS                        Zigbee_Number_AIR_HUMI + 2
#define Zigbee_Number_AIR_HUMI_UNITS                        Zigbee_Number_AIR_HUMI + 3
#define Zigbee_Number_AIR_HUMI_ONES                        Zigbee_Number_AIR_HUMI + 4
#define Zigbee_Number_AIR_HUMI_TENTHS                        Zigbee_Number_AIR_HUMI + 5

#define Zigbee_Number_GND_HUMI                        19
#define Zigbee_Number_GND_HUMI_HUNDREDS                        Zigbee_Number_GND_HUMI + 1
#define Zigbee_Number_GND_HUMI_TENS                        Zigbee_Number_GND_HUMI + 2
#define Zigbee_Number_GND_HUMI_UNITS                        Zigbee_Number_GND_HUMI + 3
#define Zigbee_Number_GND_HUMI_ONES                        Zigbee_Number_GND_HUMI + 4
#define Zigbee_Number_GND_HUMI_TENTHS                        Zigbee_Number_GND_HUMI + 5

#define Zigbee_Number_AIR_LIGHT                        25
#define Zigbee_Number_AIR_LIGHT_HUNDREDS                        Zigbee_Number_AIR_LIGHT + 1
#define Zigbee_Number_AIR_LIGHT_TENS                        Zigbee_Number_AIR_LIGHT + 2
#define Zigbee_Number_AIR_LIGHT_UNITS                        Zigbee_Number_AIR_LIGHT + 3
#define Zigbee_Number_AIR_LIGHT_ONES                        Zigbee_Number_AIR_LIGHT + 4
#define Zigbee_Number_AIR_LIGHT_TENTHS                        Zigbee_Number_AIR_LIGHT + 5

#define Zigbee_Number_AIR_CO2                        31
#define Zigbee_Number_AIR_CO2_HUNDREDS                        Zigbee_Number_AIR_CO2 + 1
#define Zigbee_Number_AIR_CO2_TENS                        Zigbee_Number_AIR_CO2 + 2
#define Zigbee_Number_AIR_CO2_UNITS                        Zigbee_Number_AIR_CO2 + 3
#define Zigbee_Number_AIR_CO2_ONES                        Zigbee_Number_AIR_CO2 + 4
#define Zigbee_Number_AIR_CO2_TENTHS                        Zigbee_Number_AIR_CO2 + 5

#define Zigbee_Number_GND_EC                        37
#define Zigbee_Number_GND_EC_HUNDREDS                        Zigbee_Number_GND_EC + 1
#define Zigbee_Number_GND_EC_TENS                        Zigbee_Number_GND_EC + 2
#define Zigbee_Number_GND_EC_UNITS                        Zigbee_Number_GND_EC + 3
#define Zigbee_Number_GND_EC_ONES                        Zigbee_Number_GND_EC + 4
#define Zigbee_Number_GND_EC_TENTHS                        Zigbee_Number_GND_EC + 5

#define Zigbee_Number_Power                        43
#define Zigbee_Number_Power_HUNDREDS                        Zigbee_Number_Power + 1
#define Zigbee_Number_Power_TENS                         Zigbee_Number_Power + 2
#define Zigbee_Number_Power_UNITS                        Zigbee_Number_Power + 3
#define Zigbee_Number_Power_ONES                        Zigbee_Number_Power + 4
#define Zigbee_Number_Power_TENTHS                        Zigbee_Number_Power + 5

char buffer[30] ;
//char asd[4] ={0x40,0xED,0xAE,0x71};


int8_t E = 0;
int8_t S = 0;
  	
	  double M =0 ;
double IEEE754(char a ,char b, char c ,char d)
{
		
	  E = 0;
    S = 0;
	  M =0 ;
	 
		double M_Value2 = 1;
	  double E_Value = 1;
		if(a & 128 )
		{
			S= -1;
		}
		else S =1;
		
		for (int i=1;i<8;i++)
		{
			if(a &(128 >> i))  // 移位判斷
			{
				E += 1<<(8-i);   // 左移累加
			}
		}
		E+=((b & 128) >> 7); //E累加最右邊一位
		 
		 
		for (int i=1;i<8;i++)
		{
			M_Value2 /=2;
			if( b & (128 >> i))
			{
				M += M_Value2 ;
			}
		}
		
		for (int i=0;i<8;i++)
		{
			M_Value2 /=2;
			if( c & (128 >> i))
			{
				M += M_Value2 ;
			}
		}
	
		for (int i=0;i<8;i++)
		{
			M_Value2 /=2;
			if( d & (128 >> i))
			{
				M += M_Value2 ;	
			}
		}
		
		if(E == 0 && M==0)
		{
			M =-1;
		}
		
		E=E-127; // 算出有幾次方
		if(E>0)
		{
			for (int i=0; i<E ; i++)  // 2的一次方是2
			{
				E_Value *= 2;  // 2^幾次方
			}
		}
		else if(E<0)
		{
			E=E*-1;
			for (int i=0; i<E ; i++)  // 2的一次方是2
			{
				E_Value /= 2;  // 2^幾次方
			}
		}
		else
		{
			E_Value =1;
		}
		

		return S*E_Value*(1+M) ;
		
		
	
}

void Lora_Send_Val(uint16_t ATump , uint16_t AHumi , uint16_t ALux , uint16_t WDo , uint16_t WEc , uint16_t WPh , uint16_t WTemp )
{
		RF_PutByte(0X02);
		RF_PutByte(0x02);
	  
		RF_PutByte(0x14);
		RF_PutByte(SENSORS_ADDR);
	  RF_PutByte(0x2c);
		//RF_PutByte((ATump/10000) + 0x30);
		RF_PutByte((ATump/1000 % 10) + 0x30);
		RF_PutByte((ATump/100 % 10) + 0x30);
		RF_PutByte((ATump/10 % 10) + 0x30);
	  RF_PutByte(0x2e);
		RF_PutByte((ATump% 10) + 0x30);
		RF_PutByte(0x2c);
		//RF_PutByte((AHumi/10000) + 0x30);
		RF_PutByte((AHumi/1000 % 10) + 0x30);
		RF_PutByte((AHumi/100 % 10) + 0x30);
		RF_PutByte((AHumi/10 % 10) + 0x30);
	  RF_PutByte(0x2e);
		RF_PutByte((AHumi% 10) + 0x30);
	  RF_PutByte(0x2c);
		RF_PutByte((ALux/10000) + 0x30);
		RF_PutByte((ALux/1000 % 10) + 0x30);
		RF_PutByte((ALux/100 % 10) + 0x30);
		RF_PutByte((ALux/10 % 10) + 0x30);
		RF_PutByte((ALux% 10) + 0x30);
		RF_PutByte(0x2c);
		
		RF_PutByte((WDo/10000) + 0x30);
		RF_PutByte((WDo/1000 % 10) + 0x30);
		RF_PutByte(0x2e);
		RF_PutByte((WDo/100 % 10) + 0x30);
		RF_PutByte((WDo/10 % 10) + 0x30);
		RF_PutByte((WDo% 10) + 0x30);
		RF_PutByte(0x2c);
		
		RF_PutByte((WEc/10000) + 0x30);
		RF_PutByte((WEc/1000 % 10) + 0x30);
		RF_PutByte(0x2e);
		RF_PutByte((WEc/100 % 10) + 0x30);
		RF_PutByte((WEc/10 % 10) + 0x30);
		RF_PutByte((WEc% 10) + 0x30);
		RF_PutByte(0x2c);
		
		RF_PutByte((WPh/10000) + 0x30);
		RF_PutByte((WPh/1000 % 10) + 0x30);
		RF_PutByte(0x2e);
		RF_PutByte((WPh/100 % 10) + 0x30);
		RF_PutByte((WPh/10 % 10) + 0x30);
		RF_PutByte((WPh% 10) + 0x30);
		RF_PutByte(0x2c);
		
		//RF_PutByte((WTemp/10000) + 0x30);
		RF_PutByte((WTemp/1000 % 10) + 0x30);
		RF_PutByte((WTemp/100 % 10) + 0x30);
		RF_PutByte((WTemp/10 % 10) + 0x30);
    RF_PutByte(0x2e);
		RF_PutByte((WTemp% 10) + 0x30);
		RF_PutByte(0x2a);
		
		
		RF_PutEnd();
}
		uint8_t flag , len;
		uint8_t Tx[30];
// -------------------------------------------------------------------
int main(void)
{
		HAL_Init();
		SystemClock_Config();
		GPIO_Init();
		UART_Init();
		IWDG_Init();
		RTC_Init();
		ADC_Init();

		LED_R_On(60);
		LED_G_On(60);
		BEEP_On(30);
		IWDG_Reset();

		DELAY_Ms(300);

		TIMER_SleepCount = 0;
		POWER_Flag = 0;
		COMM_Slave = 1;
		LED_R_OFF();
		M200_Init();
		M650_Init();
		SC_Sleep_Time = 300;
		SC_Sleep_Time_Count = 280;
		
		AIR_Temp = AIR_Humi = GND_Temp = GND_Humi = AIR_Lux = AIR_CO2 = SC_Move_Flag = Water_do = Water_ec = Water_ph = Water_temp =0;
		EN_E5V_ON();
		EN_E12V_ON();
		EN_R12V_ON();
		EN_R5V_ON(); 
		EN_RF_ON();
		/*while(1)
		{
				UART_Init();
				DELAY_Ms(2000);
				Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
			DELAY_Ms(50);
		
		}*/
		while(1)
		{
				
			
				// 10 ms
				if (TIMER_MsCount > 0)
				{
					TIMER_MsCount = 0;
					if (DEVICE_ResetFlag == 0)
					{
						IWDG_Reset();
					}
					else
					{
						DELAY_Ms(30);
						NVIC_SystemReset();
					}
				}
				
				//1 s
				if (TIMER_SecCount > 1)
				{
						TIMER_SecCount--;
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time - 19)				//打開電源
				{
						GPIO_Init();
						UART_Init();
						ADC_Init();
					
						EN_E5V_ON();
						EN_E12V_ON();
						EN_R12V_ON();
						EN_R5V_ON();
						EN_RF_ON();
							
						M200_Init();
						GND_M200_Init();
						M650_Init();
						RF_TX_Flag = 0;
						len = RF_RxLen();
						DELAY_Ms(500);
				}
			
				if(SC_Sleep_Time_Count == SC_Sleep_Time-14)				//感測空氣溫濕 土壤溫濕 光照 並取值
				{
						uint8_t air_temphumi_count = 3;
						uint16_t air_temp_new_val = 0xf0f0;
						uint16_t air_humi_new_val = 0xf0f0 ;
					while(air_temphumi_count--)
						{
								M200_GetValue();
								if(M200_Temp > air_temp_new_val)
								{
										if((M200_Temp - air_temp_new_val) < 50)
										{
												AIR_Temp = M200_Temp;
										}
										air_temp_new_val = M200_Temp;
								}
								else
								{
										if((air_temp_new_val - M200_Temp) < 50)
										{
												AIR_Temp = M200_Temp;
										}
										air_temp_new_val = M200_Temp;
								}
								
								if((M200_Humi > 0) && (M200_Humi < 1000))
								{
										AIR_Humi = M200_Humi;
										air_temphumi_count = 0;
										break;
								}
								DELAY_Ms(20);	
						}
						AIR_Temp = M200_Temp;
						AIR_Humi = M200_Humi;
						//GND_M200_GetValue();
						
						uint8_t air_lux_count = 3;
						uint32_t air_lux_new_val = 0xffffffff;
						while(air_lux_count--)
						{
								M650_GetValue();
								if((M650_Lux > air_lux_new_val))
								{
										if((M650_Lux - air_lux_new_val) < 1000)
										{
												AIR_Lux = M650_Lux;
												air_lux_count = 0;
												break;
										}
										air_lux_new_val = M650_Lux;
								}
								else
								{
										if((air_lux_new_val - M650_Lux) < 1000)
										{
												AIR_Lux = M650_Lux;
												air_lux_count = 0;
												break;
										}
										air_lux_new_val = M650_Lux;
								}
								AIR_Lux = M650_Lux;
								DELAY_Ms(50);	
						}
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-99)				//感測CO2 1次
				{
						/*CO2_PutByte('Z');
						CO2_PutByte(0x0D);
						CO2_PutByte(0x0A);
						CO2_PutEnd();*/
				}
				if(SC_Sleep_Time_Count == SC_Sleep_Time-13) //do
				{		
						RS485_GetValue(Tx);
						DELAY_Ms(5);
						RS485_PutByte(0x01);
						RS485_PutByte(0x03);
						RS485_PutByte(0x00);
						RS485_PutByte(0x01);
						RS485_PutByte(0x00);
						RS485_PutByte(0x02);

						RS485_PutByte(0x95);
						RS485_PutByte(0xCB);
						RS485_PutEnd();
						DELAY_Ms(300);
					  
					  
					
				}
				if(SC_Sleep_Time_Count == SC_Sleep_Time-12)				//取值 do
				{
						/*AIR_CO2 = CO2_GetValue();*/
						len = RS485_RxLen();
						if(len)
						{
								RS485_GetValue(Tx);
							  do_value = IEEE754(Tx[5],Tx[6],Tx[3],Tx[4]);
							  Water_do = do_value*1000;
						   DELAY_Ms(50);
						}
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-11)				//送值 EC
				{
						RS485_GetValue(Tx);
						DELAY_Ms(5);
						RS485_PutByte(0x02);
						RS485_PutByte(0x03);
						RS485_PutByte(0x00);
						RS485_PutByte(0x00);
						RS485_PutByte(0x00);
						RS485_PutByte(0x02);

						RS485_PutByte(0xc4);
						RS485_PutByte(0x38);;
						RS485_PutEnd();
						DELAY_Ms(300);
					
						SC_Move_Flag ++;
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-10)				//取值 EC
				{
						len = RS485_RxLen();
						if(len)
						{
								RS485_GetValue(Tx);
							  ec_value = IEEE754(Tx[3],Tx[4],Tx[5],Tx[6]);
							  Water_ec = ec_value *1000;
								
						}
						DELAY_Ms(50);
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-9)				//送值 PH
				{
						RS485_GetValue(Tx);
						DELAY_Ms(5);
						RS485_PutByte(0x03);
						RS485_PutByte(0x03);
						RS485_PutByte(0x00);
						RS485_PutByte(0x01);
						RS485_PutByte(0x00);
						RS485_PutByte(0x02);

						RS485_PutByte(0x94);
						RS485_PutByte(0x29);
						RS485_PutEnd();
						DELAY_Ms(300);
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-8)				//取值 PH
				{
						len = RS485_RxLen();
						if(len)
						{
								RS485_GetValue(Tx);
							  ph_value = IEEE754(Tx[5],Tx[6],Tx[3],Tx[4]);
							  Water_ph = ph_value*1000;
							
						}
						/*len = RF_RxLen();
						DELAY_Ms(30);*/
						/*Lora_Send_Val(AIR_Temp,AIR_Humi,AIR_Lux,GND_Humi,AIR_Lux,AIR_CO2,GND_EC);
						EN_E5V_OFF();
						EN_E12V_OFF();
						EN_R12V_OFF();
						EN_R5V_OFF();
						DELAY_Ms(300);*/
				}
			  if(SC_Sleep_Time_Count == SC_Sleep_Time-7)  
				{
						//Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
						//DELAY_Ms(300);
						RS485_GetValue(Tx);
						DELAY_Ms(5);
						RS485_PutByte(0x04);
						RS485_PutByte(0x03);
						RS485_PutByte(0x00);
						RS485_PutByte(0x00);
						RS485_PutByte(0x00);
						RS485_PutByte(0x02);

						RS485_PutByte(0xC4);
						RS485_PutByte(0x5E);
						RS485_PutEnd();
						DELAY_Ms(200);
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-6)   //水溫取值
				{
						//Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
						//DELAY_Ms(300);
					  len = RS485_RxLen();
						if(len)
						{
								RS485_GetValue(Tx);
							  Water_temp = (Tx[5]<<8)+Tx[6];
							
						}
					
					  Lora_Send_Val(AIR_Temp,AIR_Humi,AIR_Lux,Water_do,Water_ec,Water_ph,Water_temp);
						EN_E5V_OFF();
						EN_E12V_OFF();
						EN_R12V_OFF();
						EN_R5V_OFF();
						DELAY_Ms(300);
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-4)
				{
						//Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
						//DELAY_Ms(300);
						/*len = RF_RxLen();
						if(len > 0)
						{
								RF_GetValue(Tx);
								RF_TX_Flag = 1;
						}
						if(RF_TX_Flag == 0)
						{
								Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
								DELAY_Ms(800);
						}*/
						EN_RF_OFF();
						DELAY_Ms(100);
				}
				
				if(SC_Sleep_Time_Count == SC_Sleep_Time-2)
				{
						//Lora_Send_Val(AIR_Temp,GND_Temp,AIR_Humi,GND_Humi,AIR_Lux,AIR_CO2,GND_EC,GND_PH);						
						//DELAY_Ms(300);
				}
				
				if(SC_Sleep_Time_Count >= SC_Sleep_Time)//if(SC_Sleep_Time_Count >= SC_Sleep_Time && SC_Move_Flag ==6)				//取值 CO2
				{
						SC_Sleep_Time_Count = 0;
						SC_Move_Flag = 0;
					
						/*GPIOA->MODER = 0xFFFFFFFF;
						GPIOB->MODER = 0xFFFFFFFF;
						GPIOC->MODER = 0xFFFFFFFF;
						GPIOF->MODER = 0xFFFFFFFF;*/
						
						EN_E5V_OFF();
						EN_E12V_OFF();
						EN_R12V_OFF();
						EN_R5V_OFF(); 
						EN_RF_OFF();
						DELAY_Ms(100);
				}
				//STOP_Mode();
		}
		
}
