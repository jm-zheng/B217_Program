
//------------Declare-CC2530--------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2);            // RX, TX

//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;

char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;

uint8_t m1_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xE8,0x03};
uint8_t m1_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xD0,0x07};
uint8_t m2_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x02,0xE8,0x03};
uint8_t m2_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x02,0xD0,0x07};
uint8_t m3_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x03,0xE8,0x03};
uint8_t m3_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x03,0xD0,0x07};
uint8_t m4_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x04,0xE8,0x03};
uint8_t m4_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x04,0xD0,0x07};
uint8_t m5_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xE8,0x03};
uint8_t m5_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xD0,0x07};
uint8_t m6_1000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0xE8,0x03};
uint8_t m6_2000 [] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0xD0,0x07};
uint8_t m_1500[] ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xDC,0x05};
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
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
}
void setup()
{
    Serial.begin(9600);
    myZigbee.begin(9600);
    Zigbee_setup(20,0x1111,0x2222);
    delay(10);
    myOLED.begin(FONT_8x16);
    myOLED.print("mic_rx");
  
}
void loop() 
{
    
    while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      Serial.write(rx_data[rx_number]);
      myOLED.print(rx_data[rx_number]);
      rx_number += 1;
      
    }
    while(Serial.available())
    {
      ser_rx_data[ser_rx_number] = Serial.read();
      myZigbee.write(ser_rx_data[ser_rx_number]);
      myOLED.print(ser_rx_data[ser_rx_number]);
      ser_rx_number += 1;
      
    }
    Set(rx_data[1] );
    myOLED.setPosi(2,0);
    myOLED.print(ser_rx_data[0]);
    
    ser_rx_number= 0;
    rx_number = 0;
    rx_data[1] = 0;
}
//------------------------------------------------------------------------------
void Set(uint8_t a )
{
  if(rx_data[0] == "m")
  {
      switch(a)
   {
      case 0x31 :
      {
        for(int i=0;i<11;i++){Serial.write(m1_1000 [i]);}
        
      }
      break;
      case 0x32 :
      {
        for(int i=0;i<11;i++){Serial.write(m1_2000 [i]);}

      }
      break;
       case 0x33 :
      {
        for(int i=0;i<11;i++){Serial.write(m2_1000 [i]);}
      }
      break;
       case 0x34 :
      {
        for(int i=0;i<11;i++){Serial.write(m2_2000 [i]);}
      }
      break;
       case 0x35 :
      {
        for(int i=0;i<11;i++){Serial.write(m3_1000 [i]);}
      }
      break;
      case 0x36 :
      {
        for(int i=0;i<11;i++){Serial.write(m3_2000 [i]);}
      }
      break;
       case 0x37 :
      {
        for(int i=0;i<11;i++){Serial.write(m4_1000 [i]);}
      }
      break;
       case 0x38 :
      {
        for(int i=0;i<11;i++){Serial.write(m4_2000 [i]);}
      }
        case 0x39 :
      {
        for(int i=0;i<11;i++){Serial.write(m5_1000 [i]);}
      }
      break;
       case 0x41 :
      {
        for(int i=0;i<11;i++){Serial.write(m5_2000 [i]);}
      }
        case 0x42 :
      {
        for(int i=0;i<11;i++){Serial.write(m6_1000 [i]);}
      }
      break;
       case 0x43 :
      {
        for(int i=0;i<11;i++){Serial.write(m6_2000 [i]);}
      }
       case 0x44 :
      {
        for(int j =1 ;j<7 ;j++)
        {
          m_1500 [7] = j;
          delay(50);
         
          for(int i=0;i<11;i++)
          {
            Serial.write(m_1500 [i]);
          }
         
        }
      }
       break;
   }
  }
   
}


