// 引用 Servo Library
#include <Servo.h>// 建立一個 Servo 物件
#include <OLED.h>

OLED myOLED;

const int statusPin = A2;
const int outputPin = A1;
const int ledPin =  13;

void setup() 
{
  myOLED.begin(FONT_8x16); //FONT_6x8
  pinMode(ledPin, OUTPUT);      
  pinMode(statusPin, INPUT);     
  pinMode(outputPin, INPUT);     
}

int state;
int output;

void loop() 
{
  state = digitalRead(statusPin);
  output = digitalRead(outputPin);
  myOLED.print("PIR = ");
  if(state==1)
    myOLED.println("Detecting");  
  else   
    myOLED.println("Warm-up");  
  myOLED.print("OUT = ");
  if(output==1)
  {
    myOLED.println("ON");  
    digitalWrite(ledPin, HIGH);  
  }
  else  
  {
    myOLED.println("OFF");  
    digitalWrite(ledPin, LOW); 
  }
  delay(10);  
}

