//------------------------------------------------------------------------------
// CC2530_TxRx.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

SoftwareSerial mySerial(A1, A2); // RX, TX

#define BEEP_PIN     A3
#define LED_PIN      13

#define KEY1_PIN     2
#define KEY2_PIN     6
int Key1_Tag;
int Key2_Tag;
int OLED_Count;
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
  
  pinMode(BEEP_PIN, OUTPUT); // BEEP
  digitalWrite(BEEP_PIN, LOW);    // BEEP off

  pinMode(KEY1_PIN, INPUT);   
  digitalWrite(KEY1_PIN, HIGH);    

  pinMode(KEY2_PIN, INPUT);     
  digitalWrite(KEY2_PIN, HIGH);    
  Beep();
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
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("BLE PLAY MP3 '2'");     
    }
    Beep();
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
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(4,0);
      myOLED.print("STA PLAY MP3 '2'");     
    }
    Beep();
    digitalWrite(LED_PIN, LOW);    // BLUE LED off
    OLED_Count=0;
  }
  if(digitalRead(KEY1_PIN)==LOW)
  {
    if(Key1_Tag==0)
    {
      Key1_Tag=1;
      digitalWrite(LED_PIN, HIGH); // BLUE LED on
      mySerial.write('1');    
      myOLED.setPosi(6,0);
      myOLED.print("KEY PLAY MP3 '1'");     
      Beep();
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
      Beep();
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
void Beep(void)
{
  digitalWrite(BEEP_PIN, HIGH); // BEEP on
  delay(200);
  digitalWrite(BEEP_PIN, LOW);    // BEEP off
}

