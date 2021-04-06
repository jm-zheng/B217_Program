//------------------------------------------------------------------------------
// DHT12.cpp
//------------------------------------------------------------------------------
#include "DHT12.h"

//------------------------------------------------------------------------------
void DHT12::begin(uint8_t pin)
{
	_pin = pin;
	// set up the pins!
	pinMode(_pin, INPUT_PULLUP);
}

//------------------------------------------------------------------------------
float DHT12::readTemperature(void)
{
	float c;

  delay(250); // wait Convert
	startConvert();
	delay(20); // wait DHT12
	if (read())
	{
		c = data[2];
    c += ((float)data[3])/10.0;
		return c;
	}
	return 0;
}

//------------------------------------------------------------------------------
float DHT12::readHumidity(void)
{
	float h;

  delay(250); // wait Convert
	startConvert();
	delay(20); // wait DHT12
	if (read())
	{
			h = data[0];
      h+=  ((float)data[1])/10.0;
			return h;
	}
	return 0;
}

//------------------------------------------------------------------------------
void DHT12::startConvert(void)
{
	// now pull it low for ~20 milliseconds
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
}

//------------------------------------------------------------------------------
boolean DHT12::getConvert(float *humidity,float *temperature)
{
	if (read())
	{
	 	*humidity = data[0];
    *humidity+=  ((float)data[1])/10.0;
		*temperature = data[2];
    *temperature+=  ((float)data[3])/10.0;
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
boolean DHT12::read(void)
{
	uint8_t counter = 0;
	uint8_t j = 0, i;
	uint8_t laststate = HIGH;
	
	noInterrupts();
	digitalWrite(_pin, HIGH);
	delayMicroseconds(40);
	pinMode(_pin, INPUT_PULLUP);
	// read in timings
	for (i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(_pin) == laststate)
		{
			counter++;
			delayMicroseconds(3);
			if (counter == 255)
			{
				break;
			}
		}
		laststate = digitalRead(_pin);

		if (counter == 255)
		{
			break;
		}

		// ignore first 3 transitions
		if ((i >= 4) && (i % 2 == 0))
		{
			// shove each bit into the storage bytes
			data[j / 8] <<= 1;
			if (counter > 6)
			{
				data[j / 8] |= 1;
			}
			j++;
		}

	}
	interrupts();

	// Serial.println(j, DEC);
	// Serial.print(data[0], HEX); Serial.print(", ");
	// Serial.print(data[1], HEX); Serial.print(", ");
	// Serial.print(data[2], HEX); Serial.print(", ");
	// Serial.print(data[3], HEX); Serial.print(", ");
	// Serial.print(data[4], HEX); Serial.print(" =? ");
	// Serial.println(data[0] + data[1] + data[2] + data[3], HEX);

	// check we read 40 bits and that the checksum matches
	if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) &0xFF)))
	{
		return true;
	}

	return false;

}
