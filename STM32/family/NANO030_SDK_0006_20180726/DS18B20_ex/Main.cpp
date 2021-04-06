//-------------------------------------------------------------------
// DS18B20_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "DS18B20.h" // DS18B20
#define DATA_PIN  PA1
DS18B20 ds;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("DS18B20 Test");

  // DS18B20
  ds.begin(DATA_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
  
	//loop
	while (1)
	{
		digitalWrite(LED_R,HIGH);// LED Red ON
		float t = ds.readTemperature();
		myOLED.setPosi(4,0);
		myOLED.print("Temp.: "); 
		myOLED.print(t);
		myOLED.println(" C");          
		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(300);
	}
}
