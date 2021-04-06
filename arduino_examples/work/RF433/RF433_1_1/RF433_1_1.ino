//TitleEX026_RF_TXRX_Test
// FirmwareRF_TXRX_Test.ino
// Devices NanoKIT +  RF + KEY
// FunctionKEY_LED
// UpDate20171212
//-------Declare-OLED----------------------------------------------------
#include <OLED.h>
OLED myOLED;
//-------Declare-KEY--------------------------------------
#define  KEY1  2
#define  KEY2  6
uint8_t D2_Tag;
uint8_t D6_Tag;

//------------------------------------------------------------------------------
#define RF_RX           A1
#define RF_TX           A2

#define RF_ID           0x8888
#define RF_CH1          1
#define RF_CH2          2
#define RF_CH3          3
#define RF_CH4          4
#define RF_TX_COUNT     3
#define RF_ON           1
#define RF_OFF          0

void RF_TxData(uint16_t id, uint8_t ch,uint8_t on, uint8_t sendcount);
uint8_t RF_RxData(uint16_t *id, uint8_t *ch,uint8_t *on);
uint8_t RF_Data[4];
uint16_t RF_Id;
uint8_t RF_Ch;
uint8_t RF_On;
//--------------
uint8_t serial_flag;

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  myOLED.begin(FONT_8x16); //FONT_6x8 , FONT_8x16
  myOLED.setPosi(0,0);
  myOLED.print("RF TX RX TEST");
  myOLED.setPosi(2,0);
  myOLED.print("ID:0x");
  myOLED.print(RF_ID,HEX);    
  myOLED.print(" CH:");
  //myOLED.print(RF_CH);    

  pinMode(KEY1, INPUT_PULLUP);   
  pinMode(KEY2, INPUT_PULLUP);     

  pinMode(RF_RX, INPUT_PULLUP);
  pinMode(RF_TX, OUTPUT);  
  digitalWrite(RF_TX, LOW); 
}

//------------------------------------------------------------------------------
void loop() 
{
      serial_read();
    if (serial_flag == 1)
    {
      myOLED.setPosi(4,0);
      myOLED.print("1");
      RF_TxData(RF_ID,RF_CH1,RF_ON,RF_TX_COUNT);
    }



  
  /*if(digitalRead(KEY1)==LOW)
  {
    if(D2_Tag==0)
    {
      D2_Tag=1;
      myOLED.setPosi(4,0);
      myOLED.print("  RF TX [ON ]");
      RF_TxData(RF_ID,RF_CH,RF_ON,RF_TX_COUNT);
    }
  }
  else
  {
    D2_Tag=0;
  }
  
  if(digitalRead(KEY2)==LOW)
  {
    if(D6_Tag==0)
    {
      D6_Tag=1;
      myOLED.setPosi(4,0);
      myOLED.print("  RF TX [OFF]");
      RF_TxData(RF_ID,RF_CH,RF_OFF,RF_TX_COUNT);
    }
  }  
  else
  {
    D6_Tag=0;
  }
*/
  if(RF_RxData()>0)
  {
    myOLED.setPosi(6,0);
    myOLED.print("ID:0x");
    myOLED.print(RF_Id,HEX);    
    
    myOLED.print(" CH:");
    myOLED.print(RF_Ch);    
    
    if(RF_On==RF_ON)  
    {
      myOLED.setPosi(4,0);
      myOLED.print("  RF RX [ON ]");
    }
    else
    {
      myOLED.setPosi(4,0);
      myOLED.print("  RF RX [OFF]");
    }
    delay(1000); 
  }
}

//------------------------------------------------------------------------------
uint8_t RF_RxData(void)
{
  uint8_t i;
  uint8_t count;
  uint8_t flag;
  uint8_t rfstatus, error;
  uint8_t rno, rbyte, rbit;

  count = 0;
  flag = 0;
  for (i = 0; i < 100; i++)
  {
    if (digitalRead(RF_RX)== 0)
    {
      count++;
    }
    else
    {
      count=0;
    }
    delayMicroseconds(25); // 30us
    if (count > 12)
    {
      flag=1;
      break;
    }
  }
  if(flag==0)
  {
    return 0;
  }
  
  rno = 0;
  count = 0;
  rfstatus = 0;
  error = 0;
  while (1)
  {
    if (digitalRead(RF_RX)== 0)
    {
      if (rfstatus == 1)
      {
        rfstatus = 0;
        rbyte = (rno >> 3);
        rbit = (rno % 8);
        if (count < 35 && count > 8)
        // 16
        {
          RF_Data[rbyte] &= ~(0x80 >> rbit);
          rno++;
        }
        else if (count <= 70 && count >= 35)
        // 53
        {
          RF_Data[rbyte] |= (0x80 >> rbit);
          rno++;
        }
        else
        {
          rno = 0;
          error++;
          if (error > 5)
          {
            return 0;
          }
        }
        if (rno >= 32)
        {
          break;
        }
        count = 0;
      }
    }
    else
    {
      if (rfstatus == 0)
      {
        rfstatus = 1;
        if (count > 35)
        {
          rno = 0;
          error++;
          if (error > 5)
          {
            return 0;
          }
        }
        count = 0;
      }
    }
    delayMicroseconds(25); //30
    count++;
    if (count > 250)
    //7.5ms
    {
      return 0;
    }
  }
  if(RF_Data[2]!=0x52)
  {
    return 0;
  }
  RF_Id = RF_Data[0];
  RF_Id <<=8;
  RF_Id |= RF_Data[1];
  RF_Ch = RF_Data[3];
  if (RF_Ch&0x80)
  {
    RF_On = RF_ON; 
  }
  else
  {
    RF_On = RF_OFF; 
  }
  RF_Ch &= 0x0F;
  return 1;
}

// -------------------------------------------------------------------
void RF_TxByte(uint8_t ch)
{
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    if (ch &(0x80 >> i))
    {
      digitalWrite(RF_TX, HIGH);
      delayMicroseconds(1600);
      digitalWrite(RF_TX, LOW);
      delayMicroseconds(600);
    }
    else
    {
      digitalWrite(RF_TX, HIGH);
      delayMicroseconds(500);
      digitalWrite(RF_TX, LOW);
      delayMicroseconds(600);
    }
  }
}

// -------------------------------------------------------------------
void RF_TxData(uint16_t id, uint8_t ch,uint8_t on, uint8_t sendcount)
{
  uint8_t cmd,count;
  if (on == RF_ON)
  {
    cmd = (ch | 0x80);
  }
  else
  {
    cmd = (ch | 0x40);
  }
  for(count=0;count<sendcount;)
  {
    digitalWrite(RF_TX, HIGH); 
    delayMicroseconds(4400);
    digitalWrite(RF_TX, LOW); 
    delayMicroseconds(3000);
    RF_TxByte((id >> 8));  // 過濾低位元
    RF_TxByte((id &0xFF)); //過濾高位元
    RF_TxByte(0x52);
    RF_TxByte(cmd);
    if(count++<sendcount)
    {
      delayMicroseconds(9600);
    }
  }
}
void serial_read()
{
   String  ch;
   if (Serial.available())
   {
    delay(5);
     ch = Serial.readString();
     myOLED.print(ch);
      if (ch == "A1")
      {
          serial_flag = 1;
      }
      else if(ch == "A2")
      {
          serial_flag = 2;
      }
      else if (ch == "B1")
      {
          serial_flag = 3;
      }
       else if(ch == "B2")
      {
          serial_flag = 4;
      }
      else if (ch == "C1")
      {
         serial_flag = 5;
      }
   }
   else 
   {
     serial_flag = 0 ;
   }
}

