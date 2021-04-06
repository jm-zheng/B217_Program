//----------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>
OLED myOLED;
SoftwareSerial mySerial(A1,A2);
//-------------micorwave------------------
#define microwave_pin     A3
int microwave_tag;
int microwave_play;
//-------------micorwave------------------
//-------------LED------------------------
#define LED_pin           13
//-------------LED------------------------
//--------------button--------------------
#define button1_pin        2
#define button2_pin        6
int button1_tag;
int button2_tag;
//--------------button--------------------
//--------------mp3-----------------------
#define mp3_1_pin         A4
#define mp3_2_pin         A5
//--------------mp3-----------------------
void setup()
{
  myOLED.begin(FONT_8x16);
  mySerial.begin(9600);
  //Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("bird_station");
  myOLED.println("HUST B217");
//-------------led------------------------
  pinMode(LED_pin,OUTPUT);
  digitalWrite(LED_pin,LOW);
//-------------led------------------------
//-------------microwave------------------
  pinMode(microwave_pin,INPUT);
  digitalWrite(microwave_pin,HIGH);
//-------------microwave------------------
//-------------button---------------------
  pinMode(button1_pin,INPUT);
  digitalWrite(button1_pin,HIGH);
  int button1_tag;
  pinMode(button2_pin,INPUT);
  digitalWrite(button2_pin,HIGH);
//-------------button---------------------
//-------------mp3------------------------
  pinMode(mp3_1_pin,OUTPUT);
  digitalWrite(mp3_1_pin,HIGH);
  pinMode(mp3_2_pin,OUTPUT);
  digitalWrite(mp3_2_pin,HIGH);
//-------------mp3------------------------
  delay(200);
  mySerial.flush();
}
void loop()
{
  myOLED.setPosi(4,0);
  myOLED.print("no");
  myOLED.println(button1_tag);
  
  uint8_t ch;
  if(mySerial.available())
  {
    ch=mySerial.read();
    digitalWrite(LED_pin,HIGH);
    if(ch == 0x31) //'1'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '1'");
      mp3_play1(); 
     }
    if(ch == 0x32) //'2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '2'");
      mp3_play2(); 
    }
   }
  if(digitalRead(button1_pin) != HIGH)
  {
    button1_tag += 1;
    delay(300);
    if(button1_tag > 3)
    {
      button1_tag = 0;
      button2_tag = 0; 
    }
  }
  if(digitalRead(button2_pin) == LOW)
  {
    if(button1_tag == 1)
    {
      mySerial.write('1');
      digitalWrite(LED_pin,HIGH);
      myOLED.setPosi(4,0);
      myOLED.print("no");
      myOLED.println(button1_tag);
      myOLED.setPosi(6,0);
      myOLED.print("But play mp3 '1'");
      digitalWrite(LED_pin,LOW);
      mp3_play1(); 
    }
    delay(100);
   if(button1_tag == 2)
    {
      mySerial.write('2');
      digitalWrite(LED_pin,HIGH);
      myOLED.setPosi(4,0);
      myOLED.print("no");
      myOLED.println(button1_tag);
      myOLED.setPosi(6,0);
      myOLED.print("But play mp3 '2'");
      digitalWrite(LED_pin,LOW);
      mp3_play2(); 
    }
    delay(100);
   if(button1_tag == 3)
    {
      button2_tag += 1;
      mySerial.write('3');
    }
    }
    if(button2_tag == 1)
    {
    if(digitalRead(microwave_pin) == LOW)
    {
      microwave_tag = 0;
      digitalWrite(LED_pin,LOW);
    }
    else
    {
      digitalWrite(LED_pin,HIGH);
      if(microwave_tag == 0)
      {
        microwave_tag = 1;
        if(microwave_play == 0)
        {
         microwave_play = 1;
         mySerial.write('1');
         myOLED.setPosi(4,0);
         myOLED.print("no");
         myOLED.println(button1_tag);
         myOLED.setPosi(6,0);
         myOLED.print("MIC play mp3 '1'");
         mp3_play1(); 
        }
       else
       {
        microwave_play = 0;
        mySerial.write('2');
        myOLED.setPosi(4,0);
        myOLED.print("no");
        myOLED.println(button1_tag);
        myOLED.setPosi(6,0);
        myOLED.print("MIC play mp3 '2'");
        mp3_play2();
       }
    }
  }
  }
  delayMicroseconds(100);
}
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
//----------------------------------------------------------------
void mp3_play1(void)
{
  digitalWrite(mp3_1_pin,LOW);
  delay(200);
  digitalWrite(mp3_1_pin,HIGH);
}
//----------------------------------------------------------------
void mp3_play2(void)
{
  digitalWrite(mp3_2_pin,LOW);
  delay(200);
  digitalWrite(mp3_2_pin,HIGH);
}
