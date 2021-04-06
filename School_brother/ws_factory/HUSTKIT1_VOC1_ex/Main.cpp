//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define LORA_Serial	Serial
uint8_t LORA_RxBufCount;
uint8_t LORA_Count;
uint8_t LORA_RxBuf[100];

//------------------------------------------------------------------
#define RESET_ALL_pin PB1
uint8_t RESET_ALL_flag=0;
#define RESET_DAY_pin PB0
uint8_t RESET_DAY_flag=0;
#define MACHINE_COUNTS_pin PA4
uint8_t MACHINE_COUNTS_flag=0;

uint32_t MACHINE_DAY_COUNTS=0;
int MACHINE_ALL_COUNTS=0;


//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//------------------------------------------------------------------------------


//-------------------------------------------------------------------
int main(void)
{
	

	//setup
	SystemClock_Config();

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("WS_test");
	myOLED.setPosi(2,0);
	myOLED.println(MACHINE_DAY_COUNTS);
	myOLED.print(MACHINE_ALL_COUNTS);
	LORA_Serial.begin(9600);
  
	
	pinMode(RESET_ALL_pin,INPUT_PULLUP);
	pinMode(RESET_DAY_pin,INPUT_PULLUP);
	pinMode(MACHINE_COUNTS_pin,INPUT_PULLUP);	

	//loop
	while (1)
	{
		delay(1);
		
		if(digitalRead(MACHINE_COUNTS_pin) == LOW)
		{
		
			if(MACHINE_COUNTS_flag == 0)
			{
				MACHINE_COUNTS_flag = 1;
				
				MACHINE_DAY_COUNTS +=1;
				delay(50);
        MACHINE_ALL_COUNTS +=1;
				
				
				myOLED.setPosi(2,0);
				myOLED.println(MACHINE_DAY_COUNTS);
				myOLED.setPosi(4,0);
				myOLED.print(MACHINE_ALL_COUNTS);
				
				LORA_Serial.write(0xA0);
				LORA_Serial.write(0x01);
				LORA_Serial.write(0x14);
				LORA_Serial.print(MACHINE_DAY_COUNTS);
				LORA_Serial.print(",");
				LORA_Serial.print(MACHINE_ALL_COUNTS);
				LORA_Serial.print("*");
				delay(200);
			}
		}
		else {MACHINE_COUNTS_flag =0;}
		
//--------------------------------------------------		
		
		if(digitalRead(RESET_DAY_pin) == LOW)
		{
			delay(200);
			if(RESET_DAY_flag == 0)
			{
				
				RESET_DAY_flag = 1;

				MACHINE_DAY_COUNTS =0;
				myOLED.setPosi(2,0);
	    	myOLED.print("            ");
				myOLED.setPosi(2,0);
				myOLED.print(MACHINE_DAY_COUNTS);
				LORA_Serial.write(0xA0);
				LORA_Serial.write(0x01);
				LORA_Serial.write(0x14);
				LORA_Serial.print(MACHINE_DAY_COUNTS);
				LORA_Serial.print(",");
				LORA_Serial.print(MACHINE_ALL_COUNTS);
				LORA_Serial.print("*");
				
			}
		}
		else {RESET_DAY_flag =0;}
//--------------------------------------------------			
		
		if(digitalRead(RESET_ALL_pin) == LOW)
		{
			delay(200);
			if(RESET_ALL_flag == 0)
			{
				RESET_ALL_flag = 1;
				MACHINE_ALL_COUNTS =0;
				myOLED.setPosi(4,0);
	    	myOLED.print("            ");
				myOLED.setPosi(4,0);
				myOLED.print(MACHINE_ALL_COUNTS);
				LORA_Serial.write(0xA0);
				LORA_Serial.write(0x01);
				LORA_Serial.write(0x14);
				LORA_Serial.print(MACHINE_DAY_COUNTS);
				LORA_Serial.print(",");
				LORA_Serial.print(MACHINE_ALL_COUNTS);
				LORA_Serial.print("*");
		
			}
		}
		else 
		{RESET_ALL_flag =0;}
			
		
	
	}
}
