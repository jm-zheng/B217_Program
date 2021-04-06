//-------------------------------------------------------------------
// DHT12_ex2
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "DHT12.h" // DHT12
#define DATA_PIN  PA1
DHT12 dht;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("DHT12 Test");

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
		dht.startConvert();
		delay(18); // wait DHT12
		dht.getConvert(&h,&t);
		myOLED.setPosi(4,0);
		myOLED.print("Humidity:"); 
		myOLED.println(h);
		myOLED.setPosi(6,0);
		myOLED.print("Temp.:"); 
		myOLED.println(t);
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(250);// wait next convert
	}
}
