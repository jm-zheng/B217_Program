//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

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
	myOLED.println("LED Blink Test");

  //loop
  while (1)
  {
		digitalWrite(PC11,HIGH);
		delay(100);
		digitalWrite(PC11,LOW);
		delay(100);
		if (digitalRead(PC0) == 0)
		{
				myOLED.setPosi(4,0);
				myOLED.println("* SELECT Press *");
				digitalWrite(PB15,LOW);
		}
		if (digitalRead(PC10) == 0)
		{
				myOLED.setPosi(4,0);
				myOLED.println("= ENTER Press  =");
				digitalWrite(PB15,HIGH);
		}
  }
}
