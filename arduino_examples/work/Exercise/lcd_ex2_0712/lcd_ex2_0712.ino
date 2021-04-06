#include<OLED.h>
OLED myOLED ;

#define key1 2
#define key2 6

#define button1_short 1
#define button1_long  2
#define button2_short 3
#define button2_long  4

#define lcd  0
#define lcdA 1
#define lcdB 2
#define lcdC 3
#define lcdD 4

uint8_t buttonflag =1 ;
uint8_t pictureflag =0;

uint8_t picturestatus =0;
uint8_t picturestatus_xx =0;  // aa1 1   

uint8_t keyflag = 0 ;

uint8_t picturereturn ;
void setup() 
{
  Serial.begin(9600);
  myOLED.begin(FONT_8x16);
 /* myOLED.setPosi(0,0);
  myOLED.print("LCDex1");*/
  pinMode(key1,INPUT_PULLUP);
  pinMode(key2,INPUT_PULLUP);

}

void loop() 
{
    keyflag =button();
   if(keyflag == button1_short ) 
   {
        if(buttonflag < 4)
        {
          buttonflag +=1;
        }
        else
        {
          buttonflag =1 ;
        }      
   }
   else if (keyflag == button1_long )
   {
      pictureflag = 0 ;
   }
   else if (keyflag == button2_short)
   {
        if(pictureflag < 2)
        {
          pictureflag +=1 ;
        }  
        else
        {
          pictureflag =2;
        }  
        if(buttonflag == 1)
        {
          picturestatus = 1;
        }
        else if(buttonflag == 2)
        {
          picturestatus = 2;
        }
        else if(buttonflag == 3)
        {
          picturestatus = 3;
        }
        else if(buttonflag == 4)
        {
          picturestatus = 4;
        }
       buttonflag = 1 ;
   }
   else if (keyflag == button2_long)
   {
        if(pictureflag >= 1)
        {
          pictureflag -=1 ;
          if(picturereturn == 0xA)
          {
            picturestatus = 1;
          }
          else if (picturereturn == 0xB)
          {
            picturestatus = 2;
          }
        } 
        else 
        {
          pictureflag =0;
        }
       
        buttonflag = 1 ; 
   }
   Star_option(buttonflag);
   picture_2();
   
   Serial.print(buttonflag);
   Serial.print(pictureflag);
   Serial.print(picturereturn);
   Serial.println(picturestatus);
   
   
   
}
void picture_2()
{
    if (pictureflag == 0)
     {
        LCD_option(1);
        picturereturn = 0;
     }
    else if (pictureflag == 1  )
    {
        if(picturestatus == 1)
        {
          picturestatus_xx =0xA1;
          LCD_option(0xA);
        }
        else if (picturestatus == 2 )
        {
           picturestatus_xx = 0xB1;
           LCD_option(0xB);
        }
        else if (picturestatus == 3 )
        {
          picturestatus_xx = 0xC1;
          LCD_option(0xC);
        }
        else if (picturestatus == 4 )
        {
          picturestatus_xx = 0xD1;
          LCD_option(0xD);
        }
    } 
    else if (pictureflag == 2  &&  picturestatus_xx == 0xA1)
    {
      if(picturestatus == 1)
      {
        LCD_option(0xA1);
        
      }
      else if (picturestatus == 2)
      {
         LCD_option(0xA2);
         picturereturn = 0xA;
      }
      else if (picturestatus == 3)
      {
         LCD_option(0xA2);
         picturereturn = 0xA;
      }
      
    }
    else if (pictureflag == 2  &&  picturestatus_xx == 0xB1)
    {
      if(picturestatus == 1)
      {
        LCD_option(0xB1);
        picturereturn = 0xB;
      }
      else if (picturestatus == 2)
      {
         LCD_option(0xB2); 
         picturereturn = 0xB;      
      } 
       
    }

    /*else if ( picturestatus == 2  && pictureflag == 2 )
    {
      LCD_option(0xBb1);
    }*/
    
}
void LCD_option(uint16_t Lcdflag)
{
  if (Lcdflag == 1)
  {
    myOLED.setPosi(0,8);
    myOLED.print("A  ");
    myOLED.setPosi(2,8);
    myOLED.print("B  ");
    myOLED.setPosi(4,8);
    myOLED.print("C  ");
    myOLED.setPosi(6,8);
    myOLED.print("D  ");
  }
  else if (Lcdflag == 0)
  {
      myOLED.setPosi(0,8);
    myOLED.print("   ");
    myOLED.setPosi(2,8);
    myOLED.print("   ");
    myOLED.setPosi(4,8);
    myOLED.print("   ");
    myOLED.setPosi(6,8);
    myOLED.print("   ");
  }
  else if (Lcdflag == 0xB )
  {
    myOLED.setPosi(0,8);
    myOLED.print("B1  ");
    myOLED.setPosi(2,8);
    myOLED.print("B2  ");
    myOLED.setPosi(4,8);
    myOLED.print("B3  ");
    myOLED.setPosi(6,8);
    myOLED.print("B4  ");
  }
  else if(Lcdflag == 0xC )
  {
      myOLED.setPosi(0,8);
      myOLED.print("C1  ");
      myOLED.setPosi(2,8);
      myOLED.print("C2  ");
      myOLED.setPosi(4,8);
      myOLED.print("C3  ");
      myOLED.setPosi(6,8);
      myOLED.print("C4  ");
  }
  else if(Lcdflag == 0xD )
  {
      myOLED.setPosi(0,8);
      myOLED.print("D1  ");
      myOLED.setPosi(2,8);
      myOLED.print("D2  ");
      myOLED.setPosi(4,8);
      myOLED.print("D3  ");
      myOLED.setPosi(6,8);
      myOLED.print("D4  ");
  }
  else if(Lcdflag == 0xA )
  {
      myOLED.setPosi(0,8);
      myOLED.print("A1  ");
      myOLED.setPosi(2,8);
      myOLED.print("A2  ");
      myOLED.setPosi(4,8);
      myOLED.print("A3  ");
      myOLED.setPosi(6,8);
      myOLED.print("A4  ");
  }
  else if(Lcdflag == 0xA1 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("A11");
      myOLED.setPosi(2,8);
      myOLED.print("A12");
      myOLED.setPosi(4,8);
      myOLED.print("A13");
      myOLED.setPosi(6,8);
      myOLED.print("A14");
  }
  else if(Lcdflag == 0xA2 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("A21");
      myOLED.setPosi(2,8);
      myOLED.print("A22");
      myOLED.setPosi(4,8);
      myOLED.print("A23");
      myOLED.setPosi(6,8);
      myOLED.print("A24");
  }
  else if(Lcdflag == 0xA3 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("A31");
      myOLED.setPosi(2,8);
      myOLED.print("A32");
      myOLED.setPosi(4,8);
      myOLED.print("A33");
      myOLED.setPosi(6,8);
      myOLED.print("A34");
  }
  else if(Lcdflag == 0xB1 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("B11");
      myOLED.setPosi(2,8);
      myOLED.print("B12");
      myOLED.setPosi(4,8);
      myOLED.print("B13");
      myOLED.setPosi(6,8);
      myOLED.print("B14");
  }
  else if(Lcdflag == 0xB2 )
  {
      myOLED.setPosi(0,8);
      myOLED.print("B21");
      myOLED.setPosi(2,8);
      myOLED.print("B22");
      myOLED.setPosi(4,8);
      myOLED.print("B23");
      myOLED.setPosi(6,8);
      myOLED.print("B24");
  }
  
  
}
void Star_option(uint8_t Starflag)
{
     /*myOLED.setPosi(0,0);
     myOLED.print(" ");
     myOLED.setPosi(2,0);
     myOLED.print(" ");
     myOLED.setPosi(4,0);
     myOLED.print(" ");
     myOLED.setPosi(6,0);
     myOLED.print(" ");*/
   
    if(Starflag == 1)
    {
      myOLED.setPosi(2,0);
      myOLED.print(" "); 
      myOLED.setPosi(6,0);
      myOLED.print(" ");
      myOLED.setPosi(4,0);
      myOLED.print(" ");
      myOLED.setPosi(0,0);
      myOLED.print("*"); 
     
    }
    else if(Starflag == 2)
    {
      myOLED.setPosi(0,0);
      myOLED.print(" ");      
      myOLED.setPosi(4,0);
      myOLED.print(" ");
      myOLED.setPosi(2,0);  
      myOLED.print("*");
       
    }
    else if(Starflag == 3)
    {
        myOLED.setPosi(2,0);
        myOLED.print(" "); 
        myOLED.setPosi(6,0);
        myOLED.print(" "); 
        
        myOLED.setPosi(4,0);
        myOLED.print("*");
     
    }
    else if(Starflag == 4)
    {
        myOLED.setPosi(0,0);
        myOLED.print(" "); 
        myOLED.setPosi(4,0);
        myOLED.print(" "); 
        myOLED.setPosi(6,0);
        myOLED.print("*");
      
    }
}
int button ()
{
      uint8_t i ;
      if(digitalRead(key1) == LOW)
      {
         while(digitalRead(key1) == LOW)
         {
             i ++;
             delay(3);
         }
         if( i <= 50)
         {
           return button1_short ;
         }
         else
         {
           return button1_long ;
         }
         i=0;
      }
      else if(digitalRead(key2) == LOW)
      {
         while(digitalRead(key2) == LOW)
         {
             i ++;
             delay(3);
         }
         if( i <= 80)
         {
           return button2_short ;
         }
         else
         {
           return button2_long ;
         }
         i=0;
      }
      else
      {
        return 0;
      }
}

