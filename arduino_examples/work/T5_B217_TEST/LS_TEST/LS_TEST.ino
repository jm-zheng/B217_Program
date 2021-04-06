#include <OLED.h>
OLED myOLED;
#define LS A0

void setup() 
{
  myOLED.begin(FONT_8x16);
  myOLED.print("B217");
  pinMode(LS,INPUT);
  
}

void loop() 
{
    int val= analogRead(LS);
    myOLED.setPosi(2,0);
    myOLED.print(val);
    ZigBee.print(val);
    delay(500);

  
}
