//------------------------------------------------------------------------------
// WS2812.cpp
//------------------------------------------------------------------------------
#include "WS2812.h"

// WS2812 takes GRB format
typedef struct {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} LED;

static LED leds[NUM_LEDS] = { { 0, 0, 0 } };
static int portpin;

//------------------------------------------------------------------------------
void WS2812::begin(uint8_t pin)
{
	if(pin==PA0)
	{
		portpin=GPIO_PIN_0;
	}
	else
	{
		portpin=GPIO_PIN_1;
	}
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin,HIGH);
  clearStrip();           // clear the strip
}

//------------------------------------------------------------------------------
// Sets the color of a certain LED (0 indexed)
//------------------------------------------------------------------------------
void WS2812::setLEDColor(uint8_t p, uint8_t r, uint8_t g, uint8_t b) 
{
	leds[p].green = g;
  leds[p].red = r;
  leds[p].blue = b;
}

//------------------------------------------------------------------------------
// Send colors to the strip and show them. Disables interrupts while processing.
//------------------------------------------------------------------------------
void WS2812::showStrip(void)
{
  __disable_irq();
  // send RGB color for every LED
  unsigned int i, j,n;
  uint8_t mask;
  uint8_t *rgb;
  for (i = 0; i < NUM_LEDS; i++) 
	{
    rgb = (uint8_t *)&leds[i]; // get GRB color for this LED
    // send green, then red, then blue
    for (j = 0; j < 3; j++) 
		{
      mask = 0x80;    // b1000000
      // check each of the 8 bits
      while (mask != 0) 
			{
        if (rgb[j] & mask) 
				{
					HAL_GPIO_WritePin(GPIOA, portpin, GPIO_PIN_SET);
					for(n=0;n<5;n++)
					{
						_NOP();
					}
					HAL_GPIO_WritePin(GPIOA, portpin, GPIO_PIN_RESET);
        } 
				else 
				{
					HAL_GPIO_WritePin(GPIOA, portpin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, portpin, GPIO_PIN_RESET);
					for(n=0;n<4;n++)
					{
						_NOP();
					}
        }
        mask >>= 1;  // check next bit
      }
    }
  }

  // send RES code for at least 50 us 
  delayMicroseconds(50);
  __enable_irq();
}

//------------------------------------------------------------------------------
// Clear the color of all LEDs (make them black/off)
//------------------------------------------------------------------------------
void WS2812::clearStrip(void) 
{
  fillStrip(0x00, 0x00, 0x00);  // black
}

//------------------------------------------------------------------------------
// Fill the strip with a solid color. This will update the strip.
//------------------------------------------------------------------------------
void WS2812::fillStrip(uint8_t r, uint8_t g, uint8_t b) 
{
  int i;
  for (i = 0; i < NUM_LEDS; i++) 
	{
    setLEDColor(i, r, g, b);  // set all LEDs to specified color
  }
  showStrip();  // refresh strip
}
