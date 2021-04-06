//-----------------雲台--------------------
#include <Servo.h>
Servo myservo1;
Servo myservo2;
int value;
//-----------------雲台--------------------
//-----------------OLED--------------------
#include <OLED.h>
OLED myOLED;
//-----------------OLED--------------------
int count;
void setup()
{
    myservo1.attach(10);
    //myservo1.write(90); // 一開始先置中90度
    myservo2.attach(11);
    myOLED.begin(FONT_8x16);
}

void loop()
{
      value =50 ;
       myservo1.write(value);
       myservo2.write(value);
  
  

  /*value = 30;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 90;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(2000);*/

   /* for(int i=10;i<=170;i+=10)
    {
        myservo1.write(i);
        myOLED.setPosi(4,0);
        myOLED.print("Motor2 = ");
        myOLED.println(i);
        delay(400);
    }
    delay(500);
    for(int i=10;i<=170;i+=10)
    {
        myservo1.write(180-i);
        myOLED.setPosi(4,0);
        myOLED.print("Motor2 = ");
        myOLED.println(180-i);
        delay(400);
    }
   delay(500);
  /*value =180 ; 
  myservo1.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  delay(500);*/
  


 




}
