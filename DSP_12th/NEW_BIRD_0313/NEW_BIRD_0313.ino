#include<SoftwareSerial.h>

//---------雲台------------
#include<Servo.h>
Servo myservo1;
Servo myservo2;
int value;
int count;
//------OLED----------------
#include<OLED.h>
OLED myOLED;
//-------zigbee--------------
SoftwareSerial ZigBee(A1,A2);
int a;

//-----------微波----------
#define mywave A0
//-------------音樂--------------
#define MP1 A4
#define MP2 A5
#define MP3 A3


void setup() 
{
  ///-----------雲台----------
    myservo1.attach(10);
    myservo2.attach(11);
  //----------OLED---------------
    myOLED.begin(FONT_8x16);
  //---------zigbee---------------------
      ZigBee.begin(9600);
      Zigbee_setup(26,0x1001,0x2002);
  //---------------wave---------
      pinMode(mywave,INPUT_PULLUP);

  //------------音樂--------------
      pinMode(MP1,OUTPUT);
      pinMode(MP2,OUTPUT);
      pinMode(MP3,OUTPUT);
      digitalWrite(MP1,HIGH);
      digitalWrite(MP2,HIGH);
      digitalWrite(MP3,HIGH);
}

void loop() 
{ 
    mp3_high();
    zigbee_read();
    
   
    
}

void servo()  //雲台
{
  

    value = 20;
    myservo1.write(value);
    myOLED.setPosi(2,0);
    myOLED.print("Motor1 = ");
    myOLED.println(value);
    value = 90;
    myservo2.write(value);
    myOLED.setPosi(4,0);
    myOLED.print("Motor2 = ");
    myOLED.println(value);
    delay(500);
    
    value = 30;
    myservo1.write(value);
    myOLED.setPosi(2,0);
    myOLED.print("Motor1 = ");
    myOLED.println(value);
    value = 0;
    myservo2.write(value);
    myOLED.setPosi(4,0);
    myOLED.print("Motor2 = ");
    myOLED.println(value);
    delay(500);
  
    value = 20;
    myservo1.write(value);
    myOLED.setPosi(2,0);
    myOLED.print("Motor1 = ");
    myOLED.println(value);
    value = 90;
    myservo2.write(value);
    myOLED.setPosi(4,0);
    myOLED.print("Motor2 = ");
    myOLED.println(value);
    delay(500);
  
    value = 30;
    myservo1.write(value);
    myOLED.setPosi(2,0);
    myOLED.print("Motor1 = ");
    myOLED.println(value);
    value = 180;
    myservo2.write(value);
    myOLED.setPosi(4,0);
    myOLED.print("Motor2 = ");
    myOLED.println(value);
    delay(500);
  

}
void zigbee_read() //ZIGBEE 讀
{   
    uint8_t ch;
   if (ZigBee.available())
   {
      ch = ZigBee.read();
      if(ch==0x31)
      {
        a=1;  
      }
      else if (ch==0x32)
      {
        a=2;
      }
       else if (ch==0x33)
      {
        a=3;
      }
       else if (ch==0x34)
      {
        a=4;
      }
       else if (ch==0x35)
      {
        a=5;
      }
       else if (ch==0x36)
      {
        a=6;
      }
       else if (ch==0x37)
      {
        a=7;
      }
       else if (ch==0x38)
      {
        a=8;
      }
         else if (ch==0x39)
      {
        a=9;
      }
      
   }
   else if (a!=9)
   {
     a=0;
   }
      if (a==1)
   {
     
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
     mp1();
     servo();
   }
   else if (a==2)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
     mp2();
     servo();
   }
    else if (a==3)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
     mp3();
     servo();
   }
    else if (a==4)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
   }
    else if (a==5)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
   }
    else if (a==6)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
   }
    else if (a==7)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
   }
    else if (a==8)
   {
     myOLED.setPosi(0,0);
     myOLED.print("zigbee=");
     myOLED.println(a);
   }
   else if (a==9)
   {
      mp3_high();
      myOLED.setPosi(0,0);
      myOLED.print("zigbee=");
      myOLED.println(a);
    
      int c = digitalRead(mywave);
      if (c==LOW)
      {
         myOLED.setPosi(6,0);
         myOLED.print("wave=");
         myOLED.println("0");
            
      }
      else if(c==HIGH)
      {
         myOLED.setPosi(6,0);
         myOLED.print("wave=");
         myOLED.println("1");
          mp2();
          servo();
      }
          
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

void mp3_high()
{
      digitalWrite(MP1,HIGH);
      digitalWrite(MP2,HIGH);
      digitalWrite(MP3,HIGH);
}
void mp1()
{
  digitalWrite(MP1,LOW);
  delay(100);
  digitalWrite(MP1,HIGH);
  delay(1000);
  digitalWrite(MP1,LOW);
  
}
void mp2()
{
  digitalWrite(MP2,LOW);
  delay(100);
  digitalWrite(MP2,HIGH);
  delay(1000);
  digitalWrite(MP2,LOW);
}
void mp3()
{
  digitalWrite(MP3,LOW);
  delay(100);
  digitalWrite(MP3,HIGH);
  delay(1000);
  digitalWrite(MP3,LOW);
}

