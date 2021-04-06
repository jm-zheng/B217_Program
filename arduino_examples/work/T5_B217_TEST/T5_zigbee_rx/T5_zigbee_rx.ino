#include<SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);

#include<OLED.h>
OLED myOLED;
int a;


void setup() 
{
   ZigBee.begin(9600);
   Zigbee_setup(26,0x1001,0x2002);
   //----------------
   myOLED.begin(FONT_8x16);
   myOLED.print("T5_RX");
  

}

void loop() 
{
    Zigbee_read();
    myOLED.setPosi(2,0);
    myOLED.print(a);
    

}

void Zigbee_read()
{
  if (ZigBee.available())
  {
    int ch=ZigBee.read();
      if(ch==0x31)
      {
         a=1;
      }
      else if (ch==0x32)
      {
        a=2;
      }
  }
}

void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0x5A);  
  ZigBee.write(channel);  
  ZigBee.write(panid>>8);  
  ZigBee.write(panid&0xff);  
  ZigBee.write(addr>>8);  
  ZigBee.write(addr&0xff);  
  ZigBee.write(0xBB); 
}
