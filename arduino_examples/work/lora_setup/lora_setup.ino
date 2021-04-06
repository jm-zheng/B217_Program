//2018/03/11


#include <SoftwareSerial.h>
SoftwareSerial mylora(A2,A1);  //RX,TX

#include <OLED.h>
OLED myOLED;
 

#define key1 2
#define key2 6

uint8_t rxbuf[127];
uint8_t rxflag ;
void setup() 
{
    Serial.begin(9600);
    mylora.begin(9600);
    myOLED.begin(FONT_8x16);
    myOLED.print("settest");
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    
    

}

void loop() 
{
  /*
    mylora.write(0xC0);
    mylora.write(0x01);
    mylora.write(0x04);
    mylora.write(0x1A);
    mylora.write(0x04);
    mylora.write(0xC4); //設定*/
    
    /*mylora.write(0x01);
    mylora.write(0x04);
    mylora.write(0x04);
    mylora.write("123"); */ //測試
    
    
    /*mylora.write(0xC1);
    mylora.write(0xC1);
    mylora.write(0xC1); //觀看目前參數*/
    
    while (mylora.available())
    {
       rxbuf[rxflag] = mylora.read();
       Serial.write(rxbuf[rxflag]);
       rxflag += 1;
        
    }
  
    rxflag =0 ;
    delay(1000);

}
