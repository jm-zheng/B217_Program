#include <OLED.h>
OLED myOLED;

#define  pwm   10
#define  key1   2
#define  key2   6
#define  relay 12
int32_t Time = 40000;
int32_t duty = 0;
void setup() 
{    
    pinMode(relay,OUTPUT);
    digitalWrite(relay,HIGH);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    pinMode(pwm,OUTPUT);
   myOLED.begin(FONT_8x16);

    /*digitalWrite(pwm,HIGH);
    delay(2000);
    digitalWrite(pwm,LOW);
    delay(2000);*/
    digitalWrite(pwm,HIGH);
    delay(4000);
}


void loop() 
{
   //HUGH 短路
   //三分之一亮度
   //HIGH開 LOW短
    if(digitalRead(key1) == LOW)
    {
        duty +=5;
        if(duty >=Time)
        {
            duty = Time;
        }
        myOLED.setPosi(0,0);
        myOLED.print(duty);
        while(digitalRead(key1) == LOW);
    }

    if(digitalRead(key2) == LOW)
    {
        duty -=5;
        if(duty <= 0)
        {
            duty = 0;
        }
        myOLED.setPosi(0,0);
        myOLED.print(duty);
        while(digitalRead(key2) == LOW);
    }
    for(int i=0; i<500;i++)
    {
        digitalWrite(pwm,LOW);
        delayMicroseconds(duty);
        
         digitalWrite(pwm,HIGH);
        delayMicroseconds(Time - duty);
        duty+=80;
        if(duty >Time)
        {
            duty = Time;  
        }
    }
  
    duty =0;
 
  
}
