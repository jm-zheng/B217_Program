///窗外感測裝置
#include<SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);

#include<OLED.h>
OLED myOLED;
#define key1  2

#define LS A0
#define lsmin 100
#define lslv1 250

#define lsmax 450
void setup() 
{
     ZigBee.begin(115200);
     //Zigbee_setup(27,0xB217,0x2002);
     Serial.begin(9600);

     myOLED.begin(FONT_8x16);
     myOLED.print("B217_power_LS");

     pinMode(LS,INPUT);
     pinMode(key1,INPUT_PULLUP);
     

}

void loop() 
{     
      
      if(digitalRead(key1)== LOW)
      {
         ZigBee.print("S1");
         myOLED.print("123");
         delay(300);
      }

     /* int LSval = analogRead(LS);
      myOLED.setPosi(2,0);
      myOLED.print(LSval);
      delay(300);

      if (LSval < lsmin)
      {
        ///全亮
        ZigBee.print("S0");
         myOLED.setPosi(4,0);
         myOLED.print("S0");
      }
      else if (lsmin < LSval && LSval < lslv1)
      {
        ///75%
         ZigBee.print("S1");
         myOLED.setPosi(4,0);
         myOLED.print("S1");
      }
     else if (lslv1<LSval && LSval<lsmax)
     {
        //50%
        ZigBee.print("S2");
        myOLED.setPosi(4,0);
         myOLED.print("S2");
     }
     else
     {
        //關
         ZigBee.print("S3");
         myOLED.setPosi(4,0);
         myOLED.print("S3");
     }
     delay(1000);*/
}


/*void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
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
}*/
