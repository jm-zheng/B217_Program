//-------------------------------------------------------------------
// PIR_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#define PIR_OUTPUT			PA3
#define PIR_STATUS			PA2
int state;
int output;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("Key Test");

	pinMode(PIR_OUTPUT, INPUT);
	pinMode(PIR_STATUS, INPUT);
	
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B,LOW);
	digitalWrite(LED_R,LOW);

	//loop
	while (1)
	{
		state = digitalRead(PIR_STATUS);
		output = digitalRead(PIR_OUTPUT);
		myOLED.setPosi(4,0);
		myOLED.print("PIR = ");
		if(state==1)
		{
			myOLED.println("Detecting");  
			digitalWrite(LED_B, HIGH);  
		}
		else   
		{
			myOLED.println("Warm-up");  
			digitalWrite(LED_B, LOW); 
		}
		myOLED.setPosi(6,0);
		myOLED.print("OUT = ");
		if(output==1)
		{
			myOLED.println("ON");  
			digitalWrite(LED_B, LOW); 
		}
		else  
		{
			myOLED.println("OFF");  
			digitalWrite(LED_B, HIGH);  
		}
		delay(20);
	}
}
