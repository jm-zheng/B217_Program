//------------------------------------------------------------------------------
#include "FastLED.h"
#include <OLED.h>
#include <DHT12.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define NUM_LEDS    3
#define LED_PIN     A0
#define BRIGHTNESS  64
CRGB leds[NUM_LEDS];

#define DATA_PIN A3
DHT12 dht;

//------------------------------------------------------------------------------
void setup() 
{
  delay( 100 ); // power-up safety delay
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  dht.begin(DATA_PIN); // pin for DHT11
}

//------------------------------------------------------------------------------
void loop() 
{
  float h,t;
  dht.startConvert();
  leds[0] = CRGB::DarkRed;
  leds[1] = CRGB::DarkGreen;
  leds[2] = CRGB::DarkBlue;
  FastLED.show();
  delay(100);
  dht.getConvert(&h,&t);
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
  delay(100);
  myOLED.println("DHT12 Test2");
  myOLED.print("Humidity:"); 
  myOLED.println(h);
  myOLED.print("Temp.:"); 
  myOLED.println(t);
  myOLED.println();  
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Black;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Blue;
  FastLED.show();
  delay(100);  
}
