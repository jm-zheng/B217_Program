//------------------------------------------------------------------------------
// CCS811.cpp
//------------------------------------------------------------------------------
#include "CCS811.h"
#include "OLED.h" // OLED
extern OLED myOLED;
//------------------------------------------------------------------------------
void CCS811::begin(uint8_t sda_pin,uint8_t scl_pin)
{
	byte status;
	sw_ccs.begin(sda_pin,scl_pin);

  CO2 = 400;
  TVOC = 0;
	
  delay(5); 
	
  sw_ccs.beginTransmission(TH_ADDR);
  sw_ccs.endTransmission();	
	
  while(sw_ccs.available())
  {
    sw_ccs.read();
  }
	
  //sw_ccs.beginTransmission(CCS811_ADDR); 
  //sw_ccs.write(SW_RESET);
  //sw_ccs.write(0x11);
  //sw_ccs.write(0xE5);
  //sw_ccs.write(0x72);
  //sw_ccs.write(0x8A);
  //sw_ccs.endTransmission();
	//delay(200); 
	
	status = readHW_ID();
  if(status != 0x81)  // this is the expected hardware ID
  {
    return;
  }
	
	delay(10); 
  status = readStatus();
  if(status != 0x10)  // this is the expected hardware ID
  {
    return;
  }
	delay(10); 
  sw_ccs.beginTransmission(CCS811_ADDR); // least significant bit indicates write (0) or read (1)
  sw_ccs.write(APP_START);
  sw_ccs.endTransmission();

	delay(10); 
  sw_ccs.beginTransmission(CCS811_ADDR);
  sw_ccs.write(MEAS_MODE);
  sw_ccs.write(0x10);  // constant power mode, IAQ measurement every second
  sw_ccs.endTransmission();

}

//------------------------------------------------------------------------------
byte CCS811::readHW_ID(void)
{
  while(sw_ccs.available())
  {
    sw_ccs.read();
  }
	
  sw_ccs.beginTransmission(CCS811_ADDR); // least significant bit indicates write (0) or read (1)
  sw_ccs.write(HW_ID);
  sw_ccs.endTransmission();

  delay(2);
  sw_ccs.requestFrom(CCS811_ADDR, (uint8_t)1);
  byte hw_id  = sw_ccs.read();
  return hw_id;
}

//------------------------------------------------------------------------------
byte CCS811::readStatus(void)
{
  while(sw_ccs.available())
  {
    sw_ccs.read();
  }
	
  sw_ccs.beginTransmission(CCS811_ADDR); // least significant bit indicates write (0) or read (1)
  sw_ccs.write(STATUS);
  sw_ccs.endTransmission();

  delay(2);
  sw_ccs.requestFrom(CCS811_ADDR, (uint8_t)1);
  byte status  = sw_ccs.read();
  return status;
}

//------------------------------------------------------------------------------
void CCS811::getData(void)
{
  int buffer[4];
	int tvoc, co2;
	sw_ccs.beginTransmission(TH_ADDR);
  sw_ccs.write(MEAS_HUMIDITY);    // reading ALG_RESULT_DATA clears DATA_READY bit in 0x00
  sw_ccs.endTransmission();

  delay(20);
  sw_ccs.requestFrom(TH_ADDR, (uint8_t)2);
  if(sw_ccs.available() == 2)
  {
    buffer[0] = sw_ccs.read();
    buffer[1] = sw_ccs.read();
  }

  sw_ccs.beginTransmission(TH_ADDR);
  sw_ccs.write(MEAS_TEMPERATURE);    // reading ALG_RESULT_DATA clears DATA_READY bit in 0x00
  sw_ccs.endTransmission();
  delay(20);
  sw_ccs.requestFrom(TH_ADDR, (uint8_t)2);
  if(sw_ccs.available() == 2)
  {
    buffer[2] = sw_ccs.read();
    buffer[3] = sw_ccs.read();
  }
	
  HUMIDITY = ((uint8_t)buffer[0] << 8) + buffer[1];
  TEMPERATURE = ((uint8_t)buffer[2] << 8) + buffer[3];
	

  while(sw_ccs.available())
  {
    sw_ccs.read();
  }
	
  sw_ccs.beginTransmission(CCS811_ADDR);
  sw_ccs.write(ALG_RESULT_DATA); 
  sw_ccs.endTransmission();
  delay(10);
  sw_ccs.requestFrom(CCS811_ADDR, (uint8_t)4);
  delay(1);
  if(sw_ccs.available() == 4)
  {
    for(int i=0; i<4; i++)
    {
      buffer[i] = sw_ccs.read();
    }
  }
  co2 = ((uint8_t)buffer[0] << 8) + buffer[1];
  tvoc = ((uint8_t)buffer[2] << 8) + buffer[3];
	
	if(tvoc<10000 && co2<10000)
	{
		CO2 = co2;
		TVOC = tvoc;
	}
}


//------------------------------------------------------------------------------
int CCS811::readTVOC(void)
{
  return TVOC;
}

//------------------------------------------------------------------------------
int CCS811::readCO2(void)
{
  return CO2;
}

//------------------------------------------------------------------------------
int CCS811::readHUMIDITY(void)
{
  return HUMIDITY;
}

//------------------------------------------------------------------------------
int CCS811::readTEMPERATURE(void)
{
  return TEMPERATURE;
}
