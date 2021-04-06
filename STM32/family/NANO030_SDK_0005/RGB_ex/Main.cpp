//-------------------------------------------------------------------
// RGB_ex
//-------------------------------------------------------------------
#include "Nano030.h" // STM32F030

//-------------------------------------------------------------------
#include "OLED.h" // OLED
OLED myOLED;

//-------------------------------------------------------------------
#include "WS2812.h" // WS2812
WS2812 rgbLED;

//-------------------------------------------------------------------
#define KEY_SELECT		PF0
#define KEY_ENETR			PF1
uint8_t KEY_SELECT_Tag;
uint8_t KEY_ENTER_Tag;

uint8_t KEY_RGB_Tag;

//-------------------------------------------------------------------
int main(void)
{
	//setup
	SystemClock_Config();

  myOLED.begin(FONT_8x16); // or FONT_6x8
  myOLED.println("RGB LED Test");

	pinMode(KEY_SELECT, INPUT_PULLUP);
	pinMode(KEY_ENETR, INPUT_PULLUP);
	pinMode(LED_R, OUTPUT);
	pinMode(LED_B, OUTPUT);
	digitalWrite(LED_B,LOW);
	digitalWrite(LED_R,LOW);

	
	rgbLED.begin(PA1);

	rgbLED.setLEDColor(0, 0xFF, 0x00, 0x00);
	rgbLED.setLEDColor(1, 0x00, 0xFF, 0x00);
	rgbLED.setLEDColor(2, 0x00, 0x00, 0xFF);
	rgbLED.showStrip();
	
	//loop
	while (1)
	{
		delayMicroseconds(1000);
		if (digitalRead(KEY_SELECT) == 0)
		{
			if (KEY_SELECT_Tag == 1)
			{
				KEY_SELECT_Tag = 0;
				myOLED.setPosi(4,0);
				myOLED.println("* SELECT Press *");
				digitalWrite(LED_B,LOW);
				digitalWrite(LED_R,HIGH);
				rgbLED.fillStrip(0x80,0x80,0x60);
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
				myOLED.println("= ENTER Press  =");
				digitalWrite(LED_R,LOW);
				digitalWrite(LED_B,HIGH);
				if(KEY_RGB_Tag==0)
				{
					KEY_RGB_Tag=1;
					rgbLED.setLEDColor(0, 0x80, 0x00, 0x00);
					rgbLED.setLEDColor(1, 0x80, 0x00, 0x00);
					rgbLED.setLEDColor(2, 0x80, 0x00, 0x00);
					rgbLED.showStrip();
				}
				else if(KEY_RGB_Tag==1)
				{
					KEY_RGB_Tag=2;
					rgbLED.setLEDColor(0, 0x00, 0x80, 0x00);
					rgbLED.setLEDColor(1, 0x00, 0x80, 0x00);
					rgbLED.setLEDColor(2, 0x00, 0x80, 0x00);
					rgbLED.showStrip();
				}
				else
				{
					KEY_RGB_Tag=0;
					rgbLED.setLEDColor(0, 0x00, 0x00, 0x80);
					rgbLED.setLEDColor(1, 0x00, 0x00, 0x80);
					rgbLED.setLEDColor(2, 0x00, 0x00, 0x80);
					rgbLED.showStrip();
				}
			}
		}
		else
		{
			KEY_ENTER_Tag = 1;
		}		
	}
}
