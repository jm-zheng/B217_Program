//------------------------------------------------------------------------------
// CC2530_TxRx.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

SoftwareSerial mySerial(A1, A2); // RX, TX

#define MICROWAVE_PIN     A3
#define LED_PIN          13

#define KEY1_PIN     2
#define KEY2_PIN     6
int Key1_Tag;
int Key2_Tag;
int Microwave_Tag;
int Microwave_Play;　　　

#define MP3_1_PIN     A4
#define MP3_2_PIN     A5

//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  //Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("BIRD-STATION v01");
  myOLED.println("   HUST B0217   ");
  
  pinMode(LED_PIN, OUTPUT); // BLUE LED
  digitalWrite(LED_PIN, LOW);    // BLUE LED off

  pinMode(MICROWAVE_PIN, INPUT);   
  digitalWrite(MICROWAVE_PIN, HIGH);    

  pinMode(KEY1_PIN, INPUT);   
  digitalWrite(KEY1_PIN, HIGH);    

  pinMode(KEY2_PIN, INPUT);     
  digitalWrite(KEY2_PIN, HIGH);   

  pinMode(MP3_1_PIN, OUTPUT); // MP3_1_PIN
  digitalWrite(MP3_1_PIN, HIGH);    // MP3_1_PIN HIGH
  
  pinMode(MP3_2_PIN, OUTPUT); // MP3_2_PIN
  digitalWrite(MP3_2_PIN, HIGH);    // MP3_2_PIN HIGH
  
  delay(200);
  mySerial.flush(); 
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  if (mySerial.available())
  {
    ch=mySerial.read();
    digitalWrite(LED_PIN, HIGH); // BLUE LED on
    if(ch==0x31) // '1'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '1'");     
      MP3_Play1 ();
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '2'");     
      MP3_Play2();
    }
    digitalWrite(LED_PIN, LOW);    // BLUE LED off
  }
  
  if(digitalRead(MICROWAVE_PIN)==LOW)
  {
    digitalWrite(LED_PIN, LOW);    // BLUE LED off
    Microwave_Tag=0;
  }
  else
  {
    digitalWrite(LED_PIN, HIGH); // BLUE LED on
    if(Microwave_Tag==0)
    {
      Microwave_Tag=1;
      if(Microwave_Play==0)
      {
        Microwave_Play=1;
        mySerial.write('1');    
        myOLED.setPosi(6,0);
        myOLED.print("MIC PLAY MP3 '1'");     
        MP3_Play1();
      }
      else
      {
        Microwave_Play=0;
        mySerial.write('2');    
        myOLED.setPosi(6,0);
        myOLED.print("MIC PLAY MP3 '2'");     
        MP3_Play2();
      }
    }
  }
 
  if(digitalRead(KEY1_PIN)==LOW)
  {
    if(Key1_Tag==0)
    {
      Key1_Tag=1;
      mySerial.write('1');    
      digitalWrite(LED_PIN, HIGH); // BLUE LED on
      myOLED.setPosi(6,0);
      myOLED.print("KEY PLAY MP3 '1'");     
      digitalWrite(LED_PIN, LOW);    // BLUE LED off
      MP3_Play1();
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
      mySerial.write('2');    
      digitalWrite(LED_PIN, HIGH); // BLUE LED on
      myOLED.setPosi(6,0);
      myOLED.print("KEY PLAY MP3 '2'");     
      digitalWrite(LED_PIN, LOW);    // BLUE LED off
      MP3_Play2();
    }
  }  
  else
  {
    Key2_Tag=0;
  }  
  delayMicroseconds(100);
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

//------------------------------------------------------------------------------
void MP3_Play1(void)
{
  digitalWrite(MP3_1_PIN, LOW);    // MP3_1 LOW
  delay(200);
  digitalWrite(MP3_1_PIN, HIGH); // MP3_1 HIGH
}

//------------------------------------------------------------------------------
void MP3_Play2(void)
{
  digitalWrite(MP3_2_PIN, LOW);    // MP3_2 LOW
  delay(200);
  digitalWrite(MP3_2_PIN, HIGH); // MP3_2 HIGH
}

