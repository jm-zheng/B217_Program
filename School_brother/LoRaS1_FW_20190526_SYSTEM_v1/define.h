//-------------------------------------------------------------------
// define.h 
//-------------------------------------------------------------------
#include "stm32f0xx_hal.h"
//-------------------------------------------------------------------
#define DEVICE_MODEL									0x1001
#define DEVICE_VERSION								0x0130

//-------------------------------------------------------------------
//#define WATCHDOG_ENABLE								1

//-------------------------------------------------------------------
#define HIBYTE(v)   									((uint8_t)((v) >> 8))
#define LOBYTE(v)   									((uint8_t)((v) & 0x00FF))

//-------------------------------------------------------------------
// main.c
//-------------------------------------------------------------------
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern IWDG_HandleTypeDef hiwdg;
extern ADC_HandleTypeDef hadc;

extern __IO uint8_t TIMER_Count;
extern __IO uint8_t TIMER_MsCount;
extern __IO uint8_t TIMER_10MsCount;
extern __IO uint8_t TIMER_SecCount;
extern uint8_t TIMER_SleepCount;

extern __IO uint8_t BEEP_Delay;
extern __IO uint8_t LED_R_Delay;
extern __IO uint8_t LED_G_Delay;

extern uint32_t DEVICE_Sn;
extern uint8_t DEVICE_ResetFlag;

extern uint8_t KEY_MODE_Tag;
extern uint8_t KEY_ENTER_Tag;

extern uint8_t POWER_Flag;
extern uint8_t ADC_Status;

extern uint16_t SC_Sleep_Time;
extern uint16_t SC_Sleep_Time_Count;
//-------------------------------------------------------------------
// board.c
//-------------------------------------------------------------------
#define BEEP_PIN                        GPIO_PIN_6
#define BEEP_GPIO_PORT                  GPIOC
#define BEEP_ON()                    		BEEP_GPIO_PORT->BSRR = BEEP_PIN
#define BEEP_OFF()                    	BEEP_GPIO_PORT->BRR = BEEP_PIN
#define BEEP_TOGGLE()                 	BEEP_GPIO_PORT->ODR ^= BEEP_PIN

#define LED_R_PIN                    		GPIO_PIN_9
#define LED_R_GPIO_PORT              		GPIOB
#define LED_R_OFF()                 		LED_R_GPIO_PORT->BSRR = LED_R_PIN
#define LED_R_ON()                  		LED_R_GPIO_PORT->BRR = LED_R_PIN
#define LED_R_TOGGLE()                 	LED_R_GPIO_PORT->ODR ^= LED_R_PIN

#define LED_G_PIN                    		GPIO_PIN_7
#define LED_G_GPIO_PORT              		GPIOB
#define LED_G_OFF()                 		LED_G_GPIO_PORT->BSRR = LED_G_PIN
#define LED_G_ON()                  		LED_G_GPIO_PORT->BRR = LED_G_PIN
#define LED_G_TOGGLE()                 	LED_G_GPIO_PORT->ODR ^= LED_G_PIN

#define KEY_MODE_PIN                    GPIO_PIN_8
#define KEY_MODE_GPIO_PORT              GPIOB
#define KEY_MODE_IN()										HAL_GPIO_ReadPin(KEY_MODE_GPIO_PORT, KEY_MODE_PIN)
#define KEY_MODE_EXTI_IRQ          			EXTI4_15_IRQn 

#define KEY_ENTER_PIN                  	GPIO_PIN_15
#define KEY_ENTER_GPIO_PORT            	GPIOA
#define KEY_ENTER_IN()									HAL_GPIO_ReadPin(KEY_ENTER_GPIO_PORT, KEY_ENTER_PIN)
#define KEY_ENTER_EXTI_IRQ          		EXTI4_15_IRQn 

#define EN_E12V_PIN                    	GPIO_PIN_3
#define EN_E12V_GPIO_PORT              	GPIOC
#define EN_E12V_ON()                 		EN_E12V_GPIO_PORT->BSRR = EN_E12V_PIN
#define EN_E12V_OFF()                  	EN_E12V_GPIO_PORT->BRR = EN_E12V_PIN

#define EN_E5V_PIN                    	GPIO_PIN_7
#define EN_E5V_GPIO_PORT              	GPIOC
#define EN_E5V_ON()                 		EN_E5V_GPIO_PORT->BSRR = EN_E5V_PIN
#define EN_E5V_OFF()                  	EN_E5V_GPIO_PORT->BRR = EN_E5V_PIN

#define EN_R12V_PIN                    	GPIO_PIN_8
#define EN_R12V_GPIO_PORT              	GPIOA
#define EN_R12V_ON()                 		EN_R12V_GPIO_PORT->BSRR = EN_R12V_PIN
#define EN_R12V_OFF()                  	EN_R12V_GPIO_PORT->BRR = EN_R12V_PIN

#define EN_R5V_PIN                    	GPIO_PIN_9
#define EN_R5V_GPIO_PORT              	GPIOC
#define EN_R5V_ON()                 		EN_R5V_GPIO_PORT->BSRR = EN_R5V_PIN
#define EN_R5V_OFF()                  	EN_R5V_GPIO_PORT->BRR = EN_R5V_PIN

#define EN_RF_PIN                     	GPIO_PIN_5
#define EN_RF_GPIO_PORT               	GPIOB
#define EN_RF_OFF()                   	EN_RF_GPIO_PORT->BSRR = EN_RF_PIN
#define EN_RF_ON()                   		EN_RF_GPIO_PORT->BRR = EN_RF_PIN

#define RF_AUX_PIN                     	GPIO_PIN_1
#define RF_AUX_GPIO_PORT               	GPIOA
#define RF_AUX_HI()                   	RF_AUX_GPIO_PORT->BSRR = RF_AUX_PIN
#define RF_AUX_LO()                   	RF_AUX_GPIO_PORT->BRR = RF_AUX_PIN
#define RF_AUX_IN()											HAL_GPIO_ReadPin(RF_AUX_GPIO_PORT, RF_AUX_PIN)

#define RF_M0_PIN                     	GPIO_PIN_2
#define RF_M0_GPIO_PORT               	GPIOB
#define RF_M0_HI()                   		RF_M0_GPIO_PORT->BSRR = RF_M0_PIN
#define RF_M0_LO()                   		RF_M0_GPIO_PORT->BRR = RF_M0_PIN

#define RF_M1_PIN                     	GPIO_PIN_1
#define RF_M1_GPIO_PORT               	GPIOB
#define RF_M1_HI()                   		RF_M1_GPIO_PORT->BSRR = RF_M1_PIN
#define RF_M1_LO()                   		RF_M1_GPIO_PORT->BRR = RF_M1_PIN

#define RS485_PIN                     	GPIO_PIN_8
#define RS485_GPIO_PORT               	GPIOC
#define RS485_TX()                   		RS485_GPIO_PORT->BSRR = RS485_PIN
#define RS485_RX()                   		RS485_GPIO_PORT->BRR = RS485_PIN

#define SDA_1_PIN                     	GPIO_PIN_6
#define SDA_1_GPIO_PORT               	GPIOA
#define SDA_1_HI()                   		SDA_1_GPIO_PORT->BSRR = SDA_1_PIN
#define SDA_1_LO()                   		SDA_1_GPIO_PORT->BRR = SDA_1_PIN
#define SDA_1_IN()											HAL_GPIO_ReadPin(SDA_1_GPIO_PORT, SDA_1_PIN)

#define SCL_1_PIN                     	GPIO_PIN_7
#define SCL_1_GPIO_PORT               	GPIOA
#define SCL_1_HI()                   		SCL_1_GPIO_PORT->BSRR = SCL_1_PIN
#define SCL_1_LO()                   		SCL_1_GPIO_PORT->BRR = SCL_1_PIN

#define SDA_2_PIN                     	GPIO_PIN_4
#define SDA_2_GPIO_PORT               	GPIOC
#define SDA_2_HI()                   		SDA_2_GPIO_PORT->BSRR = SDA_2_PIN
#define SDA_2_LO()                   		SDA_2_GPIO_PORT->BRR = SDA_2_PIN
#define SDA_2_IN()											HAL_GPIO_ReadPin(SDA_2_GPIO_PORT, SDA_2_PIN)

#define SCL_2_PIN                     	GPIO_PIN_5
#define SCL_2_GPIO_PORT               	GPIOC
#define SCL_2_HI()                   		SCL_2_GPIO_PORT->BSRR = SCL_2_PIN
#define SCL_2_LO()                   		SCL_2_GPIO_PORT->BRR = SCL_2_PIN

#define SDA_3_PIN                     	GPIO_PIN_13
#define SDA_3_GPIO_PORT               	GPIOB
#define SDA_3_HI()                   		SDA_3_GPIO_PORT->BSRR = SDA_3_PIN
#define SDA_3_LO()                   		SDA_3_GPIO_PORT->BRR = SDA_3_PIN
#define SDA_3_IN()											HAL_GPIO_ReadPin(SDA_3_GPIO_PORT, SDA_3_PIN)

#define SCL_3_PIN                     	GPIO_PIN_12
#define SCL_3_GPIO_PORT               	GPIOB
#define SCL_3_HI()                   		SCL_3_GPIO_PORT->BSRR = SCL_3_PIN
#define SCL_3_LO()                   		SCL_3_GPIO_PORT->BRR = SCL_3_PIN

#define SDA_4_PIN                     	GPIO_PIN_15
#define SDA_4_GPIO_PORT               	GPIOB
#define SDA_4_HI()                   		SDA_4_GPIO_PORT->BSRR = SDA_4_PIN
#define SDA_4_LO()                   		SDA_4_GPIO_PORT->BRR = SDA_4_PIN
#define SDA_4_IN()											HAL_GPIO_ReadPin(SDA_4_GPIO_PORT, SDA_4_PIN)

#define SCL_4_PIN                     	GPIO_PIN_14
#define SCL_4_GPIO_PORT               	GPIOB
#define SCL_4_HI()                   		SCL_4_GPIO_PORT->BSRR = SCL_4_PIN
#define SCL_4_LO()                   		SCL_4_GPIO_PORT->BRR = SCL_4_PIN

#define DP_1_PIN                     		GPIO_PIN_13
#define DP_1_GPIO_PORT               		GPIOC
#define DP_1_IN()												HAL_GPIO_ReadPin(DP_1_GPIO_PORT, DP_1_PIN)

#define DP_2_PIN                     		GPIO_PIN_14
#define DP_2_GPIO_PORT               		GPIOC
#define DP_2_IN()												HAL_GPIO_ReadPin(DP_2_GPIO_PORT, DP_2_PIN)

#define DP_3_PIN                     		GPIO_PIN_15
#define DP_3_GPIO_PORT               		GPIOC
#define DP_3_IN()												HAL_GPIO_ReadPin(DP_3_GPIO_PORT, DP_3_PIN)

#define DP_4_PIN                     		GPIO_PIN_2
#define DP_4_GPIO_PORT               		GPIOC
#define DP_4_IN()												HAL_GPIO_ReadPin(DP_4_GPIO_PORT, DP_4_PIN)

#define DP_5_PIN                     		GPIO_PIN_1
#define DP_5_GPIO_PORT               		GPIOC
#define DP_5_IN()												HAL_GPIO_ReadPin(DP_5_GPIO_PORT, DP_5_PIN)

#define DP_6_PIN                     		GPIO_PIN_0
#define DP_6_GPIO_PORT               		GPIOC
#define DP_6_IN()												HAL_GPIO_ReadPin(DP_6_GPIO_PORT, DP_6_PIN)

#define DP_7_PIN                     		GPIO_PIN_1
#define DP_7_GPIO_PORT               		GPIOF
#define DP_7_IN()												HAL_GPIO_ReadPin(DP_7_GPIO_PORT, DP_7_PIN)

#define DP_8_PIN                     		GPIO_PIN_0
#define DP_8_GPIO_PORT               		GPIOF
#define DP_8_IN()												HAL_GPIO_ReadPin(DP_8_GPIO_PORT, DP_8_PIN)

#define VDEC_PIN                     		GPIO_PIN_0
#define VDEC_GPIO_PORT               		GPIOA
#define VDEC_ADC_CHANNEL                ADC_CHANNEL_0

#define AIN_1_PIN                     	GPIO_PIN_4
#define AIN_1_GPIO_PORT               	GPIOA
#define AIN_1_ADC_CHANNEL               ADC_CHANNEL_4

#define AIN_2_PIN                     	GPIO_PIN_5
#define AIN_2_GPIO_PORT               	GPIOA
#define AIN_2_ADC_CHANNEL               ADC_CHANNEL_5

//-------------------------------------------------------------------
// USART Communication boards Interface 
// RS485
#define USART1_TX_PIN                   GPIO_PIN_9
#define USART1_RX_PIN                   GPIO_PIN_10          
#define USART1_GPIO_PORT             		GPIOA

// RF (LoRa)
#define USART2_TX_PIN                   GPIO_PIN_2
#define USART2_RX_PIN                   GPIO_PIN_3
#define USART2_GPIO_PORT             		GPIOA              

// CO2
#define USART3_TX_PIN                   GPIO_PIN_10
#define USART3_RX_PIN                   GPIO_PIN_11
#define USART3_GPIO_PORT             		GPIOB              

// ISP
#define USART4_TX_PIN                   GPIO_PIN_10
#define USART4_RX_PIN                   GPIO_PIN_11
#define USART4_GPIO_PORT             		GPIOC        


//-------------------------------------------------------------------
extern __IO uint16_t VDEC_Value;

void SystemClock_Config(void);
void GPIO_Init(void);
void ADC_Init(void);
void IWDG_Init(void);
void IWDG_Reset(void);
void RTC_Init(void);
void STOP_Mode(void);
void JUMP_ToIspProgram(void);
void DELAY_Us(uint16_t us);
#define DELAY_Ms(ms)  	HAL_Delay(ms)
void BEEP_On(uint8_t delay);
void LED_R_On(uint8_t delay);
void LED_G_On(uint8_t delay);
void BEEP_Ok(void);
void BEEP_Key(void);

//-------------------------------------------------------------------
// flash.c
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// Flash Address Define
//-------------------------------------------------------------------
// STM32F071xB STM32F072xB 128K FLASH 配置
// 0x0800 0000 - 0x0801 BFFF  118K 主程式 
// 0x0801 C000 - 0x0801 EFFF   12K Bootloader
// 0x0801 F000 - 0x0801 F7FF   2K Parameter
// 0x0801 F800 - 0x0801 FFFF   2K SN/Model/PIN
// Page Size = 2K , Sector Size = 4K
//-------------------------------------------------------------------
#define FLASH_PROG_START_ADDR   					((uint32_t)0x08000000) // Start @ of MAIN PROGRAM flash area 
#define FLASH_ISP_START_ADDR   						((uint32_t)0x0801C000) // Start @ of ISP PROGRAM flash area 
#define FLASH_PARAMATER_START_ADDR  			((uint32_t)0x0801F000) // Start @ of PARAMETER DATA flash area 
#define FLASH_FACTORY_START_ADDR  				((uint32_t)0x0801F800) // Start @ of FACTORY DATA flash area 

#define FLASH_BUFFER_MAX									128
extern uint32_t FLASH_Buffer[FLASH_BUFFER_MAX];

void FLASH_EraseBlock( uint32_t addr);
void FLASH_WriteBlock(uint32_t addr,uint16_t dwords);
void FLASH_ReadBlock(uint32_t addr,uint16_t dwords);


//-------------------------------------------------------------------
// library.c
//-------------------------------------------------------------------
typedef struct
{
	uint8_t High;
	uint8_t Low;
} TYPE_AscHex;

TYPE_AscHex LIB_HexToAsc(uint8_t uch);
uint8_t LIB_AscToDec(uint8_t ch);
uint8_t LIB_AscToHex(uint8_t ch);
uint8_t LIB_StrLen(char ucDataStr[]);
void LIB_MemCpy(uint8_t mtag[],uint8_t msrc[],uint8_t len);

//-------------------------------------------------------------------
// uart.c
//-------------------------------------------------------------------
#define COMM_CMD_READ_HOLDING_REGISTER				0x03
#define COMM_CMD_PRESET_SINGLE_REGISTER				0x06
#define COMM_CMD_PRESET_MULTIPLE_REGISTER			0x10

#define COMM_CMD_GET_SLAVE										0xE1
#define COMM_CMD_GET_SN_VERSION								0xE2
#define COMM_CMD_SET_SLAVE_BY_SN							0xE3
#define COMM_CMD_SET_SLAVE										0xE4
#define COMM_CMD_SET_RESET										0xE5
#define COMM_CMD_SET_TXRXID										0xE6

#define COMM_CMD_FLASH_MODE										0xF0
#define COMM_CMD_FLASH_PROGRAM_PAGE						0xF1
#define COMM_CMD_FLASH_READ_PAGE							0xF2
#define COMM_CMD_FLASH_EXIT										0xF4
#define COMM_CMD_FLASH_ENTER									0xF5

extern uint8_t COMM_Slave;
extern uint8_t *COMM_Buffer;
extern uint8_t COMM_Flag;
extern uint8_t COMM_Cmd;
extern uint8_t COMM_Addr;
extern uint8_t COMM_Reg;
extern uint8_t COMM_Len;
extern uint8_t COMM_Read;
extern uint8_t COMM_Point;
extern uint16_t COMM_Crc;
extern uint8_t COMM_CrcHi;
extern uint8_t COMM_CrcLo;

void COMM_PutStart(void);
void COMM_PutEnd(void);
void COMM_CrcStart(void);
void COMM_CrcCal(uint8_t ch);
void COMM_CrcEnd(void);
void COMM_CrcCheck(void);
void COMM_PutWord(uint16_t ch);
void COMM_PutDWord(uint32_t ch);
uint8_t COMM_GetByte(void);
uint16_t COMM_GetWord(void);
uint32_t COMM_GetDWord(void);

void COMM_ReadHoldingRegisters(void);
void COMM_PresetSingleRegister(void);
void COMM_PresetMultipleRegisters(void);
void COMM_GetSlave(void);
void COMM_GetSnVersion(void);
void COMM_SetSlave(void);
void COMM_SetSlaveBySN(void);
void COMM_SetReset(void);

void UART_Init(void);
void UART_Proc(void);

uint16_t CO2_GetValue(void);

#define RS485_TX_BUFFER_MAX						250
#define RS485_RX_BUFFER_MAX						250
extern __IO uint8_t RS485_TxBuffer[RS485_TX_BUFFER_MAX];
extern __IO uint8_t RS485_RxBuffer[RS485_RX_BUFFER_MAX];
extern __IO uint8_t RS485_TxLength;
extern __IO uint8_t RS485_TxIndex;
extern __IO uint8_t RS485_RxLength;
extern __IO uint8_t RS485_Count;
extern uint8_t RS485_Read;
void RS485_PutByte(uint8_t ch);
void RS485_PutEnd(void);
uint8_t RS485_GetByte(void);
uint16_t RS485_GetValue(uint8_t *RS485_Buffer);
uint8_t RS485_RxLen(void);


#define ISP_TX_BUFFER_MAX							250
#define ISP_RX_BUFFER_MAX							250
extern __IO uint8_t ISP_TxBuffer[ISP_TX_BUFFER_MAX];
extern __IO uint8_t ISP_RxBuffer[ISP_RX_BUFFER_MAX];
extern __IO uint8_t ISP_Flag;
extern __IO uint8_t ISP_TxLength;
extern __IO uint8_t ISP_RxLength;
extern __IO uint8_t ISP_RxIndex;
extern __IO uint8_t ISP_TxIndex;
extern __IO uint8_t ISP_Count;
extern uint8_t ISP_Read;

void ISP_PutByte(uint8_t ch);
void ISP_PutEnd(void);
uint8_t ISP_GetByte(void);


#define RF_TX_BUFFER_MAX							250
#define RF_RX_BUFFER_MAX							250
extern __IO uint8_t RF_TxBuffer[RF_TX_BUFFER_MAX];
extern __IO uint8_t RF_RxBuffer[RF_RX_BUFFER_MAX];
extern __IO uint8_t RF_Flag;
extern __IO uint8_t RF_TxLength;
extern __IO uint8_t RF_RxLength;
extern __IO uint8_t RF_RxIndex;
extern __IO uint8_t RF_TxIndex;
extern __IO uint8_t RF_Count;
extern uint8_t RF_Read;

void RF_PutByte(uint8_t ch);
void RF_PutEnd(void);
uint8_t RF_GetByte(void);
uint16_t RF_GetValue(uint8_t *RF_Buffer);
uint8_t RF_RxLen(void);


#define CO2_TX_BUFFER_MAX							250
#define CO2_RX_BUFFER_MAX							250
extern __IO uint8_t CO2_TxBuffer[CO2_TX_BUFFER_MAX];
extern __IO uint8_t CO2_RxBuffer[CO2_RX_BUFFER_MAX];
extern __IO uint8_t CO2_Flag;
extern __IO uint8_t CO2_TxLength;
extern __IO uint8_t CO2_RxLength;
extern __IO uint8_t CO2_RxIndex;
extern __IO uint8_t CO2_TxIndex;
extern __IO uint8_t CO2_Count;
extern uint8_t CO2_Read;

void CO2_PutByte(uint8_t ch);
void CO2_PutEnd(void);
uint8_t CO2_GetByte(void);


