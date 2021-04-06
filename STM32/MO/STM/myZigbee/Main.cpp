//-------------------------------------------------------------------
// Serial_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1
#define myZigbee Serial1
char rx_data[127];
uint8_t rx_number ;
char ser_rx_data[127];
uint8_t ser_rx_number ;

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;


//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

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
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("myZigbee");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	myZigbee.begin(9600);
	Zigbee_setup(20,0x1111,0x2222);

	//loop
	while (1)
	{
		 while(myZigbee.available())
    {
      rx_data[rx_number] = myZigbee.read();
      Serial.write(rx_data[rx_number]);
     
      rx_number += 1;
        
      //Set(rx_data[1] );
     
    }
    while(Serial.available())
    {
      ser_rx_data[ser_rx_number] = Serial.read();
      myZigbee.write(ser_rx_data[ser_rx_number]);
			
      ser_rx_number += 1;
      //Set(rx_data[ser_rx_number]);
    }
    //myOLED.setPosi(2,0);
    //myOLED.print(ser_rx_data);
		myOLED.setPosi(4,0);
    myOLED.print(rx_data);
    ser_rx_number= 0;
    rx_number = 0;
	}
}
