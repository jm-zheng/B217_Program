//-------------------------------------------------------------------
// Nano030.h
//------------------------------------------------------------------------------
#ifndef NANO030_H
#define NANO030_H

#include "stm32f0xx_hal.h"
#include <stm32f0xx.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif 

#define F_CPU 						48000000

#define HIGH 							0x1
#define LOW  							0x0

#define INPUT 						0x0
#define OUTPUT 						0x1
#define INPUT_PULLUP 			0x2
#define INPUT_PULLDOWN 		0x3
#define OUTPUT_OD					0x4
#define OUTPUT_OD_PULLUP	0x5
#define ANALOG						0x9

#define IT_RISING											0x11
#define IT_FALLING										0x12
#define IT_RISING_FALLING							0x13
#define IT_RISING_PULLUP							0x14
#define IT_FALLING_PULLUP							0x15
#define IT_RISING_FALLING_PULLUP			0x16
#define IT_RISING_PULLDOWN						0x17
#define IT_FALLING_PULLDOWN						0x18
#define IT_RISING_FALLING_PULLDOWN		0x19
	
#define PI 							3.1415926535897932384626433832795
#define HALF_PI 				1.5707963267948966192313216916398
#define TWO_PI 					6.283185307179586476925286766559
#define DEG_TO_RAD 			0.017453292519943295769236907684886
#define RAD_TO_DEG 			57.295779513082320876798154814105
#define EULER 					2.718281828459045235360287471352

#define SERIAL  			0x0
#define DISPLAY 			0x1

#define LSBFIRST 			0
#define MSBFIRST 			1

#define CHANGE 				1
#define FALLING 			2
#define RISING 				3

#define EXTERNAL 			0
#define DEFAULT 			1
#define INTERNAL 			3

//DEFAULT, INTERNAL, INTERNAL1V1, INTERNAL2V56, or EXTERNAL)

// undefine stdlib's abs if encountered
#ifdef abs
	#undef abs
#endif 

#define min(a,b) 			((a)<(b)?(a):(b))
#define max(a,b) 			((a)>(b)?(a):(b))
#define abs(x) 				((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     	((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) 	((deg)*DEG_TO_RAD)
#define degrees(rad) 	((rad)*RAD_TO_DEG)
#define sq(x) 				((x)*(x))

#define interrupts() 	sei()
#define noInterrupts() cli()

#define clockCyclesPerMicrosecond() 	( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) 	( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) 	( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) 	((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) 	(((value) >> (bit)) & 0x01)
#define bitSet(value, bit) 		((value) |= (1UL << (bit)))
#define bitClear(value, bit) 	((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
	#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif 

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

#define PA				 		0x00
#define PA0				 		0x00
#define PA1				 		0x01
#define PA2				 		0x02
#define PA3				 		0x03
#define PA4				 		0x04
#define PA5				 		0x05
#define PA6				 		0x06
#define PA7				 		0x07
#define PA8				 		0x08
#define PA9				 		0x09
#define PA10			 		0x0A
#define PA11			 		0x0B
#define PA12			 		0x0C
#define PA13			 		0x0D
#define PA14			 		0x0E
#define PA15			 		0x0F

#define PB				 		0x10
#define PB0				 		0x10
#define PB1				 		0x11
#define PB2				 		0x12
#define PB3				 		0x13
#define PB4				 		0x14
#define PB5				 		0x15
#define PB6				 		0x16
#define PB7				 		0x17
#define PB8				 		0x18
#define PB9				 		0x19
#define PB10			 		0x1A
#define PB11			 		0x1B
#define PB12			 		0x1C
#define PB13			 		0x1D
#define PB14			 		0x1E
#define PB15			 		0x1F

#define PC				 		0x20
#define PC0				 		0x20
#define PC1				 		0x21
#define PC2				 		0x22
#define PC3				 		0x23
#define PC4				 		0x24
#define PC5				 		0x25
#define PC6				 		0x26
#define PC7				 		0x27
#define PC8				 		0x28
#define PC9				 		0x29
#define PC10			 		0x2A
#define PC11			 		0x2B
#define PC12			 		0x2C
#define PC13			 		0x2D
#define PC14			 		0x2E
#define PC15			 		0x2F

#define PD				 		0x30
#define PD0				 		0x30
#define PD1				 		0x31
#define PD2				 		0x32
#define PD3				 		0x33
#define PD4				 		0x34
#define PD5				 		0x35
#define PD6				 		0x36
#define PD7				 		0x37
#define PD8				 		0x38
#define PD9				 		0x39
#define PD10			 		0x3A
#define PD11			 		0x3B
#define PD12			 		0x3C
#define PD13			 		0x3D
#define PD14			 		0x3E
#define PD15			 		0x3F

#define PE				 		0x40
#define PE0				 		0x40
#define PE1				 		0x41
#define PE2				 		0x42
#define PE3				 		0x43
#define PE4				 		0x44
#define PE5				 		0x45
#define PE6				 		0x46
#define PE7				 		0x47
#define PE8				 		0x48
#define PE9				 		0x49
#define PE10			 		0x4A
#define PE11			 		0x4B
#define PE12			 		0x4C
#define PE13			 		0x4D
#define PE14			 		0x4E
#define PE15			 		0x4F

#define PF				 		0x50
#define PF0				 		0x50
#define PF1				 		0x51
#define PF2				 		0x52
#define PF3				 		0x53
#define PF4				 		0x54
#define PF5				 		0x55
#define PF6				 		0x56
#define PF7				 		0x57
#define PF8				 		0x58
#define PF9				 		0x59
#define PF10			 		0x5A
#define PF11			 		0x5B
#define PF12			 		0x5C
#define PF13			 		0x5D
#define PF14			 		0x5E
#define PF15			 		0x5F

#define AI_TEMP		 		0x60
#define AI_VREF		 		0x61
#define AI_VBAT		 		0x62

#define NOT_A_PIN 		0
#define NOT_A_PORT 		0

#define NOT_AN_INTERRUPT 	-1

#define K1	 					PF0
#define K1_PIN				GPIO_PIN_0
#define K2						PF1
#define K2_PIN				GPIO_PIN_1

#define LED_R					PA8
#define LED_B					PA11

#define M_CS					PA12
#define SPI_SS				PA15

#ifdef __cplusplus
} // extern "C"
#endif 

extern void pinMode(uint8_t, uint8_t);
extern void digitalWrite(uint8_t, uint8_t);
extern int digitalRead(uint8_t);
extern int analogRead(uint8_t);
extern int analogRead12(uint8_t);
extern void analogReference(uint8_t mode);
extern void analogWrite(uint8_t, int);

extern unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
extern unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

extern void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
extern uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

extern void attachInterrupt(uint8_t pin, void(*run)(void), int mode);
extern void detachInterrupt(uint8_t pin);

// WMath prototypes
extern long random( long ) ;
extern long random2( long, long ) ;
extern void randomSeed( uint32_t dwSeed ) ;
extern long map( long, long, long, long, long ) ;

extern uint16_t makeWord( uint8_t h, uint8_t l ) ;
//extern unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
//extern unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
//extern void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
extern void noTone(uint8_t _pin);

//-------------------------------------------------------------------
extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim16;

void SystemClock_Config(void);
extern void delayMicroseconds(uint16_t us);
#define delay(ms)  	HAL_Delay(ms)
#define millis(void) HAL_GetTick(void)
extern uint16_t micros(void);

#endif
