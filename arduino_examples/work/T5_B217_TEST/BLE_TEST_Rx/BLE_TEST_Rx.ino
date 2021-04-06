#include<SoftwareSerial.h>
SoftwareSerial myBLE(A1,A2);

#include <OLED.h>
OLED myOLED;

int LSval;
uint8_t BLE_Rx_Data[127];
uint8_t BLE_Rx_number;
void setup() 
{
   Serial.begin(9600);
    //========SETUP BLE==============================================
   myBLE.begin(9600);
   BLE_setName("NanoBLExx"); //自訂BLE裝置訂編號

    myOLED.begin(FONT_8x16);
    myOLED.print("B217_power_LS");

   
}

void loop() 
{
  String uartRead="";
  if (myBLE.available()) {
    // read the most recent byte (which will be from 0 to 255):
    uartRead = myBLE.readString() ;
    // set the brightness of the LED:
    myOLED.setPosi(4,0);
    myOLED.print("CMD:");
    myOLED.println(uartRead);
     Serial.println(uartRead);
   }
}
void BLE_setName(char blename[])
{
  int i,len;
  
  // BLE module get mac
  myBLE.write(0xAA);  
  myBLE.write(0xED);  
  myBLE.write(0xBB);  
  delay(100);

  // BLE module set name
  myBLE.write(0xAA);  
  myBLE.write(0xE3);  
  myBLE.write(0x5A);  
  len=strlen(blename);
  for(i=0;i<12;i++)
  {
    if(i<len)
    {
      myBLE.write((uint8_t)blename[i]);  
    }
    else
    {
      myBLE.write(0x20);  
    }
  }
  myBLE.write(0xBB); 
  delay(200);
  
  // BLE module reboot
  myBLE.write(0xAA);  
  myBLE.write(0xEF);  
  myBLE.write(0x5A);  
  myBLE.write(0xBB); 
  delay(200);
  while(myBLE.available())
  {
    myBLE.read();
  }
}
