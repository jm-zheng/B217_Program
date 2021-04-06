//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

SoftwareSerial mySerial(11, 12); // RX, TX

#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
int RecvLen;
int RecvCount;
int D2_Tag;
int D6_Tag;

//------------------------------------------------------------------------------
void setup()  
{
  pinMode(2, INPUT);   
  digitalWrite(2, HIGH);    
  pinMode(6, INPUT);     
  digitalWrite(6, HIGH);  
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  myOLED.println("SerialTest_11_12");
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
  delayMicroseconds(10);
  if(RecvCount>0)
  {
     RecvCount--;
     if(RecvCount==0)
     {
        RecvBuf[RecvLen++]=0x00;
        myOLED.println((char *)RecvBuf);
        RecvLen=0;
     }
  }
  if(digitalRead(2)==LOW)
  {
    if(D2_Tag==0)
    {
      D2_Tag=1;
      mySerial.println("D2 Press");
      myOLED.println("D2 Press");
    }
  }
  else
  {
    D2_Tag=0;
  }
  
  if(digitalRead(6)==LOW)
  {
    if(D6_Tag==0)
    {
      D6_Tag=1;
      mySerial.println("D6 Press");
      myOLED.println("D6 Press");
    }
  }  
  else
  {
    D6_Tag=0;
  }
}

