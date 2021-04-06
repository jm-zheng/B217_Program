//-------------------------------------------------------------------
// HUSTKIT1_HMI_ZIGBEE_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial1
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
uint8_t ZIGBEE_RxBuf[100];

//-------------------------------------------------------------------
#define HMI_Serial	Serial
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
		}
	}
	return cmd;
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
int main(void)
{
	uint16_t cmd;
	uint8_t cmdh,cmdl;
	char buf[40];
	
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HMI ZIGBEE");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	HMI_Serial.begin(115200);//HMI
	HMI_RxBufCount=0;

	ZIGBEE_Serial.begin(9600); // Zigbee module
	ZIGBEE_setup(20, 0x1111, 0x2222);
	ZIGBEE_RxBufCount = 0;
	

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
					ZIGBEE_Serial.print("{\"OUTP1\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x02:
					ZIGBEE_Serial.print("{\"OUTP2\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x03:
					ZIGBEE_Serial.print("{\"WIN1\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x04:
					ZIGBEE_Serial.print("{\"ACCLOCK\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x11:
					ZIGBEE_Serial.print("{\"LIGHT1\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x12:
					ZIGBEE_Serial.print("{\"LIGHT2\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x13:
					ZIGBEE_Serial.print("{\"LIGHT3\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
				case 0x14:
					ZIGBEE_Serial.print("{\"FAN1\":");
					ZIGBEE_Serial.print(cmdl);
					ZIGBEE_Serial.print("}");				
					break;
			}
		}

		if (ZIGBEE_Get() == 1)
		{
			if(jsonGet((char *)ZIGBEE_RxBuf,(char *)"CO21",buf)==1)
			{
				HMI_SetText((char *)"tC1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"VOC1",buf)==1)
			{
				HMI_SetText((char *)"tV1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"T1",buf)==1)
			{
				HMI_SetText((char *)"tT1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"H1",buf)==1)
			{
				HMI_SetText((char *)"tH1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"L1",buf)==1)
			{
				HMI_SetText((char *)"tL1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"CH2O1",buf)==1)
			{
				HMI_SetText((char *)"tO1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"OUTA1",buf)==1)
			{
				HMI_SetText((char *)"tA1",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"OUTA2",buf)==1)
			{
				HMI_SetText((char *)"tA2",buf);
			}
			if (jsonGet((char *)ZIGBEE_RxBuf,(char *)"ACCID",buf)==1)
			{
				HMI_SetText((char *)"tID",buf);
			}
		}		
	}
}
