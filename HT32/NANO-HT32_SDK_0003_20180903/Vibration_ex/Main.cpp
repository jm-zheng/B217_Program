//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#define INT_PIN  PC9

void blink(void);
int count;
int count_old;

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
	myOLED.println("Vibration Test");

	// INT
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(INT_PIN, blink, IT_RISING_FALLING_PULLUP);
	
  //loop
  while (1)
  {
		digitalWrite(LED_B,HIGH);
		delay(200);
		digitalWrite(LED_B,LOW);
		delay(200);

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
		
		if(count_old!=count)
		{
			count_old=count;
			myOLED.setPosi(6,0);
			myOLED.print("Count=");
			myOLED.println(count);
		}
	}
}

//-------------------------------------------------------------------
void blink(void) 
{
  count++;
}

