//------------------------------------------------------------------------------
// TitleEx027_LoRa_SendRecv
// Firmware : Ex027_LoRa_SendRecv
// Devices NanoKIT + LoRa
// Function环禯瞒肚块
// UpDate201712/12 
//--------Declare-LoRa-------------------
#include <SoftwareSerial.h>
SoftwareSerial LoRaSerial(A2, A1); // RX, TX
//-------Declare-OLED---------------------
#include <OLED.h>
OLED myOLED;
//-------Declare-KEY--------------------------------------
#define  KEY1  2
#define  KEY2  6
int Key1_Tag;
int Key2_Tag;
#define RX_MAX    20
char RxBuf[RX_MAX];
uint8_t RxDelay;
uint8_t RxLen;
//------------------------------------------------------------------------------
void setup()  
{
 // ====== Setup OLED ==============
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.clearScreen();
  myOLED.println("LoRa_SendRecv");
// ====== Setup LoRa ==============
  LoRaSerial.begin(9600);
  Serial.begin(9600);
 //=============Setup-KEY======================
 // declare KEY1_PIN!AKEY2_PIN to be an output:
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  delay(200);
  LoRaSerial.flush(); 
  RxDelay=0;
  RxLen=0;
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  char ch;

  if (LoRaSerial.available())
  {
    ch=LoRaSerial.read();
    RxDelay=0;
    if(RxLen<(RX_MAX-1))
    {
      RxBuf[RxLen++]=ch;
    }
    Serial.write(ch);
  }
  if (Serial.available())
  {
    LoRaSerial.write(Serial.read());    
  }
  if(digitalRead(KEY1)==LOW)
  {
    if(Key1_Tag==0)
    {
      Key1_Tag=1;
      LoRaSerial.println("KEY-1");
      myOLED.setPosi(2,0);
      myOLED.print("[KEY-1 TX]");     
    }
  }
  else
  {
    Key1_Tag=0;
  }
  if(digitalRead(KEY2)==LOW)
  {
    if(Key2_Tag==0)
    {
      Key2_Tag=1;      
      LoRaSerial.println("KEY-2");
      myOLED.setPosi(2,0);
      myOLED.print("[KEY-2 TX]");     
    }
  }  
  else
  {
    Key2_Tag=0;
  }  
  if(RxDelay>100)
  {
    RxDelay=0;
    if(RxLen>0)
    {
      RxBuf[RxLen]=0;
      myOLED.setPosi(4,0);
      myOLED.print("RX:");     
      myOLED.setPosi(6,0);
      myOLED.print(RxBuf);    
      RxLen=0;
    }
  }
  delayMicroseconds(20);
  RxDelay++;
}
