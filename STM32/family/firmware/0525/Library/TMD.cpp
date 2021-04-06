//------------------------------------------------------------------------------
// TMD.cpp
//------------------------------------------------------------------------------
#include "TMD.h"

//------------------------------------------------------------------------------
void TMD::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	sw_tmd.begin(sda_pin,scl_pin);
  //setReg(REG_BW_RATE, BW_RATE_100); // Set ON and Sample 100 Hz
	//setReg(REG_POWER_CTL,PW_MEASURE);
}

//------------------------------------------------------------------------------
uint16_t TMD::getData(uint8_t reg)
{
  uint16_t val;

  sw_tmd.startI2C(TMD_ADDR,I2C_WRITE);
  sw_tmd.writeI2C(reg);
  sw_tmd.restartI2C(TMD_ADDR,I2C_READ);
  val = sw_tmd.readI2C(0);
  val += (sw_tmd.readI2C(1)<<8);
  sw_tmd.stopI2C();
	
  return val;
}

//------------------------------------------------------------------------------
uint8_t TMD::getReg(uint8_t reg)
{
  uint8_t val;

  sw_tmd.startI2C(TMD_ADDR,I2C_WRITE);
  sw_tmd.writeI2C(reg);
  sw_tmd.restartI2C(TMD_ADDR,I2C_READ);
  val = sw_tmd.readI2C(0);
  sw_tmd.stopI2C();
  return val;
}

//------------------------------------------------------------------------------
void TMD::setReg(uint8_t reg, uint8_t data)
{     
  sw_tmd.startI2C(TMD_ADDR,I2C_WRITE);
  sw_tmd.writeI2C(reg);
  sw_tmd.writeI2C(data);
  sw_tmd.stopI2C();
  delay(1);
}
