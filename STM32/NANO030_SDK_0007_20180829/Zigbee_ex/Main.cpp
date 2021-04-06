//-------------------------------------------------------------------
// Zigbee_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
// Serial is RX1/TX1 conect to PC
// Serial1 is RX2/TX2 conect to Zigbee module
//-------------------------------------------------------------------
#define RECV_MAX    32
uint8_t RecvBuf[RECV_MAX];
uint8_t RecvLen;
int RecvCount;
void Zigbee_setup(uint8_t channel, uint16_t panid, uint16_t addr);

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("Zigbee Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600); // PC
	Serial1.begin(9600); // Zigbee module

	Zigbee_setup(26, 0x1001, 0x2002);

	//loop
	while (1)
	{
		uint8_t ch;
		if (Serial1.available())
		{
			ch = Serial1.read();
			if (RecvLen < RECV_MAX)
			{
				RecvBuf[RecvLen++] = ch;
			}
			RecvCount = 200;
		}
		if (Serial.available())
		{
			ch = Serial.read();
			Serial1.write(ch);
		}
		delayMicroseconds(10);
		if (RecvCount > 0)
		{
			RecvCount--;
			if (RecvCount == 0)
			{
				RecvBuf[RecvLen++] = 0x00;
				Serial.println((char*)RecvBuf);
				myOLED.println((char*)RecvBuf);
				RecvLen = 0;
			}
		}
	}
}

//------------------------------------------------------------------------------
void Zigbee_setup(uint8_t channel, uint16_t panid, uint16_t addr)
{
	// get Channel/PAN ID/Address
	Serial1.write(0xAA);
	Serial1.write(0xC7);
	Serial1.write(0xBB);
	delay(30);

	// set Channel/PAN ID/Address
	Serial1.write(0xAA);
	Serial1.write(0xC7);
	Serial1.write(0x5A);
	Serial1.write(channel);
	Serial1.write(panid >> 8);
	Serial1.write(panid &0xff);
	Serial1.write(addr >> 8);
	Serial1.write(addr &0xff);
	Serial1.write(0xBB);
}
