#define LED_PIN 3
#define KEY1 2
int KEY2=6;
uint8_t a=0;
void setup() 
{
  // put your setup code here, to run once:
pinMode(LED_PIN , OUTPUT);
pinMode(KEY1,OUTPUT);
pinMode(KEY2,INPUT_PULLUP);
digitalWrite(KEY1,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  int b=digitalRead(KEY2);
      if(b==0)
      {
    
      a=a+1;
      delay(300);
      }
      if(a>1)
      {
        a=0;
      
      }
      
      if(a==0)
      {
         digitalWrite(LED_PIN,LOW);
   
    
      }
      else if (a==1)
      {
        digitalWrite(LED_PIN,HIGH);
       
      }
}
