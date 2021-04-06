//ZigBee 送

//----------------------------
#include <SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);
//----------OLED--------
#include <OLED.h>
OLED myOLED;
//-------------------
#define key1 2
#define key2 6
#define key1_push 1
#define key2_push 2
int a ;
void setup() 
{
  
 //----------------------------
   myOLED.begin(FONT_8x16);
   myOLED.print("T5_zigbee_tx");
 //-------------------------
   pinMode(key1,INPUT_PULLUP);
   pinMode(key2,INPUT_PULLUP);
//------------zigbee_setup------
   ZigBee.begin(9600);
   Zigbee_setup(27,0xB217,0x2002);
   

}

void loop() 
{
  uint8_t bt = Key_status() ;
   
   if(bt == key1_push)
   {
      delay(300);
      switch(a)
      {
        case 1:
        ZigBee.write(0x31);
        break;
        case 2 :
        ZigBee.write(0x32);
        break;
        case 3 :
         ZigBee.write(0x33);
        break;
        case 4 :
         ZigBee.write(0x34);
        break;
        case 5 :
         ZigBee.write(0x35);
        break;
        
      }
      
   }
   else if(bt == key2_push)
   {
      if(a<5) 
      {
         a=a+1;
      }
      else
      {
        a=0; 
      }
   }

     myOLED.setPosi(2,0);
      myOLED.print(a);
      delay(250);
}




uint8_t Key_status()
{
      //為甚麼不能用void
    if (digitalRead(key1)==LOW)
    {
       return key1_push;
    }
    if (digitalRead(key2)==LOW)
    {
       return key2_push;
    }

  return 0 ;

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
