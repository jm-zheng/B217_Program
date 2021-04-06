//------------------------------------------------------------------------------
// TMD.h
//------------------------------------------------------------------------------
#ifndef TMD_H
#define TMD_H

#include "HT32IO.h"
#include "SoftwareWire.h"

#define TMD_ADDR    0x53  // Address of the sensor

//------------------------------------------------------------------------------
class TMD
{
private:
	SoftwareWire sw_tmd;
public:
	void begin(uint8_t sda_pin,uint8_t scl_pin);
	void setReg(uint8_t reg, uint8_t data);
	uint8_t getReg(uint8_t reg);
	uint16_t getData(uint8_t reg);
};
#endif
