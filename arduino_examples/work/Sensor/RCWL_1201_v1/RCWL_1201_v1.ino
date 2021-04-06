#define trig A1
#define echo A2
#define led 13

#define key 2

uint16_t echoval ;
uint16_t music_count2;
void setup() 
{
    Serial.begin(9600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);
    digitalWrite(echo,LOW);
    pinMode(key,INPUT_PULLUP);
}

void loop() 
{

    
   
      //------------發送trigger訊號----------------
       digitalWrite(trig,HIGH);
       delayMicroseconds(10);
       digitalWrite(trig,LOW);
      //------------等待ECHO回傳-------------------
        uint16_t music_count = 1; 
        while(music_count++)
        {
            if(digitalRead(echo) == HIGH)
            {
                break;
            }
            delayMicroseconds(100); 
        }
     //-----------------------------------
        music_count2 = 1; 
        while(music_count2++)
        {
            if(digitalRead(echo) == LOW)
            {
                break;
            }
            delayMicroseconds(100); 
        }
          uint8_t RCWL_status = RCWL_sensor();
          echoval = music_count2;
        delay(100);
        Serial.print("RCWL_status:");
        Serial.println(RCWL_status);
        Serial.print("music_count2:");
        Serial.println(music_count2);
        

}
uint8_t RCWL_sensor()
{
       if (echoval == music_count2)
        {
            return 0 ;           
        }
        else 
        {
            return 1 ;
        }
}

