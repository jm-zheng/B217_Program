//------------------------------------------------------------------------------
// MLX90614.cpp
//------------------------------------------------------------------------------
#include "MLX90614.h"

//------------------------------------------------------------------------------
void MLX90614::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	sw_i2c.begin(sda_pin,scl_pin);
}

double MLX90614::readObjectTempF(void) {
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}


double MLX90614::readAmbientTempF(void) {
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double MLX90614::readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}


double MLX90614::readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float MLX90614::readTemp(uint8_t reg) {
  float temp;
  
  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

//------------------------------------------------------------------------------
uint16_t MLX90614::read16(uint8_t reg)
{
  uint16_t val;

  sw_i2c.startI2C(MLX90614_I2CADDR,I2C_WRITE);
  sw_i2c.writeI2C(reg);
  sw_i2c.restartI2C(MLX90614_I2CADDR,I2C_READ);
  val = sw_i2c.readI2C(0);
  val += (sw_i2c.readI2C(1)<<8);
  sw_i2c.stopI2C();
	
  return val;
}

//------------------------------------------------------------------------------
void MLX90614::write16(uint8_t reg, uint16_t data)
{     
  sw_i2c.startI2C(MLX90614_I2CADDR,I2C_WRITE);
  sw_i2c.writeI2C(reg);
  sw_i2c.writeI2C((data>>8));
  sw_i2c.writeI2C((data&0xff));
  sw_i2c.stopI2C();
  delay(1);
}
