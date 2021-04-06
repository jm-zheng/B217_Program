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
    myservo2.attach(11);
    myOLED.begin(FONT_8x16);
}

void loop()
{

  value = 30;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 90;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(2000);

if(count < 10)
{
  value = 20;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 90;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(500);
  
  value = 30;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 0;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(500);

  value = 20;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 90;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(500);

  value = 30;
  myservo1.write(value);
  myOLED.setPosi(2,0);
  myOLED.print("Motor1 = ");
  myOLED.println(value);
  value = 180;
  myservo2.write(value);
  myOLED.setPosi(4,0);
  myOLED.print("Motor2 = ");
  myOLED.println(value);
  delay(500);

  count = 0;
}
}
