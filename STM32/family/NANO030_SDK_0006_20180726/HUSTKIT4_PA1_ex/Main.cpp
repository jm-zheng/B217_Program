//-------------------------------------------------------------------
// HUSTKIT4_PA1_ex
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

	if (LORA_Count++ >= 20)
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
	int Lux_Value;
	int Tem_H, Tem_L, STem;
	float Tem_Value;
	int SRH, Hum_H, Hum_L, Hum_Value;
	int eCO2_H, eCO2_L, eCO2_Value;
	int TVOC_H, TVOC_L, TVOC_Value;
	int CH2O_H, CH2O_L, CH2O_Value;

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT4 PA1");

	LORA_Serial.begin(9600); // Zigbee module
	pinMode(LORA_MODE0, OUTPUT);
	pinMode(LORA_MODE1, OUTPUT);
	digitalWrite(LORA_MODE0, LOW);
	digitalWrite(LORA_MODE1, LOW);

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
				
				
				/*
				
				myOLED.setPosi(0, 0);
				myOLED.print("T:");
				myOLED.print(Tem_Value);
				myOLED.print(" H:");
				myOLED.println(Hum_Value);
				myOLED.print("Lux:");
				myOLED.println(Lux_Value);
				myOLED.print("eCO2:");
				myOLED.println(eCO2_Value);
				myOLED.print("TVOC:");
				myOLED.print(TVOC_Value);
				myOLED.print(" CH2O:");
				myOLED.println(CH2O_Value);
				
				LORA_Serial.print("{\"T1\":");
				LORA_Serial.print(Tem_Value);
				LORA_Serial.print(",\"H1\":");
				LORA_Serial.print(Hum_Value);
				LORA_Serial.print(",\"L1\":");
				LORA_Serial.print(Lux_Value);
				LORA_Serial.print(",\"CO21\":");
				LORA_Serial.print(eCO2_Value);
				LORA_Serial.print(",\"VOC1\":");
				LORA_Serial.print(TVOC_Value);
				LORA_Serial.print(",\"CH2O1\":");
				LORA_Serial.print(CH2O_Value);
				LORA_Serial.print("}");
				*/
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
				/*		
				myOLED.setPosi(0, 0);
				myOLED.print("T:");
				myOLED.print(Tem_Value);
				myOLED.print(" H:");
				myOLED.println(Hum_Value);
				myOLED.print("Lux:");
				myOLED.println(Lux_Value);
				myOLED.print("eCO2:");
				myOLED.println(eCO2_Value);
				myOLED.print("TVOC:");
				myOLED.print(TVOC_Value);
				myOLED.print(" CH2O:");
				myOLED.println(CH2O_Value);
				
				LORA_Serial.print("{\"T1\":");
				LORA_Serial.print(Tem_Value);
				LORA_Serial.print(",\"H1\":");
				LORA_Serial.print(Hum_Value);
				LORA_Serial.print(",\"L1\":");
				LORA_Serial.print(Lux_Value);
				LORA_Serial.print(",\"CO21\":");
				LORA_Serial.print(eCO2_Value);
				LORA_Serial.print(",\"VOC1\":");
				LORA_Serial.print(TVOC_Value);
				LORA_Serial.print(",\"CH2O1\":");
				LORA_Serial.print(CH2O_Value);
				LORA_Serial.print("}");
				*/
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}

		LORA_Get();
	}
}
