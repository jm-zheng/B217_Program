//------------------------------------------------------------------------------
#include <DHT11.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define DATA_PIN A3
DHT11 dht;

//------------------------------------------------------------------------------
void setup() 
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  Serial.begin(9600); 
  Serial.println("DHT11 Test2");
  dht.begin(DATA_PIN); // pin for DHT11
  delay(1000); // wait DHT11 ready
}

//------------------------------------------------------------------------------
void loop() 
{
  uint8_t h,t;

  delay(250); // wait Convert
  dht.startConvert();
  delay(18); // wait DHT11
  dht.getConvert(&h,&t);
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" % , ");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");

  myOLED.println("DHT11 Test2");
  myOLED.print("Humidity:"); 
  myOLED.println(h);
  myOLED.print("Temperature:"); 
  myOLED.println(t);
  myOLED.println();
  
}

