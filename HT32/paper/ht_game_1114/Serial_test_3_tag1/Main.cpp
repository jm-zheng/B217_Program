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
//------------------------------------------------------------
#define count2_pin PB4
uint16_t count2_counts=0 ,count2_staus=0,count2_tag = 0;
//--------------------------------------------------------------------
#define   ampere_pin PA1
int readapval=0 ;
int maxapval=0 ;
double ampere_value=0;

//-----------shock------------------------------------------
#define  shock_pin PC8
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
#define LORA_Serial	Serial
uint8_t LORA_RxBufCount;
uint8_t LORA_Count;
char LORA_RxBuf[100];

//-------------------------------------------------------------------
#define RS232_Serial Serial1
uint8_t RS232_RxBufCount=0;
uint8_t RS232_RxBufCountOld;
uint8_t RS232_RxBuf[100];


uint8_t plc_stop =0;
uint8_t plc_bt =0;




void blink(void) 
{
  vibration_value++;
	shock_counts ++;
	
}




//-------------------------------------------------------------------
//int count=0;

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
	
	pinMode(count2_pin,INPUT);
	
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
	LORA_Serial.begin(9600);
	//ZIGBEE_setup(26,0x1002,0x2002);
	RS232_Serial.begin(9600);
	
	//loop
	while (1)
	{
		delay(1);
		second_flag += 1;
		
		//shock_flag +=1;
//---------------shock_flag----------------------------------
		/*if(shock_flag >100)
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
			myOLED.setPosi(2, 0);
			myOLED.print("S:");
			myOLED.println(shock_staus);
			//shock_staus = 0;
			shock_counts=0;
		 }*/
						
	
	//-----------------------------------------
	
		//----------------------------------------------
		if(second_flag == 1000)
		{
		
			second_flag=1;
			
			
			ObjectTemp=mlx.readObjectTempC();
			
								
			myOLED.setPosi(0, 0);
			myOLED.print("st1:");
			myOLED.println(ObjectTemp);
			myOLED.print("ss1:");
			myOLED.println(shock_counts);
			//rs232_read_d();
			
			//myOLED.println("*");
			LORA_Serial.write(0x01);
			LORA_Serial.write(0x01);
			LORA_Serial.write(0x04);
			LORA_Serial.print("st1:");
			LORA_Serial.print(ObjectTemp);
			LORA_Serial.print(",sa1:");
			LORA_Serial.print(ampere_value);
			LORA_Serial.print(",ss1:");
			LORA_Serial.print(shock_counts);
			
			LORA_Serial.print("*");
			//LORA_Serial.println("*");
			shock_counts = 0;
			RS232_RxBufCount = 0;
			maxapval =0;
			
		}
	}
		
	
}