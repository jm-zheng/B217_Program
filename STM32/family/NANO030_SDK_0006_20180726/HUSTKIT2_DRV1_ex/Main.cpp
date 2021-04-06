//-------------------------------------------------------------------
// HUSTKIT2_DRV1_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define LORA_Serial	Serial
uint8_t LORA_RxBufCount;
uint8_t LORA_Count;
uint8_t LORA_RxBuf[100];
#define LORA_MODE0		PF7
#define LORA_MODE1		PF6

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#define DRV_FAN1			PB0
#define DRV_PUMP1			PB1

#define DRV_WIN1A			PA6
#define DRV_WIN1B			PA7
#define DRV_WIN2A			PA2
#define DRV_WIN2B			PA3

uint16_t WIN1_Count;
uint16_t WIN2_Count;
//-------------------------------------------------------------------
uint8_t LORA_Get(void)
{
	while (LORA_Serial.available() > 0)
	{
		LORA_Count=0;
		digitalWrite(LED_B, HIGH);
		LORA_RxBuf[LORA_RxBufCount] = LORA_Serial.read();
		if (LORA_RxBufCount < 99)
		{
			LORA_RxBufCount++;
		}
	}

	if (LORA_Count++ >= 200)
	{
		LORA_Count=0;
		if (LORA_RxBufCount>0)
		{
			LORA_RxBuf[LORA_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)LORA_RxBuf);  
			LORA_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
int main(void)
{
	int val;
	char buf[40];

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	pinMode(DRV_FAN1, OUTPUT);
	pinMode(DRV_PUMP1, OUTPUT);
	digitalWrite(DRV_FAN1, LOW);
	digitalWrite(DRV_PUMP1, LOW);
	analogWrite(DRV_FAN1, 0);

	pinMode(DRV_WIN1A, OUTPUT);
	pinMode(DRV_WIN1B, OUTPUT);
	pinMode(DRV_WIN2A, OUTPUT);
	pinMode(DRV_WIN2B, OUTPUT);
	
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT2 DRV1");
	
	LORA_Serial.begin(9600); // LORA module
	pinMode(LORA_MODE0, OUTPUT);
	pinMode(LORA_MODE1, OUTPUT);
	digitalWrite(LORA_MODE0, LOW);
	digitalWrite(LORA_MODE1, LOW);
	LORA_RxBufCount=0;

	WIN1_Count=0;
	WIN2_Count=0;
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
				//myOLED.println("FAN1 OFF");
				//analogWrite(DRV_FAN1, 0);
				myOLED.println("WIN2 OPEN");
				digitalWrite(DRV_WIN2A, HIGH);
				digitalWrite(DRV_WIN2B, LOW);
				WIN2_Count=10000;				

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
				//myOLED.println("FAN1 ON");
				//analogWrite(DRV_FAN1, 255);
				myOLED.println("WIN2 CLOSE");
				digitalWrite(DRV_WIN2A, LOW);
				digitalWrite(DRV_WIN2B, HIGH);
				WIN2_Count=10000;
				
				delay(100);
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		if(WIN1_Count>0)
		{
			WIN1_Count--;
			if(WIN1_Count==0)
			{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN1 STOP");
					digitalWrite(DRV_WIN1A, LOW);
					digitalWrite(DRV_WIN1B, LOW);				
			}
		}
		if(WIN2_Count>0)
		{
			WIN2_Count--;
			if(WIN2_Count==0)
			{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN2 STOP");
					digitalWrite(DRV_WIN2A, LOW);
					digitalWrite(DRV_WIN2B, LOW);			
			}
		}

		if (LORA_Get() == 1)
		{
			if(jsonGet((char *)LORA_RxBuf,(char *)"PUMP1",buf)==1)
			{
				val=atoi(buf);				
				myOLED.setPosi(4, 0);
				myOLED.println(val);
				if (val == 1)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("PUMP1 ON");
					digitalWrite(DRV_PUMP1, HIGH);
				}
				else
				{
					myOLED.setPosi(2, 0);
					myOLED.println("PUMP1 OFF");
					digitalWrite(DRV_PUMP1, LOW);
				}				
			}
			if(jsonGet((char *)LORA_RxBuf,(char *)"WIN1",buf)==1)
			{
				val=atoi(buf);				
				myOLED.setPosi(4, 0);
				myOLED.println(val);
				if (val == 1)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN1 OPEN");
					digitalWrite(DRV_WIN1A, HIGH);
					digitalWrite(DRV_WIN1B, LOW);
					WIN1_Count=10000;
				}
				else if (val == 0)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN1 CLOSE");
					digitalWrite(DRV_WIN1A, LOW);
					digitalWrite(DRV_WIN1B, HIGH);
					WIN1_Count=10000;
				}
				else
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN1 STOP");
					digitalWrite(DRV_WIN1A, LOW);
					digitalWrite(DRV_WIN1B, LOW);
					WIN1_Count=0;
				}
			}
			if(jsonGet((char *)LORA_RxBuf,(char *)"WIN2",buf)==1)
			{
				val=atoi(buf);				
				myOLED.setPosi(4, 0);
				myOLED.println(val);
				if (val == 1)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN2 OPEN");
					digitalWrite(DRV_WIN2A, HIGH);
					digitalWrite(DRV_WIN2B, LOW);
					WIN2_Count=10000;
				}
				else if (val == 0)
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN2 CLOSE");
					digitalWrite(DRV_WIN2A, LOW);
					digitalWrite(DRV_WIN2B, HIGH);
					WIN2_Count=10000;
				}
				else
				{
					myOLED.setPosi(2, 0);
					myOLED.println("WIN2 STOP");
					digitalWrite(DRV_WIN2A, LOW);
					digitalWrite(DRV_WIN2B, LOW);
					WIN2_Count=0;
				}
			}
			if(jsonGet((char *)LORA_RxBuf,(char *)"FAN1",buf)==1)
			{
				val=atoi(buf);
				myOLED.setPosi(2, 0);
				if(val==0)
					myOLED.println("OFF");
				else
					myOLED.println("ON");
				myOLED.setPosi(4, 0);
				myOLED.print("FAN1 PWM = ");
				myOLED.println(val);
				val=val*26/10;
				if(val>255)
				{
					val=255;
				}
				analogWrite(DRV_FAN1,val);
			}
		}
	}
}
