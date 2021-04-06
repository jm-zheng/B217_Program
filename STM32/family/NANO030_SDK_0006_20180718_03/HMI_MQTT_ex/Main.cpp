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

#define HMI_Serial	Serial
uint8_t HMI_RxBufCount;
uint8_t HMI_RxBufCountOld;
uint8_t HMI_RxBuf[100];

#define WIFI_Serial	Serial1
uint8_t WIFI_RxBufCount;
uint8_t WIFI_RxBufCountOld;
uint8_t WIFI_RxBuf[100];

char *sendmqtts=(char *)"{\"T1\":25.4,\"H1\":85.0,\"L1\":3500,\"CO21\":400,\"VOC1\":0}";

int sendocount;

//-------------------------------------------------------------------
void HMI_PutCommand(char cmd[])
{
	uint8_t i, len;

	len = strlen((const char*)cmd);
	for (i = 0; i < len; i++)
	{
		Serial.write(cmd[i]);
	}
	HMI_Serial.write(0xFF);
	HMI_Serial.write(0xFF);
	HMI_Serial.write(0xFF);
}

//-------------------------------------------------------------------
void HMI_SetValue(char str[], uint16_t val)
{
	char cmd[40];

	sprintf(cmd, "%s.val=%d", str, val);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_SetText(char str[], char txt[])
{
	char cmd[40];

	sprintf(cmd, "%s.txt=\"%s\"", str, txt);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
uint16_t HMI_GetTouch(void)
{
	uint16_t cmd=0;
	//HMI Get Key
	while (HMI_Serial.available() > 0)
	{
		digitalWrite(LED_B, HIGH);
		HMI_RxBuf[HMI_RxBufCount++]=HMI_Serial.read();
	}
		
	if(HMI_RxBufCount>0)
	{
		if(HMI_RxBufCountOld!=HMI_RxBufCount)
		{
			HMI_RxBufCountOld=HMI_RxBufCount;
		}
		else
		{
			if(HMI_RxBufCount==4 && HMI_RxBuf[0]==0x5A && HMI_RxBuf[3]==0x0D)
			{
				cmd=HMI_RxBuf[1];
				cmd<<=8;
				cmd+=HMI_RxBuf[2];
			}
			HMI_RxBufCountOld=HMI_RxBufCount=0;
		}
	}
	return cmd;
}

//-------------------------------------------------------------------
void WIFI_PutCommand(char cmd[])
{
	uint8_t i, len;

	len = strlen((const char*)cmd);
	for (i = 0; i < len; i++)
	{
		WIFI_Serial.write(cmd[i]);
	}
	WIFI_Serial.write(0x0D);
	WIFI_Serial.write(0x0A);
}


//-------------------------------------------------------------------
int main(void)
{
	uint8_t i;
	uint16_t cmd;

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

	HMI_Serial.begin(115200);//HMI
	HMI_RxBufCount=0;
	HMI_RxBufCountOld=0;

	WIFI_Serial.begin(115200);//WIFI
	WIFI_RxBufCount=0;
	WIFI_RxBufCountOld=0;
	
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
				WIFI_Serial.println("AT+MQSTART");
				digitalWrite(LED_R, HIGH);
				//HMI_SetValue((char *)"hL1",10);
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
				myOLED.setPosi(2, 0);
				//Serial1.println("AT+MQSUBSCRIBE=\"HUSTKIT1\",1");
				WIFI_Serial.print("AT+MQPUBLISH=\"HUSTKIT1\",");				
				WIFI_Serial.println(strlen(sendmqtts));
				delay(10);
				Serial1.print(sendmqtts);
				digitalWrite(LED_R, HIGH);
				//HMI_SetValue((char *)"hL1",50);
				delay(100);
				digitalWrite(LED_R, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		
		cmd=HMI_GetTouch();
		if(cmd>0)
		{
			switch(cmd)
			{
				case 0x0101:
					break;
				case 0x0100:
					break;
			}
		}
		
		while (WIFI_Serial.available() > 0)
		{
			digitalWrite(LED_B, HIGH);
			WIFI_RxBuf[WIFI_RxBufCount++]=WIFI_Serial.read();
 		}		

		sendocount++;
		if(sendocount>1000)
		{
			sendocount=0;
			WIFI_Serial.print("AT+MQPUBLISH=\"HUSTKIT1\",");				
			WIFI_Serial.println(strlen(sendmqtts));
			delay(10);
			WIFI_Serial.print(sendmqtts);			
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
		
	}
}
