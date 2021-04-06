//-------門鎖---------
//----------OLED---------------
#include<OLED.h>
OLED myOLED ;

//------按鍵-----------set_card
#define  key1 2
#define  key2 6  

 int ch1=0;
 int ch2=0;
int screen=0;  //畫面1
int set_card=0; //畫面2
int key2_2=0;  //長按(返回鍵)


void setup() 
{
  //------OLED----------------
    myOLED.begin(FONT_8x16);
    myOLED.setPosi(0,0);
    myOLED.print("B217");
    myOLED.setPosi(2,0);
    myOLED.print(" :set card");
    myOLED.setPosi(4,0);
    myOLED.print(" :open door");
   
    
  //------按鍵---------------------------
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    

}

void loop() 
{   
      myOLED.setPosi(0,32);
      myOLED.print(screen);
        
    
      KEY1 ();
      KEY2 ();
      screen_tag();
  
  
  
    

              
     

}
void KEY2 ()
{
     ch2=digitalRead(key2);
   if (ch2==0)
   {    
          delay(500);
          key2_2=key2_2+1;
          
          if(key2_2<3)
          {
              if(screen<2)
              {
                  screen=screen+1;
                  delay(300);
              }
              else 
              {
                screen=screen-1;  
              }
          key2_2=0;
        }
        else
        {
            key2_2=0;
            myOLED.begin(FONT_8x16);
            myOLED.setPosi(0,0);
            myOLED.print("B217");
            myOLED.setPosi(2,0);
            myOLED.print(" :set card");
            myOLED.setPosi(4,0);
            myOLED.print(" :open door");
            
            //delay(500);
        }
    }
}
void  KEY1 ()
{
      ch1 = digitalRead(key1);
     if (ch1==0)

     {
         set_card=5;
          set_cardtag();
          
     }
}
void screen_tag()
{
     
         if(screen==1 && set_card != 5)
          {   
             myOLED.setPosi(2,0);
             myOLED.print("*:set card");
             myOLED.setPosi(4,0);
             myOLED.print(" :open door");
           
          }
        else  if (screen==2 && set_card != 5)
          {
             myOLED.setPosi(2,0);
             myOLED.print(" :set card");
             myOLED.setPosi(4,0);
             myOLED.print("*:open door");
             
          }

          if(screen==1 && set_card == 5)
          {   
             myOLED.setPosi(2,0);
             myOLED.print("*:set card");
             myOLED.setPosi(4,0);
             myOLED.print(" :open door");
           
          }
        else  if (screen==2 && set_card == 5)
          {
             myOLED.setPosi(2,0);
             myOLED.print(" :set card");
             myOLED.setPosi(4,0);
             myOLED.print("*:open door");
             
          }
}
void set_cardtag()
{
  if(set_card==5)
  {
     myOLED.setPosi(0,0);
     myOLED.print("set card");
     myOLED.setPosi(2,0);
     myOLED.print(" S/N:");
     myOLED.setPosi(4,0);
     myOLED.print(" C/N:");
  }
}

