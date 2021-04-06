//------------------------------------------------------------------------------
// DS18B20.h
//------------------------------------------------------------------------------
#ifndef DS18B20_H
#define DS18B20_H


#include <OneWire.h>

// list of commands DS18B20
#define DS1820_SKIP_ROM             0xCC
#define DS1820_CONVERT_T            0x44
#define DS1820_READ_SCRATCHPAD      0xBE

//------------------------------------------------------------------------------
class DS18B20
{
	private:
		OneWire ow_ds;
	public:
		void begin(uint8_t pin);
		float readTemperature(void);
		void startConvertTemperature(void);
		float getConvertTemperature(void);
};
#endif
