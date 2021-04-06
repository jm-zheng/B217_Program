//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

//SoftwareSerial mySerial(A5, A4); // RX, TX
//SoftwareSerial mySerial(11, 12); // RX, TX
SoftwareSerial mySerial(A1, A2); // RX, TX

//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  Serial.begin(9600);
  myOLED.println("Gateway A1A2");
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available())
  {
    mySerial.write(Serial.read());    
  }
}

