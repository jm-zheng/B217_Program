
//------------Declare-CC2530--------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2);            // RX, TX

//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;

#define key1 2
#define key2 6

int key_flag =0;
int key2_flag =0;

char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;
uint8_t re[] ={0x55,0x55,0x08,0x03,0x01,0x20,0x03,0x01,0xEE,0x02};
uint8_t ce[] ={0x55,0x55,0x08,0x03,0x01,0x20,0x03,0x01,0xD0,0x07};
uint8_t m_1500[]   ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xDC,0x05};
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  myZigbee.write(0xAA);  
  myZigbee.write(0xC7);  
  myZigbee.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  myZigbee.write(0xAA);  
  myZigbee.write(0xC7);  
  myZigbee.write(0x5A);  
  myZigbee.write(channel);  
  myZigbee.write(panid>>8);  
  myZigbee.write(panid&0xff);  
  myZigbee.write(addr>>8);  
  myZigbee.write(addr&0xff);  
  myZigbee.write(0xBB); 
}
void setup()
{
    Serial.begin(9600);
    myZigbee.begin(9600);
    //Zigbee_setup(26,0x1002,0x2002);
    delay(10);
    myOLED.begin(FONT_8x16);
    myOLED.print("hand");
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);

}
void loop() 
{
    
    while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      Serial.print(rx_data[rx_number]);
      myOLED.print(rx_data[rx_number]);
      rx_number += 1;
      
    }
    while(Serial.available())
    {
      ser_rx_data[ser_rx_number] = Serial.read();
      myZigbee.print(ser_rx_data[ser_rx_number]);
      myOLED.print(ser_rx_data[ser_rx_number]);
      ser_rx_number += 1;
      
    }
    if(digitalRead(key1) == LOW)
    {
      if(key_flag ==0 )
      {
        key_flag =1;
        hand_set(re);
        delay(2000);
        hand_set(ce);


        myOLED.print("asd");
      }
    }
    else key_flag =0;
     if(digitalRead(key2) == LOW)
    {
      if(key2_flag ==0 )
      {
        key_flag =1;
        for(int j =1 ;j<7 ;j++)
        {
          m_1500 [7] = j;
          delay(500);
         
          for(int a=0;a<10;a++)
          {
            myZigbee.write(m_1500 [a]);
          }
         myOLED.print("789");
        }
      }
    }
    else key2_flag =0;
    
    ser_rx_number= 0;
    rx_number = 0;
}
void hand_set(uint8_t *a)
{
   for(int i=0;i<10;i++)
    {
        myZigbee.write(a[i]);
    }
}
void hand_set_2(uint8_t *a)
{
   for(int i=0;i<10;i++)
    {
        myZigbee.write(a[i]);
    }

}
//------------------------------------------------------------------------------

