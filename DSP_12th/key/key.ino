//遙控器


#include<SoftwareSerial.h>
#include<OLED.h>

SoftwareSerial ZigBee(A1,A2);
OLED myOLED;

#define key1 2
#define key2 6

//---------------
#define led 3
int b=0;
#define READ_MAX  32
uint8_t READbuf[READ_MAX];
uint8_t READLEN;
int READCOUNT;
uint8_t serial_rx_number=0;
void setup() 
{
    myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
    myOLED.setPosi(0,0);
    myOLED.print("bird gw");
     Serial.begin(9600);
     ZigBee.begin(9600);
      Zigbee_setup(27,0xB217,0x2002);
    pinMode(key1,INPUT);
    pinMode(key2,INPUT);
    //----------
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);
    digitalWrite(key1,HIGH);
    digitalWrite(key2,HIGH);
}

void loop() 
{
    key_zigbee_tx();
   zigbee_rx();
   serial_tx();
    
    
    

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
void key_zigbee_tx()
{
   int a= digitalRead(key1);
     if (a==0)
     {
        delay(500);
          switch(b)
          {
            case 1:
            
               digitalWrite(led,HIGH);
               ZigBee.write('1');
               delay(200);
               break;
            case 2:
              digitalWrite(led,LOW);
              ZigBee.write('2');
              delay(200);
             break;
             case 3:
                digitalWrite(led,HIGH);
               ZigBee.write(0x33);
                delay(200);
                break;
             case 4:
               ZigBee.write(0x34);
               delay(200);
               break;

            case 5:
               ZigBee.write(0x35);
               delay(200);  
               break;
 
          }
     }


 a = digitalRead( key2);
    if(a==0)
   {
      delay(700);        // delay in between reads for stability
      if(b>4)
            b=1;
       else 
             b=b+1;
        myOLED.setPosi(4,0);   
        myOLED.print("Func No=:");
        myOLED.println(b);   
       
   } 
      
}
void zigbee_rx()
{
    uint8_t ch;
    if (ZigBee.available())
    {
      ch=ZigBee.read();
      if(READLEN<READ_MAX)
      {
        READbuf[READLEN++]=ch;
      }
      READCOUNT=200;
    }
   
    if(READCOUNT>0)
    {
      READCOUNT--;
        if(READCOUNT==0)
        {
          READbuf[READLEN++]=0x00;
          Serial.print((char *)READbuf);
          myOLED.println((char *)READbuf);
          READLEN=0;
          delay(500);
        }
    }
    
}
void serial_read()
{
       uint8_t ch;
      if(Serial.available())
      {
          ch=Serial.read();
           myOLED.print(ch);
          if(ch==0x31)
          {
            serial_rx_number=1; 
          }
          else if (ch==0x32)
          {
            serial_rx_number=2;
          }
          else if(ch==0x33)
          {
            serial_rx_number=3;
          }
          else if(ch==0x34)
          {
            serial_rx_number=4;
          }
          else if (ch==0x35)
          {
            serial_rx_number=5;
          }
          myOLED.print(ch);
      }
      else if(serial_rx_number != 3)
        {
          serial_rx_number = 0;
        } 
       
}
void serial_tx()
{
  serial_read();
      if (serial_rx_number==1)
      {
        ZigBee.write(0x31);
      }
      else if (serial_rx_number==2)
      {
        ZigBee.write(0x32);
      }
        else if (serial_rx_number==3)
      {
        ZigBee.write(0x33);
      }
        else if (serial_rx_number==4)
      {
        ZigBee.write(0x34);
      }
        else if (serial_rx_number==5)
      {
        ZigBee.write(0x35);
      }
}

