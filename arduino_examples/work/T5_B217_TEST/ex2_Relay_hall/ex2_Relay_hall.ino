#include <Servo.h>
#include <SoftwareSerial.h>
#include <OLED.h>

#define relayPin        3
#define CAR_DOOR_PIN    10
#define hallEffectPin   A3

uint16_t HEval;

uint8_t PC_Tx_Data[127];
uint8_t PC_Rx_Data[127];
uint8_t PC_Rx_Number;

uint8_t ZB_Tx_Data[127];
char ZB_Rx_Data[127];
uint8_t ZB_Rx_Number;



Servo myservo;
SoftwareSerial mySerial(A1, A2); 
OLED myOLED;
uint16_t HallEffectSensorGet(uint8_t pin);
float HallVal;

void CarDoorInit();
void CarDoorSet(uint8_t istatus);
void setup() {
  // put your setup code here, to run once:
    pinMode(relayPin , OUTPUT);
    Serial.begin(9600); 
    mySerial.begin(115200);
    CarDoorInit();
    myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
    myOLED.setPosi(0,0);    //指定行
    myOLED.println("**Meter Status**");
    myOLED.println("Switch:");
    myOLED.println("   Amp:        I");
    myOLED.println("Amount:        W");

    if(digitalRead( relayPin))
    {
        myOLED.setPosi(2,77); 
        myOLED.print("ON ");
    }
    else
    {
        myOLED.setPosi(2,77); 
        myOLED.print("OFF");
    }
    myOLED.setPosi(2,0);
    myOLED.print("               ");
     myOLED.setPosi(2,0);
}

void loop() {
    
    while(Serial.available()) 
    {
        ZB_Rx_Data[ZB_Rx_Number] = Serial.read();
myOLED.print(ZB_Rx_Data[ZB_Rx_Number]);
        ZB_Rx_Number += 1;
        uint8_t delayTime = 10;
        while(delayTime--)
        {
            delay(1);
            if(Serial.available())
            {
                break;  
            }
        }
    }
    
    if(ZB_Rx_Number > 0)
    {
        /*if(ZB_Rx_Data[2] == 'C')
        {
            if(ZB_Rx_Data[3] & 0xD0)
            {
                digitalWrite(relayPin , HIGH);
                //Serial.print("OPEN");
                myOLED.setPosi(2,77); 
                myOLED.print("ON ");
            }
            else
            {
                digitalWrite(relayPin , LOW);
                //Serial.print("CLOSE");
                myOLED.setPosi(2,77); 
                myOLED.print("OFF");
            }
        }
        else if(ZB_Rx_Data[2] == 'R')
        {
            ZB_Tx_Data[0] = ZB_Rx_Data[0];
            ZB_Tx_Data[1] = ZB_Rx_Data[1];
            ZB_Tx_Data[2] = ZB_Rx_Data[2];
            ZB_Tx_Data[3] = digitalRead(relayPin);
            ZB_Tx_Data[4] = (switchVal & 0xff00) >> 8 ;
            ZB_Tx_Data[5] = switchVal & 0x00ff;
            for(int zI=0 ; zI<6 ; zI++)
            {
                 mySerial.write(ZB_Tx_Data[zI]);
                 Serial.write(ZB_Tx_Data[zI]);
            }
        }
        else if(ZB_Rx_Data[0] == 'C')
            {
                if(ZB_Rx_Data[2] & 0x10)
                {
                    digitalWrite(relayPin , HIGH);
                    CarDoorSet(HIGH);
                    delay(2000);
                    CarDoorSet(LOW);
                }
            }*/
myOLED.setPosi(4,0);
myOLED.print(ZB_Rx_Number);
myOLED.setPosi(2,0);
        ZB_Rx_Number = 0;
        //delay(10);
    }

    /*Serial.println(HallEffectSensorGet(hallEffectPin));
    delay(1000);*/
}

uint16_t HallEffectSensorGet(uint8_t pin)
{
    uint16_t i ;
    uint16_t nowVal , newVal;
    for(i=0;i<500;i++)
    {
        newVal = analogRead(pin);
        if(newVal > nowVal)
        {
            nowVal = newVal;
        }
        delayMicroseconds(5); 
    }
    return nowVal;
}


/************Car Door***************/
void CarDoorInit()
{
    myservo.attach(CAR_DOOR_PIN);
    myservo.attach(CAR_DOOR_PIN, 500, 2400); // 修正脈衝寬度範圍
    myservo.write(15); // 一開始先置中90度  
}

void CarDoorSet(uint8_t istatus)
{
    if(istatus == HIGH)
    {
          for(int i = 15; i <= 90; i+=1)
          {
              myservo.write(i);
              delay(20);
          }  
    }
    else if(istatus == LOW)
    {
          for(int i = 90; i >= 15; i-=1)
          {
              myservo.write(i);
              delay(20);
          }  
    }
}
