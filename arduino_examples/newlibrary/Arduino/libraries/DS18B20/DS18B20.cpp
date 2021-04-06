//------------------------------------------------------------------------------
// DS18B20.cpp
//------------------------------------------------------------------------------
#include "DS18B20.h"

//------------------------------------------------------------------------------
void DS18B20::begin(uint8_t pin)
{
	ow_ds.begin(pin);
}

//------------------------------------------------------------------------------
float DS18B20::readTemperature(void)
{
  int16_t raw;
	float celsius;

  ow_ds.reset();
  ow_ds.skip();
  ow_ds.write(DS1820_CONVERT_T); // convert T command
  delay(750); // 750ms conversion time
  ow_ds.reset();
  ow_ds.skip();
  ow_ds.write(DS1820_READ_SCRATCHPAD); // read scratchpad command
  raw = ow_ds.read();
  raw = (ow_ds.read()<<8)|raw;
  celsius = (float)raw / 16.0;
	return celsius;
}

//------------------------------------------------------------------------------
void DS18B20::startConvertTemperature(void)
{
  ow_ds.reset();
  ow_ds.skip();
  ow_ds.write(DS1820_CONVERT_T); // convert T command
}

//------------------------------------------------------------------------------
//boolean S == Scale.  True == Farenheit; False == Celcius
//------------------------------------------------------------------------------
float DS18B20::getConvertTemperature(void)
{
  int16_t raw;
	float celsius;
	
  ow_ds.reset();
  ow_ds.skip();
  ow_ds.write(DS1820_READ_SCRATCHPAD); // read scratchpad command
  raw = ow_ds.read();
  raw = (ow_ds.read()<<8)|raw;
  celsius = (float)raw / 16.0;
	return celsius;
}




