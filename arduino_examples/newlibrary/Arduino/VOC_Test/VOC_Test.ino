//------------------------------------------------------------------------------
#include<CCS811.h>
CCS811 co2;

#include<OLED.h>
OLED myOLED ;

#include<Wire.h>

#define TH_addr  0x40
#define CO2_addr 0x5a
#define WAKE_PIN  4

float humidity ;
float temp;
float ctemp;
     
//------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    myOLED.begin(FONT_8x16);
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Start I2C transmission
    Wire.beginTransmission(TH_addr);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(300); 
    //------------------
    if (!co2.begin(CO2_addr,WAKE_PIN)) 
    {
      Serial.print("Initialization failed.");
    }
}

//------------------------------------------------------------------------------
void loop()
{   
    unsigned int data[2];
    // Start I2C transmission
    Wire.beginTransmission(TH_addr);
    // Send humidity measurement command, NO HOLD MASTER
    Wire.write(0xF5);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(300);
    // Request 2 bytes of data
    Wire.requestFrom(TH_addr, 2);
    // Read 2 bytes of data
    // humidity msb, humidity lsb 
    if(Wire.available()==2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
    }
    humidity = ((data[0] * 256.0)+ data[3]);
    humidity = ((125 * humidity ) / 65536.0) - 6;

    //-----------TEMP------------------ 
    // Start I2C transmission
    Wire.beginTransmission(TH_addr) ;
    // Send temperature measurement command, NO HOLD MASTER
    Wire.write(0xF3);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(300);
    
    // Request 2 bytes of data
    Wire.requestFrom(TH_addr,2);
    // Read 2 bytes of data
    // temp msb, temp lsb
    if (Wire.available() == 2)
    {
      data[0] = Wire.read();
      data[1] = Wire.read(); 
      
    }
     // Convert the data
     temp = ((data[0] * 256.0 ) + data[1]);
     ctemp = ((175.72 * temp )/ 65536.0) - 46.85;

     co2.getData();

     //-----------------
   
      Serial.print("temp :");      Serial.println(ctemp);
      Serial.print("humidity :");  Serial.println(humidity);
      Serial.print("co2 :");         Serial.println(co2.readCO2());
      Serial.print("Tvoc :");        Serial.println(co2.readTVOC());
   
      myOLED.print("temp :");        myOLED.println(ctemp);
      myOLED.print("humidity :");    myOLED.println(humidity);
      myOLED.print("co2 :");         myOLED.println(co2.readCO2());
      myOLED.print("Tvoc :");        myOLED.println(co2.readTVOC());
}
