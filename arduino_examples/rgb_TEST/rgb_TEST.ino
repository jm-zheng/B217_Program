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
#define LED1_PIN     3
#define NUM1_LEDS    8
CRGB led1[NUM1_LEDS];
#define BRIGHTNESS  64
//--------------------------------
#define LED2_PIN     5
#define NUM2_LEDS    8
CRGB led2[NUM2_LEDS];
///-------------------------------
#include<OLED.h>
OLED myOLED;

#define ls1_pin  A3
#define ls2_pin  A4
#define ls3_pin  A5
#define relay_pin 12
//---------------------------------
#include<SoftwareSerial.h>
SoftwareSerial myZigbee (A1,A2);

int time_flag=1;
//------------------------------------------------------------------------------
void setup() 
{
  myZigbee.begin(9600);
  Serial.begin(9600);
 //=========Setup-RGB===========================
  delay( 100 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED1_PIN, GRB>(led1, NUM1_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2812B, LED2_PIN, GRB>(led2, NUM2_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS );
  SET_RGB(1 ,'D');SET_RGB(2 ,'D');SET_RGB(3 ,'D');
  //------------------------------------------------------
  myOLED.begin(FONT_8x16);
  myOLED.print("RGB");
  //-------------------------------------------------------
  pinMode(ls1_pin,INPUT);
  pinMode(ls2_pin,INPUT);
  pinMode(ls3_pin,INPUT);
  pinMode(relay_pin,INPUT);
  pinMode(3,OUTPUT);
}
//------------------------------------------------------------------------------
void loop() 
{
   delay(1);
  
   time_flag ++;
   int ls1val = analogRead(ls1_pin); 
   int ls2val = analogRead(ls2_pin); 
   int ls3val = analogRead(ls3_pin);
   if(ls1val < 100)
   {
      setrgb1();
      rgb2(255); 
   }
   else if(ls2val < 100)
   {
      setrgb1();
   }
   else if (ls3val < 100)
   {
      rgb2(255);
   }
   else
   {
       closergb1();
       rgb2(0) ; 
   }
  
  if(time_flag > 1000)
  {
   myOLED.setPosi(2,0);
   myOLED.println(ls1val);
   myOLED.println(ls2val);
   myOLED.println(ls3val);
   time_flag = 0;
  }
   
   
    
   
}
//------------------------------------------------------------------------------
void SET_RGB(int m, char c)
{
    m=m-1;
    if(c=='R')      led1[m] = CRGB::Red;
    if(c=='G')      led1[m] = CRGB::Green;
    if(c=='B')      led1[m] = CRGB::Blue;
    if(c=='Y')      led1[m] = CRGB::Yellow;
    if(c=='W')      led1[m] = CRGB::White;
    if(c=='D')      led1[m] = CRGB::Black;
    if(c=='P')      led1[m] = CRGB::Purple;
    FastLED.show();  
}

void Flash_RGB(int m, char c, int n, int finv)
{
   int i;
   SET_RGB(m, 'D');
   for(i=0;i<n;i++)
   {
       SET_RGB(m, c);
       delay(finv);  
       SET_RGB(m, 'D');  
      delay(finv);     
   }
}
void setrgb1()
{
    led1[0] = CRGB(255,255,255 );
    led1[1] = CRGB(255,255,255 );
    led1[2] = CRGB(255,255,255 );
    led1[3] = CRGB(255,255,255 );
    led1[4] = CRGB(255,255,255 );
    led1[5] = CRGB(255,255,255 );
    led1[6] = CRGB(255,255,255 );
    led1[7] = CRGB(255,255,255 );
    led1[8] = CRGB(255,255,255 );
     FastLED.show();
}
void closergb1()
{
    led1[0] = CRGB(0,0,0 );
    led1[1] = CRGB(0,0,0  );
    led1[2] = CRGB(0,0,0  );
    led1[3] = CRGB(0,0,0 );
    led1[4] = CRGB(0,0,0 );
    led1[5] = CRGB(0,0,0  );
    led1[6] = CRGB(0,0,0 );
    led1[7] = CRGB(0,0,0 );
    led1[8] = CRGB(0,0,0  );
     FastLED.show();
}
void rgb2(uint8_t Status)
{
   for(int i=0;i<9;i++)
   {
     led2[i] = CRGB(Status,Status,Status );
   }
    FastLED.show();
}
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
    int i,len;
    
    // get Channel/PAN ID/Address
    myZigbee.write(0xAA);  
    myZigbee.write(0xC7);  
    myZigbee.write(0xBB);  
    delay(30);
  
    // set Channel/PAN ID/Address
    myZigbee.write(0xAA);  
    myZigbee.write(0xC7);  
    myZigbee.write(0x5A);  
    myZigbee.write(channel);  
    myZigbee.write(panid>>8);  
    myZigbee.write(panid&0xff);  
    myZigbee.write(addr>>8);  
    myZigbee.write(addr&0xff);  
    myZigbee.write(0xBB); 
}
