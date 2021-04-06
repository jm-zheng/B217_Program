
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2); 
#include <OLED.h>
OLED myOLED;

#define key1 2

int ZB_rxbuf[127] ,Ser_rxbuf[127] ;
uint8_t ZB_rxflag =0 , Ser_rxflag =0;
uint8_t ZB_set=0 ,Ser_set =0 ;

int time_flag =0,i =0;


int A001_rxbuf [127];
uint8_t A001_flag  ;

int B001_rxbuf [127];
uint8_t B001_flag ;



void setup() 
{
  myOLED.begin(FONT_8x16);
  myOLED.print("123456");
  Serial.begin(9600);
  myZigbee.begin(9600);
  pinMode(key1,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  digitalWrite(13,0x00);
}

void loop() 
{
    zigbee_read();
    serial_read();

}
/*void Set_mode (uint8_t a)
{
  if(set_count == 0)
  {
      if(a == 0xA0)
      {
        for(int j=0;j<=A001_flag;j++)
        {
          Serial.write(A001_rxbuf[j]);
        }  
      }
      else if(a == 0xB0)
      {
        for(int j=0;j<=B001_flag;j++)
        {
          Serial.write(B001_rxbuf[j]);
        }  
      }
      set_count = 1;
  }  
}*/
void zigbee_read()
{
    while(myZigbee.available() > 0)
    {
      ZB_rxbuf[ZB_rxflag]=myZigbee.read();
      if(ZB_rxbuf[ZB_rxflag] == 0x2A)
      {
        ZB_rxflag =0;
        ZB_set = 0;
        break;
      } 
      ZB_rxflag +=1; 
    }
    
   if(ZB_rxbuf[0] == 0xC0 && ZB_rxbuf[1] == 0x01  )
    {
          if(ZB_set == 0)
          {
             for(i=0;i<100;i++ )
              {
                 Serial.write (ZB_rxbuf[4+i]) ;
                 if(ZB_rxbuf[4+i] == 0x2A)
                 {
                   break; 
                 }
              }    
          }  
        ZB_set =1;
      }
 }

 void serial_read()
 {
    while(Serial.available() > 0)
    {
      Ser_rxbuf[Ser_rxflag] =  Serial.read();
      if(Ser_rxbuf[Ser_rxflag] == 0x2A )
      {
        
        Ser_rxflag = 0;
        Ser_set =0;
        break;
      }
      Ser_rxflag +=1;
    }
    if(Ser_set == 0   )
    {
      if(Ser_rxbuf[0] == 0x43)
      {
              if(Ser_rxbuf[2] == 0x38)
              {
                  for(i=0;i<100;i++)
                  {
                      Serial.write(Ser_rxbuf[i]);
                      if(Ser_rxbuf[i] == 0x2A)
                      {
                        break;
                      }
                  }
              }
              else if(Ser_rxbuf[2] == 0x37)
              {
                 for(i=0;i<100;i++)
                  {
                      Serial.write(Ser_rxbuf[i]);
                      if(Ser_rxbuf[i] == 0x2A)
                      {
                        break;
                      }
                  }
              }
              else
              {
                for(i=0;i<100;i++)
                  {
                      Serial.write(Ser_rxbuf[i]);
                      if(Ser_rxbuf[i] == 0x2A)
                      {
                        break;
                      }
                  }
              }
        }
        else if (Ser_rxbuf[0] == 0x4D)
        {
             for(i=0;i<100;i++)
              {
                  Serial.write(Ser_rxbuf[i]);
                  if(Ser_rxbuf[i] == 0x2A)
                  {
                    break;
                  }
              }
        }
       
       Ser_set =1;
    }
   
 }


