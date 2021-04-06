#include<SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);

#include<OLED.h>
OLED myOLED;

int LSval;
char ZB_Rx_Data[127];
uint8_t ZB_Rx_number;


void setup() 
{    
    Serial.begin(9600);
     ZigBee.begin(115200);
     //Zigbee_setup(27,0xB217,0x2002);

     myOLED.begin(FONT_8x16);
     myOLED.print("B217_power_LS");

     

}

void loop() 
{
    zigbee_rx();
    if (ZB_Rx_Data[0] == 83 && ZB_Rx_Data[1] == 48 )
      {
         myOLED.setPosi(4,0);
         myOLED.print("213");
      }

        delay(500);
  
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
uint8_t oledClearFlag = 0;
void zigbee_rx()
{
    while(ZigBee.available())
    {   
        /*if(oledClearFlag == 0)
        {
              myOLED.setPosi(2,0);
              myOLED.print("             ");
              myOLED.setPosi(2,0);
              oledClearFlag += 1;
        }*/
        ZB_Rx_Data[ZB_Rx_number] = ZigBee.read();
      
        Serial.println(ZB_Rx_Data[ZB_Rx_number]);
        ZB_Rx_number += 1;
     
        uint8_t delayTime = 10 ;   //字可以鄉間10個字
        while(delayTime--) 
        {    
            delay(1); //9600倒數
            if (ZigBee.available())
            {
                break;
            }
        }
    }
    if (ZB_Rx_number > 0)
    {   
       /* myOLED.setPosi(4,0);
        myOLED.print("    ");
        myOLED.setPosi(4,0)*/;
        Serial.println(ZB_Rx_number);
        
        ZB_Rx_number = oledClearFlag = 0; 
        
    }
}

