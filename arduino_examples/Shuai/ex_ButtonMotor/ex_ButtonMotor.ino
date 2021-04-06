#include <Servo.h>
#include <OLED.h>

OLED myOLED;
Servo myservo1;

#define BUTTON1_PIN                 2
#define BUTTON2_PIN                 6

#define BUTTON1_LONG_PUSH           1
#define BUTTON1_SHORT_PUSH          2
#define BUTTON2_LONG_PUSH           3
#define BUTTON2_SHORT_PUSH          4

#define SG90_TIME         200
#define SG90_ADD          10
#define SG90_SUB          25
#define SG90_STOP         0
void setup() {
  // put your setup code here, to run once:
    pinMode(10 , OUTPUT);
    myOLED.begin(FONT_8x16);
    shuaiButtonInit();
    myOLED.print("button status:");
}
uint8_t motorStatus = 0;
void loop() {
  // put your main code here, to run repeatedly:
    uint8_t buttonStatus = shuaiButtonStatus();
    
    if(buttonStatus > 0)
    {
        myOLED.setPosi(2,0);
        myOLED.print("Motor:");
        if(buttonStatus == BUTTON1_SHORT_PUSH)
        {
            myOLED.print("ADD");
            motorStatus = SG90_ADD;
        }
        if(buttonStatus == BUTTON2_SHORT_PUSH)
        {
            myOLED.print("SUB");
            motorStatus = SG90_SUB;
        }
        if(buttonStatus == BUTTON1_LONG_PUSH || buttonStatus == BUTTON2_LONG_PUSH)
        {
            myOLED.print("STOP");
            motorStatus = SG90_STOP;
            delay(400);
        }
    }
    
    sg90PAPAPA(motorStatus);
   

}

void shuaiButtonInit()
{
    pinMode(BUTTON1_PIN , INPUT_PULLUP);
    pinMode(BUTTON2_PIN , INPUT_PULLUP);
}

uint8_t shuaiButtonStatus()
{
    uint16_t btFlag = 1000;
    if(digitalRead(BUTTON1_PIN) == LOW)
    {
        while(digitalRead(BUTTON1_PIN) == LOW)
        {
              btFlag --;
              delay(1);
              if(btFlag == 0)
              {
                  return   BUTTON1_LONG_PUSH;
              }
        }  
        return BUTTON1_SHORT_PUSH;
    }

    if(digitalRead(BUTTON2_PIN) == LOW)
    {
        while(digitalRead(BUTTON2_PIN) == LOW)
        {
              btFlag --;
              delay(1);
              if(btFlag == 0)
              {
                  return   BUTTON2_LONG_PUSH;
              }
        }  
        return BUTTON2_SHORT_PUSH;
    }

    return 0;
}

void sg90PAPAPA(uint8_t setTime)
{
    if(setTime != SG90_STOP)
    {
        digitalWrite(10 , HIGH);
        delayMicroseconds((100 * setTime));
    
        digitalWrite(10 , LOW);
        delayMicroseconds((100 * (SG90_TIME - setTime)));
    }
    else
    {
        digitalWrite(10 , LOW);
    }
   
}


