//Ex4_5_Temp_RGB_KEY
//--------Declare--DS18B20-------------------------------------------------------
//#include <DS18B20.h>
//#include <OneWire.h>
//-------Declare-OLED-------------------------------
#include <OLED.h>
OLED myOLED;
//----------Declare-RGB LED WS2812Driver --------------------------------------------
#include "FastLED.h"
#define LED_PIN     A0
#define NUM_LEDS    3
CRGB leds[NUM_LEDS];
void SET_RGB(int m, char c);
//-------Declare-Temp Sensor DS18B20---------------------------------------
#include <DS18B20.h>
DS18B20 ds;
#define Temp_PIN  A3
float STempMax=32;
float STempMin=29;
//-------Declare-KEY---------------------------------------------
#define  KEY1  2
#define  KEY2  6
int SetiTems=0;
void setup() 
{
 //=============Setup- DS18B20=================================
  ds.begin(Temp_PIN );
  //-------Setup-KEY---------------------------------------------
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
   //=============Setup-RGB============================================
  delay( 100 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  SET_RGB(1,'D');SET_RGB(2,'D');SET_RGB(3,'D');
  //=============Setup-OLED===================================
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.print("Ex45KTRGB:");
  myOLED.print("S-");   
  myOLED.println(SetiTems+1);
  myOLED.print("STpMax:");
  myOLED.println(STempMax);
  myOLED.print("STpMin:");
  myOLED.println(STempMin);  
}

//------------------------------------------------------------------------------
void loop() 
{
  float temp = ds.readTemperature();
  if (temp<125 && temp>5) 
  {
    myOLED.setPosi(6,0);
    myOLED.print("Temp.: "); 
    myOLED.print(temp);
    myOLED.println(" *C");          
  }
//================================================
  // Read Key Send String
     int  BnState = digitalRead( KEY1);
     if(BnState==0)  {
            delay(300);        // delay in between reads for stability  
            switch(SetiTems)
            {
               case 0: STempMax= STempMax+0.5;break;
               case 1:STempMax= STempMax-0.5;break;
               case 2:STempMin=STempMin+0.5;break;
               case 3:STempMin=STempMin-0.5;break;
            }
            myOLED.setPosi(2,0);
            myOLED.print("STpMax:");
            myOLED.println(STempMax);
            myOLED.setPosi(4,0);
            myOLED.print("STpMin:");
            myOLED.println(STempMin);   
     }
    BnState = digitalRead( KEY2);
    if(BnState==0)
    {
          delay(500);        // delay in between reads for stability  
          if(SetiTems<3)
                SetiTems++;
            else
                 SetiTems=0;
           myOLED.setPosi(0,0);
           myOLED.print("Ex45KTRGB");
           myOLED.print("S-");   
           myOLED.println(SetiTems+1);  
   }
   //=======Smart Processing=============
   if(temp>STempMax)   
            SET_RGB(1,'R');
    else if (temp<STempMin)
          SET_RGB(1,'B');
   else
        SET_RGB(1,'G');
   delay(500);
}
void SET_RGB(int m, char c)
{
    m=m-1;
    if(c=='R')      leds[m] = CRGB::Red;
    if(c=='G')      leds[m] = CRGB::Green;
    if(c=='B')      leds[m] = CRGB::Blue;
    if(c=='Y')      leds[m] = CRGB::Yellow;
    if(c=='W')      leds[m] = CRGB::White;
    if(c=='D')      leds[m] = CRGB::Black;
    FastLED.show();  
}
