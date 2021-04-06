//--------co2_library--------
#include<CCS811.h>
CCS811 co2;

#include<OLED.h>
OLED myOLED ;
#include<SoftwareSerial.h>
SoftwareSerial myBLE(A1, A2);

#define TX_PIN 1 ///< pin for TXD
#define RX_PIN 12 ///< pin for RXD

SoftwareSerial pm25(RX_PIN,TX_PIN);


#include<Wire.h>

//-----------TEMP_HUMIDITY_I2C-------------
#define TH_addr  0x40
//---------CO2_I2C----------------
#define CO2_addr 0x5a
#define WAKE_PIN  A4


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
    myBLE.begin(9600);
    BLE_setName("BD104102");
    //Zigbee_setup(26,0x1001,0x2002);
    pm25.begin(9600);
    myOLED.begin(FONT_8x16);
    myOLED.println("tx");
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
      
      delay(4600);
      myBLE.print("DA");
      delay(400);
      
      pm25read() ;
      delay(400);
      co2.getData();
      myBLE.print("c:");
      myBLE.println(co2.readCO2());
      Serial.print("co2:");         
      Serial.println(co2.readCO2());
     // Serial.print(co2.readCO2());
      delay(300);
      Serial.print("TVOC:");        
      Serial.println(co2.readTVOC());
      myBLE.print("T:");
      myBLE.println(co2.readTVOC());
       //Serial.print(co2.readTVOC());
      delay(00);
     
     
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
    myBLE.print("h:");
    myBLE.println(humidity);
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
     myBLE.print("t:");
     myBLE.println(ctemp);
     Serial.print("temp :");        Serial.println(ctemp);
     delay(100);
  
     //-----------------
      
          //---------CO2 and TVOC-------

      
     
 

    /*
     Serial.print("temp :");      Serial.println(ctemp);
      Serial.print("humidity :");  Serial.println(humidity);
      Serial.print("co2 :");         Serial.println(co2.readCO2());
      Serial.print("Tvoc :");        Serial.println(co2.readTVOC());
   
    
     

     
*/
 

}
/*void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  myZigbee.write(0xAA);  
  myZigbee.write(0xC7);  
  myZigbee.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  myZigbee.write(0xAA);  
  myZigbee.write(0xC7);  
  myZigbee.write(0x5A);  
  myZigbee.write(channel);  
  myZigbee.write(panid>>8);  
  myZigbee.write(panid&0xff);  
  myZigbee.write(addr>>8);  
  myZigbee.write(addr&0xff);  
  myZigbee.write(0xBB); 
}*/
void pm25read()
{
  {
  uint8_t ch,i,sum; 
  uint16_t val; 
  
  while(1)
  {
        if(pm25.available())
        {
          ch=pm25.read();
          if(ind==0)
          {
            if(ch==0xff)
            {
              pm25data[ind++] = ch;
            }
          }
          else
          {
            pm25data[ind++] = ch;
            if(ind>=9)
            {
              sum=0;
             
              for(i=1;i<9;i++)
              {
                sum += pm25data[i];           
              }          
              ind=0;      
              if(sum==0)
              {
                break;
              }
            }
          }
        }
      }
      
      val=(pm25data[3]*20)+(pm25data[4]/5);
       pm25_val = val;
         myBLE.print("p:");
       myBLE.println(pm25_val);
       //Serial.print(pm25_val);
       Serial.print(pm25_val);
       Serial.println(" ug/m3");
    }
}
void BLE_setName(char blename[])
      {
        int i,len;
        
        // BLE module get mac
        myBLE.write(0xAA);  
        myBLE.write(0xED);  
        myBLE.write(0xBB);  
        delay(100);
      
        // BLE module set name
        myBLE.write(0xAA);  
        myBLE.write(0xE3);  
        myBLE.write(0x5A);  
        len=strlen(blename);
        for(i=0;i<12;i++)
        {
          if(i<len)
          {
            myBLE.write((uint8_t)blename[i]);  
          }
          else
          {
            myBLE.write(0x20);  
          }
        }
        myBLE.write(0xBB); 
        delay(200);
        
        // BLE module reboot
        myBLE.write(0xAA);  
        myBLE.write(0xEF);  
        myBLE.write(0x5A);  
        myBLE.write(0xBB); 
        delay(200);
        while(myBLE.available())
        {
          myBLE.read();
        }
}

