#include <SoftwareWire.h>
#include <OLED.h>

OLED myOLED;

#define SDA_PIN A1 ///< pin for SDA
#define SCL_PIN A2 ///< pin for SCL
SoftwareWire bmp; 
#define BMP_ADDRESS 0x77  // I2C address of BMP

const unsigned char OSS = 0;  // Oversampling Setting

// Calibration values
int ac1;
int ac2; 
int ac3; 
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1; 
int b2;
int mb;
int mc;
int md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long b5; 

float temperature;
long pressure;

void setup()
{
  Serial.begin(9600);
  bmp.begin(SDA_PIN, SCL_PIN);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  bmpCalibration();
}

void loop()
{
  temperature = bmpGetTemperature(bmpReadUT())/10.0;
  pressure = bmpGetPressure(bmpReadUP());
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" deg C");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");
  Serial.println();

  myOLED.print("T: ");
  myOLED.print(temperature);
  myOLED.println(" deg C");
  myOLED.print("P: ");
  myOLED.print(pressure);
  myOLED.println(" Pa");

  delay(1000);
}

// Stores all of the bmp's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void bmpCalibration()
{
  ac1 = bmpReadInt(0xAA);
  ac2 = bmpReadInt(0xAC);
  ac3 = bmpReadInt(0xAE);
  ac4 = bmpReadInt(0xB0);
  ac5 = bmpReadInt(0xB2);
  ac6 = bmpReadInt(0xB4);
  b1 = bmpReadInt(0xB6);
  b2 = bmpReadInt(0xB8);
  mb = bmpReadInt(0xBA);
  mc = bmpReadInt(0xBC);
  md = bmpReadInt(0xBE);
}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
short bmpGetTemperature(unsigned int ut)
{
  long x1, x2;
  
  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  return ((b5 + 8)>>4);  
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmpGetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmpGetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}

// Read 1 byte from the BMP at 'address'
char bmpRead(unsigned char address)
{
  unsigned char data;
  
  bmp.beginTransmission(BMP_ADDRESS);
  bmp.write(address);
  bmp.endTransmission();
  
  bmp.requestFrom(BMP_ADDRESS, 1);
  while(!bmp.available())
    ;
    
  return bmp.read();
}

// Read 2 bytes from the BMP
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmpReadInt(unsigned char address)
{
  unsigned char msb, lsb;
  
  bmp.beginTransmission(BMP_ADDRESS);
  bmp.write(address);
  bmp.endTransmission();
  
  bmp.requestFrom(BMP_ADDRESS, 2);
  while(bmp.available()<2)
    ;
  msb = bmp.read();
  lsb = bmp.read();
  
  return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int bmpReadUT()
{
  unsigned int ut;
  
  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  bmp.beginTransmission(BMP_ADDRESS);
  bmp.write(0xF4);
  bmp.write(0x2E);
  bmp.endTransmission();
  
  // Wait at least 4.5ms
  delay(5);
  
  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmpReadInt(0xF6);
  return ut;
}

// Read the uncompensated pressure value
unsigned long bmpReadUP()
{
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;
  
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  bmp.beginTransmission(BMP_ADDRESS);
  bmp.write(0xF4);
  bmp.write(0x34 + (OSS<<6));
  bmp.endTransmission();
  
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
  
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  bmp.beginTransmission(BMP_ADDRESS);
  bmp.write(0xF6);
  bmp.endTransmission();
  bmp.requestFrom(BMP_ADDRESS, 3);
  
  // Wait for data to become available
  while(bmp.available() < 3)
    ;
  msb = bmp.read();
  lsb = bmp.read();
  xlsb = bmp.read();

  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
  
  return up;
}

