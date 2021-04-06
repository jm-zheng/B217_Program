//-------------------------------------------------------------------
// Key_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("Key Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B,LOW);
	digitalWrite(LED_R,LOW);

	//loop
	while (1)
	{
		delayMicroseconds(1000);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("* SELECT Press *");
				digitalWrite(LED_B,LOW);
				digitalWrite(LED_R,HIGH);
			}
		}
		else
		{
			KEY_SELECT_Tag = 1;
		}
		if (digitalRead(KEY_ENETR) == 0)
		{
			if (KEY_ENTER_Tag == 1)
			{
				KEY_ENTER_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("= ENTER Press  =");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
	}
}
