//------------------------------------------------------------------------------
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 5; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

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
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 180);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);
  myOLED.print("sensor = ");
  myOLED.println(sensorValue);
  delay(100);
}

