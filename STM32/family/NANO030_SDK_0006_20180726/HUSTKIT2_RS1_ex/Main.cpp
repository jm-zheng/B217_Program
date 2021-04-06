//-------------------------------------------------------------------
// HUSTKIT2_RS1_ex
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
#define RS485_Serial	Serial1
uint8_t RS485_RxBufCount;
uint8_t RS485_Count;
uint8_t RS485_RxBuf[100];
uint16_t RS485_ScanCount;
uint8_t RS485_ScanTag;

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

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
uint8_t RS485_Get(void)
{
	while (RS485_Serial.available() > 0)
	{
		RS485_Count=0;
		digitalWrite(LED_B, HIGH);
		RS485_RxBuf[RS485_RxBufCount] = RS485_Serial.read();
		if (RS485_RxBufCount < 99)
		{
			RS485_RxBufCount++;
		}
	}

	if (RS485_Count++ >= 20)
	{
		RS485_Count=0;
		if (RS485_RxBufCount>0)
		{
			RS485_RxBuf[RS485_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)RS485_RxBuf);  
			RS485_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}


//-------------------------------------------------------------------
void RS485_Get_EC_T(void)
{
	// 0x01 0x03 0x00 0x00 0x00 0x02 0xC4 0x0B
	RS485_Serial.write(0x01); // EC ADDR = 1
	RS485_Serial.write(0x03);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x02);
	RS485_Serial.write(0xC4);
	RS485_Serial.write(0x0B);
}

//-------------------------------------------------------------------
void RS485_Get_PH(void)
{
	// 0x02 0x03 0x00 0x00 0x00 0x01 0x84 0x39
	RS485_Serial.write(0x02); // PH ADDR = 2
	RS485_Serial.write(0x03);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x00);
	RS485_Serial.write(0x01);
	RS485_Serial.write(0x84);
	RS485_Serial.write(0x39);
}

//-------------------------------------------------------------------
int main(void)
{
	int Tem_H, Tem_L;
	float Tem_Value;
	int Hum_H, Hum_L;
	float Hum_Value;
	int Ph_H, Ph_L;
	float Ph;

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT2 RS1");

	LORA_Serial.begin(9600); // LORA module
	pinMode(LORA_MODE0, OUTPUT);
	pinMode(LORA_MODE1, OUTPUT);
	digitalWrite(LORA_MODE0, LOW);
	digitalWrite(LORA_MODE1, LOW);
	LORA_RxBufCount=0;

	// RS485
	RS485_Serial.begin(9600); // 
	RS485_RxBufCount=0;
	RS485_ScanCount=0;
	RS485_ScanTag=0;

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
				RS485_ScanTag=1;
				RS485_Get_EC_T();
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
				RS485_ScanTag=0;
				RS485_Get_PH();
				delay(100);
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}
		
		RS485_ScanCount++;
		if(RS485_ScanCount>=5000) // 5000=1S
		{
			RS485_ScanCount=0;
			if(RS485_ScanTag==0)
			{
				RS485_ScanTag=1;
				RS485_Get_EC_T();
			}
			else
			{
				RS485_ScanTag=0;
				RS485_Get_PH();
			}
		}
		
		if (RS485_Get() == 1)
		{
			// EC&T
			if (RS485_RxBuf[0] == 0x01 && RS485_RxBuf[1] == 0x03 && RS485_RxBuf[2] == 0x04)
			{
				Tem_H = RS485_RxBuf[3];
				Tem_L = RS485_RxBuf[4];
				Tem_Value = (float)(Tem_H*256+Tem_L)/10.0;
				Hum_H = RS485_RxBuf[5];
				Hum_L = RS485_RxBuf[6];
				Hum_Value = (float)(Hum_H*256+Hum_L)/10.0;

				myOLED.setPosi(2, 0);
				myOLED.print("T:");
				myOLED.println(Tem_Value);
				myOLED.print("H:");
				myOLED.println(Hum_Value);

				LORA_Serial.print("{\"ST2\":");
				LORA_Serial.print(Tem_Value);
				LORA_Serial.print(",\"SH2\":");
				LORA_Serial.print(Hum_Value);
				LORA_Serial.print("}");				
			}
			// PH
			if (RS485_RxBuf[0] == 0x02 && RS485_RxBuf[1] == 0x03 && RS485_RxBuf[2] == 0x02)
			{
				Ph_H = RS485_RxBuf[3];
				Ph_L = RS485_RxBuf[4];
				Ph = (float)(Ph_H*256+Ph_L)/100.0;
				myOLED.setPosi(6, 0);
				myOLED.print("Ph:");
				myOLED.println(Ph);

				LORA_Serial.print("{\"PH2\":");
				LORA_Serial.print(Ph);
				LORA_Serial.print("}");
			}
		}
		LORA_Get();
	}
}
