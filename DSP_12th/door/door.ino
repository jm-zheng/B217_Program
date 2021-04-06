//2017/02/26
//已用的角位 2 3 A0 A1 A2 A4 A5 A3

#include<SoftwareSerial.h>
///---------------
#include<DHT11.h>
#define dht11 A3
DHT11 dht;
//--------------
#include<OLED.h>
OLED myOLED;
//--------------------
#define led 3
//-------------------
SoftwareSerial ZigBee(A1,A2);
//----------------
#define MICROWAVE  A0

//------------------------
#define MP3_1_PIN  A4
#define MP3_2_PIN  A5
#define MP3_3_PIN  10
#define MP3_4_PIN  11

//---------
//#define bz  A0
//-----------
#define key1 2
int a;
int b=0;






void setup() 
{

      myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
      myOLED.setPosi(0,0);
      myOLED.print("B217 BIRD:ON");
   //----------------------  
     Serial.begin(9600);
     //----------------------------
      ZigBee.begin(9600);
      Zigbee_setup(26,0x1001,0x2002);
  
      //-------------------------
      pinMode(led,OUTPUT);
      digitalWrite(led,LOW);
      //----------------------------
      //pinMode(bz,OUTPUT);
      //digitalWrite(bz,LOW);
      //------------------
      pinMode( MICROWAVE,INPUT_PULLUP);
      //------------------
      pinMode(key1,INPUT_PULLUP);  
      //--------mp3-----------
       pinMode(MP3_1_PIN,OUTPUT);  
       pinMode(MP3_2_PIN,OUTPUT);
       pinMode(MP3_3_PIN,OUTPUT);
       pinMode(MP3_4_PIN,OUTPUT);  
       digitalWrite(MP3_1_PIN,HIGH);
       digitalWrite(MP3_2_PIN,HIGH);
       digitalWrite(MP3_3_PIN,HIGH);
       digitalWrite(MP3_4_PIN,HIGH);
       
      //-----------------
      dht.begin(dht11);
      //delay(1000);
}

void loop() 
{
    zigbee_read();
    //-------------
    uint8_t h = dht.readHumidity();
    uint8_t t = dht.readTemperature();
    ZigBee.print("H"); 
    ZigBee.print(h);
    
    ZigBee.print("T"); 
    ZigBee.print(t);
    if (b==0)
    {
      ZigBee.print("Z");
    }
    else
    {
      ZigBee.print("W");
      b=b-1;
    }
       
       // myOLED.setPosi(2,0);
        //myOLED.print("h=");
        //myOLED.print(h);
        //myOLED.print("t=");
        //myOLED.print(t);
     //---------------
    if(a==1)
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
        mp3_1();
        LED(5,300);
     
        
      
    }
    if(a==2)
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
        mp3_2();
        LED(5,300);
          //BZ();
        
    }
    if(a==3)
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
       // uint8_t b =digitalRead(key1);
        int c = digitalRead( MICROWAVE);
        
         digitalWrite(led,LOW);
         myOLED.setPosi(6,0);
         myOLED.print("wp:");
         myOLED.print(c);
         digitalWrite(MP3_1_PIN,HIGH);
         digitalWrite(MP3_2_PIN,HIGH);
         delay(300);
         if(c==LOW)
          {
              digitalWrite(led,LOW);
           
          }
        
            else if ( c==HIGH)
            {
                b=1;
        
                digitalWrite(MP3_1_PIN,LOW);
                delay(100);
                digitalWrite(MP3_1_PIN,HIGH);
                delay(1000);
                 digitalWrite(MP3_2_PIN,LOW);
                delay(100);
                digitalWrite(MP3_2_PIN,HIGH);
                digitalWrite(led,HIGH);                 
            }
    }
    if(a==4)  
    {  
       myOLED.setPosi(4,0);
       myOLED.print("ZigBee:") ;
       myOLED.print(a);
       mp3_3();
    }
    if(a==5)
    {
       myOLED.setPosi(4,0);
       myOLED.print("ZigBee:") ;
       myOLED.print(a);
       mp3_4();
    }
}


void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0x5A);  
  ZigBee.write(channel);  
  ZigBee.write(panid>>8);  
  ZigBee.write(panid&0xff);  
  ZigBee.write(addr>>8);  
  ZigBee.write(addr&0xff);  
  ZigBee.write(0xBB); 
}
/*void BZ()
{
  
           digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
}
*/
void mp3_1()
{
   digitalWrite(MP3_1_PIN,LOW);
   delay(100);
   digitalWrite(MP3_1_PIN,HIGH);
   delay(1000);
   digitalWrite(MP3_1_PIN,LOW);
  delay(100);
  digitalWrite(MP3_1_PIN,HIGH);
}
void mp3_2()
{
   digitalWrite(MP3_2_PIN,LOW);
   delay(100) ;
   digitalWrite(MP3_2_PIN,HIGH);
   delay(1000);
   digitalWrite(MP3_2_PIN,LOW);
   delay(100);
   digitalWrite(MP3_2_PIN,HIGH);
   
}
void zigbee_read()
{
       uint8_t ch;
      if(ZigBee.available())
      {
          ch=ZigBee.read();
          if(ch==0x31)
          {
            a=1;
          }
          else if (ch==0x32)
          {
            a=2;
          }
          else if(ch==0x33)
          {
            a=3;
          }
          else if(ch==0x34)
          {
            a=4;
          }
          else if (ch==0x35)
          {
            a=5;
          }
      }
      else if(a != 3)
        {
          a = 0;
        } 
       
}
void LED(int Q,int finv)
{
          int i ;
          digitalWrite(led,LOW);
          for (i=0;i<Q;i++)
          {
              digitalWrite(led,HIGH);
              delay(finv);
              digitalWrite(led,LOW);
              delay(finv);
          }   
              
          
}
void mp3_3()
{
    digitalWrite(MP3_3_PIN,LOW);
    delay(200);
    digitalWrite(MP3_3_PIN,HIGH);
}

void mp3_4()
{
    digitalWrite(MP3_4_PIN,LOW);
    delay(200);
    digitalWrite(MP3_4_PIN,HIGH);
}





