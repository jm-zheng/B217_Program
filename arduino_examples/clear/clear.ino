#define key1 2
#define key2 6
#define led 3

int sec=0;
void setup() 
{ 
  Serial.begin(9600);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    pinMode(led , OUTPUT);
    digitalWrite(led,LOW);

}

void loop() 
{
    if (digitalRead(key1) == LOW)
    {
      
      sec =sec+500;
    }
    if (digitalRead(key2) == LOW)
    {
     
      sec =sec-500;
    }
    Serial.println(sec);
    digitalWrite(led,HIGH);
    delayMicroseconds(sec);   
    digitalWrite(led,LOW);
    delayMicroseconds(5000-sec);
}
