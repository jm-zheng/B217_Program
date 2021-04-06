//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include <stdio.h>

#include "Serial.h" // Serial and Serial1
#include "jsmn.h"

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

void Zigbee_setup(uint8_t channel, uint16_t panid, uint16_t addr);
#define ZIGBEE_Serial	Serial1
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_RxBufCountOld;
uint8_t ZIGBEE_RxBuf[100];


//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#define WIFI_Serial	Serial
uint8_t WIFI_RxBufCount;
uint8_t WIFI_RxBufCountOld;
uint8_t WIFI_RxBuf[100];

char *sendmqtts=(char *)"{\"T1\":25.4,\"H1\":85.0,\"L1\":3500,\"CO21\":400,\"VOC1\":0}";

int sendocount;

//-------------------------------------------------------------------
void WIFI_PutCommand(const char cmd[])
{
	WIFI_Serial.println(cmd);
}

//-------------------------------------------------------------------
void WIFI_MQTT_Publish(const char topic[],const char dat[])
{
	WIFI_Serial.print("AT+MQPUBLISH=\"");				
	Serial1.print(topic);
	WIFI_Serial.print("\",");				
	WIFI_Serial.println(strlen(sendmqtts));
	delay(10);
	Serial1.print(sendmqtts);
}

//-------------------------------------------------------------------
uint8_t WIFI_MQTT_Get(void)
{
	uint8_t i;

		while (WIFI_Serial.available() > 0)
		{
			digitalWrite(LED_B, HIGH);
			WIFI_RxBuf[WIFI_RxBufCount++]=WIFI_Serial.read();
 		}		

		if(WIFI_RxBufCount>0)
		{
			if(WIFI_RxBufCountOld!=WIFI_RxBufCount)
			{
				WIFI_RxBufCountOld=WIFI_RxBufCount;
			}
			else
			{
					myOLED.setPosi(4, 0);
					for(i=0;i<WIFI_RxBufCount;i++)
					{
						if (WIFI_RxBuf[i] < 0x10)
						{
							myOLED.print('0');  
						}
						myOLED.print(WIFI_RxBuf[i],HEX);  
					}		
				WIFI_RxBufCountOld=WIFI_RxBufCount=0;
				digitalWrite(LED_B, LOW);
			}
		}
		return 0;
}

static const char *JSON_STRING =
	"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
	"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

//-------------------------------------------------------------------
int main(void)
{
	int i;
	int r;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */
	char buf[40];
	
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HMI MQTT Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	
	ZIGBEE_Serial.begin(9600); // Zigbee module
	Zigbee_setup(26, 0x1001, 0x2002);
	
	WIFI_Serial.begin(115200);//WIFI
	WIFI_RxBufCount=0;
	WIFI_RxBufCountOld=0;
	
	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) 
	{
		myOLED.setPosi(0, 0);
		myOLED.println("Failed to parse");
		//printf("Failed to parse JSON: %d\n", r);
		//return 1;
	}
	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}

	/* Loop over all keys of the root object */
	for (i = 1; i < r; i++) 
	{
		if (jsoneq(JSON_STRING, &t[i], "user") == 0) 
		{
			/* We may use strndup() to fetch string value */
			sprintf(buf,"- User: %.*s\n", t[i+1].end-t[i+1].start,JSON_STRING + t[i+1].start);
			myOLED.println(buf);
			i++;
		} else if (jsoneq(JSON_STRING, &t[i], "uid") == 0) 
		{
			/* We may want to do strtol() here to get numeric value */
			sprintf(buf,"- UID: %.*s\n", t[i+1].end-t[i+1].start,JSON_STRING + t[i+1].start);
			myOLED.println(buf);
			i++;
		}
	}
	
	//loop
	while (1)
	{
		delay(10);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				digitalWrite(LED_R, HIGH);
				myOLED.setPosi(2, 0);
				WIFI_PutCommand("AT+MQSTART");
				delay(100);
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
				digitalWrite(LED_R, HIGH);
				myOLED.setPosi(2, 0);
				WIFI_MQTT_Publish("HUSTKIT1",sendmqtts);
				delay(100);
				digitalWrite(LED_R, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		
		//Auto send 10 sec
		sendocount++;
		if(sendocount>1000)
		{
			sendocount=0;
			WIFI_MQTT_Publish("HUSTKIT1",sendmqtts);
		}
		
		WIFI_MQTT_Get();
		
	}
}


//------------------------------------------------------------------------------
void Zigbee_setup(uint8_t channel, uint16_t panid, uint16_t addr)
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
