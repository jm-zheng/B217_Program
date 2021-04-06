//------------------------------------------------------------------------------
// 引用 Servo Library
#include <Servo.h>// 建立一個 Servo 物件
#include <OLED.h>

OLED myOLED;
Servo myservo1;
Servo myservo2;
// 旋轉角度
int value = 0;

//------------------------------------------------------------------------------
void setup() 
{
  myservo1.attach(10); // Servo 接在 pin 10
  myservo2.attach(11); // Servo 接在 pin 11
  myOLED.begin(FONT_8x16); //FONT_6x8
}

//------------------------------------------------------------------------------
void loop() 
{
  // 叫 Servo 旋轉角度:
  // myservo.write(0) 是叫 Servo 旋轉到 0 度的位置
  // myservo.write(90) 是叫 Servo 旋轉到 90 度的位置
  // myservo.write(180) 是叫 Servo 旋轉到 180 度的位置
  myOLED.clearScreen();
  value = 0;
  myservo1.write(value);
  myOLED.print("Motor-1 = ");
  myOLED.println(value);  
  delay(500);
  myservo2.write(value);
  myOLED.print("Motor-2 = ");
  myOLED.println(value);  
  delay(1000);
  value = 90;
  myservo1.write(value);
  myOLED.print("Motor-1 = ");
  myOLED.println(value);  
  delay(500);
  myservo2.write(value);
  myOLED.print("Motor-2 = ");
  myOLED.println(value);  
  delay(1000);
  myOLED.clearScreen();
  value = 180;
  myservo1.write(value);
  myOLED.print("Motor-1 = ");
  myOLED.println(value);  
  delay(500);
  myservo2.write(value);
  myOLED.print("Motor-2 = ");
  myOLED.println(value);  
  delay(1000);
  value = 90;
  myservo1.write(value);
  myOLED.print("Motor-1 = ");
  myOLED.println(value);  
  delay(500);
  myservo2.write(value);
  myOLED.print("Motor-2 = ");
  myOLED.println(value);  
  delay(1000);
  value = 0;
  myservo1.write(value);
  myOLED.print("Motor-1 = ");
  myOLED.println(value);  
  value = 90;
  myservo2.write(value);
  myOLED.print("Motor-2 = ");
  myOLED.println(value);  
  delay(3000);  
}

