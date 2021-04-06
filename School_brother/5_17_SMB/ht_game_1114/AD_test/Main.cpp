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
#define    sensorTA12  PA0// Analog input pin that sensor is attached to
float getVPP();  

float nVPP;   // Voltage measured across resistor
float nCurrThruResistorPP; // Peak Current Measured Through Resistor
float nCurrThruResistorRMS; // RMS current through Resistor
float nCurrentThruWire;     // Actual RMS current in Wire
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
float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0; 
  
  uint32_t start_time =0;
   while(start_time < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorTA12);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
			 start_time+=1;
			 delay(1);
   }
   start_time = 0;
   // Convert the digital data to a voltage
   result = (maxValue * 5.0)/1024.0;
  
   return result;
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
	pinMode(sensorTA12,INPUT);
	
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
		second_flag +=1 ;
		
    
		
		
		if(second_flag == 1000)
		{
			second_flag=1;
			nVPP = getVPP();
			nCurrThruResistorPP = (nVPP/200.0) * 1000.0;
			nCurrThruResistorRMS = nCurrThruResistorPP * 0.707;
			nCurrentThruWire = nCurrThruResistorRMS * 1000;
			ObjectTemp=mlx.readObjectTempC();
								
			myOLED.setPosi(0, 0);
			myOLED.print("MT1:");
			myOLED.println(ObjectTemp);
			myOLED.print("Current Through Wire :");
			myOLED.println(nCurrentThruWire);
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
