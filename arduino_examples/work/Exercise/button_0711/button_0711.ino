#include<OLED.h>
OLED myOLED ;
#define key1 2
#define key2 6
uint8_t i ;
void setup() 
{
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    Serial.begin(9600);
    myOLED.begin(FONT_8x16);
}

void loop() 
{
  uint8_t asd = button();
  Serial.println(asd);
  delay(1000);
  i=0;

}
int button()
{
  if(digitalRead(key1) == LOW)
  {
    while(digitalRead(key1) == LOW)
    {
      i++;
      delay(100);
    }
    if(i <= 10)
    {
      return 2;
    }
    else 
    {
      return 3;
    }
  }
  else
  {
      return 1 ;
  }
     
  

}
