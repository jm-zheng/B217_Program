#include<SoftwareSerial.h>
SoftwareSerial ZigBee(A1,A2);

#include<OLED.h>
OLED myOLED;

#include<Servo.h>
Servo myservo1;
#define ls A3 
#define T5pwm 10 
#define relay 12

uint8_t zigbee_rx_number=0 ;


int32_t Time = 20000;
int32_t duty = 3500;
int SetLSMax=400;
int SetLSMin=50;

void setup() 
{
    Serial.begin(9600);
    
    ZigBee.begin(9600);
    Zigbee_setup(27,0xB217,0x2002);

     myOLED.begin(FONT_8x16);
     myOLED.print("B217_power_LS");

     myservo1.attach(5);
     myservo1.write(80);

     pinMode(relay,OUTPUT);
     digitalWrite(relay,LOW);

     pinMode(T5pwm,OUTPUT);
      digitalWrite(T5pwm,HIGH);
   

     pinMode(ls,INPUT_PULLUP);
     



}

void loop() 
{
    zigbee_read();  
    
   
    if(zigbee_rx_number == 1)
    {
        digitalWrite(relay,HIGH);
        Serial.print(zigbee_rx_number);
    }
    if(zigbee_rx_number == 2)
    {
        digitalWrite(relay,LOW);
    }
    if(zigbee_rx_number == 4)
    {
      //收
       myservo1.write(150);
       delay(2400);
       myservo1.write(80);
    }
    if(zigbee_rx_number == 5)
    {
      //開
        myservo1.write(20);
        delay(2400);
        myservo1.write(80);
    }

    if(zigbee_rx_number == 3)
    {
       
       if( digitalRead(relay) == HIGH)
        {
          uint8_t lsval = analogRead(ls);
         // Serial.print(lsval);
         //uint8_t lsval = analogRead(ls);
         //ZigBee.print(lsval);
          //ZigBee.print("L");
        
          int duty=map(lsval, SetLSMax, SetLSMin, 0, 3500);  
          digitalWrite(T5pwm,LOW);
          //ZigBee.print("L");
          delayMicroseconds(duty);
          
          digitalWrite(T5pwm,HIGH);
         // ZigBee.print(lsval);
          delayMicroseconds(Time - duty);
     
       }  
        else
        {
           digitalWrite(relay,HIGH);
        }
  
    }

}
void Zigbee_setup(uint8_t channel,uint16_t panid,uint16_t addr)
{
  int i,len;
  
  // get Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0xBB);  
  delay(30);

  // set Channel/PAN ID/Address
  ZigBee.write(0xAA);  
  ZigBee.write(0xC7);  
  ZigBee.write(0x5A);  
  ZigBee.write(channel);  
  ZigBee.write(panid>>8);  
  ZigBee.write(panid&0xff);  
  ZigBee.write(addr>>8);  
  ZigBee.write(addr&0xff);  
  ZigBee.write(0xBB); 
}
void zigbee_read()
{
       uint8_t ch;
      if(ZigBee.available())
      {
          ch=ZigBee.read();
          if(ch==0x31)
          {
            zigbee_rx_number=1;
          }
          else if (ch==0x32)
          {
            zigbee_rx_number=2;
          }
          else if(ch==0x33)
          {
            zigbee_rx_number=3;
          }
          else if(ch==0x34)
          {
            zigbee_rx_number=4;
          }
          else if (ch==0x35)
          {
            zigbee_rx_number=5;
          }
      }
      else if(zigbee_rx_number != 3)
        {
          zigbee_rx_number = 0;
        } 
       
}
