//------------------------------------------------------------------------------
// SoftwareWire.cpp
//------------------------------------------------------------------------------
#include "SoftwareWire.h"

uint8_t SoftwareWire::rxBuffer[BUFFER_LENGTH];
uint8_t SoftwareWire::rxBufferIndex = 0;
uint8_t SoftwareWire::rxBufferLength = 0;
uint8_t SoftwareWire::txAddress = 0;
uint8_t SoftwareWire::txBuffer[BUFFER_LENGTH];
uint8_t SoftwareWire::txBufferIndex = 0;
uint8_t SoftwareWire::txBufferLength = 0;
uint8_t SoftwareWire::transmitting = 0;

#define IIC_DELAY		5 //// CCS811 = 40 , Other is 0  / MLX90614 1~23

//------------------------------------------------------------------------------
void SoftwareWire::begin(uint8_t pinSDA, uint8_t pinSCL)
{
	_pinSDA = pinSDA;
	_pinSCL = pinSCL;
	pinMode(_pinSDA, OUTPUT_OD_PULLUP);
	digitalWrite(_pinSDA, HIGH);
	pinMode(_pinSCL, OUTPUT);
	digitalWrite(_pinSCL, HIGH);
	rxBufferIndex = 0;
	rxBufferLength = 0;
	txBufferIndex = 0;
	txBufferLength = 0;
	stopI2C();
}

//------------------------------------------------------------------------------
void SoftwareWire::beginTransmission(uint8_t address)
{
	transmitting = 1;
	txAddress = address;
	txBufferIndex = 0;
	txBufferLength = 0;
}

//------------------------------------------------------------------------------
uint8_t SoftwareWire::endTransmission(void)
{
	uint8_t result = 0;
	startI2C(txAddress, I2C_WRITE);
	result += writeI2C(txBuffer, txBufferLength);
	stopI2C();
	txBufferIndex = 0;
	txBufferLength = 0;
	transmitting = 0;
	return result;
}

//------------------------------------------------------------------------------
uint8_t SoftwareWire::requestFrom(uint8_t address, uint8_t length)
{
	if (length > BUFFER_LENGTH)
	{
		length = BUFFER_LENGTH;
	}
	startI2C(address, I2C_READ);
	if (length > 1)
	{
		for (uint8_t i = 0; i < length - 1; i++)
		{
			rxBuffer[i] = readI2C(false);
		}
	}
	rxBuffer[length - 1] = readI2C(true);
	stopI2C();
	rxBufferIndex = 0;
	rxBufferLength = length;
	return length;
}

//------------------------------------------------------------------------------
size_t SoftwareWire::write(uint8_t data)
{
	if (transmitting)
	{
		if (txBufferLength >= BUFFER_LENGTH)
		{
			return 0;
		}
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		txBufferLength = txBufferIndex;
	}
	else
	{
		writeI2C(data);
	}
	return 1;
}

//------------------------------------------------------------------------------
size_t SoftwareWire::write(const uint8_t *data, size_t length)
{
	if (transmitting)
	{
		for (size_t i = 0; i < length; ++i)
		{
			write(data[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < length; ++i)
		{
			writeI2C(data[i]);
		}
	}
	return length;
}

//------------------------------------------------------------------------------
int SoftwareWire::available(void)
{
	return rxBufferLength - rxBufferIndex;
}

//------------------------------------------------------------------------------
int SoftwareWire::read(void)
{
	int value =  - 1;
	if (rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}
	return value;
}

//------------------------------------------------------------------------------
int SoftwareWire::peek(void)
{
	int value =  - 1;
	if (rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
	}
	return value;
}

//------------------------------------------------------------------------------
void SoftwareWire::stopI2C(void)
{
	digitalWrite(_pinSDA, LOW);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, HIGH);
	delayMicroseconds(IIC_DELAY);
  digitalWrite(_pinSDA, HIGH);
	delayMicroseconds(IIC_DELAY);
}

//------------------------------------------------------------------------------
uint8_t SoftwareWire::readI2C(uint8_t last)
{
	uint8_t data = 0;

	pinMode(_pinSDA, INPUT_PULLUP);
	for (uint8_t i = 0; i < 8; i++)
	{
		digitalWrite(_pinSCL, HIGH);
		delayMicroseconds(IIC_DELAY);
		data <<= 1;
		if (digitalRead(_pinSDA))
		{
			data |= 1;
		}
		digitalWrite(_pinSCL, LOW);
		delayMicroseconds(IIC_DELAY);
	}
	pinMode(_pinSDA, OUTPUT_OD_PULLUP);
	if(last)
  	digitalWrite(_pinSDA, HIGH);
	else
  	digitalWrite(_pinSDA, LOW);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, HIGH);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, LOW);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSDA, LOW);
	delayMicroseconds(IIC_DELAY);
	return data;
}

//------------------------------------------------------------------------------
uint8_t SoftwareWire::readI2C(uint8_t *data, uint8_t length)
{
	if (length > 1)
	{
		while (--length)
		{
			 *data++ = readI2C(false);
		}
	}
	*data = readI2C(true);
	return *data;
}

//------------------------------------------------------------------------------
bool SoftwareWire::writeI2C(uint8_t data)
{
	for (uint8_t i = 0; i < 8;++i)
	{
		if (data &0x80)
		{
			digitalWrite(_pinSDA, HIGH);
		}
		else
		{
			digitalWrite(_pinSDA, LOW);
		}
		data <<= 1;
		digitalWrite(_pinSCL, HIGH);
		delayMicroseconds(IIC_DELAY);
		digitalWrite(_pinSCL, LOW);
		delayMicroseconds(IIC_DELAY);
	}
	digitalWrite(_pinSCL, HIGH);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, LOW);
	delayMicroseconds(IIC_DELAY);
	return 0;
}

//------------------------------------------------------------------------------
bool SoftwareWire::startI2C(uint8_t address, uint8_t rw)
{
	digitalWrite(_pinSDA, LOW);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, LOW);
	delayMicroseconds(IIC_DELAY);
	return writeI2C((address << 1) | rw);
}

//------------------------------------------------------------------------------
bool SoftwareWire::restartI2C(uint8_t address, uint8_t rw)
{
	digitalWrite(_pinSDA, HIGH);
	delayMicroseconds(IIC_DELAY);
	digitalWrite(_pinSCL, HIGH);
	delayMicroseconds(IIC_DELAY);
	return startI2C(address, rw);
}

//------------------------------------------------------------------------------
bool SoftwareWire::writeI2C(uint8_t *data, size_t length)
{
	uint8_t result;
	for (uint8_t i = 0; i < length; i++)
	{
		result = writeI2C(data[i]);
	}
	return result;
}
