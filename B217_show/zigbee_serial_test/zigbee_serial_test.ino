#include <SoftwareSerial.h>

SoftwareSerial  myzigbee (A1,A2);

#include<OLED.h>
OLED myOLED ;

int ur_flag ;
int zb_flag ;
void setup() 
{
    myzigbee.begin(115200);
    Serial.begin(115200);
    myOLED.begin(FONT_8x16);

}

void loop() 
{
    myOLED.setPosi(2 , 0);
    myOLED.print(ur_flag);
    if (Serial.available())
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
        
    }


    //--------------------
    /*
    if (myzigbee.available())
    {
      delay(5);
      uint8_t myzigbee_data[127];
      while (myzigbee.available())
      {
        myzigbee_data[zb_flag] = myzigbee.read();
        zb_flag += 1;
        
      }
      Serial.print((char *) myzigbee_data);
      zb_flag  =0;
    }
    */

}
