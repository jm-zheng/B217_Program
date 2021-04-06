//------------------------------------------------------------------------------
#include <OneWire.h>
#include <DS18B20.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define DATA_PIN  A3
DS18B20 ds;
#define BUZZER_PIN    A0

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600); 
  Serial.println("DS18B20 Test");
  ds.begin(DATA_PIN);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("DS18B20 Test");

  pinMode(BUZZER_PIN, OUTPUT);  
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW  
}

//------------------------------------------------------------------------------
void loop() 
{
  float t = ds.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (t>125) 
  {
    Serial.println("Failed to read from DS18B20");
    myOLED.println("Failed DS18B20"); 
  } 
  else 
  {
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" C");

    myOLED.print("Temp.: "); 
    myOLED.print(t);
    myOLED.println(" C");          
  }
  digitalWrite(BUZZER_PIN, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(300);               // wait for a second
  digitalWrite(BUZZER_PIN, LOW);    // turn the BUZZER off by making the voltage LOW  
}

