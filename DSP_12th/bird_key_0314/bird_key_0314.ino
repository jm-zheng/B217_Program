#include<SoftwareSerial.h>
#include<OLED.h>

SoftwareSerial  ZigBee(A1,A2);
OLED myOLED;

#define key1 2
#define key2 6
int b=0;
void setup()
{
    myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
    myOLED.setPosi(0,0);
    myOLED.print("bird gw");
    ZigBee.begin(9600);
    Zigbee_setup(26,0x1001,0x2002);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    
}

void loop() 
{
  int a = digitalRead(key1);
  if (a==LOW)
  {
     switch(b)
      {
          case 1:
              ZigBee.write(0x31);
              myOLED.setPosi(2,0);
              myOLED.print(b);
              delay(300);
              break;
          case 2:
              ZigBee.write('2');
              myOLED.setPosi(2,0);
              myOLED.print(b);
              delay(300);
              break;
           case 3:
              ZigBee.write('3');
              myOLED.setPosi(2,0);
              myOLED.print(b);
              delay(300);
              break;
           case 4:
              ZigBee.write('4');
              myOLED.setPosi(2,0);
              myOLED.print(b);
              delay(300);
              break;

           case 5:
                ZigBee.write('5');
                myOLED.setPosi(2,0);
                myOLED.print(b);
                delay(300);
                break;

            case 6:
                    ZigBee.write('6');
                    myOLED.setPosi(2,0);
                    myOLED.print(b);
                    delay(300);
                    break;

            case 7:
                    ZigBee.write('7');
                    myOLED.setPosi(2,0);
                    myOLED.print(b);
                    delay(300);
                    break;
            case 8:
                    ZigBee.write('8');
                    myOLED.setPosi(2,0);
                    myOLED.print(b);
                    delay(300);
                    break;
            case 9:
                        ZigBee.write('9');
                        myOLED.setPosi(2,0);
                        myOLED.print(b);
                        delay(300);
                        break;        
          
        }
  }


   a=digitalRead(key2);
   if(a==0)
   {
      delay(700);
      if(b>8)
      {
        b=0;
      }
      else 
      {
        b=b+1;
        myOLED.setPosi(4,0);   
        myOLED.print("Func No=:");
        myOLED.println(b); 
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

