//------------------------------------------------------------------------------
// SoftwareSerial_Example.ino
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;

//SoftwareSerial mySerial(A5, A4); // RX, TX
SoftwareSerial mySerial(A1, A2); // RX, TX

#define key 2
//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(460800);
  Serial.begin(9600);
  BLE_setName("DC05-460800");
  myOLED.println("BLE Test");
  pinMode(key,INPUT_PULLUP);
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  /*if (mySerial.available())
  {
    ch=mySerial.read();
    myOLED.print('(');
    myOLED.print(ch,HEX);
    myOLED.print(')');
    Serial.write(ch);    
  }
  if (Serial.available())
  {
    ch=Serial.read();
    myOLED.print('[');
    myOLED.print(ch,HEX);
    myOLED.print(']');
    mySerial.write(ch);    
  }*/

  if (digitalRead(key) == LOW)
  {
    mySerial.write(0x3A);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x35);
    mySerial.write(0x42);
    mySerial.write(0x32);
    mySerial.write(0x30);
    mySerial.write(0x32);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x30);

    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x30);
    mySerial.write(0x34);
    mySerial.write(0x37);
     mySerial.write(0x0D);
    mySerial.write(0x0A);
    myOLED.setPosi(2,0);
    myOLED.print("1");
    delay(300) ;
  }
}

//------------------------------------------------------------------------------
void BLE_setName(char blename[])
{
  int i,len;
  
  // BLE module get mac
  mySerial.write(0xAA);  
  mySerial.write(0xED);  
  mySerial.write(0xBB);  
  delay(100);

  // BLE module set name
  mySerial.write(0xAA);  
  mySerial.write(0xE3);  
  mySerial.write(0x5A);  
  len=strlen(blename);
  for(i=0;i<12;i++)
  {
    if(i<len)
    {
      mySerial.write((uint8_t)blename[i]);  
    }
    else
    {
      mySerial.write(0x20);  
    }
  }
  mySerial.write(0xBB); 
  delay(200);
  
  // BLE module reboot
  mySerial.write(0xAA);  
  mySerial.write(0xEF);  
  mySerial.write(0x5A);  
  mySerial.write(0xBB); 
  delay(200);
  while(mySerial.available())
  {
    mySerial.read();
  }
}

