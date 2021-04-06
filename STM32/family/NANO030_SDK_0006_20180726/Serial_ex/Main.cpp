//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

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
	myOLED.println("Serial Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	Serial1.begin(9600);

	//loop
	while (1)
	{
		delayMicroseconds(1000);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4, 0);
				myOLED.println("* SELECT Press *");
				digitalWrite(LED_B, LOW);
				digitalWrite(LED_R, HIGH);
				Serial.println("ABC");
				Serial1.println("DEF");
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
				myOLED.setPosi(4, 0);
				myOLED.println("= ENTER Press  =");
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_B, HIGH);
				Serial.println("123");
				Serial1.println("456");
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		
		while (Serial.available() > 0)
		{
			Serial.write(Serial.read());
 		}
		
		while (Serial1.available() > 0)
		{
			Serial1.write(Serial1.read());
 		}
	}
}
