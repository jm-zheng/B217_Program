//------------------------------------------------------------------------------
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
const int waterInPin = 3;
const int ledPin =  13; 
int waterState = 0;     

//------------------------------------------------------------------------------
void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  myOLED.begin(FONT_8x16); //FONT_6x8
  pinMode(ledPin, OUTPUT);      
  pinMode(waterInPin, INPUT); 
  digitalWrite(waterInPin, HIGH);
}

void loop() 
{
  waterState = !digitalRead(waterInPin);
  myOLED.print("WATER = ");
  myOLED.println(waterState);
  delay(100);
}

