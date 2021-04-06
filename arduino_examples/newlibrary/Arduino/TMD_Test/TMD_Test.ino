//------------------------------------------------------------------------------
#include <SoftwareWire.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define SDA_PIN A2 ///< pin for SDA
#define SCL_PIN A1 ///< pin for SCL
//#define SDA_PIN A4 ///< pin for SDA
//#define SCL_PIN A5 ///< pin for SCL

#define TMD_ADDR    0x39  // 0x39

SoftwareWire tmd; 
const byte ledPin = 13;

uint16_t TMD_ALS_Ch0;
uint16_t TMD_ALS_Ch1;
uint16_t TMD_ProximityValue;

//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("TMD Test");
  tmd.begin(SDA_PIN, SCL_PIN);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("TMD Test");
  pinMode(ledPin, OUTPUT);
  delay(100);

  TMD_SetReg(0x80, 0x0E); //ALS Enable , Proximity enable , Wait Enable
  TMD_SetReg(0x81, 0xDB); //ATIME = 100ms	

  TMD_SetReg(0x82, 0xFF); // SET P_CONTROL  MXA=1023
  TMD_SetReg(0x83, 0xFF); // SET Wait time = 2.7ms
  TMD_SetReg(0x8E, 8); // SET P_PULSE = 8
  TMD_SetReg(0x8F, 0x22); // SET P_LED Courrent = 100mA , P_use IR diode , GAIN=120
  //7:6 LED Courrent => 0:100%, 1:50%, 2:25%, 3:12.5%
  //5:4 Proximity Diode => 1:CH0 , 2:CH1, 3:CH0+CH1
  //1:0 ALS Gain => 0:GAIN=1, 1:GAIN=8, 2:GAIN=16, 3:GAIN=120
  TMD_SetReg(0x80, 0x0F); // Power Enable , ALS Enable , Proximity enable , Wait Enable
}

//------------------------------------------------------------------------------
void loop()
{
  // Convert the data
  int c0Data = TMD_GetData(0x94); //Read Ch0 , Reads two bytes from sequential registers 0x14 and 0x15		
  int c1Data = TMD_GetData(0x96); //Read Ch1 , Reads two bytes from sequential registers 0x16 and 0x17	
  int proximity = TMD_GetData(0x98); // Proximity value , Reads two bytes from sequential registers 0x18 and 0x19
  float CPL = (101.0) / 24.0;
  float luminance1 = (1 * c0Data - 2 * c1Data) / CPL;
  float luminance2 = (0.6 * c0Data - 1.00 * c1Data) / CPL;
  float luminance = 0.0;
 
  if((luminance1 > 0) && (luminance1 > luminance2))
  {
    luminance = luminance1;
  }
  else if((luminance2 > 0) && (luminance2 > luminance1))
  {
    luminance = luminance2;
  }
  // Output data to serial monitor
  myOLED.print("Lux:");
  myOLED.println(luminance);
  myOLED.print("Prox:");
  myOLED.println(proximity);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

//------------------------------------------------------------------------------
void TMD_SetReg(uint8_t reg, uint8_t dat)
{
  tmd.startI2C(TMD_ADDR,I2C_WRITE);
  tmd.writeI2C(reg);
  tmd.writeI2C(dat);
  tmd.stopI2C();
  delay(1);
}

//------------------------------------------------------------------------------
uint16_t TMD_GetData(uint8_t reg)
{
  uint16_t val;
  
  tmd.startI2C(TMD_ADDR,I2C_WRITE);
  tmd.writeI2C(reg);
  tmd.restartI2C(TMD_ADDR,I2C_READ);
  val = tmd.readI2C(0);
  val+= (tmd.readI2C(1)<<8);
  tmd.stopI2C();
  return val;
}

//------------------------------------------------------------------------------
uint8_t TMD_GetReg(uint8_t reg)
{
  uint8_t val;
  
  tmd.startI2C(TMD_ADDR,I2C_WRITE);
  tmd.writeI2C(reg);
  tmd.restartI2C(TMD_ADDR,I2C_READ);
  val = tmd.readI2C(1);
  tmd.stopI2C();
  return val;
}

