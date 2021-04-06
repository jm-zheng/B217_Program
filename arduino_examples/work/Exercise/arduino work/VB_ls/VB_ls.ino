//Ex_PC_LS_LED
//-------Declare-OLED-------------------------------
#include <OLED.h>
OLED myOLED;
//-------Declare-Light Sensor ----------------------
#define LS_PIN  A0
//-------Declare-LED1W-MD1-------------------------------------------------
#define LED 3
void setup() {
 //=============Setup RS-232==============================
  Serial.begin(9600);     
 //========= Setup LS ==============
    pinMode(LS_PIN, INPUT);
 //-------Setup-LED1W-MD1---------------------------------------------
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW) ;
 // ====== Setup OLED ==============
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.clearScreen();
  myOLED.println("Ex_PC_LS_LED");
  myOLED.println("2016/12/10");
 }
void loop() {
  //========================================
   // Read LS Sensor Send Value
   int LS_Val = analogRead(LS_PIN);  
     myOLED.setPosi(4,0);
     myOLED.print("LS:");
     myOLED.print( LS_Val);
     if(LS_Val >100)
            Serial.print("L");
        else  if(LS_Val <10)
            Serial.print("L00");
         else 
            Serial.print("L0");
        
     Serial.println(LS_Val);
      delay(500);
 //========================================
 if (Serial.available()) {
    String uartRead = Serial.readString() ;
   if(uartRead[0]=='D')
   { 
        int duty=(uartRead[1]-0x30)*100+(uartRead[2]-0x30)*10+(uartRead[3]-0x30);
        analogWrite(LED, duty);        
  }
 }
}
