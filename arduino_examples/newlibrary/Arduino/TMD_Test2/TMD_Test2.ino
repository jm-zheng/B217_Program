//------------------------------------------------------------------------------
#include <SoftwareWire.h>
#include <OLED.h>
OLED myOLED;

// TMD2772 I2C address is 39(57)
#define Addr 0x39

#define SDA_PIN A2 ///< pin for SDA
#define SCL_PIN A1 ///< pin for SCL
//#define SDA_PIN A4 ///< pin for SDA
//#define SCL_PIN A5 ///< pin for SCL
SoftwareWire tmd; 

//------------------------------------------------------------------------------
void setup()
{
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  Serial.println("TMD Example");
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("TMD Example");
  
  // Initialise I2C communication as MASTER
  tmd.begin(SDA_PIN, SCL_PIN);
  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select enable register
  tmd.write(0x00 | 0x80);
  // Set power on, proximity and ALS enabled
  tmd.write(0x0F);
  // Stop I2C Transmission
  tmd.endTransmission();
  delay(500);

  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select ALS time register
  tmd.write(0x01 | 0x80);
  // Atime = 2.73 ms
  tmd.write(0xFF);
  // Stop I2C Transmission
  tmd.endTransmission();

  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select proximity time register
  tmd.write(0x02 | 0x80);
  // Ptime = 2.73 ms
  tmd.write(0xFF);
  // Stop I2C Transmission
  tmd.endTransmission();
  
  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select Wait time register
  tmd.write(0x03 | 0x80);
  // Wtime = 2.73 ms
  tmd.write(0xFF);
  // Stop I2C Transmission
  tmd.endTransmission();
  
  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select control register
  tmd.write(0x0F | 0x80);
  // 120 mA LED strength, Proximtiy uses CH1 diode, 1x PGAIN, 1x AGAIN
  tmd.write(0x20);
  // Stop I2C Transmission
  tmd.endTransmission();
  delay(300);  
}

//------------------------------------------------------------------------------
void loop()
{
  unsigned int data[6];
  
  // Start I2C Transmission
  tmd.beginTransmission(Addr);
  // Select data register
  tmd.write(0x14 | 0x80);
  // Stop I2C Transmission
  tmd.endTransmission();
  
  // Request 6 bytes of data
  tmd.requestFrom(Addr, 6);
  
  // Read 6 bytes of data
  // c0Data lsb, c0Data msb, c1Data lsb, c1Data msb, proximity lsb, proximity msb
  if(tmd.available() == 6)
  {
    data[0] = tmd.read();
    data[1] = tmd.read();
    data[2] = tmd.read();
    data[3] = tmd.read();
    data[4] = tmd.read();
    data[5] = tmd.read();
  }
  
  // Convert the data
  int c0Data = (data[1] * 256) + data[0];
  int c1Data = (data[3] * 256) + data[2];
  int proximity = (data[5] * 256) + data[4];
  float CPL = (2.73 * 1.0) / 20.0;
  float luminance1 = (1 * c0Data - 1.75 * c1Data) / CPL;
  float luminance2 = (0.63 * c0Data - 1.00 * c1Data) / CPL;
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
  Serial.print("Ambient Light luminance : ");
  Serial.print(luminance);
  Serial.println(" lux");
  Serial.print("Proximity of the device : ");
  Serial.print(proximity);
  Serial.print("\n");
  myOLED.print("Lux:");
  myOLED.println(luminance);
  myOLED.print("Prox:");
  myOLED.println(proximity);
  delay(100);
}
