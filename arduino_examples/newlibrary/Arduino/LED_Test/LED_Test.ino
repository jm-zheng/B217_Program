//------------------------------------------------------------------------------
void setup() 
{
  pinMode(13, OUTPUT);
}

//------------------------------------------------------------------------------
void loop() 
{
  digitalWrite(13, HIGH);   // turn the LED on
  delay(500); 
  digitalWrite(13, LOW);    // turn the LED off
  delay(500); 
}

