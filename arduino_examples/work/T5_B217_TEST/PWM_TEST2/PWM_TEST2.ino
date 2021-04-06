#include<SoftwareSerial.h>
SoftwareSerial mySerial (A1,A2);
#include <OLED.h>
OLED myOLED;

#define  pwm   10
#define  key1   2
#define  key2   6
#define  relay 12
#define  LS    A3
void setup() 
{    
    Serial.begin(115200);
    pinMode(relay,OUTPUT);
    digitalWrite(relay,HIGH);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    pinMode(pwm,OUTPUT);
    myOLED.begin(FONT_8x16);
    pinMode(LS,INPUT);
    /*digitalWrite(pwm,HIGH);
    delay(2000);
    digitalWrite(pwm,LOW);
    delay(2000);*/
    digitalWrite(pwm,HIGH);
    delay(4000);
}

int32_t Time = 20000;
int32_t duty = 0;
int SetLSMax=400;
int SetLSMin=50;

void loop() 
{   
    uint8_t  LSVal=analogRead(LS);
     Serial.print(LSVal);
    //int duty=map(LSVal, SetLSMax, SetLSMin, 0, 3500);
     
    {
        digitalWrite(pwm,LOW);
        delayMicroseconds(duty);
        
         digitalWrite(pwm,HIGH);
        delayMicroseconds(Time - duty);
    }

}
