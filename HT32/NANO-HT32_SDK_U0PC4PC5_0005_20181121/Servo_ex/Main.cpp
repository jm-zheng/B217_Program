//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Servo.h"

Servo myservo1;
Servo myservo2;

//-------------------------------------------------------------------

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
  myOLED.println("Servo Test");

	
  myservo1.attach(PA7); // Servo#1 接在 PA7
  myservo2.attach(PC13); // Servo#2 接在 PC13

	myservo1.write(90); //是叫 Servo1 旋轉到 90 度的位置
	myservo2.write(90); //是叫 Servo2 旋轉到 90 度的位置

	myOLED.setPosi(4,0);
	myOLED.println("* Servo =  90 *");
	
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
				myOLED.println("* Servo =   0 *");
				digitalWrite(LED_B,LOW);
				digitalWrite(LED_R,HIGH);

				myservo1.write(0); //是叫 Servo1 旋轉到 0 度的位置
				myservo2.write(0); //是叫 Servo2 旋轉到 0 度的位置
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
				myOLED.println("* Servo = 180 *");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
				myservo1.write(180); //是叫 Servo1 旋轉到 180 度的位置
				myservo2.write(180); //是叫 Servo2 旋轉到 180 度的位置
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
	}
}
