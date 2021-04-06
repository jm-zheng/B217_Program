#include<OLED.h>
OLED myOLED ;

#define key1 2
#define key2 6

uint8_t random_flag;
int8_t arrow_flag;
uint8_t button_flag;
uint8_t point ;

void setup() 
{
  myOLED.begin(FONT_8x16);
  myOLED.setPosi(0,0);
  myOLED.print("number");
  pinMode(key1,INPUT_PULLUP);
  pinMode(key2,INPUT_PULLUP);
}

void loop() 
{
  random_flag = random(4);
  star(random_flag);
   
  arrow_status();
  arrow(arrow_flag);
  delay(100);
    
}

void star(uint8_t a)
{
  myOLED.setPosi(2,0);
  myOLED.print(" ");
  myOLED.setPosi(2,40);
  myOLED.print(" ");
  myOLED.setPosi(2,80);
  myOLED.print(" ");
  myOLED.setPosi(2,120);
  myOLED.print(" ");
 
  switch(a)
  {
    case 0 :
      myOLED.setPosi(2,0);
      myOLED.print("*");
      delay(75);
      break ;
      case 1 :
      myOLED.setPosi(2,40);
      myOLED.print("*");
      delay(75);
      break ;
      case 2 :
      myOLED.setPosi(2,80);
      myOLED.print("*");
      delay(75);
      break ;
      case 3 :
      myOLED.setPosi(2,120);
      myOLED.print("*");
      delay(75);
      break ;
      
  }
}
void arrow(uint8_t b)
{
  
  myOLED.setPosi(5,0);
  myOLED.print(" ");
  myOLED.setPosi(5,40);
  myOLED.print(" ");
  myOLED.setPosi(5,80);
  myOLED.print(" ");
  myOLED.setPosi(5,120);
  myOLED.print(" ");
  
  switch(b)
  {
    case 0 :
    myOLED.setPosi(5,0);
    myOLED.print("^");
    delay(75);
    break ;
    case 1 :
    myOLED.setPosi(5,40);
    myOLED.print("^");
    delay(75);
    break ;
    case 2 :
    myOLED.setPosi(5,80);
    myOLED.print("^");
    delay(75);
    break ;
    case 3 :
    myOLED.setPosi(5,120);
    myOLED.print("^");
    delay(75);
    break ;
  }
    
}
int button_status ()
{
  if (digitalRead(key1) == LOW && digitalRead(key2) == HIGH)
  {
    return 1 ;
  }
  else if (digitalRead(key1) == HIGH && digitalRead(key2) == LOW)
  {
    return 2 ;
  }
   else if (digitalRead(key1) == LOW && digitalRead(key2) == LOW)
  {
    return 3 ;
  }
  else 
  {
    return 0;
  }
}

void arrow_status ()
{
  button_flag =  button_status ();
  if(arrow_flag < 4 && arrow_flag >= 0)
  {
      if(button_flag == 1)
      {
        arrow_flag -= 1;
      }
      else if (button_flag == 2)
      {
        arrow_flag += 1;
      }
      else if (button_flag == 3 && random_flag == arrow_flag)
      {
        point+=1;
        myOLED.setPosi(0,80);
        myOLED.print(point);
        delay(50);
      }
  }
  else if (arrow_flag < 0)
  {
    arrow_flag = 3;
  }
  else if (arrow_flag == 4)
  {
    arrow_flag = 0;
  }
  
}




