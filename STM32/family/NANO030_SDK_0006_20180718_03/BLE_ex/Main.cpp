//-------------------------------------------------------------------
// BLE_ex
//-------------------------------------------------------------------
#include "Serial.h" // Serial and Serial1

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
// Serial is RX1/TX1 conect to PC
// Serial1 is RX2/TX2 conect to BLE module
//-------------------------------------------------------------------
void BLE_setName(char *blename);

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.println("BLE Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B, LOW);
	digitalWrite(LED_R, LOW);

	Serial.begin(9600);
	Serial1.begin(9600);
	BLE_setName((char *)"BLE-222222");

	//loop
	while (1)
	{
		uint8_t ch;
		if (Serial1.available())
		{
			ch = Serial1.read();
			myOLED.print('(');
			myOLED.print(ch, HEX);
			myOLED.print(')');
			Serial.write(ch);
		}
		if (Serial.available())
		{
			ch = Serial.read();
			myOLED.print('[');
			myOLED.print(ch, HEX);
			myOLED.print(']');
			Serial1.write(ch);
		}
	}
}

//------------------------------------------------------------------------------
void BLE_setName(char blename[])
{
	int i, len;

	// BLE module get mac
	Serial1.write(0xAA);
	Serial1.write(0xED);
	Serial1.write(0xBB);
	delay(100);

	// BLE module set name
	Serial1.write(0xAA);
	Serial1.write(0xE3);
	Serial1.write(0x5A);
	len = strlen(blename);
	for (i = 0; i < 12; i++)
	{
		if (i < len)
		{
			Serial1.write((uint8_t)blename[i]);
		}
		else
		{
			Serial1.write(0x20);
		}
	}
	Serial1.write(0xBB);
	delay(200);

	// BLE module reboot
	Serial1.write(0xAA);
	Serial1.write(0xEF);
	Serial1.write(0x5A);
	Serial1.write(0xBB);
	delay(200);
	while (Serial1.available())
	{
		Serial1.read();
	}
}
