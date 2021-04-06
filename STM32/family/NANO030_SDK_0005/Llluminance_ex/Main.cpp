//-------------------------------------------------------------------
// Llluminance_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//------------------------------------------------------------------------------
#define LS_PIN  	PA1

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

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
	}
}
