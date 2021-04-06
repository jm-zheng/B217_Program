//-------------------------------------------------------------------
// HUSTKIT1_LIGHT1_ex
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
#define WIFI_Serial	Serial1
uint8_t WIFI_RxBufCount;
uint8_t WIFI_Count;
uint8_t WIFI_RxBuf[100];
int WIFI_Step;
int WIFI_CheckCount;
#define WIFI_AP "hustkit"
#define WIFI_PASSWORD "12345678"
#define MQTT_SERVER "liantw.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "HUSTKIT1"
char *JSON_ptr;

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

#define DRV_IN1			PA5
#define DRV_IN2			PA4

//-------------------------------------------------------------------
uint8_t WIFI_Get(void)
{
	while (WIFI_Serial.available() > 0)
	{
		WIFI_Count = 0;
		digitalWrite(LED_B, HIGH);
		WIFI_RxBuf[WIFI_RxBufCount] = WIFI_Serial.read();
		if (WIFI_RxBufCount < 99)
		{
			WIFI_RxBufCount++;
		}
	}

	if (WIFI_Count++ >= 20)
	{
		WIFI_Count = 0;
		if (WIFI_RxBufCount > 0)
		{
			WIFI_RxBuf[WIFI_RxBufCount] = 0;
			if (WIFI_Step != 2)
			{
				myOLED.clearScreen();
				myOLED.println((char*)WIFI_RxBuf);
			}
			WIFI_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
void WIFI_PutCommand(const char cmd[])
{
	WIFI_Serial.println(cmd);
}

//-------------------------------------------------------------------
void WIFI_ConnectAP(void)
{
	//AT+CWJAP_DEF="hustkit","12345678"
	//AT+CWJAP="hustkit","12345678"	
	WIFI_Serial.print("AT+CWJAP=\"");
	WIFI_Serial.print(WIFI_AP);
	WIFI_Serial.print("\",\"");
	WIFI_Serial.print(WIFI_PASSWORD);
	WIFI_Serial.println("\"");
	delay(100);
	while (WIFI_Serial.available() > 0)
	{
		WIFI_Serial.read();
	}
}

//-------------------------------------------------------------------
uint8_t WIFI_IsConnect(void)
{
	int i;
	char *p;
	char ipbuf[10];

	WIFI_PutCommand("AT+CIPSTA?");
	delay(50);
	for (i = 0; i < 500; i++)
	{
		if (WIFI_Get() == 1)
		{
			p = strstr((char*)WIFI_RxBuf, (const char*)"ip:");
			if (p)
			{
				for (i = 0; i < 7; i++)
				{
					ipbuf[i] = *(p + i + 4);
				}
				ipbuf[i] = 0;
				if (strcmp(ipbuf, "0.0.0.0") == 0)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
			return 0;
		}
		delay(1);
	}
	return 0;
}

//-------------------------------------------------------------------
void WIFI_ConnectMQTT(void)
{
	WIFI_Serial.print("AT+MQIPPORT=\"");
	WIFI_Serial.print(MQTT_SERVER);
	WIFI_Serial.print("\",");
	WIFI_Serial.println(MQTT_PORT);
	delay(500);
	while (WIFI_Serial.available() > 0)
	{
		WIFI_Serial.read();
	}
	WIFI_Serial.println("AT+MQSTART");
}

//-------------------------------------------------------------------
void WIFI_MQTT_Publish(const char topic[], const char dat[])
{
	WIFI_Serial.print("AT+MQPUBLISH=\"");
	WIFI_Serial.print(topic);
	WIFI_Serial.print("\",");
	WIFI_Serial.println(strlen(dat));
	delay(60);
	WIFI_Serial.print(dat);
	delay(200);
	while (WIFI_Serial.available() > 0)
	{
		WIFI_Serial.read();
	}
}

//-------------------------------------------------------------------
void WIFI_MQTT_Subscribe(const char topic[], uint8_t qos)
{
	WIFI_Serial.print("AT+MQSUBSCRIBE=\"");
	WIFI_Serial.print(topic);
	WIFI_Serial.print("\",");
	WIFI_Serial.println(qos);
	delay(300);
	while (WIFI_Serial.available() > 0)
	{
		WIFI_Serial.read();
	}
}

//-------------------------------------------------------------------
uint8_t MQTT_IsConnect(void)
{
	int i;
	char *p;

	WIFI_PutCommand("AT+MQSTATUS");
	delay(50);
	for (i = 0; i < 500; i++)
	{
		if (WIFI_Get() == 1)
		{
			p = strstr((char*)WIFI_RxBuf, (const char*)"MQTT CLOSED");
			if (p)
			{
				return 2;
			}
			p = strstr((char*)WIFI_RxBuf, (const char*)"MQTT CONNECTED");
			if (p)
			{
				return 1;
			}
			return 0;
		}
		delay(1);
	}
	return 0;
}

//-------------------------------------------------------------------
uint8_t MQTT_SubscribeJson(void)
{
	char *p;

	p = strstr((char*)WIFI_RxBuf, "+MQD:");
	if (p)
	{
		p = strstr(p, MQTT_TOPIC);
		if (p)
		{
			p = strstr(p, "{\"");
			if (p)
			{
				JSON_ptr = p;
				//myOLED.clearScreen();
				//myOLED.println(JSON_ptr);
				return 1;
			}
		}
	}
	return 0;
}

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
void ZIGBEE_Publish(const char topic[], int val)
{
	ZIGBEE_Serial.print("{\"");
	ZIGBEE_Serial.print(topic);
	ZIGBEE_Serial.print("\":");
	ZIGBEE_Serial.print(val);
	ZIGBEE_Serial.print("\"}");
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
	analogWrite(DRV_IN1, 0);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT1 LIGHT1");

	ZIGBEE_Serial.begin(9600); // Zigbee module
	ZIGBEE_setup(20, 0x1111, 0x2222);

	WIFI_Serial.begin(9600); //WIFI
	WIFI_RxBufCount = 0;

	WIFI_Step = 0;

	WIFI_ConnectAP();

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
				myOLED.println("OFF");
				//WIFI_PutCommand("AT+MQSTART");
				analogWrite(DRV_IN1, 0);
				//ZIGBEE_Publish("ACCLOCK",1);
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
				myOLED.println("ON");
				//WIFI_MQTT_Publish("HUSTKIT1",sendmqtts);
				analogWrite(DRV_IN1, 255);
				//ZIGBEE_Publish("ACCLOCK",0);
				delay(100);
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
			
		if (WIFI_Step == 0)
		{
			WIFI_CheckCount++;
			if(WIFI_CheckCount>500)
			{
				WIFI_CheckCount=0;
				if (WIFI_IsConnect() == 1)
				{
					WIFI_Step = 1;
					WIFI_ConnectMQTT();
				}
			}
		}
		else if (WIFI_Step == 1)
		{
			WIFI_CheckCount++;
			if(WIFI_CheckCount>500)
			{
				WIFI_CheckCount=0;
				i = MQTT_IsConnect();
				if (i == 2)
				{
					delay(200);
					WIFI_Serial.println("AT+MQSTART");
				}
				else if (i == 1)
				{
					delay(200);
					WIFI_MQTT_Subscribe(MQTT_TOPIC, 1);
					WIFI_Step = 2;
				}
			}
		}
		else
		{
			if (WIFI_Get() == 1)
			{
				if (MQTT_SubscribeJson() == 1)
				{
					if(jsonGet((char *)JSON_ptr,(char *)"LIGHT1",buf)==1)
					{
						val=atoi(buf);
						myOLED.setPosi(2, 0);
						if(val==0)
							myOLED.println("OFF");
						else
							myOLED.println("ON");
						myOLED.setPosi(4, 0);
						myOLED.print("PWM = ");
						myOLED.println(val);
						val=val*26/10;
						if(val>255)
						{
							val=255;
						}
						analogWrite(DRV_IN1,val);
					}							
					ZIGBEE_Serial.print(JSON_ptr);
				}
			}
		}
		
		if (ZIGBEE_Get() == 1)
		{
			if (WIFI_Step == 2)
			{
				WIFI_MQTT_Publish(MQTT_TOPIC, (char*)ZIGBEE_RxBuf);
			}
			if(jsonGet((char *)ZIGBEE_RxBuf,(char *)"LIGHT1",buf)==1)
			{
				val=atoi(buf);
				myOLED.setPosi(2, 0);
				if(val==0)
					myOLED.println("OFF");
				else
					myOLED.println("ON");
				myOLED.setPosi(4, 0);
				myOLED.print("PWM = ");
				myOLED.println(val);
				val=val*26/10;
				if(val>255)
				{
					val=255;
				}
				analogWrite(DRV_IN1,val);
			}		
		}
	}
}
