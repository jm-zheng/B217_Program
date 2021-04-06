//-------門鎖---------
//----------OLED---------------
#include<OLED.h>
OLED myOLED ;

//------按鍵-----------
#define  key1 2
#define  key2 6  


int a=0 ;
int b=0;


void setup() 
{
  //------OLED----------------
    myOLED.begin(FONT_8x16);
    myOLED.setPosi(0,0);
    myOLED.print("B217");
  //------按鍵---------------------------
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    

}

void loop() 
{   
    
    KEY1();
    KEY2();
    
    

              
     

}


void KEY1()
{
      int ch1 = digitalRead(key1);
    if (ch1==0)
    {
      if(a==1)
      {
        myOLED.setPosi(4,0);
        myOLED.print("123");
      }
      else if (a==2)
      {
        myOLED.setPosi(4,0);
        myOLED.print("456");
      }
     
    }
}
void KEY2 ()
{
     int ch2 = digitalRead(key2);
     if (ch2==0)
     {
         delay(700);
   
             if (a>3)
             {
                a=1;
             }
             else
             {
                a=a+1;
                 myOLED.setPosi(0,40);
                 myOLED.print("ch=");
                 myOLED.println(a);
             }
        
  
     }
   
}

