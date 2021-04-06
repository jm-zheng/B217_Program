//-------------------------------------------------------------------
// ADXL345_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "CCS811.h" // DS18B20
#define SDA_PIN PA4 ///< pin for SDA
#define SCL_PIN PA5 ///< pin for SCL
CCS811 voc;

float humidity ;
float temp;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("VOC Test");

  delay(100);
  // VOC
  voc.begin(SDA_PIN, SCL_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
  
	//loop
	while (1)
	{
		delay(1000);
		digitalWrite(LED_R,HIGH);// LED Red ON
		
    voc.getData();
		
    humidity = ((125 * voc.readHUMIDITY() ) / 65536.0) - 6;
    temp = ((175.72 * voc.readTEMPERATURE() )/ 65536.0) - 46.85;
		myOLED.setPosi(0,0);
    myOLED.print("temp :");        myOLED.println(temp);
    myOLED.print("humidity :");    myOLED.println(humidity);
    myOLED.print("co2 :");         myOLED.println(voc.readCO2());
    myOLED.print("Tvoc :");        myOLED.println(voc.readTVOC());

		digitalWrite(LED_R,LOW);// LED Red OFF
	}
}
