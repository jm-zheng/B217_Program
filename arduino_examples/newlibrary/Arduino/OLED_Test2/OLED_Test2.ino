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
  myOLED.setBrightness(0);
  myOLED.println("Hello, world?");
  myOLED.println("1234567890123456");
  myOLED.println("abcdefghijklmnop");
  myOLED.println("ABCDEFGHIJKLMNOP");
  delay(2000);
  myOLED.clearScreen();
  myOLED.setBrightness(255);
}

//------------------------------------------------------------------------------
void loop() // run over and over
{
  if(n>20)
  {
    myOLED.print(n);
    myOLED.print(" HEX=");
    myOLED.print(n,HEX);
    myOLED.print(" ");
    myOLED.println(fn);
  }
  else
  {
    myOLED.print(n);
    myOLED.print(" H=");
    myOLED.print(n,HEX);
    myOLED.print(" ");
    myOLED.println(fn);
  }
  if(n==20)
  {
    myOLED.begin(FONT_8x16); //FONT_6x8
    myOLED.println("Hello, world?");
    myOLED.println("1234567890123456");
    myOLED.println("abcdefghijklmnop");
    myOLED.println("ABCDEFGHIJKLMNOP");
    delay(2000);
    myOLED.BlinkON();
    delay(2000);
    myOLED.BlinkOFF();
    delay(1000);
    myOLED.setFont(FONT_6x8);
  }
  n++;
  fn+=1.23;
  delay(10);
  
  if(n==40)
  {
    myOLED.setFont(FONT_8x16);
    n=0;
    fn=0.0;
  }
}

