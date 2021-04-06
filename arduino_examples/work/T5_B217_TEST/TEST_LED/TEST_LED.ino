#include<OLED.h>
OLED myOLED;
#define LED 3
void setup() 
{
    myOLED.begin(FONT_8x16);
    myOLED.print("B217");

  //-----------------
    pinMode(LED,OUTPUT);
    digitalWrite(LED,0);
 

}

void loop() 
{
    
    analogWrite(LED,30);

}
