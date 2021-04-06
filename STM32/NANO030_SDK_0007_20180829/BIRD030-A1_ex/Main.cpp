//-------------------------------------------------------------------
// HUSTKIT1_LIGHT1_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

//-------------------------------------------------------------------
#define BLE_PWRC			PA6
#define BLE_STAT			PA7

#define BLE_Serial	Serial1
uint8_t BLE_RxBufCount;
uint8_t BLE_Count;
uint8_t BLE_RxBuf[100];

//-------------------------------------------------------------------
#define UART_Serial	Serial
uint8_t UART_RxBufCount;
uint8_t UART_Count;
uint8_t UART_RxBuf[100];

//-------------------------------------------------------------------
#define KEY1					PF6
#define KEY2					PF7
uint8_t KEY1_Tag;
uint8_t KEY2_Tag;

//-------------------------------------------------------------------
#define MP3_POWER			PB11
#define MP3_ONLINE		PB13

//-------------------------------------------------------------------
#define LUX_PIN  			PA1 //LUX SENSOR

//-------------------------------------------------------------------
#define RF_EN  				PA5
#define RF_DAT  			PA4

//-------------------------------------------------------------------
#define DRV_POWER			PA15
#define DRV_LED1			PB6
#define DRV_LED2			PB7

//-------------------------------------------------------------------
#define IIC_SDA				PB0
#define IIC_SCL				PB1

//-------------------------------------------------------------------
uint8_t UART_Get(void)
{
	while (UART_Serial.available() > 0)
	{
		UART_Count = 0;
		digitalWrite(LED_B, HIGH);
		UART_RxBuf[UART_RxBufCount] = UART_Serial.read();
		if (UART_RxBufCount < 99)
		{
			UART_RxBufCount++;
		}
	}

	if (UART_Count++ >= 20)
	{
		UART_Count = 0;
		if (UART_RxBufCount > 0)
		{
			UART_RxBuf[UART_RxBufCount] = 0;
			myOLED.clearScreen();
			myOLED.println((char*)UART_RxBuf);
			UART_RxBufCount = 0;
			digitalWrite(LED_B, LOW);
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
void UART_PutCommand(const char cmd[])
{
	UART_Serial.println(cmd);
}

//------------------------------------------------------------------------------
void BLE_SetName(char *sname)
{
	BLE_Serial.print("AT+NAME");
	BLE_Serial.println(sname);
	delay(50);
	while (BLE_Serial.available() > 0)
	{
		BLE_Serial.read();
	}
}

//-------------------------------------------------------------------
uint8_t BLE_Get(void)
{
	while (BLE_Serial.available() > 0)
	{
		BLE_Count = 0;
		digitalWrite(LED_B, HIGH);
		BLE_RxBuf[BLE_RxBufCount] = BLE_Serial.read();
		if (BLE_RxBufCount < 99)
		{
			BLE_RxBufCount++;
		}
	}

	if (BLE_Count++ >= 20)
	{
		BLE_Count = 0;
		if (BLE_RxBufCount > 0)
		{
			BLE_RxBuf[BLE_RxBufCount] = 0;
			myOLED.clearScreen();
			myOLED.println((char *)BLE_RxBuf);  
			digitalWrite(LED_B, LOW);
			BLE_RxBufCount = 0;
			return 1;
		}
	}
	return 0;
}

//-------------------------------------------------------------------
void MP3_SendData(uint8_t addr )
{
	uint8_t i;

	digitalWrite(MP3_ONLINE, HIGH);
	delay(2);
	digitalWrite(MP3_ONLINE, LOW);
	delay(4);
	for ( i = 0; i < 8; i++ )
	{
		digitalWrite(MP3_ONLINE, HIGH);
		if ( addr & 0x01 )
		{
			delayMicroseconds ( 500 );
			digitalWrite(MP3_ONLINE, LOW);
			delayMicroseconds ( 210 );
		}
		else
		{
			delayMicroseconds ( 210 );
			digitalWrite(MP3_ONLINE, LOW);
			delayMicroseconds ( 500 );
		}
		addr >>= 1;
	}
	digitalWrite(MP3_ONLINE, HIGH);
	delay(10);
}

//-------------------------------------------------------------------
void MP3_SetVolume(uint8_t vol )//1-20
{
	uint8_t hi,lo;
	hi=vol/10;
	lo=vol%10;
	MP3_SendData(0x0A);
	if(hi>0)
	{
		MP3_SendData(hi);
	}
	MP3_SendData(lo);
	MP3_SendData(0x0C);
}

//-------------------------------------------------------------------
void MP3_Play(uint8_t no)//1-N
{
	uint8_t hi,lo;
	hi=no/10;
	lo=no%10;
	MP3_SendData(0x0A);
	if(hi>0)
	{
		MP3_SendData(hi);
	}
	MP3_SendData(lo);
	MP3_SendData(0x0B);
	delay(10);
	MP3_SendData(0x11);
	
}

//-------------------------------------------------------------------
void LIGHT_Flash(void)
{
	digitalWrite(DRV_POWER, HIGH);//DRV POWER ON
	digitalWrite(DRV_LED1, HIGH);//DRV_LED1 ON
	delay(200);
	digitalWrite(DRV_LED1, LOW);//DRV_LED1 OFF
	delay(200);
	digitalWrite(DRV_LED2, HIGH);//DRV_LED2 ON
	delay(200);
	digitalWrite(DRV_LED2, LOW);//DRV_LED2 OFF
	digitalWrite(DRV_POWER, LOW);//DRV POWER OFF
}

uint8_t RF_Data[4];
uint16_t RF_Id;
uint8_t RF_Dat;

//------------------------------------------------------------------------------
uint8_t RF_Check(void)
{
  uint8_t i;
  uint16_t count;
  uint8_t rfstatus, error;
  uint8_t rno, rbyte, rbit;

  rno = 0;
  count = 0;
  rfstatus = 0;
  error = 0;
  while (1)
  {
    if (digitalRead(RF_DAT)== 0)
    {
      if (rfstatus == 1)
      {
        rfstatus = 0;
        rbyte = (rno >> 3);
        rbit = (rno % 8);
        if (count < 30 && count > 8)
        // 16
        {
          RF_Data[rbyte] &= ~(0x80 >> rbit);
          rno++;
        }
        else if (count <= 70 && count >= 30)
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
        if (rno >= 25)
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
        if (count > 70 || count < 8)
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
    if (count > 800)
    //20ms
    {
      return 0;
    }
  }
  RF_Id = RF_Data[0];
  RF_Id <<=8;
  RF_Id |= RF_Data[1];
  RF_Dat = RF_Data[2];
  return 1;
}

//-------------------------------------------------------------------
int main(void)
{
	int i, val;
	char buf[40];
	int timer_ms,timer_off;
	//setup
	SystemClock_Config();

	pinMode(KEY1, INPUT_PULLUP);
	pinMode(KEY2, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, HIGH);

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("BIRD030-A1");

	// RF 433
	pinMode(RF_EN, OUTPUT);
	pinMode(RF_DAT, INPUT);
	digitalWrite(RF_EN, LOW);// ENABLE

	// BLE module
	pinMode(BLE_PWRC, OUTPUT);
	pinMode(BLE_STAT, INPUT);
	digitalWrite(BLE_PWRC, HIGH);//
	BLE_Serial.begin(9600,SERIAL_8N1,true); 
	BLE_RxBufCount = 0;

	// UART
	UART_Serial.begin(9600); // RS485/UART
	UART_RxBufCount = 0;

	// MP3
	pinMode(MP3_POWER, OUTPUT);
	pinMode(MP3_ONLINE, OUTPUT);
	digitalWrite(MP3_ONLINE, HIGH);
	digitalWrite(MP3_POWER, LOW);//MP3 POWER OFF

	// EXT DRV
	pinMode(DRV_POWER, OUTPUT);
	digitalWrite(DRV_POWER, LOW);//DRV POWER OFF

	pinMode(DRV_LED1, OUTPUT);
	pinMode(DRV_LED2, OUTPUT);
	digitalWrite(DRV_LED1, LOW);//DRV_LED1 OFF
	digitalWrite(DRV_LED2, LOW);//DRV_LED2 OFF

	//loop
	while (1)
	{
		delay(1);
		timer_ms++;
		if(timer_ms>=100)
		{
			timer_ms=0;
			if(RF_Check()>0)
			{
				myOLED.setPosi(4,0);
				myOLED.print("ID:0x");
				myOLED.println(RF_Id,HEX);
				myOLED.setPosi(6,0);
				if(RF_Dat<0x10)
				{
					myOLED.print("DAT:0x0");
					myOLED.println(RF_Dat,HEX);    
				}
				else
				{
					myOLED.print("DAT:0x");
					myOLED.println(RF_Dat,HEX);    
				}
				digitalWrite(LED_B, HIGH);
				LIGHT_Flash();
				delay(500); 
				digitalWrite(LED_B, LOW);
			}
			timer_off++;
			if(timer_off>=50)
			{
				timer_off=0;
				digitalWrite(MP3_POWER, LOW);//MP3 POWER OFF
			}
		}
		
		if (digitalRead(KEY1) == 0)
		{
			if (KEY1_Tag == 1)
			{
				KEY1_Tag = 0;
				digitalWrite(LED_B, HIGH);
				myOLED.setPosi(2, 0);
				myOLED.println("KEY1");
				delay(100);
				digitalWrite(LED_B, LOW);
				//MP3_SetVolume(20);
				//MP3_Play(1);
				BLE_Serial.print("123");
				LIGHT_Flash();
			}
		}
		else
		{
			KEY1_Tag = 1;
		}
		if (digitalRead(KEY2) == 0)
		{
			if (KEY2_Tag == 1)
			{
				KEY2_Tag = 0;
				digitalWrite(LED_B, HIGH);
				myOLED.setPosi(2, 0);
				myOLED.println("KEY2");
				delay(100);
				digitalWrite(LED_B, LOW);
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(2);
			}
		}
		else
		{
			KEY2_Tag = 1;
		}
			
		if (UART_Get() == 1)
		{
			
		}
		
		if (BLE_Get() == 1)
		{
			if(BLE_RxBuf[0]==0x00)
			{
				LIGHT_Flash();
			}
			if(BLE_RxBuf[0]==0x01)
			{
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(1);
			}
			if(BLE_RxBuf[0]==0x02)
			{
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(2);
			}
			if(BLE_RxBuf[0]==0x03)
			{
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(3);
			}
			if(BLE_RxBuf[0]==0x04)
			{
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(4);
			}
			if(BLE_RxBuf[0]==0x05)
			{
				digitalWrite(MP3_POWER, HIGH);//MP3 POWER ON
				timer_off=0;
				delay(500);
				MP3_SetVolume(20);
				MP3_Play(5);
			}
		}
	}
}
