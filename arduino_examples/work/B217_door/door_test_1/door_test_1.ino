#include<OLED.h>
OLED myOLED ;


#define key1 2
#define key2 6

#define bt1_1 1
#define bt2_1 2
#define bt1_2 3

uint8_t switch_flag = 0 ;
uint8_t picture_flag = 0 ;
void setup() 
{
    Serial.begin(9600);
    myOLED.begin(FONT_8x16);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    myOLED.print("B217_door");

    picture_flag = 0;
    switch_flag = 1;

    PictureFunction(picture_flag);
    SwitchFunction(switch_flag);
    


}

void loop() 
{
    uint8_t bt = ButtonStatus();
    
    if(bt == bt2_1)
    {
        switch_flag += 1;
        if (switch_flag > 3 )
        {
            switch_flag = 1;
        }
        SwitchFunction(switch_flag);
        delay(200);
    }
    else if (bt == bt1_1)
    {
        if (picture_flag == 0)
        {
          PictureFunction(switch_flag);
         
          picture_flag = switch_flag ;
          switch_flag = 1;
          SwitchFunction(switch_flag);
        
          
        }
    }
    
    
}


void PictureFunction(uint8_t  ptNumber)
{
   if (ptNumber == 1)
   {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 1.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 1.2");
   }
   else if (ptNumber == 2)
   {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 2.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 2.2");
   }
   else if(ptNumber == 0)
   {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 0.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 0.2");
        myOLED.setPosi(6,0);
        myOLED.print(" 0.3");
   }
}

void SwitchFunction(uint8_t sw)
{
  //---------*歸零----------
    myOLED.setPosi(2,0);
    myOLED.print(" ");
    myOLED.setPosi(4,0);
    myOLED.print(" ");
    myOLED.setPosi(6,0);
    myOLED.print(" ");

    if (sw == 1 )
    {
        myOLED.setPosi(2,0);
        myOLED.print("*");
    }
    else if(sw == 2)
    {
        myOLED.setPosi(4,0);
        myOLED.print("*"); 
    }
    else if (sw == 3 )
    {
        myOLED.setPosi(6,0);
        myOLED.print("*");
    }
    
}

uint8_t ButtonStatus()  //為甚麼不能用void
{
    uint8_t bt1_flag=0 ;
    if (digitalRead(key1) == LOW)
    {
        while(digitalRead(key1) == LOW)
      {
         bt1_flag += 1;
         myOLED.setPosi(4,80);
         myOLED.print(bt1_flag); 
      }
     if (bt1_flag > 100)
      {
        return bt1_2 ; 
        
      }
      if (bt1_flag < 100)
      {
        return bt1_1 ;
        
      }
        bt1_flag = 0;
          
          
    }
    else if (digitalRead(key2) == LOW )
    {
         return bt2_1 ;
         
    }
    return 0 ;
    
}


