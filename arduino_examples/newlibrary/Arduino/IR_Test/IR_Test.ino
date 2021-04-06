//------------------------------------------------------------------------------
#include <OLED.h>
OLED myOLED;

#include <IRremote.h>
#define RECV_PIN  0
IRrecv irrecv(RECV_PIN);

decode_results results;

//------------------------------------------------------------------------------
void setup()
{
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.println("IR REMOTE CODE");  
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

//------------------------------------------------------------------------------
void loop() 
{
  if(irrecv.decode(&results)) 
  {
    myOLED.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  //delay(100);
}
