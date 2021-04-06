//------------------------------------------------------------------------------
//Title:SD_Temp_LED_PWM
// Firmware:SD_Temp_LED_PWM
// Devices:NanoKIT + OLED + LED+DS18B20.h
// Function: OK
//UpDate:2016/11/11  
//--------Declare--DS18B20-------------------------------------------------------
//#include <DS18B20.h>
//#include <OneWire.h>
//-------Declare-OLED-------------------------------
#include <OLED.h>
OLED myOLED;
//-------Declare-LED1W-MD1--------------------------------
#define LED 3
//-------Declare-Temp Sensor DS18B20---------------------------------------
#include <DS18B20.h>
DS18B20 ds;
#define Temp_PIN  A3
float STempMax=32;
float STempMin=29;
void setup() 
{
 //=============Setup-ED1W-MD1================================
  pinMode(LED, OUTPUT);
 //=============Setup- DS18B20=================================
  ds.begin(Temp_PIN );
  //=============Setup-OLED===================================
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("SD_Temp_LED_PWM");
  //myOLED.println("Date:2016/11/19");
  myOLED.print("T1:");
  myOLED.print(STempMax);
   myOLED.print("T2:");
  myOLED.println(STempMin);   
}

//------------------------------------------------------------------------------
void loop() 
{
  float temp = ds.readTemperature();
  if (temp<125 && temp>5) 
  {
    myOLED.setPosi(4,0);
    myOLED.print("Temp.: "); 
    myOLED.print(temp);
    myOLED.println(" *C");          
  }
   //=======Smart Processing=============
   //map(value, fromLow, fromHigh, toLow, toHigh)
   int duty=map(temp, STempMin, STempMax, 0, 255);
   myOLED.setPosi(6,0);
    myOLED.print("Duty: "); 
   if(temp>STempMax)   
   {
       digitalWrite(LED,HIGH);
       myOLED.print("255");
   }
   else if (temp<STempMin)
   {   
       digitalWrite(LED,LOW);
       myOLED.print(0);
   }
   else
   {
       myOLED.print(duty);
       analogWrite(LED, duty);
    } 
   delay(500);
}
