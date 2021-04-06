//-------------------------------------------------------------------
// HUSTKIT2_HMI_LORA_ex
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
#define HMI_Serial	Serial1
uint8_t HMI_RxBufCount;
uint8_t HMI_Count;
uint8_t HMI_RxBuf[100];

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
void HMI_PutCommand(char cmd[])
{
	HMI_Serial.print(cmd);
	HMI_Serial.write(0xFF);
	HMI_Serial.write(0xFF);
	HMI_Serial.write(0xFF);
	delay(20);
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
		HMI_Count=0;
		digitalWrite(LED_B, HIGH);
		HMI_RxBuf[HMI_RxBufCount]=HMI_Serial.read();
		if (HMI_RxBufCount < 99)
		{
			HMI_RxBufCount++;
		}
	}
		
	if(HMI_Count++>=20)
	{
		HMI_Count=0;
		if(HMI_RxBufCount>0)
		{
			if(HMI_RxBufCount==4 && HMI_RxBuf[0]==0x5A && HMI_RxBuf[3]==0x0D)
			{
				cmd=HMI_RxBuf[1];
				cmd<<=8;
				cmd+=HMI_RxBuf[2];
			}
			HMI_RxBufCount=0;
			digitalWrite(LED_B, LOW);
		}
	}
	return cmd;
}

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
	int light;
	uint16_t cmd;
	uint8_t cmdh,cmdl;
	char buf[40];
	
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT2 HMI");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);
	
	HMI_Serial.begin(115200);//HMI
	HMI_RxBufCount=0;
	
	LORA_Serial.begin(9600); // LORA module
	pinMode(LORA_MODE0, OUTPUT);
	pinMode(LORA_MODE1, OUTPUT);
	digitalWrite(LORA_MODE0, LOW);
	digitalWrite(LORA_MODE1, LOW);
	LORA_RxBufCount=0;

	//loop
	while (1)
	{
		delay(1);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(2, 0);
				digitalWrite(LED_R, HIGH);
				//HMI_SetValue((char *)"hL1",10);
				//HMI_SetText((char *)"tC1",(char *)"27.0");
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
				digitalWrite(LED_R, HIGH);
				//HMI_SetValue((char *)"hL1",10);
				//HMI_SetText((char *)"tH1",(char *)"80");
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
			myOLED.setPosi(6, 0);
			sprintf(buf, "%04X", cmd);
			myOLED.println(buf);
			cmdh=(cmd>>8);
			cmdl=(cmd&0xff);
			switch(cmdh)
			{
				case 0x01:
					LORA_Serial.print("{\"WIN1\":");
					LORA_Serial.print(cmdl);
					LORA_Serial.print("}");
					break;
				case 0x02:
					LORA_Serial.print("{\"WIN2\":");
					LORA_Serial.print(cmdl);
					LORA_Serial.print("}");				
					break;
				case 0x03:
					LORA_Serial.print("{\"PUMP1\":");
					LORA_Serial.print(cmdl);
					LORA_Serial.print("}");				
					break;
				case 0x11:
					LORA_Serial.print("{\"FAN1\":");
					LORA_Serial.print(cmdl);
					LORA_Serial.print("}");				
					break;
			}
		}

		if (LORA_Get() == 1)
		{
			if(jsonGet((char *)LORA_RxBuf,(char *)"CO21",buf)==1)
			{
				HMI_SetText((char *)"tC1",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"VOC1",buf)==1)
			{
				HMI_SetText((char *)"tV1",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"T1",buf)==1)
			{
				HMI_SetText((char *)"tT1",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"H1",buf)==1)
			{
				HMI_SetText((char *)"tH1",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"L1",buf)==1)
			{
				HMI_SetText((char *)"tL1",buf);
				light=atoi(buf);
				if(light>5000)
				{
					
				}
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"CH2O1",buf)==1)
			{
				HMI_SetText((char *)"tO1",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"ST2",buf)==1)
			{
				HMI_SetText((char *)"tT2",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"SH2",buf)==1)
			{
				HMI_SetText((char *)"tH2",buf);
			}
			if (jsonGet((char *)LORA_RxBuf,(char *)"PH2",buf)==1)
			{
				HMI_SetText((char *)"tP2",buf);
			}
		}		
	}
}
