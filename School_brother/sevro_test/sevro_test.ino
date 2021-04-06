//Ex011_MOTOR 
//-------Declare-OLED-----------------------------------------------
#include <OLED.h>
OLED myOLED;
//-------Declare Servo Motor --------------------------------------
//引用 Servo Library
#include <Servo.h>// 建立一個 Servo 物件
Servo myservo1;
Servo myservo2;
// 旋轉角度
int value = 0;

#define key1 2 
#define key2 6
//------------------------------------------------------------------------
void setup() 
{
  myservo1.attach(11); // Servo 接在 pin 9
  myservo2.attach(10); // Servo 接在 pin 9
  myOLED.begin(FONT_8x16); //FONT_6x8
  pinMode(13, OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  
}
//------------------------------------------------------------------------
void loop() 
{
 
  if(digitalRead(key1)== LOW)
  {
    delay(500);    // delay in between reads for stability 
    myservo1.write(100);
    myservo2.write(100);
    delay(500);
  }
  else
  {
     myservo1.write(value);
     myservo2.write(value);
  }
  // 叫 Servo 旋轉角度:
  // myservo.write(0) 是叫 Servo 旋轉到 0 度的位置
  // myservo.write(180) 是叫 Servo 旋轉到 180 度的位置
  myservo1.write(value);
  myservo2.write(value);
  myOLED.print("Motor = ");
  myOLED.println(value);  
 
}
//------------------------------------------------------------------------
