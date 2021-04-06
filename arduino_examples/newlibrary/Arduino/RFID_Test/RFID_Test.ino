//------------------------------------------------------------------------------
#include <SPI.h>
#include <SoftwareSPI.h>
#include <RFID_SIC.h>
#include <OLED.h>

OLED myOLED;

//RDID_SIC SPI Setting Pin
#define SIC_CS        10 //CS
#define SIC_SCK       13 //SCK
#define SIC_MISO      12 //MISO
#define SIC_MOSI      11 //MOSI

#define BUZZER_PIN    A0

RFID_SIC sic;

//------------------------------------------------------------------------------
// setup
//------------------------------------------------------------------------------
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("RFID Test");
  myOLED.begin(FONT_8x16); //FONT_6x8
  myOLED.println("RFID Test");    
  sic.begin(SIC_CS,SIC_SCK,SIC_MISO,SIC_MOSI);
  sic.sicInit();
 
  pinMode(BUZZER_PIN, OUTPUT);  
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
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
        Beep();
        myOLED.print("UID:[0x");  
        Serial.print("UID:[0x");
        for(i=0;i<4;i++)
        {
          if (sic.sicUID[3-i] < 0x10)
          {
            Serial.print('0');
            myOLED.print('0');  
          }
          Serial.print(sic.sicUID[3-i],HEX);
          myOLED.print(sic.sicUID[3-i],HEX);  
        }
        Serial.println("]");
        myOLED.println("]");  
      }
    }
  }
  delay(100);
}


void Beep() 
{
  digitalWrite(BUZZER_PIN, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(300);               // wait for a second
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
}


