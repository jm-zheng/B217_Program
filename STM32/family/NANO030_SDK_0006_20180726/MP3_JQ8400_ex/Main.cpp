//-------------------------------------------------------------------
// MP3_JQ8400_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
// Serial1 is RX2/TX2 conect to JQ8400
//-------------------------------------------------------------------
#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
uint8_t RecvLen;
int RecvCount;
//void Zigbee_setup(uint8_t channel, uint16_t panid, uint16_t addr);

#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

void MP3_play(uint16_t no);
void MP3_volume(uint8_t vol);
//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("MP3 JQ8400 Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);

	Serial1.begin(9600); // JQ8400

	//MP3_volume(10);
	
	//loop
	while (1)
	{
		delay(100);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("* Play MP3 1 *");
				digitalWrite(LED_B,LOW);
				digitalWrite(LED_R,HIGH);
				MP3_play(1);
			}
		}
		else
		{
			KEY_SELECT_Tag = 1;
		}
		if (digitalRead(KEY_ENETR) == 0)
		{
			if (KEY_ENTER_Tag == 1)
			{
				KEY_ENTER_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("= Play MP3 2  =");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
				MP3_play(2);
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
	}
}

uint8_t MP3_sum;
//------------------------------------------------------------------------------
void MP3_byte(uint8_t ch)
{
	Serial1.write(ch);
	MP3_sum+=ch;
}

//------------------------------------------------------------------------------
void MP3_play(uint16_t no)
{
	MP3_sum=0;
	MP3_byte(0xAA);
	MP3_byte(0x07);
	MP3_byte(0x02);
	MP3_byte((no>>8));
	MP3_byte((no&0xff));
	MP3_byte(MP3_sum);
}

//------------------------------------------------------------------------------
void MP3_volume(uint8_t vol)
{
	MP3_sum=0;
	MP3_byte(0xAA);
	MP3_byte(0x13);
	MP3_byte(0x01);
	MP3_byte(vol);
	MP3_byte(MP3_sum);
}
