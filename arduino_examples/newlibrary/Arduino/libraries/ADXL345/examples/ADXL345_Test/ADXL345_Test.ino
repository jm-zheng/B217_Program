//------------------------------------------------------------------------------
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
}

//------------------------------------------------------------------------------
void loop()
{
  uint16_t iX, iY, iZ;
  float fX,fY,fZ;

  iX = adxl.getData(0x32); // 取得 X 軸
  fX = iX / 256.0;

  iY = adxl.getData(0x34); // 取得 Y 軸
  fY = iY / 256.0;

  iZ = adxl.getData(0x36); // 取得 Z 軸
  fZ = iZ / 256.0;

  Serial.print("X= ");
  Serial.print(fX);
  Serial.print(" , Y= ");
  Serial.print(fY);
  Serial.print(" , Z= ");
  Serial.println(fZ);

  myOLED.println("ADXL345 Example");
  myOLED.print("X = ");
  myOLED.println(fX);
  myOLED.print("Y = ");
  myOLED.println(fY);
  myOLED.print("Z = ");
  myOLED.println(fZ);
      
  delay(100);
}


