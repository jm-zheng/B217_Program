//-------------------------------------------------------------------
// Blink_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("LED Blink Test");

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B,LOW); // LED Blue OFF
  
	//loop
	while (1)
	{
		digitalWrite(LED_R,HIGH);// LED Red ON
		digitalWrite(LED_B,LOW);// LED Blue OFF
		delay(500);
		digitalWrite(LED_B,HIGH);// LED Blue ON
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(500);
	}
}
