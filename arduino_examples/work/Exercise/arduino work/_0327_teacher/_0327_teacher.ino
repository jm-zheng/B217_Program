#include<OLED.h>
OLED myOLED;


#define button1 2
#define button2 6

int bt_flag;
void setup() 
{
    myOLED.begin(FONT_8x16);
    pinMode(button1,INPUT_PULLUP);
    pinMode(button2,INPUT_PULLUP);


}

void loop() 
{
      int a = Button_status();
      if(a ==1)
      {
         bt_flag += 1;
      }
      else if(a ==2)
      {
         bt_flag -= 1;
      }
      myOLED.setPosi(0,0);
      myOLED.print(bt_flag);
}
uint8_t Button_status()
{    
  int b;
    if (digitalRead(button1) ==LOW)
    {
      while(digitalRead(button1) == LOW)
          {
            b += 1;
            delay(100);
          }
             if(b < 5)
          {
            return 1;
          }
          else if (b > 5)
          {
            return 2;
          }
    }

    
    return  0;
    
}

