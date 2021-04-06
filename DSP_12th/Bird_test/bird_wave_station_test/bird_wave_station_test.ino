//-----------------OLED-------------------------------
#include <OLED.h>
OLED myOLED;
//-----------------OLED-------------------------------
//-------------SoftwareSerial-------------------------
#include <SoftwareSerial.h>
SoftwareSerial mySerial(A1,A2);
//-------------SoftwareSerial-------------------------
//------------------LED-------------------------------
#define led_pin  13
//------------------LED-------------------------------
//-----------------Button-----------------------------
#define button_1_pin  2
#define button_2_pin  6
int button_1_tag;
int button_2_tag;
//-----------------Button-----------------------------
//---------------Microwave----------------------------
#define microwave_pin  A3
int microwave_tag;
int microwave_play;
//---------------Microwave----------------------------
void setup()
{
  myOLED.begin(FONT_8x16);
  mySerial.begin(9600);
  //Serial.begin(9600);
  Zigbee_setup(26,0x1001,0x2002);
  myOLED.println("wave_station");
  myOLED.println("HUST B217");
//---------------LED----------------------------------
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);
//---------------LED----------------------------------
//--------------Button--------------------------------
  pinMode(button_1_pin,INPUT);
  digitalWrite(button_1_pin,HIGH);
  pinMode(button_2_pin,INPUT);
  digitalWrite(button_2_pin,HIGH);
//--------------Button--------------------------------
//------------Microwave-------------------------------
  pinMode(microwave_pin,INPUT);
  digitalWrite(microwave_pin,HIGH);
//------------Microwave-------------------------------
delay(200);
mySerial.flush();
}
void loop()
{
  myOLED.setPosi(4,0);
  myOLED.print("Status = ");
  myOLED.println(button_1_tag);
  uint8_t ch;
  if(mySerial.available())
  {
    ch = mySerial.read();
    digitalWrite(led_pin,HIGH);
//-------------BLE-----------------------
    
   }
   if(digitalRead(button_1_pin) != HIGH)
   {
     button_1_tag += 1;
     delay(300);
     if(button_1_tag > 6)
     {
      button_1_tag = 0;
      button_2_tag = 0;
      microwave_tag = 0;
      }
    }
    if(digitalRead(button_2_pin) != HIGH)
    {
     if(button_1_tag == 1)
     {
       mySerial.write('3');
       digitalWrite(led_pin,HIGH);
       myOLED.setPosi(4,0);
       myOLED.print("Status = ");
       myOLED.println(button_1_tag);
       myOLED.setPosi(6,0);
       myOLED.print("BUT PLAY MP3 '1'");
       digitalWrite(led_pin,LOW);
      }
      if(button_1_tag == 2)
     {
       mySerial.write('4');
       digitalWrite(led_pin,HIGH);
       myOLED.setPosi(4,0);
       myOLED.print("Status = ");
       myOLED.println(button_1_tag);
       myOLED.setPosi(6,0);
       myOLED.print("BUT PLAY MP3 '2'");
       digitalWrite(led_pin,LOW);
      }
      if(button_1_tag == 3)
     {
       mySerial.write('5');
       digitalWrite(led_pin,HIGH);
       myOLED.setPosi(4,0);
       myOLED.print("Status = ");
       myOLED.println(button_1_tag);
       myOLED.setPosi(6,0);
       myOLED.print("BUT PLAY MP3 '3'");
       digitalWrite(led_pin,LOW);
      }
      if(button_1_tag == 4)
     {
       mySerial.write('6');
       digitalWrite(led_pin,HIGH);
       myOLED.setPosi(4,0);
       myOLED.print("Status = ");
       myOLED.println(button_1_tag);
       myOLED.setPosi(6,0);
       myOLED.print("BUT PLAY MP3 '4'");
       digitalWrite(led_pin,LOW);
      }
      if(button_1_tag == 5)
     {
       mySerial.write('7');
       digitalWrite(led_pin,HIGH);
       myOLED.setPosi(4,0);
       myOLED.print("Status = ");
       myOLED.println(button_1_tag);
       myOLED.setPosi(6,0);
       myOLED.print("BUT PLAY MP3 '5'");
       digitalWrite(led_pin,LOW);
      }
      delay(100);
      if(button_1_tag == 3)
      {
       button_2_tag = 1;
       mySerial.write('8');
       }
     }
     if(button_2_tag == 1)
     { 
      if(digitalRead(microwave_pin) != LOW)
      {
       microwave_tag = 0;
       digitalWrite(led_pin,LOW); 
       }
       else
       {
        digitalWrite(led_pin,HIGH);
        if( microwave_tag == 0)
        {
          microwave_tag = 1;
          if( microwave_play == 0)
          {
           microwave_play = 1;
           mySerial.write('9');
           myOLED.setPosi(4,0);
           myOLED.print("Status = ");
           myOLED.println(button_1_tag);
           myOLED.setPosi(6,0);
           myOLED.print("MIC PLAY MP3 '1'");
           delay(200);
          }
           else
         {
          microwave_play = 0;
          mySerial.write('A');
          myOLED.setPosi(4,0);
          myOLED.print("Status = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("MIC PLAY MP3 '2'");
          delay(200);
          }
         }
        }
      }
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
