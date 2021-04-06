//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;
//--------------------------------------------------------------------
#define key3 PB2
#define key4 PB3
#define key5 PB5
#define key6 PB4


uint8_t key3_Tag;
uint8_t key4_Tag;
uint8_t key5_Tag;
uint8_t key6_Tag;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define ZIGBEE_Serial	Serial
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
char ZIGBEE_RxBuf[100];

//-------------------------------------------------------------------
#define RS232_Serial Serial1
uint8_t RS232_RxBufCount=0;
uint8_t RS232_RxBufCountOld;
uint8_t RS232_RxBuf[100];
uint8_t read_y_8bit[] = {0x02,0x30,0x30,0x30,0x41,0x30,0x30,0x31,0x03,0x36,0x35};
uint8_t Set_m_8bit_off[] = {0x02,0x31,0x30,0x31,0x30,0x30,0x30,0x31,0x30,0x30,0x03,0x42,0x36};
uint8_t Set_M0[] = {0x02,0x31,0x30,0x31,0x30,0x30,0x30,0x31,0x30,0x31,0x03,0x42,0x37};
uint8_t Set_M1[] = {0x02,0x31,0x30,0x31,0x30,0x30,0x30,0x31,0x30,0x32,0x03,0x42,0x38};
uint8_t Set_M3[] = {0x02,0x31,0x30,0x31,0x30,0x30,0x30,0x31,0x30,0x38,0x03,0x42,0x45};
uint8_t plc_bt =0;



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
  myOLED.println("zigbee_button");

//--------------------------------------------

	pinMode(key3, INPUT_PULLUP);
	pinMode(key4, INPUT_PULLUP);
	pinMode(key5, INPUT_PULLUP);
	pinMode(key6, INPUT_PULLUP);

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
	
	
	//loop
	while (1)
	{
		delay(1);
		if(digitalRead (key3) == LOW)
		{
			if (key3_Tag  == 1)
			{
				key3_Tag = 0;
				ZIGBEE_Serial .print ("BT:0*");
				myOLED.setPosi (4,0);
				myOLED.print ("      ");
				myOLED.setPosi (4,0);
				myOLED.print ("Start");
			}
			
		}
		else 
			key3_Tag = 1;
		//----------------------------------------
		if(digitalRead (key4) == LOW)
		{
			if (key4_Tag  == 1)
			{
				key4_Tag = 0;
				ZIGBEE_Serial .print ("BT:1*");
				myOLED.setPosi (4,0);
				myOLED.print ("      ");
				myOLED.setPosi (4,0);
				myOLED.print ("Clear");
			}
			
		}
		else 
			key4_Tag = 1;
		//--------------------------------------
			if(digitalRead (key5) == LOW)
		{
			if (key5_Tag  == 1)
			{
				key5_Tag = 0;
				ZIGBEE_Serial .print ("BT:4*");
				myOLED.setPosi (4,0);
				myOLED.print ("      ");
				myOLED.setPosi (4,0);
				myOLED.print ("Return");
			}
			
		}
		else 
			key5_Tag = 1;
		//--------------------------------------
		if(digitalRead (key6) == LOW)
		{
			if (key6_Tag  == 1)
			{
				key6_Tag = 0;
				ZIGBEE_Serial .print ("BT:3*");
				myOLED.setPosi (4,0);
				myOLED.print ("      ");
				myOLED.setPosi (4,0);
				myOLED.print ("Stop");
			}
			
		}
		else 
			key6_Tag = 1;
			
	}

}