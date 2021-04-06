//-------------------------------------------------------------------
// ADXL345_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "ADXL345.h" // DS18B20
#define SDA_PIN PA2 ///< pin for SDA
#define SCL_PIN PA3 ///< pin for SCL
ADXL345 adxl;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("ADXL345 Test");

  // ADXL345
  adxl.begin(SDA_PIN, SCL_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
  
	//loop
	while (1)
	{
		digitalWrite(LED_R,HIGH);// LED Red ON
		
		int16_t iX, iY, iZ;
		float fX,fY,fZ;  

		iX = adxl.getData(0x32); // Get X
		fX = iX / 256.00;
		iY = adxl.getData(0x34); // Get Y
		fY = iY / 256.00;
		iZ = adxl.getData(0x36); // Get Z
		fZ = iZ / 256.00;

		myOLED.setPosi(2,0);
		myOLED.print("X = ");
		myOLED.println(fX);
		myOLED.setPosi(4,0);
		myOLED.print("Y = ");
		myOLED.println(fY);
		myOLED.setPosi(6,0);
		myOLED.print("Z = ");
		myOLED.println(fZ);
	
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(100);
	}
}
