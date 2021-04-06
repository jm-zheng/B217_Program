//------------------------------------------------------------------------------
// DHT12.h
//------------------------------------------------------------------------------
#ifndef DHT12_H
#define DHT12_H
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 		85

//------------------------------------------------------------------------------
class DHT12
{
private:
	uint8_t data[6];
	uint8_t _pin;
	boolean read(void);
public:
	void begin(uint8_t pin);
	float readTemperature(void);
	float readHumidity(void);
	void startConvert(void);
	boolean getConvert(float *humidity,float *temperature);
};
#endif
