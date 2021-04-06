#define  relay 12
#define  pwm   10
#define  key1   2
#define  key2   6
int a=0 ;
int b=0 ;
#include<OLED.h>
OLED myOLED;
void setup()
{   
    myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
    myOLED.print("B217");
    pinMode(relay,OUTPUT);
    digitalWrite(relay,HIGH);

    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    pinMode(pwm,OUTPUT);

    
  
  

 

}

void loop() 
{
   
    myOLED.print(b);
    if(digitalRead(key1)== LOW)
    {
        if(a==0)
        {
            digitalWrite(relay,LOW);
            a=1;
           
        }
        else if(a==1)
        {
            digitalWrite(relay,HIGH);
            a=0;
     
        }
        delay(300);
    }


