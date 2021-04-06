#include <Servo.h>
#include <SoftwareSerial.h>
#include <OLED.h>
//---------------------------
#define TX_PIN 12 ///< pin for TXD
#define RX_PIN 11 ///< pin for RXD
SoftwareSerial myWiFi(RX_PIN,TX_PIN); 
//-----------------------
#define relayPin        5
#define CAR_DOOR_PIN    10
#define hallEffectPin   A7

uint16_t HEval;

uint8_t PC_Tx_Data[127];
uint8_t PC_Rx_Data[127];
uint8_t PC_Rx_Number;

uint8_t ZB_Tx_Data[127];
uint8_t ZB_Rx_Data[127];
uint8_t ZB_Rx_Number;



Servo myservo;
SoftwareSerial mySerial(A1, A2); 
OLED myOLED;
uint16_t HallEffectSensorGet(uint8_t pin);
float HallVal;

void CarDoorInit();
void CarDoorSet(uint8_t istatus);
void setup() 
    { 
      //-------Setup-UART myWiFi---------------------------------------------
    myWiFi.begin(9600); 
    //put your setup code here, to run once:
    pinMode(relayPin , OUTPUT);
    //Serial.begin(115200); 
    //mySerial.begin(9600);
    Zigbee_setup(12,0xB217,0x2002);   
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
}

void loop() {
    uint16_t switchVal;
    HallVal = HallEffectSensorGet(hallEffectPin);
    //運算公式做在這 2172
    /*if(HallVal <= 508)
    {
        HallVal = 0;
    }
    else
    {
        HallVal = ((HallVal*0.26506)-133.06024) + 0.5;
        switchVal = HallVal;
        HallVal = switchVal;
    }*/
    //運算公式做在這 2172                 
    if(HallVal <= 517)
    {
        HallVal = 0;
    }
    else
    {
        HallVal = ((HallVal*0.23037)-109.88428) + 0.5;
        switchVal = HallVal;
        HallVal = switchVal;
    }
    myOLED.setPosi(4,73); 
    myOLED.print(HallVal/100); //myOLED.print(HallVal/ 100);
    
    myOLED.setPosi(6,77); 
    myOLED.print(1.10*HallVal);
    /*if(HallVal < 999)
    {
        myOLED.print("   ");
    }*/
    while(myWiFi.available()) 
    {
        ZB_Rx_Data[ZB_Rx_Number] = myWiFi.read();
        ZB_Rx_Number += 1;
//        Serial.print(ZB_Rx_Number);
        uint8_t delayTime = 10;
        while(delayTime--)
        {
            delay(1);
            if(myWiFi.available())
            {
                break;  
            }
        }
    }
    
    if(ZB_Rx_Number > 0)
    {
        if(ZB_Rx_Data[2] == 'C')
        {
            if(ZB_Rx_Data[3] == 0x31)
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
                 myWiFi.write(ZB_Tx_Data[zI]);
                // Serial.write(ZB_Tx_Data[zI]);
            }
        }
        ZB_Rx_Number = 0;
        delay(10);
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

void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  mySerial.write(0xAA);  
  mySerial.write(0xC7);  
  mySerial.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  mySerial.write(0xAA);  
  mySerial.write(0xC7);  
  mySerial.write(0x5A);  
  mySerial.write(channel);  
  mySerial.write(panid>>8);  
  mySerial.write(panid&0xff);  
  mySerial.write(addr>>8);  
  mySerial.write(addr&0xff);  
  mySerial.write(0xBB); 
}

