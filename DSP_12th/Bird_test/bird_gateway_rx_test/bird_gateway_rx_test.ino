//-----------OLED-------------------
#include <OLED.h>
OLED myOLED;
int OLED_Count;
//-----------OLED-------------------
//-----------SoftwareSerial---------
#include <SoftwareSerial.h>
SoftwareSerial mySerial(A1, A2);
//-----------SoftwareSerial---------
//-----------MicroWave--------------
#define microwave_pin     A3
int micwave_tag;
int micwave_play;
//-----------MicroWave--------------
//-----------MP3--------------------
#define mp3_1_pin         A4
#define mp3_2_pin         A5
#define mp3_3_pin         10
#define mp3_4_pin         11
#define mp3_5_pin         12
//-----------MP3--------------------
//-----------LED--------------------
#define led_pin  13
//-----------LED--------------------
//-----------BUTTON-----------------
#define button_1_pin  2
int button_1_tag;
#define button_2_pin  6
int button_2_tag;
//-----------BUTTON-----------------
//-----------DHT11------------------
#include <DHT11.h>
#define DATA_pin  A0
DHT11 dht;
//-----------DHT11------------------
//-----------EC---------------------
const int soiltemp_pin = A6;
const int soilhumi_pin = A7;
int soiltemp;
uint32_t  st;
int soilhumi;
uint32_t  sh;
//-----------EC---------------------
void setup()
{
myOLED.begin(FONT_8x16);
mySerial.begin(9600);
Serial.begin(9600);
Zigbee_setup(26,0x1001,0x2002);
dht.begin(DATA_pin);
myOLED.println("BIRD-GATEWAY");
myOLED.println("   HUST B0217   ");
//-----------LED-----------------------
pinMode(led_pin,OUTPUT);
digitalWrite(led_pin,LOW);
//-----------MicroWave-----------------
pinMode(microwave_pin,INPUT);
digitalWrite(microwave_pin,HIGH);
//-----------MP3-----------------------
pinMode(mp3_1_pin,OUTPUT);
digitalWrite(mp3_1_pin,HIGH);
pinMode(mp3_2_pin,OUTPUT);
digitalWrite(mp3_2_pin,HIGH);
pinMode(mp3_3_pin,OUTPUT);
digitalWrite(mp3_3_pin,HIGH);
pinMode(mp3_4_pin,OUTPUT);
digitalWrite(mp3_4_pin,HIGH);
pinMode(mp3_5_pin,OUTPUT);
digitalWrite(mp3_5_pin,HIGH);
//-------------------------------------
//----------BUTTON---------------------
pinMode(button_1_pin,INPUT_PULLUP);
digitalWrite(button_1_pin,HIGH);
pinMode(button_2_pin,INPUT);
digitalWrite(button_2_pin,HIGH);
//----------BUTTON---------------------
delay(200);
Serial.flush();
mySerial.flush();
}
 int f;
 int w;
void loop()
{
//-----------------EC----------------
for(int a=0 ; a<200 ;a++)
  {
    soiltemp = analogRead(soiltemp_pin);
    soilhumi = analogRead(soilhumi_pin);
    st = st + soiltemp;
    sh = sh + soilhumi;
  }
   st /= 200;
   st = 0.4665 * st - 156.88;  
   sh /= 200;
   sh = (45.15 * sh - 5507.90)/1000;
   myOLED.setPosi(0,0);
   myOLED.print("stm: ");
   myOLED.println(st);
   myOLED.setPosi(0,70);
   myOLED.print("shm: ");
   myOLED.println(sh);
//-----------------EC----------------
//----------------DHT11--------------
 
  uint8_t H = dht.readHumidity();
  uint8_t T = dht.readTemperature();
  myOLED.setPosi(2,0);
  myOLED.print("Hum:");
  myOLED.println(H);
  myOLED.setPosi(2,60);
  myOLED.print("Tem:");
  myOLED.println(T);
   //----------------DHT11--------------
   //-----------------------------------
  f += 1;
  if(f > 6)
  {
  mySerial.print("Hum: ");
  mySerial.write(((int)H/10)+0x30);
  mySerial.write(((int)H%10)+0x30);
  mySerial.print("Tem: "); 
  mySerial.write(((int)T/10)+0x30);
  mySerial.write(((int)T%10)+0x30);
  mySerial.print("STm: ");
  mySerial.write(((int)st/10)+0x30);
  mySerial.write(((int)st%10)+0x30);
  mySerial.print("SHm: ");
  mySerial.write(((int)sh/10)+0x30);
  mySerial.write(((int)sh%10)+0x30);
  Serial.print("Hum: ");
  Serial.print(H);
  Serial.print("Tem: "); 
  Serial.print(T);
  Serial.print("STm: ");
  Serial.print(st);
  Serial.print("SHm: "); 
  Serial.print(sh);
  f =0;
  }
  
   //-----------------------------------
  myOLED.setPosi(4,0);
  myOLED.print("no = ");
  myOLED.println(button_1_tag);
//-----------BLE----------------------
uint8_t ch;
  if (Serial.available())
  {
    ch=Serial.read();
    digitalWrite(led_pin, HIGH); // BLUE LED on
    mySerial.write(ch);    
    if(ch==0x31) // '1'
    {
      myOLED.setPosi(6,0);
      myOLED.print("BLE PLAY MP3 '1'");
      mp3_play1();    
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(6,0);
      myOLED.print("BLE PLAY MP3 '2'");
      mp3_play2 ();     
    }
    if(ch==0x33) // '3'
    {
      myOLED.setPosi(6,0);
      myOLED.print("BLE PLAY MP3 '3'");
      mp3_play3 ();     
    } 
    digitalWrite(led_pin, LOW);    // BLUE LED off
    OLED_Count=0;
  }
  if(mySerial.available())
  {
    ch = mySerial.read();
    digitalWrite(led_pin,HIGH);
    Serial.write(ch);
//-----------------BLE----------------------
    if(ch==0x31) // '1'
    {
      myOLED.setPosi(6,0);
      myOLED.print("BLE PLAY MP3 '1'");
      mp3_play1();    
    }
    if(ch==0x32) // '2'
    {
      myOLED.setPosi(6,0);
      myOLED.print("BLE PLAY MP3 '2'");
      mp3_play2 ();     
    }
//---------BUTTON PART RX------------------------
    if(ch == 0x33) //'3'
    {
     myOLED.setPosi(6,0);
     myOLED.print("BUT PLAY MP3 '1'");
     digitalWrite(led_pin,HIGH);
     mp3_play1();
     }
     if(ch == 0x34) //'4'
     {
      myOLED.setPosi(6,0);
      myOLED.print("BUT PLAY MP3 '2'");
      digitalWrite(led_pin,HIGH);
      mp3_play2();
      }
      if(ch == 0x35) //'5'
       {
        myOLED.setPosi(6,0);
        myOLED.print("BUT PLAY MP3 '3'");
        digitalWrite(led_pin,HIGH);
        mp3_play3();
        }
        if(ch == 0x36) //'6'
       {
        myOLED.setPosi(6,0);
        myOLED.print("BUT PLAY MP3 '4'");
        digitalWrite(led_pin,HIGH);
        mp3_play4();
        }
        if(ch == 0x37) //'7'
       {
        myOLED.setPosi(6,0);
        myOLED.print("BUT PLAY MP3 '5'");
        digitalWrite(led_pin,HIGH);
        mp3_play5();
        }
//---------MICROWAVE PART RX------------------------
      if(ch == 0x38) //'8'
      {
        microwave_Status();
       }

      if(ch == 0x39) //'9'
      {
       myOLED.setPosi(6,0);
       myOLED.print("MIC PLAY MP3 '1'");
       Serial.print("WP: Y");
       digitalWrite(led_pin,HIGH);
       mp3_play1();
       }
       if(ch == 0x3A) //'10'
      {
       myOLED.setPosi(6,0);
       myOLED.print("MIC PLAY MP3 '2'");
       Serial.print("WP: Y");
       digitalWrite(led_pin,HIGH);
       mp3_play2();
       }
   }
   //---------Manual operation---------------------------
      if(digitalRead(button_1_pin) != HIGH)
      {
        button_1_tag += 1;
        delay(100);
        if(button_1_tag > 6)
        {
         button_1_tag = 0;
         button_2_tag = 0;
         micwave_tag = 0;
         }
       }
       if(digitalRead(button_2_pin) == LOW)
       {
        if(button_1_tag == 1)
        {
          digitalWrite(led_pin,HIGH);
          myOLED.setPosi(4,0);
          myOLED.print("no = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("BUT PLAY MP3 '1'");
          digitalWrite(led_pin,LOW);
          mp3_play1();
         }
         if(button_1_tag == 2)
        {
          digitalWrite(led_pin,HIGH);
          myOLED.setPosi(4,0);
          myOLED.print("no = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("BUT PLAY MP3 '2'");
          digitalWrite(led_pin,LOW);
          mp3_play2();
         }
         if(button_1_tag == 3)
        {
          digitalWrite(led_pin,HIGH);
          myOLED.setPosi(4,0);
          myOLED.print("no = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("BUT PLAY MP3 '3'");
          digitalWrite(led_pin,LOW);
          mp3_play3();
         }
         if(button_1_tag == 4)
        {
          digitalWrite(led_pin,HIGH);
          myOLED.setPosi(4,0);
          myOLED.print("no = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("BUT PLAY MP3 '4'");
          digitalWrite(led_pin,LOW);
          mp3_play4();
         }
         if(button_1_tag == 5)
        {
          digitalWrite(led_pin,HIGH);
          myOLED.setPosi(4,0);
          myOLED.print("no = ");
          myOLED.println(button_1_tag);
          myOLED.setPosi(6,0);
          myOLED.print("BUT PLAY MP3 '5'");
          digitalWrite(led_pin,LOW);
          mp3_play5();
         }
         if(button_1_tag == 6)
         {
          button_2_tag = 1;
          }
        }
      if(button_2_tag == 1)
      {
       w += 1;
        if(w > 6)
        {
        if(digitalRead(microwave_pin) == LOW)
      {
        micwave_tag = 0;
        mySerial.print("WP: N");
        Serial.print("WP: N");
        digitalWrite(led_pin,LOW);
       }
       else
       {
        digitalWrite(led_pin,HIGH);
        if(micwave_tag == 0)
        {
          micwave_tag = 1;
          if(micwave_play == 0)
          {
            micwave_play = 1;
            myOLED.setPosi(6,0);
            myOLED.print("MIC PLAY MP3 '1'");
            mySerial.print("WP: Y");
            Serial.print("WP: Y");
            mp3_play1();
           }
           else
           {
            micwave_play = 0;
            myOLED.setPosi(6,0);
            myOLED.print("MIC PLAY MP3 '2'");
            mySerial.print("WP: Y");
            Serial.print("WP: Y");
            mp3_play2();
            }
         }
        }
        w = 0;
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
void mp3_play1(void)
{
  digitalWrite(mp3_1_pin,LOW);
  delay(200);
  digitalWrite(mp3_1_pin,HIGH);
}

void mp3_play2(void)
{
  digitalWrite(mp3_2_pin,LOW);
  delay(200);
  digitalWrite(mp3_2_pin,HIGH);
}

void mp3_play3(void)
{
  digitalWrite(mp3_3_pin,LOW);
  delay(200);
  digitalWrite(mp3_3_pin,HIGH);
}

void mp3_play4(void)
{
  digitalWrite(mp3_4_pin,LOW);
  delay(200);
  digitalWrite(mp3_4_pin,HIGH);
}

void mp3_play5(void)
{
  digitalWrite(mp3_5_pin,LOW);
  delay(200);
  digitalWrite(mp3_5_pin,HIGH);
}
//----------------------------------------------------------------
void microwave_Status(void)
{
 if(digitalRead(microwave_pin) != LOW)
 {
   micwave_tag = 0;
   digitalWrite(led_pin,LOW);
  }
  else
  {
    digitalWrite(led_pin,HIGH);
    if(micwave_tag == 0)
    {
      micwave_tag = 1;
      if(micwave_play == 0)
          {
            micwave_play = 1;
            myOLED.setPosi(6,0);
            myOLED.print("MIC PLAY MP3 '1'");
            mp3_play1();
           }
           else
           {
            micwave_play = 0;
            myOLED.setPosi(6,0);
            myOLED.print("MIC PLAY MP3 '2'");
            mp3_play2();
            }
     }
   } 
}
