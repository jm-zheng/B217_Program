#include<SoftwareSerial.h>
#define RX_PIN 12 //Rx
#define TX_PIN 11 //  Tx
SoftwareSerial pm25(RX_PIN,TX_PIN);
//--------co2_library--------
#include<CCS811.h>
CCS811 co2;

#include<OLED.h>
OLED myOLED ;

#include<Wire.h>

//-----------TEMP_HUMIDITY_I2C-------------
#define TH_addr  0x40
//---------CO2_I2C----------------
#define CO2_addr 0x5a
#define WAKE_PIN  4


float humidity ;
float temp;
float ctemp;
//------------------------
uint8_t rx_data[127];
uint8_t rx_number;
float val;
uint16_t  PM2point;
uint8_t flag = 0;     

void setup()
{
    Serial.begin(115200);
    myOLED.begin(FONT_8x16);
    myOLED.print("fan_test");
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Start I2C transmission
    Wire.beginTransmission(TH_addr);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(300); 
    //----------------------------
    pm25.begin(2400);
    
    
    //-------co2_初始化判斷-----------
    if (!co2.begin(CO2_addr,WAKE_PIN)) 
    {
      Serial.print("Initialization failed.");
    }
    
}

void loop()
{   
     pm25_read();
     co2.getData();
     humtempread();
     
     
    
      Serial.print("temp :");      Serial.println(ctemp);
      Serial.print("humidity :");  Serial.println(humidity);
      Serial.print("co2 :");         Serial.println(co2.readCO2());
      Serial.print("Tvoc :");        Serial.println(co2.readTVOC());
      Serial.print("pm25 :");        Serial.println(PM2point);
   /* myOLED.print("temp :");        myOLED.println(ctemp);
      myOLED.print("humidity :");    myOLED.println(humidity);
      myOLED.print("co2 :");         myOLED.println(co2.readCO2());
      myOLED.print("Tvoc :");        myOLED.println(co2.readTVOC());*/
}

void humtempread()
{
    //----------濕度-------------
    unsigned int data[2];
    // Start I2C transmission
    Wire.beginTransmission(TH_addr);
    // Send humidity measurement command, NO HOLD MASTER
    Wire.write(0xF5);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(50);
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
    delay(50);
    
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
}
void pm25_read()
{
    if(pm25.available())
    {
        
        while(pm25.available())
        {
            rx_data[rx_number] = pm25.read();
            //Serial.write(rx_data[rx_number]);
           // Serial.write(rx_data[rx_number]);
            rx_number +=1;
        }
        
        /*uint8_t delaytime = 4 ;
        while (delaytime--)
        {
            if (pm25.available())
            {
              break;
            }
            delay(1);
        }*/
    }
    else if (rx_number > 0 && rx_data[rx_number-1] == 0xFF)
    {
  
          //myOLED.setPosi(4,0);
         // myOLED.print(rx_number);          
          if(rx_data[0] == 0xAA && rx_data[6] == 0xFF)
          {
              flag += 1;            
               val += ((rx_data[1]*256+rx_data[2])* 2.5/1024) ;
              if (flag >= 10)
              {      
                  float val_1= val/10;
                 // Serial.print(val_1);
                  //Serial.print("X");
                  //------------------------------
                  if (0.045 > val_1)
                   {
                      PM2point =  val_1 * 200 ;
                   }

                  else if(0.044 < val_1 && val_1 > 0.049)
                  {
                     PM2point =  val_1 * 400 ;
                  }
                  else if (0.048 < val_1 && val_1 > 0.052)
                  {
                     PM2point =  val_1 * 600;
                  }
                  else if (0.051 > val_1 && val_1 < 0.055 )
                  {
                       PM2point =  val_1 * 750;
                  }
                  else if  (0.055 < val_1 && val_1 < 0.059)
                  {
                      PM2point =  val_1 * 900;
                  }
                  else if  (0.059 < val_1 && val_1 < 0.065)
                  {
                      PM2point =  val_1 * 1000;
                  }
                  else if  (0.065 < val_1 && val_1 < 0.071)
                  {
                      PM2point =  val_1 * 1250;
                  }
                  else if (0.071 > val_1 && val_1 > 0.076)
                  {
                       PM2point =  val_1 * 1400;
                  }
                  else if  (0.076 < val_1 && val_1 < 0.081)
                  {
                      PM2point =  val_1 * 1700;
                  }
                  else if  (0.081 < val_1 && val_1 < 0.086)
                  {
                      PM2point =  val_1 * 1800 ;
                  }
                  else if  (0.086 < val_1 && val_1 < 0.091)
                  {
                        PM2point =  val_1 * 1900 ;
                  }
                  else if  (0.091 < val_1 && val_1 < 0.101)
                  {
                        PM2point =  val_1 * 2000 ;
                  }
                  else if  (0.101 < val_1 && val_1 < 0.111)
                  {
                         PM2point =  val_1 * 2200 ;
                  }                
                                
                  else if ( 0.111 < val_1 )
                  {
                      PM2point =  val_1 * 3000 ;
                  }
                 //----------------------------------
                //uint8_t PM2point =  (float)(val_1)* 2.5/1024;  
                //Serial.print(PM2point);
               // myOLED.print("               ");
               // myOLED.setPosi(6,50);
               // myOLED.print(PM2point); 
                
                flag = val=val_1=0 ;
              }            
            }          
              //myOLED.setPosi(6,0);
              //myOLED.print(PM2point5);*/
         }
           rx_number= 0;     
}
  
 


