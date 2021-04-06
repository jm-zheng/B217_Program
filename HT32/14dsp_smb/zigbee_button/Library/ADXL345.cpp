//------------------------------------------------------------------------------
// ADXL345.cpp
//------------------------------------------------------------------------------
#include "ADXL345.h"

//------------------------------------------------------------------------------
void ADXL345::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	sw_adxl.begin(sda_pin,scl_pin);
	//setReg(REG_OFSX,0x06);
	//setReg(REG_OFSY,0xF9);
	//setReg(REG_OFSZ,0xFC);
	//setReg(REG_THRESH_ACT,0x08);
	//setReg(REG_THRESH_INACT,0x03);
	//setReg(REG_TIME_INACT,0x02);
	//setReg(REG_ACT_INACT_CTL,0xEF);
	//setReg(REG_THRESH_FF,0x09);
	//setReg(REG_TIME_FF,0x14);	
  setReg(REG_BW_RATE, BW_RATE_100); // Set ON and Sample 100 Hz
	setReg(REG_POWER_CTL,PW_MEASURE);
}

//------------------------------------------------------------------------------
int16_t ADXL345::getData(uint8_t reg)
{
  int16_t val;

  sw_adxl.startI2C(ADXL345_ADDR,I2C_WRITE);
  sw_adxl.writeI2C(reg);
  sw_adxl.restartI2C(ADXL345_ADDR,I2C_READ);
  val = sw_adxl.readI2C(0);
  val += (sw_adxl.readI2C(1)<<8);
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
