//------------------------------------------------------------------------------
// SPI.h
//------------------------------------------------------------------------------
#ifndef _SPI_H
#define _SPI_H

#include "HT32IO.h"

// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT 1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION 1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect an LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

#ifndef LSBFIRST
#define LSBFIRST 0
#endif 
#ifndef MSBFIRST
#define MSBFIRST 1
#endif 

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR


class SPISettings
{
	public:
		SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
		{
				//init_MightInline(clock, bitOrder, dataMode);
		}
		SPISettings()
		{
				//init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
		}
	private:
		friend class SPIClass;
};


class SPIClass
{
	public:
		// Initialize the SPI library
		static void begin();

		// If SPI is used from within an interrupt, this function registers
		// that interrupt with the SPI library, so beginTransaction() can
		// prevent conflicts.  The input interruptNumber is the number used
		// with attachInterrupt.  If SPI is used from a different interrupt
		// (eg, a timer), interruptNumber should be 255.
		static void usingInterrupt(uint8_t interruptNumber);
		// And this does the opposite.
		static void notUsingInterrupt(uint8_t interruptNumber);
		// Note: the usingInterrupt and notUsingInterrupt functions should
		// not to be called from ISR context or inside a transaction.
		// For details see:
		// https://github.com/arduino/Arduino/pull/2381
		// https://github.com/arduino/Arduino/pull/2449

		// Before using SPI.transfer() or asserting chip select pins,
		// this function is used to gain exclusive access to the SPI bus
		// and configure the correct settings.
		static void beginTransaction(SPISettings settings){

		}

		// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
		static uint8_t transfer(uint8_t data)
		{
				//SPDR = data;
				//while (!(SPSR &_BV(SPIF)))
				//	;
				// wait
				//return SPDR;
				return 0;
		}
		static uint16_t transfer16(uint16_t data)
		{
				//				union
				//				{
				//						uint16_t val;
				//						struct
				//						{
				//								uint8_t lsb;
				//								uint8_t msb;
				//						};
				//				}
				//				in, out;
				//				in.val = data;
				//				return out.val;
				return 0;
		}
		static void transfer(void *buf, size_t count)
		{
				if (count == 0)
				{
						return ;
				}
				//uint8_t *p = (uint8_t*)buf;
				//				SPDR =  *p;
				//				while (--count > 0)
				//				{
				//						uint8_t out = *(p + 1);
				//						while (!(SPSR &_BV(SPIF)))
				//							;
				//						uint8_t in = SPDR;
				//						SPDR = out;
				//						*p++ = in;
				//				}
				//				while (!(SPSR &_BV(SPIF)))
				//					;
				//				*p = SPDR;
		}
		// After performing a group of transfers and releasing the chip select
		// signal, this function allows others to access the SPI bus
		static void endTransaction(void){}

		// Disable the SPI bus
		static void end();

		// This function is deprecated.  New applications should use
		// beginTransaction() to configure SPI settings.
		static void setBitOrder(uint8_t bitOrder)
		{
				if (bitOrder == LSBFIRST)
				{
						//SPCR |= _BV(DORD);
				}
				else
				{
						//SPCR &= ~(_BV(DORD));
				}
		}
		// This function is deprecated.  New applications should use
		// beginTransaction() to configure SPI settings.
		static void setDataMode(uint8_t dataMode)
		{
				//SPCR = (SPCR &~SPI_MODE_MASK) | dataMode;
		}
		// This function is deprecated.  New applications should use
		// beginTransaction() to configure SPI settings.
		static void setClockDivider(uint8_t clockDiv)
		{
				//SPCR = (SPCR &~SPI_CLOCK_MASK) | (clockDiv &SPI_CLOCK_MASK);
				//SPSR = (SPSR &~SPI_2XCLOCK_MASK) | ((clockDiv >> 2) &SPI_2XCLOCK_MASK);
		}
		// These undocumented functions should not be used.  SPI.transfer()
		// polls the hardware flag which is automatically cleared as the
		// AVR responds to SPI's interrupt
		inline static void attachInterrupt()
		{
				//SPCR |= _BV(SPIE);
		}
		inline static void detachInterrupt()
		{
				//SPCR &= ~_BV(SPIE);
		}

	private:
		static uint8_t initialized;
		static uint8_t interruptMode; // 0=none, 1=mask, 2=global
		static uint8_t interruptMask; // which interrupts to mask
		static uint8_t interruptSave; // temp storage, to restore state
};

extern SPIClass SPI;

#endif
