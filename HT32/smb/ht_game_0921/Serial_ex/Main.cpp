//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;
//--------------------------------------------------------------------
#define counts_pin PA0
uint16_t counts_counts=0 ,counts_staus=0,counts_tag = 0;
//--------------------------------------------------------------------
#define   ampere_pin PA1
uint32_t  ampere ,ampere_plus;
uint32_t ampere_value;
uint8_t ampere_staus ,  ampere_conut;
//-----------shock------------------------------------------
#define  shock_pin PC9
uint8_t  shock_staus;
uint32_t shock_counts=0 ,shock_flag ,vibration_value;
//-------------------------------------------------------------------

#include "MLX90614.h" // MLX90614
#define SDA_PIN PC7 ///< pin for SDA
#define SCL_PIN PC6 ///< pin for SCL
MLX90614 mlx;
float AmbientTemp,ObjectTemp; 

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
void blink(void) 
{
  vibration_value++;
	shock_counts ++;
	
}
//-------------------------------------------------------------------
int count=0;

//-------------------------------------------------------------------
int main(void)
{
	uint8_t i;
	int second_flag=1;
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
  myOLED.println("Serial Test");

	//---------------------------------------------------------------
	mlx.begin(SDA_PIN, SCL_PIN);
	
	//---------ampere---------------------
	pinMode(ampere_pin,INPUT);
	
	//-------counts------------------------
	pinMode(counts_pin,INPUT);

	
	//-------shock------------------------
	pinMode(shock_pin,INPUT_PULLUP);
	attachInterrupt(shock_pin, blink, IT_RISING_FALLING_PULLUP);
//--------------------------------------------
	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	//-------Serial-----------------------	
	ZIGBEE_Serial.begin(9600);
	ZIGBEE_setup(26, 0x1001, 0x2002);
	
	
	//loop
	while (1)
	{
		delay(1);
		second_flag += 1;
		
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
						
	
	//-----------------------------------------
		if (digitalRead(counts_pin)==LOW)
		{
			if(counts_tag == 1)
			{
				counts_tag = 0;
				counts_staus = 1;
			}
			else if (counts_staus == 1 && counts_tag==0)
			{
				counts_staus = 0;	
				counts_counts ++;
			}
		}
    else 
		{
			counts_tag = 1;
		}
		
		
		if(second_flag == 1000)
		{
			second_flag=1;
			ObjectTemp=mlx.readObjectTempC();
								
			myOLED.setPosi(0, 0);
			myOLED.print("MT1:");
			myOLED.println(ObjectTemp);
			myOLED.print("MS1:");
			myOLED.println(shock_staus);
			myOLED.print("MC1:");
			myOLED.println(counts_counts);
			/*myOLED.print("MA1:");
			myOLED.println(ampere_staus);*/
			
			ZIGBEE_Serial.print("MT1:");
			ZIGBEE_Serial.println(ObjectTemp);
			ZIGBEE_Serial.print("MS1:");
			ZIGBEE_Serial.println(shock_staus);
			//ZIGBEE_Serial.print("MV1:");
			//ZIGBEE_Serial.print(vibration_value);vibration_value=0;
			ZIGBEE_Serial.print("MC1");
			ZIGBEE_Serial.println(counts_counts);
			/*ZIGBEE_Serial.print(",\"MI1\":");
			ZIGBEE_Serial.print(ampere_staus);
			ZIGBEE_Serial.print(",\"MA1\":");
			ZIGBEE_Serial.print(ampere_value*0.03587,0);ampere_value=0;
			ZIGBEE_Serial.println("}");*/
		}
	}
}
