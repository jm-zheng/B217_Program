//------------------------------------------------------------------------------
#include <OLED.h>

OLED myOLED;

uint32_t n=0;
float fn=0.0;
//------------------------------------------------------------------------------
void setup()  
{
  // set the data rate for the SoftwareSerial port
  myOLED.begin(FONT_8x16); //FONT_6x8
  myOLED.println("Hello, world?");
  myOLED.println("1234567890123456");
  myOLED.println("abcdefghijklmnop");
  myOLED.println("ABCDEFGHIJKLMNOP");
  delay(2000);
  myOLED.clearScreen();
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  
  if(n>50)
  {
    myOLED.print(n);
    myOLED.print(" HEX=");
    myOLED.print(n,HEX);
    myOLED.print(" Float=");
    myOLED.println(fn);
  }
  else
  {
    myOLED.print(n);
    myOLED.print(" H=");
    myOLED.print(n,HEX);
    myOLED.print(" f=");
    myOLED.println(fn);
  }
  if(n==50)
  {
    myOLED.setFont(FONT_6x8);
    myOLED.println("Hello, world?");
    myOLED.println("123456789012345678901");
    myOLED.println("abcdefghijklmnopqrstu");
    myOLED.println("ABCDEFGHIJKLMNOPQRSTU");
    myOLED.println("111111111111111111111");
    myOLED.println("222222222222222222222");
    myOLED.println("333333333333333333333");
    myOLED.println("444444444444444444444");
    delay(2000);
  }
  n++;
  fn+=1.23;
  delay(10);
  
  if(n==100)
  {
    myOLED.setFont(FONT_8x16);
    n=0;
    fn=0.0;
  }
  
}

