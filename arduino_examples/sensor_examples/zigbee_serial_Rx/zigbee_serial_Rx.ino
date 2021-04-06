#include <SoftwareSerial.h>

SoftwareSerial mySerial (A1,A2);

#include<OLED.h>
OLED myOLED ;

int ur_flag ;
int zb_flag ;
void setup() 
{
    mySerial.begin(9600);
    Zigbee_setup(26,0x1001,0x2002);
    Serial.begin(9600);
    myOLED.begin(FONT_8x16);

}

void loop() 
{
    myOLED.setPosi(2 , 0);
    myOLED.print(ur_flag);
    /*if (Serial.available())
    {
        delay(5);
        myOLED.setPosi(4 , 0);
        myOLED.print("ABC");
        uint8_t usbrx_data[127] ;
        while(Serial.available())
        {
            usbrx_data[ur_flag] = Serial .read();
            ur_flag += 1;
        }
        delay(5);
        if (usbrx_data[0] == 0x41)
        {
            switch (usbrx_data[1])
            {
                case '1':
                       if (usbrx_data[2] == 0x31)
                       {
                            myOLED.setPosi(0, 1);
                              Serial.print("123");
                              break ;
                       }
                       else
                       {
                          myOLED.setPosi(0, 1);
                           Serial.print("ABC");
                           break ;
                       }      
            }
        }
        else 
        {
          for(int i=0; i< ur_flag ; i++)
          {
             myzigbee.write(usbrx_data[i]);
             
          }
        }
         ur_flag = 0;
        
    }*/


    //--------------------

    if (mySerial.available())
    {
      delay(5);
      uint8_t mySerial_data[127];
      while (mySerial.available())
      {
        mySerial_data[zb_flag] = mySerial.read();
        zb_flag += 1;
        
      }
      Serial.print((char *) mySerial_data);
      zb_flag  =0;
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

