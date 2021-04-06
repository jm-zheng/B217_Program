#include<OLED.h>
OLED myOLED ;

#define key1 2
#define key2 6

#define lcd0 1
#define lcd1 2
#define lcd2 3
#define lcd3 4

uint8_t buttonflag =1 ;
void setup() 
{
  myOLED.begin(FONT_8x16);
 /* myOLED.setPosi(0,0);
  myOLED.print("LCDex1");*/
  pinMode(key1,INPUT_PULLUP);
  pinMode(key2,INPUT_PULLUP);

}

void loop() 
{
    if(buttonflag == 0)
    {
      buttonflag = 7;
    }
    else if(buttonflag <= 7 && buttonflag > 0)
      {
            if(digitalRead(key1) == LOW)
           {
              buttonflag ++;
              delay(500);
           }
           else if (digitalRead(key2) == LOW)
           {
              buttonflag --;
              delay(500);
           }
      }
    else
      {
        buttonflag = 1;
      }
    if (buttonflag == 1)
      {
        Star_option(lcd0);
        LCD_option(lcd0);
        
      }
    else if (buttonflag == 2)
      {
        Star_option(lcd1);
        LCD_option(lcd0);
      }
      else if (buttonflag == 3)
      {
        Star_option(lcd2);
        LCD_option(lcd0);
      }
      else if (buttonflag == 4)
      {
        Star_option(lcd3);
        LCD_option(lcd0);
      }
      else if (buttonflag == 5)
      {
        Star_option(lcd3);
        LCD_option(lcd1);
      }
      else if (buttonflag == 6)
      {
        Star_option(lcd3);
        LCD_option(lcd2);
      }
      else if (buttonflag == 7)
      {
        Star_option(lcd3);
        LCD_option(lcd3);
      }
      
}
void LCD_option(uint8_t Lcdflag)
{
  if (Lcdflag == 1)
  {
    myOLED.setPosi(0,8);
    myOLED.print("A");
    myOLED.setPosi(2,8);
    myOLED.print("B");
    myOLED.setPosi(4,8);
    myOLED.print("C");
    myOLED.setPosi(6,8);
    myOLED.print("D");
  }
  else if (Lcdflag == 2)
  {
    myOLED.setPosi(0,8);
    myOLED.print("B");
    myOLED.setPosi(2,8);
    myOLED.print("C");
    myOLED.setPosi(4,8);
    myOLED.print("D");
    myOLED.setPosi(6,8);
    myOLED.print("E");
  }
  else if(Lcdflag == 3 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("C");
      myOLED.setPosi(2,8);
      myOLED.print("D");
      myOLED.setPosi(4,8);
      myOLED.print("E");
      myOLED.setPosi(6,8);
      myOLED.print("F");
  }
  else if(Lcdflag == 4 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("D");
      myOLED.setPosi(2,8);
      myOLED.print("E");
      myOLED.setPosi(4,8);
      myOLED.print("F");
      myOLED.setPosi(6,8);
      myOLED.print("G");
  }
}
void Star_option(uint8_t Starflag)
{
     /*myOLED.setPosi(0,0);
     myOLED.print(" ");
     myOLED.setPosi(2,0);
     myOLED.print(" ");
     myOLED.setPosi(4,0);
     myOLED.print(" ");
     myOLED.setPosi(6,0);
     myOLED.print(" ");*/
   
    if(Starflag == 1)
    {
      myOLED.setPosi(2,0);
      myOLED.print(" "); 
      myOLED.setPosi(6,0);
      myOLED.print(" ");
      myOLED.setPosi(0,0);
      myOLED.print("*"); 
     
    }
    else if(Starflag == 2)
    {
      myOLED.setPosi(0,0);
      myOLED.print(" ");      
      myOLED.setPosi(4,0);
      myOLED.print(" ");
      myOLED.setPosi(2,0);  
      myOLED.print("*");
       
    }
    else if(Starflag == 3)
    {
        myOLED.setPosi(2,0);
        myOLED.print(" "); 
        myOLED.setPosi(6,0);
        myOLED.print(" "); 
        myOLED.setPosi(4,0);
        myOLED.print("*");
     
    }
    else if(Starflag == 4)
    {
        myOLED.setPosi(0,0);
        myOLED.print(" "); 
        myOLED.setPosi(4,0);
        myOLED.print(" "); 
        myOLED.setPosi(6,0);
        myOLED.print("*");
      
    }
}
int button ()
{
  if(digitalRead(key1) == LOW)
  {
     while(1)
     {
      
     }
  }
}

