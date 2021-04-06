//------------------------------------------------------------------------------
// ADXL345.h
//------------------------------------------------------------------------------
#ifndef ADXL345_H
#define ADXL345_H

#include "HT32IO.h"
#include "SoftwareWire.h"

#define ADXL345_ADDR    0x53  // Address of the sensor

//------------------------------------------------------------------------------
// Register names
//------------------------------------------------------------------------------
#define REG_DEVID 					0x00
#define REG_RESERVED1 			0x01
#define REG_THRESH_TAP 			0x1D
#define REG_OFSX 						0x1E
#define REG_OFSY 						0x1F
#define REG_OFSZ 						0x20
#define REG_DUR 						0x21
#define REG_LATENT 					0x22
#define REG_WINDOW 					0x23
#define REG_THRESH_ACT 			0x24
#define REG_THRESH_INACT 		0x25
#define REG_TIME_INACT 			0x26
#define REG_ACT_INACT_CTL 	0x27
#define REG_THRESH_FF 			0x28
#define REG_TIME_FF 				0x29
#define REG_TAP_AXES 				0x2A
#define REG_ACT_TAP_STATUS 	0x2B
#define REG_BW_RATE 				0x2C
#define REG_POWER_CTL 			0x2D
#define REG_INT_ENABLE 			0x2E
#define REG_INT_MAP 				0x2F
#define REG_INT_SOURCE 			0x30
#define REG_DATA_FORMAT 		0x31
#define REG_DATAX0 					0x32
#define REG_DATAX1 					0x33
#define REG_DATAY0 					0x34
#define REG_DATAY1 					0x35
#define REG_DATAZ0 					0x36
#define REG_DATAZ1 					0x37
#define REG_FIFO_CTL 				0x38
#define REG_FIFO_STATUS 		0x39

//------------------------------------------------------------------------------
//Bit field definitions and register values
//------------------------------------------------------------------------------
//#define XL345_
#define XL345_ID 				0xe5
// Reserved soft reset value 
#define XL345_SOFT_RESET 		0x52

//------------------------------------------------------------------------------
// Registers THRESH_TAP through TIME_INACT take only 8-bit values
// Bit values in ACT_INACT_CTL 
//------------------------------------------------------------------------------
#define CTL_ACT_AC 					0x80
#define CTL_ACT_X_EN	 			0x40
#define CTL_ACT_Y_EN	 			0x20
#define CTL_ACT_Z_EN				0x10
#define CTL_INACT_AC 				0x08
#define CTL_INACT_X_EN	 		0x04
#define CTL_INACT_Y_EN	 		0x02
#define CTL_INACT_Z_EN	 		0x01

//------------------------------------------------------------------------------
// Registers THRESH_FF and TIME_FF take only 8-bit values There are no specific bit fields in these registers
// Bit values in TAP_AXES
//------------------------------------------------------------------------------
#define AEX_TAP_SUPPRESS 		0x08
#define AEX_TAP_X_EN				0x04
#define AEX_TAP_Y_EN 				0x02
#define AEX_TAP_Z_EN				0x01

// Bit values in ACT_TAP_STATUS 
#define SOURCE_ACT_X	 			0x40
#define SOURCE_ACT_Y	 			0x20
#define SOURCE_ACT_Z	 			0x10
#define SOURCE_ASLEEP	 			0x08
#define SOURCE_TAP_X 				0x04
#define SOURCE_TAP_Y	 			0x02
#define SOURCE_TAP_Z	 			0x01

// Bit values in BW_RATE 
// Expresed as output data rate 
#define BW_RATE_3200 				0x0F
#define BW_RATE_1600 				0x0E
#define BW_RATE_800 				0x0D
#define BW_RATE_400 				0x0C
#define BW_RATE_200 				0x0B
#define BW_RATE_100 				0x0A
#define BW_RATE_50 					0x09
#define BW_RATE_25 					0x08
#define BW_RATE_12_5 				0x07
#define BW_RATE_6_25 				0x06
#define BW_RATE_3_125 			0x05
#define BW_RATE_1_563 			0x04
#define BW_RATE__782 				0x03
#define BW_RATE__39 				0x02
#define BW_RATE__195 				0x01
#define BW_RATE__098 				0x00

// Expressed as output bandwidth 
// Use either the bandwidth or rate code,whichever is more appropriate for your application 
#define XL345_BW_1600 			0x0f
#define XL345_BW_800 				0x0e
#define XL345_BW_400 				0x0d
#define XL345_BW_200 				0x0c
#define XL345_BW_100 				0x0b
#define XL345_BW_50 				0x0a
#define XL345_BW_25 			0	x09
#define XL345_BW_12_5 			0x08
#define XL345_BW_6_25 			0x07
#define XL345_BW_3_125 			0x06
#define XL345_BW_1_563 			0x05
#define XL345_BW__782 			0x04
#define XL345_BW__39 				0x03
#define XL345_BW__195 			0x02
#define XL345_BW__098 			0x01
#define XL345_BW__048 			0x00
#define XL345_LOW_POWER 		0x08
#define XL345_LOW_NOISE 		0x00

// Bit values in POWER_CTL 
#define PW_WAKEUP_8HZ 			0x00
#define PW_WAKEUP_4HZ 			0x01
#define PW_WAKEUP_2HZ 			0x02
#define PW_WAKEUP_1HZ 			0x03
#define PW_SLEEP 						0x04
#define PW_MEASURE 					0x08
#define PW_STANDBY 					0x00
#define PW_AUTO_SLEEP 			0x10
#define PW_ACT_INACT_SERIAL 	0x20
#define PW_ACT_INACT_CONCURRENT 0x00

// Bit values in INT_ENABLE, INT_MAP, and INT_SOURCE are identical
#define INT_OVERRUN 				0x01
#define INT_WATERMARK 			0x02
#define INT_FREEFALL 				0x04
#define INT_INACTIVITY 			0x08
#define INT_ACTIVITY 				0x10
#define INT_DOUBLETAP 			0x20
#define INT_SINGLETAP 			0x40
#define INT_DATAREADY 			0x80

// Bit values in DATA_FORMAT 
// Register values read in DATAX0 through DATAZ1 are dependent on the value specified in data format. Customer code will need to interpret the data as desired. 
#define DATA_RANGE_2G 			0x00
#define DATA_RANGE_4G 			0x01
#define DATA_RANGE_8G 			0x02
#define DATA_RANGE_16G 			0x03
#define DATA_JUST_RIGHT 		0x00
#define DATA_JUST_LEFT 			0x04
#define DATA_10BIT 					0x00
#define DATA_FULL_RESOLUTION 	0x08
#define DATA_INT_LOW 				0x20
#define DATA_INT_HIGH 			0x00
#define DATA_SPI3WIRE 			0x40
#define DATA_SPI4WIRE 			0x00
#define DATA_SELFTEST 			0x80

// Bit values in FIFO_CTL 
// The low bits are a value 0 to 31 used for the watermark or the number of pre-trigger samples when in triggered mode 
#define XL345_TRIGGER_INT1 		0x00

#define XL345_TRIGGER_INT2 		0x20
#define XL345_FIFO_MODE_BYPASS 	0x00

#define XL345_FIFO_RESET 		0x00
#define XL345_FIFO_MODE_FIFO 	0x40
#define XL345_FIFO_MODE_STREAM 	0x80
#define XL345_FIFO_MODE_TRIGGER 0xC0

// Bit values in FIFO_STATUS 
// The low bits are a value 0 to 32 showing the number of entries currently available in the FIFO buffer 
#define XL345_FIFO_TRIGGERED 	0x80

#define		STRIKE_THRESHOLD		0x20	//62.5mg/LSB, 0x20=2g
#define		STRIKE_WINDOW			0x0A	//20ms/LSB, 0x0A=10=200ms

#define		STABLE_THRESHOLD		0x08	//62.5mg/LSB, 0x08=0.5g
#define		STABLE_TIME				0x02	//1s/LSB, 0x02=2s
#define		STABLE_WINDOW			0xAF	//20ms/LSB, 0xAF=175=3.5s

#define		NOMOVEMENT_THRESHOLD	0x03	//62.5mg/LSB, 0x03=0.1875g
#define		NOMOVEMENT_TIME			0x0A	//1s/LSB, 0x0A=10s

#define		FREE_FALL_THRESHOLD		0x0C	//62.5mg/LSB, 0x0C=0.75g
#define		FREE_FALL_TIME			0x06	//5ms/LSB, 0x06=30ms
#define		FREE_FALL_OVERTIME		0x0F	//20ms/LSB, 0x0F=15=300ms
#define		FREE_FALL_INTERVAL		0x05	//20ms/LSB, 0x05=100ms


//------------------------------------------------------------------------------
class ADXL345
{
private:
	SoftwareWire sw_adxl;
public:
	void begin(uint8_t sda_pin,uint8_t scl_pin);
	void setReg(uint8_t reg, uint8_t data);
	uint8_t getReg(uint8_t reg);
	int16_t getData(uint8_t reg);
};
#endif
