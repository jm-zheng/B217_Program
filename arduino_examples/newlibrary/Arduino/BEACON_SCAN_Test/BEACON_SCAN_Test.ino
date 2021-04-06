//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define TX_PIN A2 ///< pin for TXD
#define RX_PIN A1 ///< pin for RXD

SoftwareSerial mySerial(RX_PIN,TX_PIN);

char buffer[250];
uint8_t ind=0;
//------------------------------------------------------------------------------
void setup() 
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  mySerial.begin(9600);
  pinMode(13, OUTPUT);
}

//------------------------------------------------------------------------------
void loop()
{
  uint8_t ch; 
  // UUID , Major , Minor , Power , RSSI [0x0D][0x0A] 
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 
  // 36 39 39 45 42 43 38 30 45 31 46 33 31 31 45 33 39 41 30 46 30 43 46 33 45 45 33 42 43 30 31 32 2C 31 2C 31 34 34 32 33 2C 31 38 35 2C 38 31 0D 0A 
  while(1)
  {
    if(mySerial.available())
    {
      ch=mySerial.read();
      buffer[ind++] = ch;
      if(ch==0x0A)
      {
        if(ind>40 && ind<54)
        {
          buffer[ind++]=0x00; 
          break;
        }
        else
        {
          ind=0;
        }
      }
    }
  }
  String stringOne;
  stringOne=String(buffer);
  int p1 = stringOne.indexOf(',');
  int p2 = stringOne.indexOf(',',p1+1);
  int p3 = stringOne.indexOf(',',p2+1);
  int p4 = stringOne.indexOf(',',p3+1);
  int p5 = stringOne.indexOf('\n',p4+1);
  if(p1==32 && p2>p1 && p3>p2 && p4>p3 && p5>p4)
  { 
    digitalWrite(13, HIGH);
    myOLED.println("iBeacon Scan");  
    int major=stringOne.substring(p1+1,p2).toInt();
    int minor=stringOne.substring(p2+1,p3).toInt();
    int rssi=stringOne.substring(p4+1,p5).toInt();
    myOLED.print("Major=");
    myOLED.println(major);
    myOLED.print("Minor=");
    myOLED.println(minor);
    myOLED.print("RSSI=");
    myOLED.println(rssi);
    digitalWrite(13, LOW);
  }
  ind=0;
}

