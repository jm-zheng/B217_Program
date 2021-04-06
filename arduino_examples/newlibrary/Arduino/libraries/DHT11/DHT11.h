//------------------------------------------------------------------------------
// DHT11.h
//------------------------------------------------------------------------------
#ifndef DHT11_H
#define DHT11_H
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 		85

//------------------------------------------------------------------------------
class DHT11
{
private:
	uint8_t data[6];
	uint8_t _pin;
	boolean read(void);
public:
	void begin(uint8_t pin);
	uint8_t readTemperature(void);
	uint8_t readHumidity(void);
	void startConvert(void);
	boolean getConvert(uint8_t *humidity,uint8_t *temperature);
};
#endif
