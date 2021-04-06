//------------------------------------------------------------------------------
// RFID_SIC_Test.ino
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
  sic.sicInit();
  if(sic.ISO14443A_Request()==1)
  {
    if(sic.ISO14443A_Anticoll(0x93)==1)
    {
      if(sic.ISO14443A_Select(0x93)==1)
      {
        Serial.print("UID:[0x");
        for(i=0;i<4;i++)
        {
          if (sic.sicUID[3-i] < 0x10)
          {
            Serial.print('0');
          }
          Serial.print(sic.sicUID[3-i],HEX);
        }
        Serial.println("]");
      }
    }
  }
  delay(100);
}

