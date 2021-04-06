//-------------------------------------------------------------------
// DC_MOTOR_ex
//-------------------------------------------------------------------

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------

#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#define MOTOR_A1		PB6
#define MOTOR_A2		PB7

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("DC MOTOR Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);

	pinMode(MOTOR_A1, OUTPUT);
	pinMode(MOTOR_A2, OUTPUT);
	digitalWrite(MOTOR_A1, LOW);
	digitalWrite(MOTOR_A2, LOW);
	//loop
	while (1)
	{
		delay(100);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("* MOTOR CW  *");
				digitalWrite(LED_B,LOW);
				digitalWrite(LED_R,HIGH);

				digitalWrite(MOTOR_A1, HIGH);
				digitalWrite(MOTOR_A2, LOW);
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
				myOLED.println("= MOTOR CCW =");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
				
				digitalWrite(MOTOR_A1, LOW);
				digitalWrite(MOTOR_A2, HIGH);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
	}
}

