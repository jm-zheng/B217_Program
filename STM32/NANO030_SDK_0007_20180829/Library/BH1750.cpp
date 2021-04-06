//------------------------------------------------------------------------------
// BH1750.cpp
//------------------------------------------------------------------------------
#include "BH1750.h"

//------------------------------------------------------------------------------
void BH1750::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	sw_bh.begin(sda_pin,scl_pin);
  sw_bh.startI2C(BH1750_I2CADDR,I2C_WRITE);
  sw_bh.writeI2C(CONTINUOUS_HIGH_RES_MODE);
  sw_bh.stopI2C();
	readLightLevel();
}

//------------------------------------------------------------------------------
// Read light level from sensor
// @return Light level in lux (0 ~ 65535)
//------------------------------------------------------------------------------
uint16_t BH1750::readLightLevel(void) 
{
  // Measurement result will be stored here
  uint32_t level;

  sw_bh.startI2C(BH1750_I2CADDR,I2C_READ);
  level = sw_bh.readI2C(0);
  level += (sw_bh.readI2C(1)<<8);
  sw_bh.stopI2C();	
	
  // Convert raw value to lux
  level *= 10;
  level /= 12;

  return level;

}
