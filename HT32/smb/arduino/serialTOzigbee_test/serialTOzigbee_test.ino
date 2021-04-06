
//------------Declare-CC2530--------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2);            // RX, TX
uint8_t ZIGBEE_RxBufCount;
uint8_t ZIGBEE_Count;
char ZIGBEE_RxBuf[100];
uint8_t plc_bt =0;
//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;

char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;

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
    Zigbee_setup(26,0x1002,0x2002);
    delay(10);
    myOLED.begin(FONT_8x16);
    myOLED.print("rx");
  
}
void loop() 
{
    
   while(myZigbee.available () >0 )
   {
      ZIGBEE_RxBuf[ZIGBEE_Count] = myZigbee.read();
      Serial.print(ZIGBEE_RxBuf[ZIGBEE_Count]);
      ZIGBEE_Count +=1;
      if (ZIGBEE_RxBuf[ZIGBEE_Count] == 0x42)
      {
        myOLED.setPosi(4,0);
        myOLED.print("132");
         if (ZIGBEE_RxBuf[ZIGBEE_Count-2]==0x54 && ZIGBEE_RxBuf[ZIGBEE_Count-3] == 0x42)
         {
          plc_bt = ZIGBEE_RxBuf[ZIGBEE_Count-1];
           myOLED.setPosi(2,0);
           myOLED.print(plc_bt);
           break;
         }
         else
         {
           break ;
         }
      }
            
    }
    ZIGBEE_Count =0;
   
}
//------------------------------------------------------------------------------

