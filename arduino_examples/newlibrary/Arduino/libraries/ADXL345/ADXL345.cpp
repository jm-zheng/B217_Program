//------------------------------------------------------------------------------
// ADXL345.cpp
//------------------------------------------------------------------------------
#include "ADXL345.h"

//------------------------------------------------------------------------------
void ADXL345::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	sw_adxl.begin(sda_pin,scl_pin);
  setReg(0x2D, 0x0A); // Set ON and Sample 100 Hz
}

//------------------------------------------------------------------------------
uint16_t ADXL345::getData(uint8_t reg)
{
  uint16_t val;

  sw_adxl.startI2C(ADXL345_ADDR,I2C_WRITE);
  sw_adxl.writeI2C(reg);
  sw_adxl.restartI2C(ADXL345_ADDR,I2C_READ);
  val = sw_adxl.readI2C(0);
  val+= (sw_adxl.readI2C(1)<<8);
  sw_adxl.stopI2C();
  return val;
}

//------------------------------------------------------------------------------
uint8_t ADXL345::getReg(uint8_t reg)
{
  uint8_t val;

  sw_adxl.startI2C(ADXL345_ADDR,I2C_WRITE);
  sw_adxl.writeI2C(reg);
  sw_adxl.restartI2C(ADXL345_ADDR,I2C_READ);
  val = sw_adxl.readI2C(0);
  sw_adxl.stopI2C();
  return val;
}

//------------------------------------------------------------------------------
void ADXL345::setReg(uint8_t reg, uint8_t data)
{     
  sw_adxl.startI2C(ADXL345_ADDR,I2C_WRITE);
  sw_adxl.writeI2C(reg);
  sw_adxl.writeI2C(data);
  sw_adxl.stopI2C();
  delay(1);
}
