#include<OLED.h>
OLED myOLED;

#define ampere_pin  A0
int second_flag = 0;
int readapval = 0;
int maxapval= 0;
float ampere_value=0;

void setup() 
{
   Serial.begin(9600);
   myOLED.begin(FONT_8x16);
   myOLED.print("AD_test");
   pinMode(ampere_pin,INPUT);
}

void loop() 
{
  delay(1);
  second_flag +=1;
  
  if(second_flag < 1000)
    {
      readapval = analogRead(ampere_pin);
      if(readapval > maxapval)
      {
        maxapval = readapval;
        //myOLED.setPosi(4,0);
        
        
        
      }
      ampere_value = 3.7557*(0.0032*maxapval+0.1895)+0.6704;
      if(ampere_value < 0)
      {
        ampere_value = 0 ;
      }
      else
      {
        ampere_value=ampere_value;
      }
    }
   else if (second_flag == 1000)
   {
    myOLED.setPosi(2,0);
    myOLED.print(ampere_value);
    Serial.println(ampere_value);
    second_flag = 0 ;
    maxapval = 0;
   }
}
