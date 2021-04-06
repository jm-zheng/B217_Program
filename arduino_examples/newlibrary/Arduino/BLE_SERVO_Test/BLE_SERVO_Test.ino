//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>
#include <Servo.h>// 

OLED myOLED;

SoftwareSerial myBLE(A5, A4); // RX, TX

Servo myservo1;
Servo myservo2;
int value1 = 90;
int value2 = 90;

//------------------------------------------------------------------------------
void setup()  
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myBLE.begin(9600);
  myservo1.attach(10); // Servo 1 = pin 10
  myservo2.attach(11); // Servo 2 = pin 11  
  myOLED.println("BLE Serv");
  //BLE_setName((char *)"Serv-101");
  myservo1.write(value1);
  myservo2.write(value2);
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  uint8_t ch;
  if (myBLE.available())
  {
    ch=myBLE.read();
    if(ch==0x11)
    {
        myOLED.println("Key #1");
        value1+=20;
        myservo1.write(value1);
        if(value1>160)
        {
          value1=0;
        }
    }
    if(ch==0x22)
    {
       myOLED.println("Key #2");
       value2+=20;
       myservo2.write(value2);
       if(value2>160)
       {
         value2=0;
       }
    }
    if(ch==0x44)
    {
      myOLED.println("Key #3");
       myservo1.write(90);   
       myservo1.write(90);   
       value1=90;
       value2=90;
    }
  }
}

//------------------------------------------------------------------------------
void BLE_setName(char blename[])
{
  int i,len;
  
  // BLE module get mac
  myBLE.write(0xAA);  
  myBLE.write(0xED);  
  myBLE.write(0xBB);  
  delay(100);

  // BLE module set name and Save
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
}
