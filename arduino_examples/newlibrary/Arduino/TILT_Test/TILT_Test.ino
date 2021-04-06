//------------------------------------------------------------------------------
#include <OLED.h>
OLED myOLED;

//------------------------------------------------------------------------------
#define NOT_AN_INTERRUPT -1
const byte interruptPin =3;
const byte ledPin = 13;
volatile int count;

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("TILT Test");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  pinMode(ledPin, OUTPUT);
}

//------------------------------------------------------------------------------
void loop()
{
  Serial.print("Count= ");
  Serial.print(count);
  myOLED.print("Count = ");
  myOLED.println(count);      
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

void blink() 
{
  count++;
}

