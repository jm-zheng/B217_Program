//------------------------------------------------------------------------------
// SoftwareSPI.h
//------------------------------------------------------------------------------
#ifndef _SOFTWARE_SPI_H
#define _SOFTWARE_SPI_H

//------------------------------------------------------------------------------
class SoftwareSPI
{
public:
	uint8_t transfer(uint8_t _data)
	{
		uint8_t readData;
		uint8_t writeData;
		uint8_t builtReturn;
		uint8_t mask;

		if (_bitOrder == MSBFIRST)
		{
			mask = 0x80;
		}
		else
		{
			mask = 0x01;
		}
		builtReturn = 0;
		readData = 0;

		for (uint8_t count = 0; count < 8; count++)
		{
			if (_data &mask)
			{
				writeData = HIGH;
			}
			else
			{
				writeData = LOW;
			}

			if (_clockPhase == 1)
			{
				// CPHA=1, miso/mosi changing state now
				digitalWrite(_mosi, writeData);
				digitalWrite(_sck, ~_clockPolarity);
				//delayPeriod();

				// CPHA=1, miso/mosi stable now
				readData = digitalRead(_miso);
				digitalWrite(_sck, _clockPolarity);
				//delayPeriod();
			}
			else
			{
				// CPHA=0, miso/mosi changing state now
				digitalWrite(_mosi, writeData);
				digitalWrite(_sck, _clockPolarity);
				//delayPeriod();

				// CPHA=0, miso/mosi stable now
				readData = digitalRead(_miso);
				digitalWrite(_sck, ~_clockPolarity);
				//delayPeriod();
			}

			if (_bitOrder == MSBFIRST)
			{
				mask >>= 1;
				builtReturn |= (readData << (7-count));
			}
			else
			{
				mask <<= 1;
				builtReturn |= (readData << count);
			}
		}

		digitalWrite(_sck, _clockPolarity);

		return builtReturn;
	}

	// Not implemented.
	void attachInterrupt(){}

	// Not implemented.
	void detachInterrupt(){}

	// Initialise the SPI library
	void begin()
	{
		_clockPolarity = LOW;
		_clockPhase = 0;
		_bitOrder = MSBFIRST;
		_delayCounts = SPI_CLOCK_DIV4;
	}

	// Disables the SPI bus usually, in this case
	// there is no hardware controller to disable.
	void end(){}

	// Sets the pins used by this SoftwareSPIClass instance.
	// \param[in] miso master in slave out pin used
	// \param[in] mosi master out slave in pin used
	// \param[in] sck clock pin used
	void setPins(uint8_t sck, uint8_t miso, uint8_t mosi)
	{
		_miso = miso;
		_mosi = mosi;
		_sck = sck;

		pinMode(_miso, INPUT);
		pinMode(_mosi, OUTPUT);
		pinMode(_sck, OUTPUT);
		digitalWrite(_sck, _clockPolarity);
	}

	// Sets the bit order the SPI interface will use
	// Sets the order of the bits shifted out of and into the SPI bus, either 
	// LSBFIRST (least-significant bit first) or MSBFIRST (most-significant bit first). 
	// \param[in] bitOrder Bit order to be used: LSBFIRST or MSBFIRST
	void setBitOrder(uint8_t bitOrder)
	{
		_bitOrder = bitOrder;
	}

	// Sets the SPI data mode: that is, clock polarity and phase. 
	// See the Wikipedia article on SPI for details. 
	// \param[in] mode The mode to use: SPI_MODE0 SPI_MODE1 SPI_MODE2 SPI_MODE3 
	void setDataMode(uint8_t mode)
	{
		if (mode == SPI_MODE0 || mode == SPI_MODE1)
		{
			_clockPolarity = LOW;
		}
		else
		{
			_clockPhase = HIGH;
		}

		if (mode == SPI_MODE0 || mode == SPI_MODE2)
		{
			_clockPhase = 0;
		}
		else
		{
			_clockPhase = 1;
		}

		digitalWrite(_sck, _clockPolarity);
	}

	// Sets the SPI clock divider relative to the system clock. 
	// In this case, the software SPI does a basic delay in a loop for whatever
	// rate is set too.
	// The default setting is SPI_CLOCK_DIV4, 
	// \param[in] rate The data rate to use: one of SPI_CLOCK_
	void setClockDivider(uint8_t rate)
	{
		_delayCounts = rate;
	}

private:
	// Delay routine for bus timing.
	void delayPeriod()
	{
		for (volatile uint8_t count; count < _delayCounts; count++)
		{
			__asm__ __volatile__("nop");
		}
	}

	uint8_t _miso;
	uint8_t _mosi;
	uint8_t _sck;
	uint8_t _bitOrder;
	uint8_t _delayCounts;
	uint8_t _clockPolarity;
	uint8_t _clockPhase;
};

#endif
