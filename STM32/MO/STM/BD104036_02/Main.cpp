//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define myZigbee Serial1
char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;


//-------RALAY-------------------------------------------------------------------------------
#define RALAY PB6

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;


//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

//------------------------------------------------------------------
//??
///----------------------------------------------------------------------------------------
uint8_t REST[]                ={0x55,0x55,0x17,0x03,0x06,0xE8,0x03,0x06,0xD0,0x05,0x05,0xDC,0x05,0x04,0xEE,0x02,0x03,0xE2,0x04,0x02,0xD0,0x05,0x01,0x65,0x04};
//??
//-------?-------------------------------------------------------------------------------
uint8_t Server1[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x01,0xD0,0x07};
//?
uint8_t Server2[]             ={0x55,0x55,0x08,0x03,0x01,0xDC,0x05,0x01,0xE8,0x03};
//?
uint8_t Server3[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x03,0x5F,0x05};
//??
uint8_t Server4[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x42,0x04};
//?
uint8_t Server5[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xE2,0x04};
//?
uint8_t Server6[]             ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0x66,0x08,0x04,0xDC,0x05,0x03,0xE2,0x04,0x02,0x11,0x04};
//?
uint8_t Server7[]             ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xD0,0x05};
//?
uint8_t Server8[]             ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x06,0xDC,0x05,0x05,0xD0,0x05,0x02,0xD0,0x05};
//?
uint8_t Server9[]             ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0xE2,0x04,0x04,0xB0,0x02,0x03,0x9E,0x05};
//??
uint8_t Server10[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0xDC,0x05,0x04,0x33,0x02,0x03,0x1B,0x06};
//?
uint8_t Server11[]            ={0x55,0x55,0x14,0x03,0x05,0xE8,0x03,0x06,0xDC,0x05,0x05,0xDC,0x05,0x04,0xDC,0x05,0x03,0xDC,0x05,0x02,0xDC,0x05};
//?or??
uint8_t Server12[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0xD6,0x06,0x04,0x65,0x04,0x03,0x98,0x06};
//???
uint8_t Server13[]            ={0x55,0x55,0x14,0x03,0x05,0xE8,0x03,0x06,0xDC,0x05,0x05,0xDC,0x05,0x04,0xDC,0x05,0x03,0xDC,0x05,0x02,0xDC,0x05};
//?
uint8_t Server14[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0x5F,0x05,0x04,0xEE,0x02,0x03,0x5F,0x05};
//?
uint8_t Server15[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x05,0x05,0xDC,0x05};
//?
uint8_t Server16[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x05,0x03,0xB4,0x05};
//?
uint8_t Server17[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x05,0x04,0xAD,0x02};
//?
uint8_t Server18[]            ={0x55,0x55,0x14,0x03,0x05,0xE8,0x03,0x06,0xDC,0x05,0x05,0xDC,0x05,0x04,0xDC,0x05,0x03,0xDC,0x05,0x02,0xDC,0x05};
//?
uint8_t Server19[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x03,0x5F,0x05};
//??
uint8_t Server20[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x04,0xEE,0x02};
//?
uint8_t Server21[]            ={0x55,0x55,0x14,0x03,0x05,0xE8,0x03,0x06,0xDC,0x05,0x05,0xDC,0x05,0x04,0xDC,0x05,0x03,0xDC,0x05,0x02,0xDC,0x05};
//?
uint8_t Server22[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0x1B,0x06,0x04,0x71,0x02,0x03,0xDC,0x05};
//?
uint8_t Server23[]            ={0x55,0x55,0x0E,0x03,0x03,0xE8,0x03,0x05,0x5F,0x05,0x04,0xEE,0x02,0x03,0xDC,0x05};
//?
uint8_t Server24[]            ={0x55,0x55,0x14,0x03,0x05,0xE8,0x03,0x06,0xDC,0x05,0x05,0xDC,0x05,0x04,0xDC,0x05,0x03,0xDC,0x05,0x02,0xDC,0x05};
//?
uint8_t Server25[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x62,0x07};
//?
uint8_t Server26[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0x4D,0x08,0x04,0xDC,0x05,0x03,0xE2,0x04,0x02,0x8A,0x07};
//??
uint8_t Server27[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x05,0xDC,0x05};
//?
//--------?------------------------------------------------------------------------------
uint8_t Server28[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x42,0x05};
//??(?)?
uint8_t Server29[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0xD6,0x06,0x04,0x65,0x04,0x03,0xAE,0x06,0x02,0x2F,0x05};
//???(?)
//-------?-------------------------------------------------------------------------------
uint8_t Server30[]            ={0x55,0x55,0x08,0x03,0x01,0xE8,0x03,0x06,0x76,0x06};
//??(?)?
uint8_t Server31[]            ={0x55,0x55,0x11,0x03,0x04,0xE8,0x03,0x05,0xD6,0x06,0x04,0x65,0x04,0x03,0xAE,0x06,0x02,0x68,0x06};
//???(?)
//------------------------------------------------------------------------------------------

//-------------------------------------------------------------------
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
void set_motor( uint8_t a )
{
 if(rx_data[0] == 'B')
 {
    switch(a)
   {
      case 0x32 ://-----?--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server8 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server9 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server10 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server11 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server12 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server13 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server14 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server15 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server17 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server18 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}//3
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server19 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server20 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server21 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server22 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server23 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server24 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server25 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server26 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server27 [i]);}
        delay(2000);        
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("B2end");
        myOLED.setPosi(4,0);
        myOLED.print("B2end");
      }
      break;
       case 0x33 ://-----?--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server8 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server9 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server10 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server11 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server28 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server29 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server13 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server14 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server15 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server17 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server18 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}//3
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server19 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server20 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server21 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server22 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server23 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server24 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server25 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server26 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server27 [i]);}
        delay(2000);        
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("B3end");
        myOLED.setPosi(4,0);
        myOLED.print("B3end");
      }
      break;
       case 0x31 ://-----?--------------------------------
      {
        for(int i=0;i<10;i++){Serial.write(Server4 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server5 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server6 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server7 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server8 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server9 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server10 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server11 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server30 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server31 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server13 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server14 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server15 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server16 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server17 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server18 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}//3
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server19 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server20 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server21 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server22 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server1 [i]);}
        delay(2000);
        for(int i=0;i<16;i++){Serial.write(Server23 [i]);}
        delay(2000);
        for(int i=0;i<22;i++){Serial.write(Server24 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server25 [i]);}
        delay(2000);
        for(int i=0;i<19;i++){Serial.write(Server26 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server2 [i]);}
        delay(2000);
        for(int i=0;i<10;i++){Serial.write(Server27 [i]);}
        delay(2000);        
        for(int i=0;i<25;i++){Serial.write(REST [i]);}
        myZigbee.print("B1end");
        myOLED.setPosi(4,0);
        myOLED.print("B1end");
      }
      break;
   }
  
  }
  


  //-----------------------------------------
   else if(rx_data[0]=='R')
  {
    {
    switch(a)
   {
      case 0x31 ://-----??--------------------------------
      {
        digitalWrite(RALAY, HIGH);
        myZigbee.print("R1end");
        myOLED.setPosi(4,0);
        myOLED.print("R1end");
      }
      break;
      case 0x32 ://-----??--------------------------------
      {
        digitalWrite(RALAY, LOW);
        myZigbee.print("R2end");
        myOLED.setPosi(4,0);
        myOLED.print("R2end");
      }
      break;
       
      }
    }
  }
}
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("MBOT_V2");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	pinMode(RALAY,OUTPUT);
	digitalWrite(RALAY,LOW);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	myZigbee.begin(9600);
	Zigbee_setup(20,0x1111,0x2222);
  for(int i=0;i<25;i++){Serial.write(REST [i]);}
	//loop
	while (1)
	{
		 while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      //Serial.write(rx_data[rx_number]);
      myOLED.print(rx_data[rx_number]);
      rx_number += 1;
        
      //Set(rx_data[1] );
     
    }
   
    ser_rx_number= 0;
    rx_number = 0;
		set_motor(rx_data[1]);
    myOLED.setPosi(2,0);
		ser_rx_number= 0;
    rx_number = 0;
    rx_data[0] = 0;
    rx_data[1] = 0;
	}
}
