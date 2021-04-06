//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();
	
  // KEY / LED
	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);
	
  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("LED Fade Test");

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
