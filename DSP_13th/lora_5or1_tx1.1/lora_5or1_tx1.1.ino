//2018/03/11
//lora addh 01 addl 02 channl 01


#include <SoftwareSerial.h>
SoftwareSerial mylora(A2,A1);  //RX,TX

#include <OLED.h>
OLED myOLED;

#include <CCS811.h>
CCS811 co2;


#define rxpin 12
#define txpin 11
SoftwareSerial pm25(rxpin,txpin);

#include<Wire.h>
//-----------TEMP_HUMIDITY_I2C-------------
#define TH_addr  0x40
//---------CO2_I2C----------------
#define CO2_addr 0x5a
#define WAKE_PIN  4 

#define key1 2
#define key2 6



float humidity  ;
float temp;
float ctemp;

String pm25_val= ""; //holds the string of the value
//uint16_t pm25_val;
//uint16_t co2 =0; // holds the actual value
uint8_t pm25data[25];
uint8_t ind =0; 

void setup() 
{
    Serial.begin(9600);
    mylora.begin(9600);
    myOLED.begin(FONT_8x16);
    myOLED.println("tx");
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);

    pm25.begin(9600);

    // Initialise I2C communication as MASTER
    Wire.begin();
    // Start I2C transmission
    Wire.beginTransmission(TH_addr);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(300); 
    
    
    //-------co2_初始化判斷-----------
    if (!co2.begin(CO2_addr,WAKE_PIN)) 
    {
      Serial.print("Initialization failed.");
    }
  
    

}

void loop() 
{
      delay(4400);
    
      lora_set();
      mylora.println("DC001");
      delay(200);
      
      lora_set();
      mylora.println("PC001");
      delay(200);
      
      pm25read() ;
      delay(200);

     
      co2.getData();
      lora_set();
      mylora.print("c:");
      mylora.println(co2.readCO2());
      Serial.print("co2:");         
      Serial.println(co2.readCO2());
     // Serial.print(co2.readCO2());
      delay(300);
      Serial.print("TVOC:");        
      Serial.println(co2.readTVOC());
      lora_set();
      mylora.print("T:");
      mylora.println(co2.readTVOC());
       //Serial.print(co2.readTVOC());
      delay(300);
     
    
    //----------濕度-------------
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
    lora_set();
    mylora.print("h:");
    mylora.println(humidity);
    Serial.print("humidity :");    Serial.println(humidity);

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
      lora_set();
      mylora.print("t:");
      mylora.println(ctemp);
      Serial.print("temp :");       
      Serial.println(ctemp);
      //delay(100);
}
void pm25read()
{
  {
    uint8_t ch, i, sum;
    uint16_t val;

    while (1)
    {
      if (pm25.available())
      {
        ch = pm25.read();
        if (ind == 0)
        {
          if (ch == 0xff)
          {
            pm25data[ind++] = ch;
          }
        }
        else
        {
          pm25data[ind++] = ch;
          if (ind >= 9)
          {
            sum = 0;

            for (i = 1; i < 9; i++)
            {
              sum += pm25data[i];
            }
            ind = 0;
            if (sum == 0)
            {
              break;
            }
          }
        }
      }
    }

    val = (pm25data[3] * 20) + (pm25data[4] / 5);
    pm25_val = val;
    mylora.write(0x01);
    mylora.write(0x04);
    mylora.write(0x04);
    mylora.print("p:");
    mylora.println(pm25_val);
    //Serial.print(pm25_val);
    Serial.print(pm25_val);
    Serial.println(" ug/m3");
  }
}
void lora_set()
{
   mylora.write(0x01);
    mylora.write(0x04);
    mylora.write(0x04);
    
}

