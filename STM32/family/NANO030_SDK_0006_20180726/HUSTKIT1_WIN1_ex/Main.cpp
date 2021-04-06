//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
uint8_t ZIGBEE_RxBuf[100];

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#define DRV_IN1			PA2
#define DRV_IN2			PA3

//------------------------------------------------------------------------------
void ZIGBEE_setup(uint8_t channel, uint16_t panid, uint16_t addr)
{
	// get Channel/PAN ID/Address
	ZIGBEE_Serial.write(0xAA);
	ZIGBEE_Serial.write(0xC7);
	ZIGBEE_Serial.write(0xBB);
	delay(30);

	// set Channel/PAN ID/Address
	ZIGBEE_Serial.write(0xAA);
	ZIGBEE_Serial.write(0xC7);
	ZIGBEE_Serial.write(0x5A);
	ZIGBEE_Serial.write(channel);
	ZIGBEE_Serial.write(panid >> 8);
	ZIGBEE_Serial.write(panid &0xff);
	ZIGBEE_Serial.write(addr >> 8);
	ZIGBEE_Serial.write(addr &0xff);
	ZIGBEE_Serial.write(0xBB);
	delay(50);
	while (ZIGBEE_Serial.available() > 0)
	{
		ZIGBEE_Serial.read();
	}
}

//-------------------------------------------------------------------
uint8_t ZIGBEE_Get(void)
{
	while (ZIGBEE_Serial.available() > 0)
	{
		ZIGBEE_Count = 0;
		digitalWrite(LED_B, HIGH);
		ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = ZIGBEE_Serial.read();
		if (ZIGBEE_RxBufCount < 99)
		{
			ZIGBEE_RxBufCount++;
		}
	}

	if (ZIGBEE_Count++ >= 20)
	{
		ZIGBEE_Count = 0;
		if (ZIGBEE_RxBufCount > 0)
		{
			ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)ZIGBEE_RxBuf);  
			digitalWrite(LED_B, LOW);
			ZIGBEE_RxBufCount = 0;
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
int main(void)
{
	int i, val;
	char buf[40];

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	pinMode(DRV_IN1, OUTPUT);
	pinMode(DRV_IN2, OUTPUT);
	digitalWrite(DRV_IN1, LOW);
	digitalWrite(DRV_IN2, LOW);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT1 WIN1");

	ZIGBEE_Serial.begin(9600); // Zigbee module
	ZIGBEE_setup(20, 0x1111, 0x2222);
  ZIGBEE_RxBufCount=0;
  
	//loop
	while (1)
	{
		delay(1);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				digitalWrite(LED_B, HIGH);
				myOLED.setPosi(2, 0);
				myOLED.println("OPEN");
				digitalWrite(DRV_IN1, HIGH);
				digitalWrite(DRV_IN2, LOW);
				delay(100);
				digitalWrite(LED_B, LOW);
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
				digitalWrite(LED_B, HIGH);
				myOLED.setPosi(2, 0);
				myOLED.println("CLOSE");
				digitalWrite(DRV_IN1, LOW);
				digitalWrite(DRV_IN2, HIGH);
				delay(100);
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}

		if (ZIGBEE_Get() == 1)
		{
			if(jsonGet((char *)ZIGBEE_RxBuf,(char *)"WIN1",buf)==1)
			{
				val=atoi(buf);				
				myOLED.setPosi(4, 0);
				myOLED.println(val);
				if (val == 1)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("OPEN");
					digitalWrite(DRV_IN1, HIGH);
					digitalWrite(DRV_IN2, LOW);
				}
				else if (val == 0)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("CLOSE");
					digitalWrite(DRV_IN1, LOW);
					digitalWrite(DRV_IN2, HIGH);
				}
				else
				{
					myOLED.setPosi(2, 0);
					myOLED.println("STOP");
					digitalWrite(DRV_IN1, LOW);
					digitalWrite(DRV_IN2, LOW);
				}
			}
		}
	}
}
