//------------------------------------------------------------------------------
// CC2530_TxRx.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>
OLED myOLED;
SoftwareSerial mySerial(A1, A2); // RX, TX
#define microwave_pin     A3
#define LED_PIN      13
#define KEY1_PIN     2
#define KEY2_PIN     6
//--------------mp3-----------------------
#define mp3_1_pin         A4
#define mp3_2_pin         A5
//--------------mp3-----------------------
int Key1_Tag;
int Key2_Tag;
int OLED_Count;
int microwave_tag;
int microwave_play;
int wave_tag;
//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("BIRD-GATEWAY v01");
  myOLED.println("   HUST B0217   ");
  pinMode(LED_PIN, OUTPUT); // BLUE LED
  digitalWrite(LED_PIN, LOW);    // BLUE LED off
  pinMode(KEY1_PIN, INPUT);
  digitalWrite(KEY1_PIN, HIGH);
  pinMode(KEY2_PIN, INPUT);     
  digitalWrite(KEY2_PIN, HIGH);
  //-------------mp3------------------------
  pinMode(mp3_1_pin,OUTPUT);
  digitalWrite(mp3_1_pin,HIGH);
  pinMode(mp3_2_pin,OUTPUT);
  digitalWrite(mp3_2_pin,HIGH);
//-------------mp3------------------------
  Serial.flush();
  mySerial.flush();
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  if (Serial.available())
  {
    ch=Serial.read();
    digitalWrite(LED_PIN, HIGH); // BLUE LED on
    mySerial.write(ch);    
    if(ch==0x31) // '1'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '1'");
      mp3_play1();     
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '2'");
      mp3_play2;     
    }
    
    digitalWrite(LED_PIN, LOW);    // BLUE LED off
    OLED_Count=0;
  }
  if (mySerial.available())
  {
    ch=mySerial.read();
    digitalWrite(LED_PIN, HIGH); // BLUE LED on
    Serial.write(ch);    
    if(ch==0x31) // '1'
    {
      myOLED.setPosi(4,0);
      myOLED.print("STA PLAY MP3 '1'");
      wave_tag = 0;
      mp3_play1();      
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("STA PLAY MP3 '2'");
      wave_tag = 0;
      mp3_play2();      
    }
    if(ch==0x33) // '3'
    {
     myOLED.setPosi(4,0);
     myOLED.print("MIC PLAY MP3 '2'");
     wave_tag = 1;
     }
    
    }
    digitalWrite(LED_PIN, LOW);    // BLUE LED off
    OLED_Count=0;
  
  if(digitalRead(KEY1_PIN)==LOW)
  {
    if(Key1_Tag==0)
    {
      Key1_Tag=1;
      digitalWrite(LED_PIN, HIGH); // BLUE LED on
      mySerial.write('1');    
      myOLED.setPosi(6,0);
      myOLED.print("KEY PLAY MP3 '1'");     

      digitalWrite(LED_PIN, LOW);    // BLUE LED off
      OLED_Count=0;
    }
  }
  else
  {
    Key1_Tag=0;
  }
  
  if(digitalRead(KEY2_PIN)==LOW)
  {
    if(Key2_Tag==0)
    {
      Key2_Tag=1;
      digitalWrite(LED_PIN, HIGH); // BLUE LED on
      mySerial.write('2');    
      myOLED.setPosi(6,0);
      myOLED.print("KEY PLAY MP3 '2'");     
      digitalWrite(LED_PIN, LOW);    // BLUE LED off
      OLED_Count=0;
    }
  }  
  else
  {
    Key2_Tag=0;
  }  
  delayMicroseconds(100);
  OLED_Count++;
  if(OLED_Count>10000)
  {
    OLED_Count=0;
    myOLED.setPosi(4,0);
    myOLED.print("                ");     
    myOLED.setPosi(6,0);
    myOLED.print("                ");     
  }
  if(wave_tag == 1)
  {
   if(digitalRead(microwave_pin) == LOW)
    {
      microwave_tag = 0;
      digitalWrite(LED_PIN,LOW);
    }
    else
    {
      digitalWrite(LED_PIN,HIGH);
      if(microwave_tag == 0)
      {
        microwave_tag = 1;
        if(microwave_play == 0)
        {
         microwave_play = 1;
         mySerial.write('1');
         myOLED.setPosi(6,0);
         myOLED.print("MIC play mp3 '1'");
         mp3_play1(); 
        }
       else
       {
        microwave_play = 0;
        mySerial.write('2');
        myOLED.setPosi(6,0);
        myOLED.print("MIC play mp3 '2'");
        mp3_play2();
       }
  }
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
