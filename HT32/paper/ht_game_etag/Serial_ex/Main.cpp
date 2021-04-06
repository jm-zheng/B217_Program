//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;


//-------------------------------------------------------------------
#define VOC_Serial	Serial1
uint8_t VOC_RxBufCount;
uint8_t VOC_Count;
uint8_t VOC_RxBuf[100];

//-------------------------------------------------------------------
#include "BH1750.h" // BH1750
#define SDA_PIN PC7 ///< pin for SDA
#define SCL_PIN PC6 ///< pin for SCL
BH1750 lux;


//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
uint8_t ZIGBEE_RxBuf[100];
uint8_t RxBufCount;
uint8_t RxBufCountOld;
uint8_t RxBuf[100];
uint8_t RxBufCount1;
uint8_t RxBufCountOld1;
uint8_t RxBuf1[100];
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

//-----------------------------------------------------
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

/*void blink(void) 
{
  vibration_value++;
	shock_counts ++;
	
}*/
//-------------------------------------------------------------------
int count=0;

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

	int second_flag=1;
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
  myOLED.println("etag_test");
	// VOC
	VOC_Serial.begin(9600); // VOC module

	// BH1750
	lux.begin(SDA_PIN, SCL_PIN);

	
//--------------------------------------------
	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	//-------Serial-----------------------	
	ZIGBEE_Serial.begin(9600);
	//ZIGBEE_setup(26, 0x1002, 0x2002);
	
	
	//loop
	while (1)
	{
		delay(1);
		//second_flag += 1;
		if (VOC_Get() == 1)
		{
			if (VOC_RxBuf[0] == 0x42 && VOC_RxBuf[1] == 0x4D)
			{
				myOLED.setPosi(0, 0); 
				myOLED.print("abc");
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
				myOLED.print("et:");
				myOLED.print(Tem_Value);
				myOLED.print("eh:");
				myOLED.println(Hum_Value);
				myOLED.print("ec:");
				myOLED.println(eCO2_Value);
			  myOLED.print("ef:");
				myOLED.println(CH2O_Value);
				myOLED.print("ev:");
				myOLED.print(TVOC_Value);
			  myOLED.print("el:");
				myOLED.println(Lux_Value);
				
				ZIGBEE_Serial.write(0x01);
				ZIGBEE_Serial.write(0x01);
				ZIGBEE_Serial.write(0x04);
				ZIGBEE_Serial.print("et:");;
				ZIGBEE_Serial.print(Tem_Value);
				ZIGBEE_Serial.print(",eh:");;
				ZIGBEE_Serial.print(Hum_Value);				
				ZIGBEE_Serial.print(",ec:");
				ZIGBEE_Serial.print(eCO2_Value);
				ZIGBEE_Serial.print(",ef:");
				ZIGBEE_Serial.print(CH2O_Value);
				ZIGBEE_Serial.print(",ev:");
				ZIGBEE_Serial.print(TVOC_Value);
				ZIGBEE_Serial.print(",el:");;
				ZIGBEE_Serial.print(Lux_Value);
				ZIGBEE_Serial.print("*");
				//ZIGBEE_Serial.println("*");
			}
		}
		
		/*if(second_flag == 1000)
		{
			second_flag=1;
			  Lux_Value = lux.readLightLevel();							
		    myOLED.setPosi(0, 0);
				myOLED.print("et:");
				myOLED.print(Tem_Value);
				myOLED.print("eh:");
				myOLED.println(Hum_Value);
				myOLED.print("ec:");
				myOLED.println(eCO2_Value);
			  myOLED.print("ef:");
				myOLED.println(CH2O_Value);
				myOLED.print("ev:");
				myOLED.print(TVOC_Value);
			  myOLED.print("el:");
				myOLED.println(Lux_Value);
			
			
				
				ZIGBEE_Serial.print("et:");;
				ZIGBEE_Serial.println(Tem_Value);
				ZIGBEE_Serial.print("eh:");;
				ZIGBEE_Serial.println(Hum_Value);				
				ZIGBEE_Serial.print("ec:");
				ZIGBEE_Serial.println(eCO2_Value);
				ZIGBEE_Serial.print("ef:");
				ZIGBEE_Serial.println(CH2O_Value);
				ZIGBEE_Serial.print("ev:");
				ZIGBEE_Serial.println(TVOC_Value);
				ZIGBEE_Serial.print("el:");;
				ZIGBEE_Serial.println(Lux_Value);
				ZIGBEE_Serial.println("*");
				//ZIGBEE_Serial.println("*");
		}*/
	}
}
