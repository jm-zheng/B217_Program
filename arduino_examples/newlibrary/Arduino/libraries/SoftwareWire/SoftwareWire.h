//------------------------------------------------------------------------------
// SoftwareWire.h
//------------------------------------------------------------------------------
#ifndef SOFTWARE_WIRE_H
#define SOFTWARE_WIRE_H

#include <avr/io.h>
#include <Arduino.h>

#define I2C_READ 				1
#define I2C_WRITE 		  0

#define BUFFER_LENGTH 	16

//------------------------------------------------------------------------------
class SoftwareWire
{
public:
	void begin(uint8_t pinSDA, uint8_t pinSCL);
	void beginTransmission(uint8_t address);
	uint8_t endTransmission(void);
	virtual size_t write(uint8_t data);
	virtual size_t write(const uint8_t *data, size_t length);
	uint8_t requestFrom(uint8_t address, uint8_t length);
	virtual int available(void);
	virtual int read(void);
	virtual int peek(void);

	uint8_t readI2C(uint8_t last = false);
	uint8_t readI2C(uint8_t *data, uint8_t length);
	bool restartI2C(uint8_t address, uint8_t rw);
	bool startI2C(uint8_t address, uint8_t rw);
	void stopI2C();
	bool writeI2C(uint8_t data);
	bool writeI2C(uint8_t *data, size_t length);

private:
	uint8_t _pinSDA, _pinSCL;
	static uint8_t txAddress;
	static uint8_t rxBuffer[];
	static uint8_t rxBufferIndex;
	static uint8_t rxBufferLength;
	static uint8_t txBuffer[];
	static uint8_t txBufferIndex;
	static uint8_t txBufferLength;
	static uint8_t transmitting;
};
#endif
