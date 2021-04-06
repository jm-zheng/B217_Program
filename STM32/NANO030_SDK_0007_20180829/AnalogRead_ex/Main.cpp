//-------------------------------------------------------------------
// AnalogRead_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

// AnalogRead PIN
// PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,AI_TEMP,AI_VREF,AI_VBAT
// analogRead is 0-255 (8 bits)
// analogRead12 is 0-2048 (12 bits)
// AI_TEMP is TEMPSENSOR
// AI_VREF is VREFINT
// AI_VBAT is VBAT

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("AnalogRead Test");

	//loop
	while (1)
	{
	  myOLED.setPosi(2,0);
		myOLED.print("PA0 AD=");
		myOLED.println(analogRead(PA0)); 
	  myOLED.setPosi(4,0);
		myOLED.print("PA1 AD=");
		myOLED.println(analogRead12(PA1));
	  myOLED.setPosi(6,0);
		myOLED.print("Temp AD=");
		myOLED.println(analogRead12(AI_TEMP));
	}
}
