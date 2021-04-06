//-------------------------------------------------------------------
// HUSTKIT3_MAC1_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "MLX90614.h" // MLX90614
#define SDA_PIN PA4 ///< pin for SDA
#define SCL_PIN PA5 ///< pin for SCL
MLX90614 mlx;
float AmbientTemp,ObjectTemp; 

//-----------shock------------------------------------------
#define  shock_pin PB0
uint8_t  shock_staus;
uint32_t shock_counts=0 ,shock_flag;
 

//-------ampere------------------------------------------------------
#define   ampere_pin PA1
uint32_t  ampere ,ampere_plus;
uint8_t ampere_staus ,  ampere_conut;
//-------------------------------------------------------------------
#define  counts_pin PA0
uint16_t counts_counts=0 ,counts_staus=0,counts_tag = 0;
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
uint8_t ZIGBEE_RxBuf[100];

//-------------------------------------------------------------------
#define RS232_Serial	Serial1
uint8_t RS232_RxBufCount;
uint8_t RS232_Count;
uint8_t RS232_RxBuf[100];

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;
void blink(void) 
{
  shock_counts ++;
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
		ZIGBEE_Count=0;
		digitalWrite(LED_B, HIGH);
		ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = ZIGBEE_Serial.read();
		if (ZIGBEE_RxBufCount < 99)
		{
			ZIGBEE_RxBufCount++;
		}
	}

	if (ZIGBEE_Count++ >= 20)
	{
		ZIGBEE_Count=0;
		if (ZIGBEE_RxBufCount>0)
		{
			ZIGBEE_RxBuf[ZIGBEE_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)ZIGBEE_RxBuf);  
			ZIGBEE_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
uint8_t RS232_Get(void)
{
	
	while (RS232_Serial.available() > 0)
	{
		RS232_Count=0;
		digitalWrite(LED_B, HIGH);
		RS232_RxBuf[RS232_RxBufCount] = RS232_Serial.read();
		if (RS232_RxBufCount < 99)
		{
			RS232_RxBufCount++;
		}
	}

	if (RS232_Count++ >= 20)
	{
		RS232_Count=0;
		if (RS232_RxBufCount>0)
		{
			RS232_RxBuf[RS232_RxBufCount] = 0;
			//myOLED.clearScreen();
			//myOLED.println((char *)RS232_RxBuf);  
			RS232_RxBufCount = 0;
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
	int second_flag=1;
	
	
	

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);
	//---------ampere---------------------
	pinMode(ampere_pin,INPUT);
	
	//-------counts------------------------
	pinMode(PA0,INPUT);

	
	//-------shock------------------------
	pinMode(shock_pin,INPUT_PULLUP);
	attachInterrupt(shock_pin, blink, IT_RISING_FALLING_PULLUP);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("HUSTKIT3 MAC1");

  //-----------mlx-------------
  mlx.begin(SDA_PIN, SCL_PIN);
	
	ZIGBEE_Serial.begin(9600); // Zigbee module
	ZIGBEE_setup(22, 0x2222, 0x3333);

	// RS232
	RS232_Serial.begin(9600,SERIAL_7E1,false); // VOC module

	//loop
	while (1)
	{
		delay(1);
		second_flag+=1;	
		shock_flag +=1;
//---------------shock_flag----------------------------------
		if(shock_flag >100)
		{
			shock_flag=0;
			if (shock_counts < 1)
			{
				shock_staus=0;   //not
			}			
			else if (shock_counts >=1 && shock_counts <7 )
			{
				shock_staus=1;   //slight
			}
				else if (shock_counts >=7 && shock_counts <10 )
			{
				shock_staus=2;   //Moderate
			}
				else 
			{
				shock_staus=3;   //Severe
			}
			/*myOLED.setPosi(2, 0);
			myOLED.print("S:");
			myOLED.println(shock_staus);
			//shock_staus = 0;*/
			shock_counts=0;
		 }
	  
		
//-------------counts---------------------------------
		if(digitalRead(counts_pin) == LOW)
		{
			if(counts_tag == 1)
			{
				counts_tag = 0;
				counts_staus =1 ;	
			}
			else if(counts_staus == 1  && counts_tag == 0)
			{			
				counts_counts +=1 ;
				counts_staus =0 ;
			}
		}
		else 
		{
			counts_staus = 0;
			counts_tag = 1;
		}
		
	/*
			myOLED.setPosi(4, 0);
			myOLED.print("C:");
			myOLED.println(counts_counts);*/
		
//-------ampere-------------------------------------
		ampere = analogRead(ampere_pin);
		ampere_plus = ampere_plus + ampere;
		ampere_conut++;

		if (ampere_conut > 100)
		{
			ampere_conut = 0 ;
			ampere_plus=ampere_plus /10;
			
			if (ampere_plus< 3 )
			{
				ampere_staus = 0 ;
			}
			else 
			{
				ampere_staus = 1;
			}	
		/*
				myOLED.setPosi(6, 0);
				myOLED.print("A:");
				myOLED.println(ampere_staus);*/
					
			ampere_plus =0;
		}
//----------------mlx---------------------------
   /* ObjectTemp=mlx.readObjectTempC();
		myOLED.setPosi(0, 0);
		myOLED.print("T:");
		myOLED.println(ObjectTemp);*/
		if(second_flag == 500)
			{
				second_flag=1;
				ObjectTemp=mlx.readObjectTempC();
									
				myOLED.setPosi(0, 0);
				myOLED.print("T:");
				myOLED.println(ObjectTemp);
				myOLED.print("S:");
				myOLED.println(shock_staus);
				myOLED.print("C:");
				myOLED.println(counts_counts);
				myOLED.print("A:");
				myOLED.println(ampere_staus);
				
				ZIGBEE_Serial.print("{\"T1\":");
				ZIGBEE_Serial.print(ObjectTemp);
				ZIGBEE_Serial.print(",\"S1\":");
				ZIGBEE_Serial.print(shock_staus);
				ZIGBEE_Serial.print(",\"C1\":");
				ZIGBEE_Serial.print(counts_counts);
				ZIGBEE_Serial.print(",\"A1\":");
				ZIGBEE_Serial.print(ampere_staus);
				ZIGBEE_Serial.print("}");
			}
			

		
    if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				digitalWrite(LED_B, HIGH);
				ObjectTemp=mlx.readObjectTempC();
				
									
				myOLED.setPosi(0, 0);
				myOLED.print("T:");
				myOLED.println(ObjectTemp);
				myOLED.print("S:");
				myOLED.println(shock_staus);
				myOLED.print("C:");
				myOLED.println(counts_counts);
				myOLED.print("A:");
				myOLED.println(ampere_staus);
				
				ZIGBEE_Serial.print("{\"T1\":");
				ZIGBEE_Serial.print(ObjectTemp);
				ZIGBEE_Serial.print(",\"S1\":");
				ZIGBEE_Serial.print(shock_staus);
				ZIGBEE_Serial.print(",\"C1\":");
				ZIGBEE_Serial.print(counts_counts);
				ZIGBEE_Serial.print(",\"A1\":");
				ZIGBEE_Serial.print(ampere_staus);
				ZIGBEE_Serial.print("}");
				
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_SELECT_Tag = 1;
		}
		/*if (digitalRead(KEY_ENETR) == 0)
		{
			if (KEY_ENTER_Tag == 1)
			{
				KEY_ENTER_Tag = 0;
				digitalWrite(LED_B, HIGH);
					
				
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
				
				ZIGBEE_Serial.print("{\"T1\":");
				ZIGBEE_Serial.print(Tem_Value);
				ZIGBEE_Serial.print(",\"H1\":");
				ZIGBEE_Serial.print(Hum_Value);
				ZIGBEE_Serial.print(",\"L1\":");
				ZIGBEE_Serial.print(Lux_Value);
				ZIGBEE_Serial.print(",\"CO21\":");
				ZIGBEE_Serial.print(eCO2_Value);
				ZIGBEE_Serial.print(",\"VOC1\":");
				ZIGBEE_Serial.print(TVOC_Value);
				ZIGBEE_Serial.print(",\"CH2O1\":");
				ZIGBEE_Serial.print(CH2O_Value);
				ZIGBEE_Serial.print("}");
				
				digitalWrite(LED_B, LOW);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}*/

		if (RS232_Get() == 1)
		{
			if (RS232_RxBuf[0] == 0x42 && RS232_RxBuf[1] == 0x4D)
			{
				/*
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

				ZIGBEE_Serial.print("{\"T1\":");
				ZIGBEE_Serial.print(Tem_Value);
				ZIGBEE_Serial.print(",\"H1\":");
				ZIGBEE_Serial.print(Hum_Value);
				ZIGBEE_Serial.print(",\"L1\":");
				ZIGBEE_Serial.print(Lux_Value);
				ZIGBEE_Serial.print(",\"CO21\":");
				ZIGBEE_Serial.print(eCO2_Value);
				ZIGBEE_Serial.print(",\"VOC1\":");
				ZIGBEE_Serial.print(TVOC_Value);
				ZIGBEE_Serial.print(",\"CH2O1\":");
				ZIGBEE_Serial.print(CH2O_Value);
				ZIGBEE_Serial.print("}");
				*/
			}
		}
		ZIGBEE_Get();
	}
}
