#define trig A1
#define echo A2
#define led 13

void setup() 
{
    Serial.begin(9600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);
    digitalWrite(echo,LOW);
}

void loop() 
{
  
   /*uint8_t trigval = digitalRead (trig);
   
  if (trigval == 1)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
   Serial.print("tr=");
   Serial.println(digitalRead (trig));
   Serial.print("ec=");
   Serial.println(digitalRead (echo));

   delay(800);*/
   digitalWrite(trig,HIGH);
   delayMicroseconds(5000);
   digitalWrite(trig,LOW);
   uint16_t music_count = 500; 
    while(music_count--)
    {
        if(digitalRead(echo) == HIGH)
        {
            break;
        }
        delayMicroseconds(100); 
    }

    uint16_t music_count2 = 1; 
    while(music_count2++)
    {
        if(digitalRead(echo) == LOW)
        {
            break;
        }
        delayMicroseconds(100); 
    }
    /*if(music_count == 0)
    {
        Serial.print("no fuck!!");  
    }
    else
    {
        Serial.print("fuck!!");  
    }*/
    Serial.print("music_count:");
    Serial.println(music_count);
    Serial.print("music_count2:");
    Serial.println(music_count2);
    delay(1000);

}
