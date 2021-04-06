//-------------------------------------------------------------------
// Main.cpp
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//-------------------------------------------------------------------
int count=0;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
  myOLED.println("OLED Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);

	myOLED.setFont(FONT_6x8);
  myOLED.setPosi(2,0);
  myOLED.println("FONT_6x8");
  myOLED.println("FONT_6x8");
	
	myOLED.setFont(FONT_8x16);
  myOLED.setPosi(2,55);
  myOLED.println("FONT_8x16");
  
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
		
		myOLED.Set_Inverse_Display(count%2);
	}
}
