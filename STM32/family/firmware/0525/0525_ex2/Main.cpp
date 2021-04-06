//-------------------------------------------------------------------
// DHT12_ex2
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "DHT12.h" // DHT12
#define DATA_PIN  PA1
DHT12 dht;

#include "ADXL345.h" // DS18B20
#define SDA_PIN PA4 ///< pin for SDA
#define SCL_PIN PA5 ///< pin for SCL
ADXL345 adxl;
//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("BD104102");
	
	 // ADXL345
  adxl.begin(SDA_PIN, SCL_PIN);

  // DHT12
  dht.begin(DATA_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
	
	
  
	//loop
	while (1)
	{
		float h,t;
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
		myOLED.print("X=");
		myOLED.print(fX);
		myOLED.print("Y=");
		myOLED.print(fY);
		myOLED.print("Z=");
		myOLED.println(fZ);
		dht.startConvert();
		delay(18); // wait DHT12
		dht.getConvert(&h,&t);
		myOLED.setPosi(4,0);
		myOLED.print("H:"); 
		myOLED.println(h);
		myOLED.setPosi(6,0);
		myOLED.print("T:"); 
		myOLED.println(t);
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(250);// wait next convert
	}
}
