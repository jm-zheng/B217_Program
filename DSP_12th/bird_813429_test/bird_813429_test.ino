#include<SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);

#include<OLED.h>
OLED myOLED;
#define MICROWAVE  A0
#define bz  A3
#define key1 2
#define led 3
int a;
void setup() 
{

      myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
      myOLED.setPosi(0,0);
      myOLED.print("B217 BIRD:ON");

      Serial.begin(9600);
     //----------------------------
      ZigBee.begin(9600);
      Zigbee_setup(28,0xB217,0x2002);
      pinMode(led,OUTPUT);
      digitalWrite(led,LOW);

      pinMode( MICROWAVE,INPUT_PULLUP);

      pinMode(bz,OUTPUT);
      digitalWrite(bz,LOW);
      
}
void loop()
{
    zigbee_read();
    if(a==1) //  Zigbee1
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
       beeb();
    }
    if(a==2)//  Zigbee2
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
        bb();
    }
       if(a==3)//  Zigbee3
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
        bbb();
    }
      if(a==4)//  Zigbee4 微波
    {
        myOLED.setPosi(4,0);
        myOLED.print("ZigBee:") ;
        myOLED.print(a);
         int c = digitalRead( MICROWAVE);  //微波變數
          myOLED.setPosi(6,0);
         myOLED.print("wp:");
         myOLED.print(c);
         if(c==LOW)  //微波未觸發
          {
              digitalWrite(led,LOW);
           
          }
        
            else if ( c==HIGH)  // 微波觸發
            {
                  bbb();
                  LED(2,300);
                  
            }
      
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
      else if(a != 4)
        {
          a = 0;
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
void beeb()
{
  
           digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
}
void bb()  //兩聲
{
  
              digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
              delay(500);
              digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
}
void bbb()  //三聲
{
  
              digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
              delay(500);
              digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
              delay(500);
              digitalWrite(bz,HIGH);
              delay(500);
              digitalWrite(bz,LOW);
}

