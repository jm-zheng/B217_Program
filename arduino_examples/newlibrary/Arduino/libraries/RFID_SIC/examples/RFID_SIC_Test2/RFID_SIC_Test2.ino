//------------------------------------------------------------------------------
// RFID_SIC_Test2.ino
//------------------------------------------------------------------------------
#include <SPI.h>
#include <SoftwareSPI.h>
#include <RFID_SIC.h>

//RDID_SIC SPI Setting Pin
#define SIC_CS        P2_0 //CS
#define SIC_SCK       P1_5 //SCK
#define SIC_MISO      P1_6 //MISO
#define SIC_MOSI      P1_7 //MOSI

RFID_SIC sic;

//------------------------------------------------------------------------------
// setup
//------------------------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("RFID_SIC Test");
  sic.begin(SIC_CS,SIC_SCK,SIC_MISO,SIC_MOSI);
  //sic.begin(SIC_CS);
  sic.sicInit();
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop(void)
{
  uint8_t i;
  uint16_t type;

  type=sic.ISO14443A_getUID();
  if(type>0)
  {
    Serial.print("CHIP:[0x");
    Serial.print(type,HEX);
    Serial.print("] , UID:[0x");
    for(i=0;i<7;i++)
    {
      if (sic.sicUID[6-i] < 0x10)
      {
        Serial.print('0');
      }
      Serial.print(sic.sicUID[6-i],HEX);
    }
    Serial.println("]");
  }
  delay(100);
}

