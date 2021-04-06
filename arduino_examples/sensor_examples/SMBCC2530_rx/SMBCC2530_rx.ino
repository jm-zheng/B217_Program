//------------------------------------------------------------------------------
// CC2530_TxRx.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

//SoftwareSerial mySerial(A5, A4); // RX, TX
SoftwareSerial mySerial(A1, A2); // RX, TX

const int key1Pin = 2;     // the number of the pushbutton pin
const int key2Pin = 6;     // the number of the pushbutton pin

#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
uint8_t RecvLen;
int RecvCount;

uint8_t tempval = 27;
uint8_t amperval = 3;
uint8_t countval = 17;
uint8_t shockval = 3;

//------------------------------------------------------------------------------
void setup()  
{
  pinMode(key1Pin, INPUT);    
  digitalWrite(key1Pin, HIGH);
  pinMode(key2Pin, INPUT);    
  digitalWrite(key2Pin, HIGH);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("CC2530 Test");
  RecvCount=0;
  RecvLen=0;
  Serial.flush();
  mySerial.flush();
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  if ( digitalRead(key1Pin) == LOW)
  {     
    /*mySerial.print("box1t:"); 
    mySerial.println(tempval);  
    mySerial.print("box1a:"); 
    mySerial.println(amperval);
    mySerial.print("box1c:"); 
    mySerial.println(countval);
    mySerial.print("box1s:"); 
    mySerial.println("boxt1:"); */    
    myOLED.println(shockval);
    delay(200);
  }  
  if ( digitalRead(key2Pin) == LOW)
  {     
    mySerial.println("KEY ENTER");    
    myOLED.println("KEY ENTER");
    delay(200);
  }  
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

