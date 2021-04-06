//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//------------------------------------------------------------------------------
#define LS_PIN  	PA1

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();
	
  // KEY / LED
	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);
	
  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("Llluminance Test");

	//loop
  while (1)
  {
		
		int sensorValue = analogRead(LS_PIN);
	  myOLED.setPosi(4,0);
		myOLED.print("Sensor = ");
		myOLED.println(sensorValue);		
		delay(200);
		
		digitalWrite(LED_B, LOW);
		digitalWrite(LED_R, LOW);
		delay(5);
		digitalWrite(LED_B, HIGH);
		digitalWrite(LED_R, HIGH);
		delay(5);
  }
}
