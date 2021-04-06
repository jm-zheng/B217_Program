//-------------------------------------------------------------------
// Zigbee_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
// Serial is RX1/TX1 conect to PC
// Serial1 is RX2/TX2 conect to LORA module
//-------------------------------------------------------------------
#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
uint8_t RecvLen;
int RecvCount;

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
	myOLED.println("LORA Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600); // PC
	Serial1.begin(9600,SERIAL_8N1,true); // LORA module

	//loop
	while (1)
	{
		uint8_t ch;
		if (Serial1.available())
		{
			ch = Serial1.read();
			if (RecvLen < RECV_MAX)
			{
				RecvBuf[RecvLen++] = ch;
			}
			RecvCount = 200;
		}
		if (Serial.available())
		{
			ch = Serial.read();
			Serial1.write(ch);
		}
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("* SELECT Press *");
				Serial1.println("SELECT Press");
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
				Serial1.println("ENTER Press");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
		
		delayMicroseconds(10);
		if (RecvCount > 0)
		{
			RecvCount--;
			if (RecvCount == 0)
			{
				RecvBuf[RecvLen++] = 0x00;
				Serial.println((char*)RecvBuf);
				myOLED.println((char*)RecvBuf);
				RecvLen = 0;
			}
		}
	}
}

