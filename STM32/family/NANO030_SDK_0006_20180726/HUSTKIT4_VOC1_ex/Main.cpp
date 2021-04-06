//-------------------------------------------------------------------
// HUSTKIT4_VOC1_ex
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
#define VOC_Serial	Serial1
uint8_t VOC_RxBufCount;
uint8_t VOC_Count;
uint8_t VOC_RxBuf[100];

//-------------------------------------------------------------------
#include "BH1750.h" // BH1750
#define SDA_PIN PA7 ///< pin for SDA
#define SCL_PIN PA6 ///< pin for SCL
BH1750 lux;

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
uint8_t VOC_Get(void)
{
	while (VOC_Serial.available() > 0)
	{
		VOC_Count=0;
		digitalWrite(LED_B, HIGH);
		VOC_RxBuf[VOC_RxBufCount] = VOC_Serial.read();
		if (VOC_RxBufCount < 99)
		{
			VOC_RxBufCount++;
		}
	}

	if (VOC_Count++ >= 20)
	{
		VOC_Count=0;
		if (VOC_RxBufCount>0)
		{
			VOC_RxBuf[VOC_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)VOC_RxBuf);  
			VOC_RxBufCount = 0;
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
	myOLED.println("HUSTKIT4 VOC1");

	LORA_Serial.begin(9600); // Zigbee module
	pinMode(LORA_MODE0, OUTPUT);
	pinMode(LORA_MODE1, OUTPUT);
	digitalWrite(LORA_MODE0, LOW);
	digitalWrite(LORA_MODE1, LOW);

	// VOC
	VOC_Serial.begin(9600); // VOC module

	// BH1750
	lux.begin(SDA_PIN, SCL_PIN);

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
				Lux_Value = lux.readLightLevel();			
				
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
				Lux_Value = lux.readLightLevel();			
				
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

				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}

		if (VOC_Get() == 1)
		{
			if (VOC_RxBuf[0] == 0x42 && VOC_RxBuf[1] == 0x4D)
			{
				Tem_H = VOC_RxBuf[5];
				Tem_L = VOC_RxBuf[6];
				STem = Tem_H * 256+Tem_L;
				Tem_Value =  - 46.85 + 175.72 * (float)STem / 65536.0;
				Hum_H = VOC_RxBuf[7];
				Hum_L = VOC_RxBuf[8];
				SRH = Hum_H * 256+Hum_L;
				Hum_Value =  - 6+125 * SRH / 65536;
				eCO2_H = VOC_RxBuf[9];
				eCO2_L = VOC_RxBuf[10];
				eCO2_Value = eCO2_H * 256+eCO2_L;
				TVOC_H = VOC_RxBuf[11];
				TVOC_L = VOC_RxBuf[12];
				TVOC_Value = TVOC_H * 256+TVOC_L;
				CH2O_H = VOC_RxBuf[13];
				CH2O_L = VOC_RxBuf[14];
				CH2O_Value = CH2O_H * 256+CH2O_L;
				Lux_Value = lux.readLightLevel();				
				
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
			}
		}
		LORA_Get();
	}
}
