//------------------------------------------------------------------------------
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

//------------------------------------------------------------------------------
void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  myOLED.begin(FONT_8x16); //FONT_6x8
}

void loop() 
{
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  myOLED.print("sensor = ");
  myOLED.println(sensorValue);
  delay(100);
}

