//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#include "Serial.h" // Serial
uint8_t RxBufCount;
uint8_t RxBufCountOld;
uint8_t RxBuf[100];
uint8_t RxBufCount1;
uint8_t RxBufCountOld1;
uint8_t RxBuf1[100];

//-------------------------------------------------------------------
int count=0;

//-------------------------------------------------------------------
int main(void)
{
	uint8_t i;
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
  myOLED.println("Serial Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	Serial1.begin(9600);
	RxBufCount=0;
	RxBufCountOld=0;  
	RxBufCount1=0;
	RxBufCountOld1=0;  
	//loop
	while (1)
	{
		delay(10);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(2, 0);
				myOLED.println("TX:ABC/DEF");
				digitalWrite(LED_B, LOW);
				digitalWrite(LED_R, HIGH);
				Serial.write("a");
				Serial.write("b");
				Serial.write("c");
				Serial.print("ABC");
				Serial1.write("a");
				Serial1.write("b");
				Serial1.write("c");
				Serial1.print("DEF");
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
				myOLED.setPosi(2, 0);
				myOLED.println("TX:123/456");
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_B, HIGH);
				Serial.write("a");
				Serial.write("b");
				Serial.write("c");
				Serial.print("123");
				Serial1.write("a");
				Serial1.write("b");
				Serial1.write("c");
				Serial1.print("456");
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}

		while (Serial.available() > 0)
		{
			digitalWrite(LED_B, HIGH);
			RxBuf[RxBufCount++]=Serial.read();
 		}

		if(RxBufCount>0)
		{
			if(RxBufCountOld!=RxBufCount)
			{
				RxBufCountOld=RxBufCount;
			}
			else
			{
				myOLED.setPosi(4, 0);
				RxBuf[RxBufCount]=0;
        myOLED.println((char *)RxBuf);  
				RxBufCountOld=RxBufCount=0;
				digitalWrite(LED_B, LOW);
			}
		}

		while (Serial1.available() > 0)
		{
			digitalWrite(LED_B, HIGH);
			RxBuf1[RxBufCount1++]=Serial1.read();
 		}
		
		if(RxBufCount1>0)
		{
			if(RxBufCountOld1!=RxBufCount1)
			{
				RxBufCountOld1=RxBufCount1;
			}
			else
			{
				myOLED.setPosi(6, 0);
				RxBuf1[RxBufCount1]=0;
        myOLED.println((char *)RxBuf1);  
				RxBufCountOld1=RxBufCount1=0;
				digitalWrite(LED_B, LOW);
			}
		}		
	}
}
