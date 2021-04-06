//------------------------------------------------------------------------------
// CCS811.h
//------------------------------------------------------------------------------
#ifndef CCS811_h
#define CCS811_h

#include "Nano030.h"
#include "SoftwareWire.h"

//------------------------------------------------------------------------------
#define CCS811_ADDR     0x5A
#define TH_ADDR     		0x40

//------------------------------------------------------------------------------
// Registers for SI7006
#define MEAS_HUMIDITY   	    0xF5
#define MEAS_TEMPERATURE      0xF3

//------------------------------------------------------------------------------
// Registers for CCS811
#define STATUS          			0x00
#define MEAS_MODE       			0x01
#define ALG_RESULT_DATA 			0x02
#define ENV_DATA        			0x05
#define APP_START       			0xF4
#define HW_ID           			0x20
#define ERROR_ID        			0xE0
#define SW_RESET        			0xFF

class CCS811
{
  private:
	  SoftwareWire sw_ccs;
  public:
  	void begin(uint8_t sda_pin,uint8_t scl_pin);
    byte readHW_ID(void);
		byte readStatus(void);
    int readTVOC(void);
    int readCO2(void);
    int readHUMIDITY(void);
    int readTEMPERATURE(void);
    void getData(void);
    int TVOC, CO2;
    int HUMIDITY, TEMPERATURE;
};

#endif
