//EC測試
//----------OLED-----------
#include <OLED.h>
OLED myOLED;
//------EC--------
int ECT = A6;
int ECI = A7;
//---------------------
int ectval = 0;
int ecival = 0;
int i;
uint32_t t;
uint32_t a ;
void setup() 
{
    Serial.begin(9600);
    myOLED.begin(FONT_8x16);
    myOLED.setPosi(0,0);
    myOLED.print("B217_EC_TEST");
}

void loop() 
{
       for(i=0;i<200;i++)
       {
          ectval = analogRead(ECT);
          t=t+ectval;
          
       }
       for (i=0;i<200;i++)
       {
          ecival=analogRead(ECI);
          a= a+ ecival;
       }
   
    t = t/200;
    a /= 200 ;
    myOLED.print(" t=");
    myOLED.println(t);
    myOLED.print("i=");
    myOLED.print(a);
    
    

}
