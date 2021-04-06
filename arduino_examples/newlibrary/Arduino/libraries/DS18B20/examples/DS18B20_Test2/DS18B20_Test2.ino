//------------------------------------------------------------------------------
#include <DS18B20.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define DATA_PIN  A3
DS18B20 ds;

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600); 
  Serial.println("DS18B20 Test2");
  ds.begin(DATA_PIN);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("DS18B20 Test2");
}

//------------------------------------------------------------------------------
void loop() 
{
  float celsius;
  ds.startConvertTemperature();
  delay(750); // 750ms conversion time
  celsius = ds.getConvertTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (celsius>125)
  {
    Serial.println("Failed to read from DS18B20");
    myOLED.println("Failed DS18B20"); 
  } 
  else 
  {
    Serial.print("Temperature = ");
    Serial.print(celsius);
    Serial.print(" *C, ");
    float fahrenheit = (celsius * 1.8) + 32.0;
    Serial.print(fahrenheit);
    Serial.println(" *F");
    
    myOLED.print("Celsius: "); 
    myOLED.print(celsius);
    myOLED.println(" C");       
    myOLED.print("Fahre.: "); 
    myOLED.print(fahrenheit);
    myOLED.println(" F");       
  }
}


