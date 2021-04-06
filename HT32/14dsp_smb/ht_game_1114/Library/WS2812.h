//------------------------------------------------------------------------------
// WS2812.h
//------------------------------------------------------------------------------
#ifndef WS2812_H
#define WS2812_H

#include "HT32IO.h"

#define NUM_LEDS    3    // NUMBER OF LEDS IN YOUR STRIP

// Transmit codes
#define HIGH_CODE   (0xF0)      // b11110000
#define LOW_CODE    (0xC0)      // b11000000

//------------------------------------------------------------------------------
class WS2812
{
private:
	uint8_t _pin;
public:
	void begin(uint8_t pin);
	// Send colors to the strip and show them. Disables interrupts while processing.
	void showStrip(void);
	// Set the color of a certain LED
	void setLEDColor(uint8_t p, uint8_t r, uint8_t g, uint8_t b);
	// Clear the color of all LEDs (make them black/off)
	void clearStrip(void);
	// Fill the strip with a solid color. This will update the strip.
	void fillStrip(uint8_t r, uint8_t g, uint8_t b);
};
#endif
