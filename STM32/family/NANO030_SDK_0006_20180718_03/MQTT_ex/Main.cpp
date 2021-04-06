//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define WIFI_Serial	Serial1
uint8_t WIFI_RxBufCount;
uint8_t WIFI_RxBufCountOld;
uint8_t WIFI_RxBuf[100];
int WIFI_Step;

#define WIFI_AP "hustkit"
#define WIFI_PASSWORD "12345678"
#define MQTT_SERVER "liantw.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "HUSTKIT1"

//-------------------------------------------------------------------
#include "jsmn.h"
int JSON_r;
jsmn_parser JSON_p;
jsmntok_t JSON_t[64]; // We expect no more than 64 tokens 
char *JSON_ptr;
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}


static const char *JSON_STRING =
	"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
	"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

char *sendmqtts=(char *)"{\"T1\":25.4,\"H1\":85.0,\"L1\":3500,\"CO21\":400,\"VOC1\":0}";

int sendocount;

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
uint8_t WIFI_Get(void)
{
	uint8_t i;

		while (WIFI_Serial.available() > 0)
		{
			digitalWrite(LED_B, HIGH);
			WIFI_RxBuf[WIFI_RxBufCount]=WIFI_Serial.read();
			if(WIFI_RxBufCount<99)
			{
				WIFI_RxBufCount++;
			}
 		}

		if(WIFI_RxBufCount>0)
		{
			if(WIFI_RxBufCountOld!=WIFI_RxBufCount)
			{
				WIFI_RxBufCountOld=WIFI_RxBufCount;
			}
			else
			{
				//myOLED.clearScreen();
				WIFI_RxBuf[WIFI_RxBufCount]=0;
				//myOLED.println((char *)WIFI_RxBuf);  
				WIFI_RxBufCountOld=WIFI_RxBufCount=0;
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
}

//-------------------------------------------------------------------
uint8_t WIFI_IsConnect(void)
{
	uint8_t i,j;
	char *p;
	char ipbuf[10];
	
	WIFI_PutCommand("AT+CIPSTA?");
	delay(50);
	for(i=0;i<20;i++)
	{
		if(WIFI_Get()==1)
		{
			p = strstr((char *)WIFI_RxBuf,(const char *) "ip:");
			if(p)
			{
				for(i=0;i<7;i++)
				{
					ipbuf[i]=*(p+i+4);
				}
				ipbuf[i]=0;
				if(strcmp (ipbuf, "0.0.0.0")==0)
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
		delay(10);
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
	WIFI_Serial.println("AT+MQSTART");	
}

//-------------------------------------------------------------------
void WIFI_MQTT_Publish(const char topic[],const char dat[])
{
	WIFI_Serial.print("AT+MQPUBLISH=\"");				
	WIFI_Serial.print(topic);
	WIFI_Serial.print("\",");				
	WIFI_Serial.println(strlen(sendmqtts));
	delay(10);
	Serial1.print(sendmqtts);
}

//-------------------------------------------------------------------
void WIFI_MQTT_Subscribe(const char topic[],uint8_t qos)
{
	WIFI_Serial.print("AT+MQSUBSCRIBE=\"");				
	WIFI_Serial.print(topic);
	WIFI_Serial.print("\",");				
	WIFI_Serial.println(qos);
}

//-------------------------------------------------------------------
uint8_t MQTT_IsConnect(void)
{
	uint8_t i,j;
	char *p;
	char ipbuf[10];
	WIFI_PutCommand("AT+MQSTATUS");
	delay(50);
	for(i=0;i<20;i++)
	{
		if(WIFI_Get()==1)
		{
			p = strstr((char *)WIFI_RxBuf,(const char *) "MQTT CLOSED");
			if(p)
			{
				return 2;
			}
			p = strstr((char *)WIFI_RxBuf,(const char *) "MQTT CONNECTED");
			if(p)
			{
				return 1;
			}
			return 0;
		}
		delay(10);
	}
	return 0;
} 

//-------------------------------------------------------------------
uint8_t MQTT_SubscribeJson(void)
{
	uint8_t i,j;
	char *p;
	char ipbuf[10];
	
	
	p = strstr((char *)WIFI_RxBuf,"+MQD:");
	if(p)
	{
		p = strstr(p,MQTT_TOPIC);
		if(p)
		{
			p = strstr(p,"{\"");
			if(p)
			{
				//myOLED.clearScreen();
				//myOLED.println((char *)(p+1));
				JSON_ptr=p;
				//p = strstr(p,"}");
				//*(p+1)=0;
				return 1;
			}
		}
	}
	return 0;
}

//-------------------------------------------------------------------
int main(void)
{
	int i;
	char buf[40];
	
	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HMI MQTT Test");

	WIFI_Serial.begin(115200);//WIFI
	WIFI_RxBufCount=0;
	WIFI_RxBufCountOld=0;
	WIFI_Step=0;
	
	//JSON INIT
	jsmn_init(&JSON_p);
	
	WIFI_ConnectAP();

	//loop
	while (1)
	{
		if(WIFI_Step==0)
		{
			if(WIFI_IsConnect()==1)
			{
				WIFI_Step=1;
				WIFI_ConnectMQTT();
			}
			delay(500);
		}
		else if(WIFI_Step==1)
		{
			i=MQTT_IsConnect();
			if(i==2)
			{
				delay(200);
				WIFI_Serial.println("AT+MQSTART");	
			}
			else if(i==1)
			{
				delay(200);
				WIFI_MQTT_Subscribe(MQTT_TOPIC,1);
				WIFI_Step=2;
			}
			delay(500);
		}
		delay(10);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				digitalWrite(LED_R, HIGH);
				myOLED.setPosi(2, 0);
				//WIFI_PutCommand("AT+MQSTART");
				//WIFI_ConnectMQTT();
				WIFI_IsConnect();
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
				//digitalWrite(LED_R, HIGH);
				//myOLED.setPosi(2, 0);
				//WIFI_MQTT_Publish("HUSTKIT1",sendmqtts);
				//WIFI_MQTT_Subscribe("HUSTKIT1",1);
				//delay(100);
				//digitalWrite(LED_R, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		
		i=WIFI_Get();
		if(WIFI_Step==2)
		{
			if(i==1)
			{
				if(MQTT_SubscribeJson()==1)
				{						
					myOLED.setPosi(0, 0);
					//myOLED.println((char *)JSON_ptr);  
					JSON_r = jsmn_parse(&JSON_p, JSON_ptr, strlen(JSON_ptr), JSON_t, sizeof(JSON_t)/sizeof(JSON_t[0]));
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
								sprintf(buf,"%.*s", JSON_t[i+1].end-JSON_t[i+1].start,JSON_ptr + JSON_t[i+1].start);
								myOLED.println(atoi(buf));
								//myOLED.println(atof(buf));
								i++;
							} 
							else if (jsoneq(JSON_ptr, &JSON_t[i], "LIGHT1") == 0) 
							{
								// We may want to do strtol() here to get numeric value 
								sprintf(buf,"%.*s", JSON_t[i+1].end-JSON_t[i+1].start,JSON_ptr + JSON_t[i+1].start);
								myOLED.println(atoi(buf));
								//myOLED.println(atof(buf));
								i++;
							}
						}
					}
					
				}					
			}
			//Auto send 10 sec
			sendocount++;
			if(sendocount>1000)
			{
				sendocount=0;
				WIFI_MQTT_Publish(MQTT_TOPIC,sendmqtts);
			}
		}
		
	}
}
