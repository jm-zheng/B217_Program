//-------------------------------------------------------------------
// NeoPixel_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "WS2812.h" // WS2812
WS2812 rgbLED;

void gradualFill(uint8_t n, uint8_t r, uint8_t g, uint8_t b);

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("NeoPixel Test");

	rgbLED.begin(PA1);
	rgbLED.fillStrip(0xFF,0x00,0x00);
	
	//loop
	while (1)
	{
    gradualFill(NUM_LEDS, 0x00, 0xFF, 0x00);  // green
    gradualFill(NUM_LEDS, 0x00, 0x00, 0xFF);  // blue
    gradualFill(NUM_LEDS, 0xFF, 0x00, 0xFF);  // magenta
    gradualFill(NUM_LEDS, 0xFF, 0xFF, 0x00);  // yellow
    gradualFill(NUM_LEDS, 0x00, 0xFF, 0xFF);  // cyan
    gradualFill(NUM_LEDS, 0xFF, 0x00, 0x00);  // red		
	}
}

//-------------------------------------------------------------------
void gradualFill(uint8_t n, uint8_t r, uint8_t g, uint8_t b)
{
  int i;
  for (i = 0; i < NUM_LEDS; i++)
	{       
    rgbLED.setLEDColor(i, r, g, b);
    rgbLED.showStrip();
    delay(50); 
  }
}

