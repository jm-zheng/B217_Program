//-------------------------------------------------------------------
// ADXL345_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "MLX90614.h" // MLX90614
#define SDA_PIN PA2 ///< pin for SDA
#define SCL_PIN PA3 ///< pin for SCL

MLX90614 mlx;
float AmbientTemp,ObjectTemp;  

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  // OLED
	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("MLX90614 Test");

  // ADXL345
  mlx.begin(SDA_PIN, SCL_PIN);

  // LED
	pinMode(LED_R, OUTPUT);
	digitalWrite(LED_R,LOW); // LED Red OFF
  
	//loop
	while (1)
	{
		digitalWrite(LED_R,HIGH);// LED Red ON
		
		AmbientTemp=mlx.readAmbientTempC();
		ObjectTemp=mlx.readObjectTempC();
		
		myOLED.setPosi(4,0);
		myOLED.print("Ambient:");
		myOLED.println(AmbientTemp);
		myOLED.setPosi(6,0);
		myOLED.print("Object:");
		myOLED.println(ObjectTemp);

		digitalWrite(LED_R,LOW);// LED Red OFF
		delay(100);
	}
}
