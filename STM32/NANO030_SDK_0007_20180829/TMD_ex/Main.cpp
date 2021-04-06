//-------------------------------------------------------------------
// TMD_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "TMD.h" // DS18B20
#define SDA_PIN PA2 ///< pin for SDA
#define SCL_PIN PA3 ///< pin for SCL
TMD tmd;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("TMD Test");

  // TMD
  tmd.begin(SDA_PIN, SCL_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
  
	//loop
	while (1)
	{
		digitalWrite(LED_R,HIGH);// LED Red ON
		
		// Convert the data
		int c0Data = tmd.getData(0x94); //Read Ch0 , Reads two bytes from sequential registers 0x14 and 0x15		
		int c1Data = tmd.getData(0x96); //Read Ch1 , Reads two bytes from sequential registers 0x16 and 0x17	
		int proximity = tmd.getData(0x98); // Proximity value , Reads two bytes from sequential registers 0x18 and 0x19
		float CPL = (101.0) / 24.0;
		float luminance1 = (1 * c0Data - 2 * c1Data) / CPL;
		float luminance2 = (0.6 * c0Data - 1.00 * c1Data) / CPL;
		float luminance = 0.0;
 
		if((luminance1 > 0) && (luminance1 > luminance2))
		{
			luminance = luminance1;
		}
		else if((luminance2 > 0) && (luminance2 > luminance1))
		{
			luminance = luminance2;
		}
		// Output data to serial monitor
		myOLED.setPosi(2,0);
		myOLED.print("Lux:");
		myOLED.println(luminance);
		myOLED.print("Prox:");
		myOLED.println(proximity);
	
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(100);
	}
}
