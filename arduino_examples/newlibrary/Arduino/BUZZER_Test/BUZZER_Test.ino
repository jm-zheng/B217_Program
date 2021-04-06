//------------------------------------------------------------------------------
#include <OLED.h>
OLED myOLED;

#define BUZZER_PIN    A0

//------------------------------------------------------------------------------
void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);  
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("BUZZER Test");
}

//------------------------------------------------------------------------------
void loop() 
{
  Beep();
  myOLED.println("Beep");
  delay(500);
  BeepBeep();
  myOLED.println("Beep Beep");
  delay(500);
}

//------------------------------------------------------------------------------
void Beep() 
{
  digitalWrite(BUZZER_PIN, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(300);               // wait for a second
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
}

//------------------------------------------------------------------------------
void BeepBeep() 
{
  digitalWrite(BUZZER_PIN, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
  delay(200);               // wait for a second
  digitalWrite(BUZZER_PIN, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW
}

