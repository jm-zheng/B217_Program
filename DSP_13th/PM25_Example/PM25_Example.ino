//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <OLED.h>

OLED myOLED;
//------------------------------------------------------------------------------
#define TX_PIN  1  ///< pin for TXD
#define RX_PIN 0 ///< pin for RXD

SoftwareSerial mySerial(RX_PIN,TX_PIN);

String val= ""; //holds the string of the value
uint16_t co2 =0; // holds the actual value
uint8_t buffer[25];
uint8_t ind =0; 
//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  Serial.println("PM2.5 Test");
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("PM2.5 Test");  
  mySerial.begin(9600);
  pinMode(13, OUTPUT);
}

//------------------------------------------------------------------------------
void loop()
{
  uint8_t ch,i,sum; 
  uint16_t val; 

  while(1)
  {
    if(mySerial.available())
    {
      ch=mySerial.read();
      if(ind==0)
      {
        if(ch==0xff)
        {
          buffer[ind++] = ch;
        }
      }
      else
      {
        buffer[ind++] = ch;
        if(ind>=9)
        {
          sum=0;
          for(i=1;i<9;i++)
          {
            sum+=buffer[i];
          }          
          ind=0;      
          if(sum==0)
          {
            break;
          }
        }
      }
    }
  }
  digitalWrite(13, HIGH);
  val=(buffer[3]*20)+(buffer[4]/5);
  myOLED.print(val);
  myOLED.println(" ug/m3");
  Serial.print(val);
  Serial.println(" ug/m3");
  digitalWrite(13, LOW);
}

