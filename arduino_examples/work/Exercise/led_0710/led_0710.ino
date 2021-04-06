#define key1 2
#define key2 6
#define led 3

#define LED_TIME                  100   

uint16_t button_count;
int16_t led_count;

void setup() {
  // put your setup code here, to run once:
     Serial.begin(9600);
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);
    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(key1)==LOW)
    {
        button_count += 1;
        if(button_count >= 3000)
        {
            button_count = 0;
            led_count += 5;
        }
        if(led_count > 100)
        {
            led_count = 100;
        }
    }
    else if(digitalRead(key2)==LOW)
    {
        button_count += 1;
        if(button_count >= 3000)
        {
            button_count = 0;
            led_count -= 5;
        }
        if(led_count < 0)
        {
            led_count = 0;
        }
    }
    else
    {
        button_count = 0;
    }



    if(led_count == 100)
    {
        digitalWrite(led,HIGH);
        delayMicroseconds(LED_TIME);
    }
    else if(led_count == 0)
    {
        digitalWrite(led,LOW);
    delayMicroseconds(LED_TIME);
    }
    else
    {
        digitalWrite(led,HIGH);
        delayMicroseconds(led_count);
        digitalWrite(led,LOW);
        delayMicroseconds(LED_TIME- led_count);
    }

}
