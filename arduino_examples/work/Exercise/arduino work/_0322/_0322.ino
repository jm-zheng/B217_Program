#include<OLED.h>
OLED myOLED;

#define key1 2
#define key2 6

#define PICTUER_1         0
#define PICTUER_2         1
#define PICTUER_3         2
#define PICTUER_4         3

#define BUTTON1_PUSH      1
#define BUTTON2_PUSH      2

uint8_t sWitch_Flag = 0;
uint8_t pIcture_Flag = 0;

void setup() {
  // put your setup code here, to run once:
    myOLED.begin(FONT_8x16);

    pinMode(key1,INPUT_PULLUP);
    pinMode(key2,INPUT_PULLUP);
    pIcture_Flag = 0;
    sWitch_Flag = 1;
    
    PictureFunction(pIcture_Flag);
    SwitchFunction(sWitch_Flag);
}

void loop() 
{
    uint8_t bt = ButtonStatus();
    if(bt == BUTTON2_PUSH)
    {
        sWitch_Flag += 1;
        if(sWitch_Flag > 3)
        {
            sWitch_Flag = 1;
        }
        SwitchFunction(sWitch_Flag);
        delay(200);
    }
    else if(bt == BUTTON1_PUSH)
    {
        if(pIcture_Flag == 0)
        {
             PictureFunction(sWitch_Flag);
             myOLED.setPosi(4,80);
             myOLED.print(sWitch_Flag);
             pIcture_Flag = sWitch_Flag;
            sWitch_Flag = 1;
            SwitchFunction(sWitch_Flag);
        }
        if(pIcture_Flag == 1)
        {
                       
        }
        delay(200);
    }
}

void PictureFunction(uint8_t ptNumber)
{
    if(ptNumber == 0)
    {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 1.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 1.2");
    }
    else if(ptNumber == 1)
    {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 2.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 2.2");
    }
    else if(ptNumber == 2)
    {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 3.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 3.2");
    }
    else if(ptNumber == 3)
    {
        myOLED.setPosi(0,0);
        myOLED.print("*** B217 ***");
        myOLED.setPosi(2,0);
        myOLED.print(" 4.1");
        myOLED.setPosi(4,0);
        myOLED.print(" 4.2");
    }
}

void SwitchFunction(uint8_t sw)
{
    myOLED.setPosi(2,0);
    myOLED.print(" ");
    myOLED.setPosi(4,0);
    myOLED.print(" ");
    myOLED.setPosi(6,0);
    myOLED.print(" ");
    if(sw == 1)
    {
        myOLED.setPosi(2,0);
        myOLED.print("*");
    }
    else if(sw == 2)
    {
        myOLED.setPosi(4,0);
        myOLED.print("*");
    }
    else if(sw == 3)
    {
        myOLED.setPosi(6,0);
        myOLED.print("*");
    }
}

uint8_t ButtonStatus()
{
    if(digitalRead(key1) == LOW)
    {
        return BUTTON1_PUSH;  
    }
    else if(digitalRead(key2) == LOW)
    {
        return BUTTON2_PUSH;  
    } 
    return 0; 
}
