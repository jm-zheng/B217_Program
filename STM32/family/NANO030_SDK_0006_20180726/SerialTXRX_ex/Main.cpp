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

uint8_t RxBufCount;
uint8_t RxBufCountOld;
uint8_t RxBuf[100];

//-------------------------------------------------------------------
int main(void)
{
	uint8_t i;
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("SerialTXRX Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	RxBufCount=0;
	RxBufCountOld=0;
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
				myOLED.println("TX:ABC");
				digitalWrite(LED_R, HIGH);
				Serial.print("ABC");
				digitalWrite(LED_R, LOW);
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
				myOLED.println("TX:123");
				digitalWrite(LED_R, HIGH);
				Serial.print("123");
				digitalWrite(LED_R, LOW);
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
        for(i=0;i<RxBufCount;i++)
        {
          if (RxBuf[i] < 0x10)
          {
            myOLED.print('0');  
          }
          myOLED.print(RxBuf[i],HEX);  
        }				
				RxBufCountOld=RxBufCount=0;
				digitalWrite(LED_B, LOW);
			}
		}
	}
}
