//-------------------------------------------------------------------
// RFID_ex
//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "RFID.h" // RFID
#define SIC_CS        10 //CS
#define SIC_SCK       13 //SCK
#define SIC_MISO      12 //MISO
#define SIC_MOSI      11 //MOSI
RFID_SIC sic;

//-------------------------------------------------------------------
int count = 0;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

	myOLED.begin(FONT_8x16); // or FONT_6x8
	myOLED.clearScreen();
	myOLED.println("OLED Test");

	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);

	sic.begin(SIC_CS, SIC_SCK, SIC_MISO, SIC_MOSI);
	sic.sicInit();

	//loop
	while (1)
	{
		uint8_t i;
		sic.sicInit();
		if (sic.ISO14443A_Request() == 1)
		{
			if (sic.ISO14443A_Anticoll(0x93) == 1)
			{
				if (sic.ISO14443A_Select(0x93) == 1)
				{
					myOLED.setPosi(4, 0);
					myOLED.print("UID:[0x");
					for (i = 0; i < 4; i++)
					{
						if (sic.sicUID[3-i] < 0x10)
						{
							myOLED.print('0');
						}
						myOLED.print(sic.sicUID[3-i], HEX);
					}
					myOLED.println("]");
				}
			}
		}
		delay(100);
	}
}
