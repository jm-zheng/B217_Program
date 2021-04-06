#define pir A2 

#define led  3

#define key 2
void setup() {
  pinMode(pir,INPUT_PULLUP);
 pinMode(key,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() 
{
    if(digitalRead(pir) == HIGH)
    {
       digitalWrite(led,HIGH);
    
    }
    if(digitalRead(key) == LOW)
    {
       digitalWrite(led,HIGH);
    }
    
   /* else if (digitalRead(pir) == HIGH)
    {
        digitalWrite(led,LOW);
    }*/
    delay(100);
}
