#include<SoftwareSerial.h>
//-------------------
#include<OLED.h>
OLED myOLED;

SoftwareSerial Zigbee(A1,A2);

//--------
#define READ_MAX  32
uint8_t READbuf[READ_MAX];
uint8_t READLEN;
int READCOUNT;

void setup() 
{
   myOLED.begin(FONT_8x16);
   myOLED.setPosi(0,0);
   myOLED.print("bird_com_GW");
   ///-------------------------
   Serial.begin(9600);
   //-----------------------
    Zigbee.begin(9600);
    Zigbee_setup(26,0x1001,0x2002);
    

}

void loop() 
{    
    uint8_t ch;
    if (Zigbee.available())
    {
      ch=Zigbee.read();
      if(READLEN<READ_MAX)
      {
        READbuf[READLEN++]=ch;
      }
      READCOUNT=200;
    }
   
    if(READCOUNT>0)
    {
      READCOUNT--;
        if(READCOUNT==0)
        {
          READbuf[READLEN++]=0x00;
          Serial.print((char *)READbuf);
          myOLED.println((char *)READbuf);
          READLEN=0;
        }
    }

}
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
    int i,len;
    
    // get Channel/PAN ID/Address
    Zigbee.write(0xAA);  
    Zigbee.write(0xC7);  
    Zigbee.write(0xBB);  
    delay(30);
  
    // set Channel/PAN ID/Address
    Zigbee.write(0xAA);  
    Zigbee.write(0xC7);  
    Zigbee.write(0x5A);  
    Zigbee.write(channel);  
    Zigbee.write(panid>>8);  
    Zigbee.write(panid&0xff);  
    Zigbee.write(addr>>8);  
    Zigbee.write(addr&0xff);  
    Zigbee.write(0xBB); 
}
