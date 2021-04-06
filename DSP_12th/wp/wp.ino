#include<OLED.h>
OLED myOLED;
#define wp A3
#define key 2
void setup() {
  pinMode(wp,INPUT_PULLUP);
 pinMode(key,INPUT_PULLUP);
  myOLED.begin(FONT_8x16); 
  
}

void loop() 
{
      myOLED.setPosi(2,0);
      myOLED.print("B217");
     int c=  digitalRead(wp);
     //int c=  digitalRead(key);
      if(c==LOW)
          {
            myOLED.setPosi(4,0);
             myOLED.print("WP");
            myOLED.print("0");
          }
          else if(c==HIGH)
          {
             myOLED.setPosi(4,0);
              myOLED.print("WP");
            myOLED.print("1");
          }

}
