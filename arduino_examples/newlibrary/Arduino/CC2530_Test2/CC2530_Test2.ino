//------------------------------------------------------------------------------
// CC2530_TxRx.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

//SoftwareSerial mySerial(A5, A4); // RX, TX
SoftwareSerial mySerial(A1, A2); // RX, TX

#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
uint8_t RecvLen;
int RecvCount;

//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("CC2530 Test");
  RecvCount=0;
  RecvLen=0;
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  if (mySerial.available())
  {
    ch=mySerial.read();
    if(RecvLen<RECV_MAX)
    {
      RecvBuf[RecvLen++]=ch;
    }
    RecvCount=200;
  }
  if (Serial.available())
  {
    ch=Serial.read();
    mySerial.write(ch);    
  }
  delayMicroseconds(10);
  if(RecvCount>0)
  {
     RecvCount--;
     if(RecvCount==0)
     {
        RecvBuf[RecvLen++]=0x00;
        Serial.println((char *)RecvBuf);    
        myOLED.println((char *)RecvBuf);
        RecvLen=0;
     }
  }
}

//------------------------------------------------------------------------------
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  mySerial.write(0xAA);  
  mySerial.write(0xC7);  
  mySerial.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  mySerial.write(0xAA);  
  mySerial.write(0xC7);  
  mySerial.write(0x5A);  
  mySerial.write(channel);  
  mySerial.write(panid>>8);  
  mySerial.write(panid&0xff);  
  mySerial.write(addr>>8);  
  mySerial.write(addr&0xff);  
  mySerial.write(0xBB); 
}

