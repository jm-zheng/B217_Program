//-------------------------------------------------------------------
// DHT12_ex
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
		digitalWrite(LED_R,HIGH);// LED Red ON
		float h = dht.readHumidity();
		float t = dht.readTemperature();
		myOLED.setPosi(4,0);
		myOLED.print("Humidity:"); 
		myOLED.println(h);
		myOLED.setPosi(6,0);
		myOLED.print("Temp.:"); 
		myOLED.println(t);
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(300);
	}
}
