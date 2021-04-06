//---------參考版-------------

#include<OLED.h>
OLED myOLED ;
//-----------------------
#define key1 2
#define key2 6

#define BUTTON1_PUSH 1
#define BUTTON2_PUSH 2

void setup() 
{
    myOLED.begin(FONT_8x16);
   //-----------------------
   pinMode(key1,INPUT_PULLUP);
   pinMode(key2,INPUT_PULLUP);

}

void loop() 
{

  
}


void ButtonStatus()
{
    if(digitalRead(key1)==LOW)
    {
        return BUTTON1_PUSH;
    }
    if(digitalRead(key2)==LOW)
    {
        return BUTTON2_PUSH;
    }
      return 0;
}

