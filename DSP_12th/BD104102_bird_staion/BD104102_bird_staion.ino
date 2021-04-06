//-------------BD104102_station
#include <SoftwareSerial.h>
#include<OLED.h>

OLED myOLED;
SoftwareSerial mySerial(A1,A2);//RX,TX

#define MICROWAVE_PIN  A3
#define LED_PIN        13

#define KEY1_PIN  2
#define  KEY2_PIN  6

int Key1_Tag;
int Key2_Tag;
int Microwave_Tag;
int Microwave_Play;


#define MP3_1_PIN  A4
#define MP3_2_PIN  A5

void setup() 
{
  myOLED.begin(FONT_8x16);
 mySerial.begin(9600);
 Zigbee_setup(26,0x1001,0x2002);
 myOLED.println("BIRD-station 1");
 myOLED.println("HUST B217");
 
 pinMode(LED_PIN, OUTPUT);
 digitalWrite(LED_PIN, LOW);

 pinMode(MICROWAVE_PIN, INPUT);
 digitalWrite(MICRWAVE_PIN, HIGH);

 pinMode(KEY_PIN, INPUT);
 digitalWrite(KEY1_PIN , HIGH);

 pinMode(KEY2_PIN, INPUT);
 digitalWrite(KEY2_PIN, HIGH);

 pinMode (MP3_1_PIN, OUTPUT);
 digitalWrite(MP3_1_PIN, HIGH);

 pinMode(MP3_2_PIN,OUTPUT);
 digitalWrite(MP3_2_PIN, HIGH);
 delay(200);
 mySerial.flush();
 
}

void loop() 
{
   uint8_t ch;
   if (mySerial.available())
    {
      ch=mySerial.read();
      digitalWrite(LED_PIN,HIGH);
      if(cg==0x31)
         {
          myOLED.setPosi(4,0);
          myOLED.print("BLE PLAY MP3 '1'");
          MP3_Play1();
        
         }
         if(cg==0x32)
         {
         myOLED.setPosi(4,0);
         myOLED.print("BLE PLAY MP3'2'");
         MP3_Play2();
         }
         digitalWrite(LED_PIN,LOW);

        }
         if(digitalWrite(MICROWAVE_PIN)==LOW)
         {
          digitalWrite(LED_PIN,LOW);//led off
          Microwavw_Tag=0;
         }
         else
         {
          digitalWrite(LED_PIN,HIGH);//led on
          if(Micorwave_Tag==0)
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
            myOLED.print("MIC PLAY MP3'2'");
            MP3_Play2();
          }
         
       }
    }
    if(digitalRead)(KEY1_PIN)==LOW)
    {
      if(KEY1_Tag==0)
      {
        Key_Tag=1;
        mySerial.write('1');
        digitalWrite(LED_PIN,HIGH);
        mrOLED.setPosi(6,0);
        myOLED.print("KEY PLAY MP3'1'");
        digitalWrite(LED_PIN,LOW);
        MP3_Play1();
      }
    }
    else

