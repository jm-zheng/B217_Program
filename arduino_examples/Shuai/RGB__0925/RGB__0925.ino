//--------------------------------------------------
// Title:Ex1_6_RGBLED
// Devices1: Nano328KIT(http://120.109.165.16/sch/Nano328KIT.pdf)
// Devices2: RGB_LED_Strip(http://120.109.165.16/sch/Ex1_6_RGBLED.pdf)
// Schematic:http://120.109.165.16/sch/NANO328P-A1_SCH_V03.pdf
// Schematic:http://120.109.165.16/sch/WS2812-A1_SCH_V02.pdf
// Function:RGB LED
// UpDate:2018/08/22
//----------Declare-RGB LED WS2812Driver -------------
#include "FastLED.h"
#define LED_PIN     A0
#define NUM_LEDS    3
CRGB leds[NUM_LEDS];
#define BRIGHTNESS  64
//------------------------------------------------------------------------------
void setup() 
{
 //=========Setup-RGB===========================
  delay( 100 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS );
  SET_RGB(1 ,'D');SET_RGB(2 ,'D');SET_RGB(3 ,'D');
}
//------------------------------------------------------------------------------
void loop() 
{
    SET_RGB(1 ,'R');
    SET_RGB(2 ,'G');
    SET_RGB(3 ,'B');
    delay(3000);
    Flash_RGB(1,'Y', 3, 200); // No.1 Yellow Short Flash  3    
    Flash_RGB(2,'P', 5, 200); // No.1 Purple Short Flash  5 
    Flash_RGB(3,'W', 2, 1000); // No.1 Long  Flash  2 
    delay(2000);
}
//------------------------------------------------------------------------------
void SET_RGB(int m, char c)
{
    m=m-1;
    if(c=='R')      leds[m] = CRGB::Red;
    if(c=='G')      leds[m] = CRGB::Green;
    if(c=='B')      leds[m] = CRGB::Blue;
    if(c=='Y')      leds[m] = CRGB::Yellow;
    if(c=='W')      leds[m] = CRGB::White;
    if(c=='D')      leds[m] = CRGB::Black;
    if(c=='P')      leds[m] = CRGB::Purple;
    FastLED.show();  
}

void Flash_RGB(int m, char c, int n, int finv)
{
   int i;
   SET_RGB(m, 'D');
   for(i=0;i<n;i++){
       SET_RGB(m, c);
       delay(finv);  
       SET_RGB(m, 'D');  
      delay(finv);     
   }}

