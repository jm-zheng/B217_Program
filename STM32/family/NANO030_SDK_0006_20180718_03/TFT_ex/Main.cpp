//-------------------------------------------------------------------
// OLED_ex
//-------------------------------------------------------------------
#include "TFT.h" // OLED
TFT myTFT;

//-------------------------------------------------------------------
// Img.cpp
//-------------------------------------------------------------------
extern const unsigned char imgLogo[];//128*64

//-------------------------------------------------------------------
int count=0;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myTFT.begin();
	myTFT.clearScreen();
	
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);

	//loop	
	while (1)
	{
	  myTFT.setPosi(0,0);
		myTFT.setColor(WHITE,BLACK);
		myTFT.println("TFT Test");
	  myTFT.setPosi(2,0);
		myTFT.setColor(RED,YELLOW);
		myTFT.println("Set Color");
		
	  myTFT.setPosi(4,0);
		myTFT.setColor(WHITE,BLUE);
		myTFT.println("LED Blue");
		digitalWrite(LED_R,LOW);
		digitalWrite(LED_B,HIGH);
		
		delay(200);
	  myTFT.setPosi(4,0);
		myTFT.setColor(RED,BLUE);
		myTFT.println("LED Red ");
		digitalWrite(LED_B,LOW);
		digitalWrite(LED_R,HIGH);
		
		myTFT.setColor(WHITE,BLACK);
		delay(200);
	  myTFT.setPosi(6,0);
		myTFT.print("Count=");
		myTFT.println(count++);

		delay(500);
		//image
		myTFT.imageDraw(imgLogo, 0, 0, 128, 64);
		delay(500);
	}
}
