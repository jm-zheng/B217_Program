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
int readapval=0 ;
int maxapval=0 ;
float ampere_value=0;

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

//-------------------------------------------------------------------
#define RS232_Serial Serial1
uint8_t RS232_RxBufCount=0;
uint8_t RS232_RxBufCountOld;
uint8_t RS232_RxBuf[100];
uint8_t read_y_8bit[] = {0x02,0x30,0x30,0x30,0x41,0x30,0x30,0x31,0x03,0x36,0x35};




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
void rs232_read_y()
{
	for(int i=0;i<11;i++)
		{
			RS232_Serial.write(read_y_8bit[i]);
			
		}
		delay(5)	;	
	while (RS232_Serial.available()>0)
		{
			digitalWrite(LED_B, HIGH);
			RS232_RxBuf[RS232_RxBufCount]=RS232_Serial.read();
			//ZIGBEE_Serial.write(RS232_RxBuf[RS232_RxBufCount]) ;
			
			RS232_RxBufCount +=1 ;
 		}
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
	ZIGBEE_setup(26,0x1002,0x2002);
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
		if(second_flag < 999)
		{
			readapval = analogRead(ampere_pin);
			
			if(readapval > maxapval)
			{
				maxapval = readapval;
			}
			ampere_value = 0.0121*maxapval-0.0125;
			if(ampere_value < 0)
			{
				ampere_value = 0 ;
			}
			else
			{
				ampere_value=ampere_value;
			}
		}
		
		else if(second_flag == 1000)
		{
			second_flag=1;
			maxapval =0;
			rs232_read_y();
			ObjectTemp=mlx.readObjectTempC();
								
			myOLED.setPosi(0, 0);
			myOLED.print("st1:");
			myOLED.println(ObjectTemp);
			myOLED.print("ss1:");
			myOLED.println(shock_counts);
			myOLED.print("sp1:");
			myOLED.print(RS232_RxBuf[1]);
			myOLED.println(RS232_RxBuf[2]);
			myOLED.print("sa1:");
			myOLED.println(ampere_value);
			myOLED.print("sc1:");
			myOLED.println(counts_counts);
			/*myOLED.print("MA1:");
			myOLED.println(ampere_staus);*/
			
			ZIGBEE_Serial.print("st1:");
			ZIGBEE_Serial.println(ObjectTemp);
			ZIGBEE_Serial.print("ss1:");
			ZIGBEE_Serial.println(shock_counts);
			ZIGBEE_Serial.print("sp1:");
			ZIGBEE_Serial.write(RS232_RxBuf[1]);
			ZIGBEE_Serial.write(RS232_RxBuf[2]);
			ZIGBEE_Serial.write(0x0a);
			ZIGBEE_Serial.print("sa1:");
			ZIGBEE_Serial.println(ampere_value);
			ZIGBEE_Serial.print("sc1:");
			ZIGBEE_Serial.println(counts_counts);
			ZIGBEE_Serial.println("*");
			ZIGBEE_Serial.println("*");
			shock_counts = 0;
			RS232_RxBufCount = 0;
			
		}
		
	}
}
