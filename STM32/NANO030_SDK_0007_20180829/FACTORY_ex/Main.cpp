//-------------------------------------------------------------------
// OLED_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
int count=0;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
  myOLED.println("Factory Test");
  myOLED.println("2018/03/20");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);

	//loop
	while (1)
	{
	  myOLED.setPosi(4,0);
		myOLED.println("LED Blue");
		digitalWrite(LED_R,LOW);
		digitalWrite(LED_B,HIGH);
		
		delay(200);
	  myOLED.setPosi(4,0);
		myOLED.println("LED Red ");
		digitalWrite(LED_B,LOW);
		digitalWrite(LED_R,HIGH);
		
		delay(200);
	  myOLED.setPosi(6,0);
		myOLED.print("Count=");
		myOLED.println(count++);
	}
}
