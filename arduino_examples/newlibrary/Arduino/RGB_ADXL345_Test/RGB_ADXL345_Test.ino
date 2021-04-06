//------------------------------------------------------------------------------
#include "FastLED.h"
#include <OLED.h>
#include <SoftwareWire.h>
#include <ADXL345.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define NUM_LEDS    3
#define LED_PIN     A0
#define BRIGHTNESS  64
CRGB leds[NUM_LEDS];

//------------------------------------------------------------------------------
#define SDA_PIN A2 ///< pin for SDA
#define SCL_PIN A1 ///< pin for SCL
//#define SDA_PIN A4 ///< pin for SDA
//#define SCL_PIN A5 ///< pin for SCL
ADXL345 adxl;

//------------------------------------------------------------------------------
void setup() 
{
  delay( 100 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  adxl.begin(SDA_PIN, SCL_PIN);
  Serial.println("ADXL345 Test");
}

//------------------------------------------------------------------------------
void loop() 
{
  uint16_t iX, iY, iZ;
  float fX,fY,fZ;

  iX = adxl.getData(0x32); // 取得 X 軸
  fX = iX / 256.0;

  iY = adxl.getData(0x34); // 取得 Y 軸
  fY = iY / 256.0;

  iZ = adxl.getData(0x36); // 取得 Z 軸
  fZ = iZ / 256.0;

  myOLED.println("ADXL345 Example");
  myOLED.print("X = ");
  myOLED.println(fX);
  myOLED.print("Y = ");
  myOLED.println(fY);
  myOLED.print("Z = ");
  myOLED.println(fZ); 

  leds[0] = iX;
  leds[1] = iY;
  leds[2] = iZ;
  FastLED.show();
  delay(100);  
}
