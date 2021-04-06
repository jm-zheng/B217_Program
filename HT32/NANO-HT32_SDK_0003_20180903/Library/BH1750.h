//------------------------------------------------------------------------------
// BH1750.h
//------------------------------------------------------------------------------
#ifndef BH1750_H
#define BH1750_H

#include "HT32IO.h"
#include "SoftwareWire.h"

#define BH1750_I2CADDR		0x23

// Uncomment, to enable debug messages
// #define BH1750_DEBUG

// No active state
#define BH1750_POWER_DOWN 0x00

// Wating for measurement command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

class BH1750 {

  public:
    enum Mode
    {
      UNCONFIGURED = 0,
      // Measurement at 1lx resolution. Measurement time is approx 120ms.
      CONTINUOUS_HIGH_RES_MODE  = 0x10,
      // Measurement at 0.5lx resolution. Measurement time is approx 120ms.
      CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
      // Measurement at 4lx resolution. Measurement time is approx 16ms.
      CONTINUOUS_LOW_RES_MODE = 0x13,
      // Measurement at 1lx resolution. Measurement time is approx 120ms.
      ONE_TIME_HIGH_RES_MODE = 0x20,
      // Measurement at 0.5lx resolution. Measurement time is approx 120ms.
      ONE_TIME_HIGH_RES_MODE_2 = 0x21,
      // Measurement at 1lx resolution. Measurement time is approx 120ms.
      ONE_TIME_LOW_RES_MODE = 0x23
    };

		void begin(uint8_t sda_pin,uint8_t scl_pin);
    uint16_t readLightLevel(void);

  private:
		SoftwareWire sw_bh;
};

#endif
