//------------------------------------------------------------------------------
#include <DHT12.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define DATA_PIN A3
DHT12 dht;

//------------------------------------------------------------------------------
void setup() 
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  Serial.begin(9600); 
  Serial.println("DHT12 Test");
  dht.begin(DATA_PIN); // pin for DHT12
  delay(1000); // wait DHT12 ready
}

//------------------------------------------------------------------------------
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" % , ");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");

  myOLED.println("DHT12 Test");
  myOLED.print("Humidity:"); 
  myOLED.println(h);
  myOLED.print("Temp.:"); 
  myOLED.println(t);
  myOLED.println();
  
  delay(1000);  
}

