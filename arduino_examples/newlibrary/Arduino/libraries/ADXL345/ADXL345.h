//------------------------------------------------------------------------------
// ADXL345.h
//------------------------------------------------------------------------------
#ifndef ADXL345_H
#define ADXL345_H

#include <Arduino.h>
#include <SoftwareWire.h>

#define ADXL345_ADDR    0x53  // Address of the sensor

//------------------------------------------------------------------------------
class ADXL345
{
private:
	SoftwareWire sw_adxl;
public:
	void begin(uint8_t sda_pin,uint8_t scl_pin);
	void setReg(uint8_t reg, uint8_t data);
	uint8_t getReg(uint8_t reg);
	uint16_t getData(uint8_t reg);
};
#endif
