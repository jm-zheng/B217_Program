//------------------------------------------------------------------------------
#include <SoftwareWire.h>
#include <ADXL345.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define SDA_PIN A2 ///< pin for SDA
#define SCL_PIN A1 ///< pin for SCL
//#define SDA_PIN A4 ///< pin for SDA
//#define SCL_PIN A5 ///< pin for SCL
ADXL345 adxl;

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("ADXL345 Test");
  adxl.begin(SDA_PIN, SCL_PIN);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  adxl.setReg(0x2D, 10); // POWER ON , Set Rate 100 Hz  
}

//------------------------------------------------------------------------------
void loop()
{
  int X, Y, Z;
  float fX,fY,fZ;  
  X = adxl.getData(0x32); // Get X
  fX = X / 256.00;
 
  Y = adxl.getData(0x34); // Get Y
  fY = Y / 256.00;
 
  Z = adxl.getData(0x36); // Get Z
  fZ = Z/ 256.00;
  
  Serial.print("X= ");
  Serial.print(fX);
  Serial.print(" , Y= ");
  Serial.print(fY);
  Serial.print(" , Z= ");
  Serial.println(fZ);

  myOLED.println("ADXL345 Test");
  myOLED.print("X = ");
  myOLED.println(fX);
  myOLED.print("Y = ");
  myOLED.println(fY);
  myOLED.print("Z = ");
  myOLED.println(fZ);
      
  delay(300);
}


