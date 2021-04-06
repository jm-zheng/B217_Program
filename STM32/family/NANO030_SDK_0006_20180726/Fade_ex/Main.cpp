//-------------------------------------------------------------------
// Fade_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	//OLED
  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("LED Fade Test");
  myOLED.println("0123456789012345");
  myOLED.println("ABCDEFGHIJKLMNOP");
  myOLED.println("abcdefghijklmnop");
	//loop
	while (1)
	{
		// set the brightness LED
		analogWrite(LED_R, brightness);
		analogWrite(LED_B, brightness);

		// change the brightness for next time through the loop:
		brightness = brightness + fadeAmount;

		// reverse the direction of the fading at the ends of the fade:
		if (brightness <= 0 || brightness >= 255) {
			fadeAmount = -fadeAmount;
		}
		// wait for 30 milliseconds to see the dimming effect
		delay(30);
	}
}
