//------------------------------------------------------------------------------
#include <SoftwareWire.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define SDA_PIN A2 ///< pin for SDA
#define SCL_PIN A1 ///< pin for SCL
//#define SDA_PIN A4 ///< pin for SDA
//#define SCL_PIN A5 ///< pin for SCL

#define ADXL345_ADDR    0x53
SoftwareWire adxl; 

uint16_t X0, X1, Y0, Y1, Z1, Z0;
float fX,fY,fZ;

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("ADXL345 Example");
  adxl.begin(SDA_PIN, SCL_PIN);
  setReg(0x2D, 0x0A); // Set ON and Sample 100 Hz
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
}

//------------------------------------------------------------------------------
void loop()
{
  X0 = getData(0x32); // Get X
  fX = X0 / 256.0;
 
  Y0 = getData(0x34); // Get Y
  fY = Y0 / 256.0;
 
  Z0 = getData(0x36); // Get Z
  fZ = Z0 / 256.0;
    
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

//------------------------------------------------------------------------------
void setReg(uint8_t reg, uint8_t data)
{
  adxl.beginTransmission(ADXL345_ADDR);
  adxl.write(reg);
  adxl.write(data);
  adxl.endTransmission();
  delay(1);
}

//------------------------------------------------------------------------------
uint16_t getData(uint8_t reg)
{
  uint16_t val;
  
  adxl.beginTransmission(ADXL345_ADDR);
  adxl.write(reg);
  adxl.endTransmission();   
  adxl.requestFrom(ADXL345_ADDR,2);    
  while(adxl.available()>=2)
  {
    val=adxl.read();
    val+= (adxl.read()<<8);   
  }
  return val;  
}

