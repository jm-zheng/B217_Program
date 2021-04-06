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

//--------------------------------------------------
#define RS232_Serial Serial1
uint8_t RS232_RxBufCount=0;
uint8_t RS232_RxBufCountOld;
uint8_t RS232_RxBuf[100];
uint8_t Set_M1[] = {0x02,0x31,0x30,0x31,0x30,0x30,0x30,0x31,0x30,0x32,0x03,0x42,0x38};
/*uint8_t RxBufCount1;
uint8_t RxBufCountOld1;
uint8_t RxBuf1[100];*/
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
	//ZIGBEE_setup(26, 0x1001, 0x2002);
	RS232_Serial.begin(9600);
	
	
	//loop
	while (1)
	{
		delay(1);
		if(digitalRead(KEY_SELECT) == LOW)
		{
			if(KEY_SELECT_Tag == 1)
			{
				myOLED.print("asd");
				
				for(int i=0;i<13;i++)
				{
					RS232_Serial.write(Set_M1[i]);
					//myOLED.print(Set_M1[i]);
				}
				KEY_SELECT_Tag = 0;
			}
			
		}
		else
		{
			KEY_SELECT_Tag = 1;
		}
		while (RS232_Serial.available()>0)
		{
			digitalWrite(LED_B, HIGH);
			RS232_RxBuf[RS232_RxBufCount]=RS232_Serial.read();
			ZIGBEE_Serial.write (RS232_RxBuf[RS232_RxBufCount]) ;
			//ZIGBEE_Serial.write(0x0a);
			
			RS232_RxBufCount +=1 ;
 		}
		ZIGBEE_Serial.write(RS232_RxBuf[1]);
		ZIGBEE_Serial.write(RS232_RxBuf[2]);
	  //ZIGBEE_Serial.write(RS232_RxBufCount);
		RS232_RxBufCount = 0;
		digitalWrite(LED_B, LOW);
		
		delay(1500);
	
	}
}
