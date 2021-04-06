//------------Declare-CC2530--------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial myZigbee(A1, A2);            // RX, TX
//-------RALAY-------------------------------------------------------------------------------
#define RALAY 2

//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;

char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;

//動作
//----------------------------------------------------------------------------------------
uint8_t REST[]                ={0x55,0x55,0x17,0x03,0x06,0xE8,0x03,0x06,0xD0,0x05,0x05,0xDC,0x05,0x04,0xEE,0x02,0x03,0xE2,0x04,0x02,0xD0,0x05,0x01,0x65,0x04};
//重置
//-------大-------------------------------------------------------------------------------
uint8_t Server0[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0xF0,0x05};
//下
uint8_t Server1[]             ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0x1B,0x06,0x04,0x53,0x02,0x03,0xDC,0x05};
//下
uint8_t Server2[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xD0,0x07};
//夾
uint8_t Server3[]             ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0x5F,0x05,0x04,0x2D,0x03,0x03,0x5F,0x05};
//上升
uint8_t Server4[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x53,0x07};
//向左
uint8_t Server5[]             ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0x71,0x08,0x04,0xDC,0x05,0x03,0xE2,0x04,0x02,0x27,0x07};
//下降
uint8_t Server6[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0x65,0x04};
//放
uint8_t Server7[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xDC,0x05};
//上升
uint8_t Server8[]             ={0x55,0x55,0x17,0x03,0x06,0xE8,0x03,0x06,0xD0,0x05,0x05,0xDC,0x05,0x04,0xEE,0x02,0x03,0xE2,0x04,0x02,0xD0,0x05,0x01,0x65,0x04};
//回歸
//-------小-------------------------------------------------------------------------------
uint8_t Server9[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x0A,0x05};
//右移
uint8_t Server10[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0x98,0x06,0x04,0xF9,0x02,0x03,0x69,0x05,0x02,0xEC,0x04};
//下降
//-------中-------------------------------------------------------------------------------
uint8_t Server11[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0xAD,0x06};
//左移
uint8_t Server12[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0xD6,0x06,0x04,0x41,0x03,0x03,0x69,0x05,0x02,0x46,0x06};
//下降
//-------第一-------------------------------------------------------------------------------
uint8_t Server13[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x77,0x04};
//下降
uint8_t Server14[]            ={0x55,0x55,0x0B,0x03,0x02,0xE8,0x03,0x05,0x53,0x07,0x04,0xDC,0x05};
//下降
uint8_t Server15[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0x66,0x08,0x04,0xDC,0x05,0x03,0xE2,0x04,0x02,0x88,0x04};
//下降
uint8_t Server16[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0x53,0x05};
//下降
uint8_t Server17[]            ={0x55,0x55,0x0B,0x03,0x02,0xE8,0x03,0x06,0xF4,0x01,0x02,0xDC,0x05};
//下降
uint8_t Server18[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x06,0x18,0x02,0x05,0xFA,0x07,0x03,0x65,0x04,0x02,0xDC,0x05};
//下降
uint8_t Server19[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xD6,0x06};
//下降
//-------第二-------------------------------------------------------------------------------
uint8_t Server20[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0xD0,0x05,0x04,0xEE,0x02,0x03,0xE2,0x04};
//下降
//-------第三-------------------------------------------------------------------------------
uint8_t Server21[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0xF4,0x02};
//下降
uint8_t Server22[]            ={0x55,0x55,0x0B,0x03,0x02,0xE8,0x03,0x05,0x4D,0x08,0x02,0xAC,0x06};
//下降
//------------------------------------------------------------------------------------------
void setup()
{
    pinMode(RALAY,OUTPUT);
    Serial.begin(9600);
    myZigbee.begin(9600);
    Zigbee_setup(20,0x1111,0x2222);
    delay(10);
    myOLED.begin(FONT_8x16);
    myOLED.print("MBOT_V1");
    for(int i=0;i<25;i++){Serial.write(REST [i]);}
}
void loop() 
{
    
    while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      //Serial.write(rx_data[rx_number]);
      myOLED.print(rx_data[rx_number]);
      rx_number += 1;
        
      //Set(rx_data[1] );
     
    }
    /*while(Serial.available())
    {
      ser_rx_data[ser_rx_number] = Serial.read();
      myZigbee.write(ser_rx_data[ser_rx_number]);
      //myOLED.print(ser_rx_data[ser_rx_number]);
      ser_rx_number += 1;
      //Set(rx_data[ser_rx_number]);
    }*/
    
   
    Set(rx_data[1]);
    myOLED.setPosi(2,0);
   //myOLED.println(rx_data[rx_number]);
    
    ser_rx_number= 0;
    rx_number = 0;
    rx_data[0] = 0;
    rx_data[1] = 0;
    
}
//------------------------------------------------------------------------------
void Set( uint8_t a )
{
 if(rx_data[0] == 'A')
 {
    switch(a)
   {
      case 0x32 ://-----大--------------------------------
      {
        for(int i=0;i<16;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(1500);
        for(int i=0;i<16;i++){Serial.write(Server3 [i]);}
        delay(1000);
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(1000);
        for(int i=0;i<19;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(1000);
        for(int i=0;i<25;i++){Serial.write(Server8 [i]);}
        myZigbee.print("A2end");
        myOLED.setPosi(4,0);
        myOLED.print("A2end");
        
      }
      break;
       case 0x33 ://-----小--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server9 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server10 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server3 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(2000);
        for(int i=0;i<25;i++){Serial.write(Server8 [i]);}
        myZigbee.print("A3end");
        myOLED.setPosi(4,0);
        myOLED.print("A3end");
      }
      break;
       case 0x31 ://-----中--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server11 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server12 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server3 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(2000);
        for(int i=0;i<25;i++){Serial.write(Server8 [i]);}
        myZigbee.print("A1end");
        myOLED.setPosi(4,0);
        myOLED.print("A1end");
      }
      break;
   }
  
  }
  //--------------------------------------------------------------------------
  else if(rx_data[0]=='C')
  {
    {
    switch(a)
   {
      case 0x33 ://-----第一--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server13 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server14 [i]);}
        delay(2500);
        for(int i=0;i<19;i++){Serial.write(Server15 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server17 [i]);}
        delay(2500);
        for(int i=0;i<19;i++){Serial.write(Server18 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server19 [i]);}
        delay(2500);
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("C3end");
        myOLED.setPosi(4,0);
        myOLED.print("C3end");
      }
      break;
       case 0x31 ://-----第二--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server13 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server14 [i]);}
        delay(2500);
        for(int i=0;i<19;i++){Serial.write(Server15 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server17 [i]);}
        delay(2500);
        for(int i=0;i<16;i++){Serial.write(Server20 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2500);
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("C1end");
        myOLED.setPosi(4,0);
        myOLED.print("C1end");
      }
      break;
       case 0x32 ://-----第三--------------------------------
      {
       for(int i=0;i<10;i++){Serial.write(Server13 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server14 [i]);}
        delay(2500);
        for(int i=0;i<19;i++){Serial.write(Server15 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server21 [i]);}
        delay(2500);
        for(int i=0;i<13;i++){Serial.write(Server22 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server6 [i]);}
        delay(2500);
        for(int i=0;i<10;i++){Serial.write(Server19 [i]);}
        delay(2500);
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("C2end");
        myOLED.setPosi(4,0);
        myOLED.print("C2end");
      }
      break;
      }
    }
  }
  //-----------------------------------------
   else if(rx_data[0]=='E')
  {
    {
    switch(a)
   {
      case 0x31 ://-----啟動--------------------------------
      {
        digitalWrite(RALAY, HIGH);
        myZigbee.print("E1end");
        myOLED.setPosi(4,0);
        myOLED.print("E1end");
      }
      break;
      case 0x32 ://-----關閉--------------------------------
      {
        digitalWrite(RALAY, LOW);
        myZigbee.print("E2end");
        myOLED.setPosi(4,0);
        myOLED.print("E2end");
      }
      break;
       
      }
    }
  }
}
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
