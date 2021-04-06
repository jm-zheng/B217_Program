//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_RxBufCountOld;
uint8_t ZIGBEE_RxBuf[100];

//-------------------------------------------------------------------
#include "jsmn.h"
int JSON_r;
jsmn_parser JSON_p;
jsmntok_t JSON_t[64]; // We expect no more than 64 tokens 
char *JSON_ptr;
static int jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0)
	{
		return 0;
	}
	return  - 1;
}

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
}

//-------------------------------------------------------------------
uint8_t ZIGBEE_Get(void)
{

	while (ZIGBEE_Serial.available() > 0)
	{
		digitalWrite(LED_B, HIGH);
		ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = ZIGBEE_Serial.read();
		if (ZIGBEE_RxBufCount < 99)
		{
			ZIGBEE_RxBufCount++;
		}
	}

	if (ZIGBEE_RxBufCount > 0)
	{
		if (ZIGBEE_RxBufCountOld != ZIGBEE_RxBufCount)
		{
			ZIGBEE_RxBufCountOld = ZIGBEE_RxBufCount;
		}
		else
		{
			//myOLED.clearScreen();
			ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = 0;
			//myOLED.println((char *)ZIGBEE_RxBuf);  
			ZIGBEE_RxBufCountOld = ZIGBEE_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
uint8_t ZIGBEE_SubscribeJson(void)
{
	char *p;

	p = strstr((char*)ZIGBEE_RxBuf, "{\"");
	if (p)
	{
		//myOLED.clearScreen();
		//myOLED.println((char *)p));
		JSON_ptr = p;
		return 1;
	}
	return 0;
}

//-------------------------------------------------------------------
int main(void)
{
	int i,val;
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
	analogWrite(DRV_IN1, 0);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT1 FAN1");

	ZIGBEE_Serial.begin(9600); // Zigbee module
	ZIGBEE_setup(20, 0x1111, 0x2222);

	//JSON INIT
	jsmn_init(&JSON_p);

	//loop
	while (1)
	{
		delay(10);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				digitalWrite(LED_B, HIGH);
				myOLED.setPosi(2, 0);
				myOLED.println(0);
				analogWrite(DRV_IN1, 0);
				//digitalWrite(DRV_IN1, LOW);
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
				myOLED.println(100);
				analogWrite(DRV_IN1, 100);
				//digitalWrite(DRV_IN1, HIGH);
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
			if (ZIGBEE_SubscribeJson() == 1)
			{
				myOLED.setPosi(2, 0);
				//myOLED.println((char *)JSON_ptr);  
				JSON_r = jsmn_parse(&JSON_p, JSON_ptr, strlen(JSON_ptr), JSON_t, sizeof(JSON_t) / sizeof(JSON_t[0]));
				if (JSON_r < 0)
				{
					myOLED.println("Failed to parse");
				}
				// Assume the top-level element is an object 
				else if (JSON_r < 1 || JSON_t[0].type != JSMN_OBJECT)
				{
					myOLED.println("Object expected");
				}
				else
				{
					// Loop over all keys of the root object 
					for (i = 1; i < JSON_r; i++)
					{
						if (jsoneq(JSON_ptr, &JSON_t[i], "FAN1") == 0)
						{
							sprintf(buf, "%.*s", JSON_t[i + 1].end - JSON_t[i + 1].start, JSON_ptr + JSON_t[i + 1].start);
							val=atoi(buf);
							myOLED.println(val);
							analogWrite(DRV_IN1,val);
							i++;
						}
					}
				}
			}
		}
	}
}
