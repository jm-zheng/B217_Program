//------------Declare-CC2530--------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2);            // RX, TX
//-------RALAY-------------------------------------------------------------------------------
#define RALAY 2

//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;

char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;


void setup()
{
    pinMode(RALAY,OUTPUT);
    Serial.begin(9600);
    myZigbee.begin(9600);
    Zigbee_setup(20,0x1111,0x2222);
    delay(10);
    myOLED.begin(FONT_8x16);
    myOLED.print("myZigbee");
   
}
void loop() 
{
    
    while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      Serial.write(rx_data[rx_number]);
      myOLED.setPosi(4,0);
      myOLED.print(rx_data[rx_number]);
      rx_number += 1;
        
      //Set(rx_data[1] );
     
    }
    while(Serial.available())
    {
      ser_rx_data[ser_rx_number] = Serial.read();
      myZigbee.write(ser_rx_data[ser_rx_number]);
      myOLED.print(ser_rx_data[ser_rx_number]);
      ser_rx_number += 1;
      //Set(rx_data[ser_rx_number]);
    }
    
   
 
    
    ser_rx_number= 0;
    rx_number = 0;
  
    
}

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
