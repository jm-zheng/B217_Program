//------------------------------------------------------------------------------
#include <OLED.h>

OLED myOLED;

//------------------------------------------------------------------------------
void setup()  
{
  pinMode(13, OUTPUT); // LED
  pinMode(A0, OUTPUT); // BEEP
  // set the data rate for the SoftwareSerial port
  myOLED.begin(FONT_8x16); //FONT_6x8
  myOLED.println("Hello, world?");
  myOLED.println("Blink D13 LED");
  myOLED.println("2017/11/01 Ok.");
  digitalWrite(A0, HIGH);   // turn the BEEP on (HIGH is the voltage level)
  delay(100);
  digitalWrite(A0, LOW);    // turn the BEEP off by making the voltage LOW
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  myOLED.setPosi(6,0);
  myOLED.print("D13 LED -> ON ");
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);
  myOLED.setPosi(6,0);
  myOLED.print("D13 LED -> OFF");
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}

