//-------------------------------------------------------------------
// HMI.cpp
//-------------------------------------------------------------------
#include "HMI.h"

//-------------------------------------------------------------------
void HMI_PutCommand(char cmd[])
{
	uint8_t i, len;

	len = strlen((const char*)cmd);
	for (i = 0; i < len; i++)
	{
		HMI_PutByte(cmd[i]);
	}
	HMI_PutByte(0xFF);
	HMI_PutByte(0xFF);
	HMI_PutByte(0xFF);
	HMI_PutEnd();
}

//-------------------------------------------------------------------
void HMI_SetValue(char str[], uint16_t val)
{
	char cmd[40];

	sprintf(cmd, "%s.val=%d", str, val);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_SetText(char str[], char txt[])
{
	char cmd[40];

	sprintf(cmd, "%s.txt=\"%s\"", str, txt);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}


//-------------------------------------------------------------------
void HMI_SetTCC(uint16_t val)
{
	char cmd[40];

	sprintf(cmd, "tcc.txt=\"%6.1f\"", (((float)val)/(60.0)));
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref tcc");
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_SetMsg(char str[], char txt[])
{
	char cmd[40];

	sprintf(cmd, "%s.txt=%s.txt", str, txt);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_SetBackColor(char str[], uint16_t color)
{
	char cmd[40];

	sprintf(cmd, "%s.bco=%d", str, color);
	HMI_PutCommand(cmd);
	sprintf(cmd, "ref %s", str);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_SetVisible(char str[], uint8_t show)
{
	char cmd[40];

	sprintf(cmd, "vis %s,%d", str, show);
	HMI_PutCommand(cmd);
}

//-------------------------------------------------------------------
void HMI_Proc(void)
{
	uint8_t cmd;
	if (HMI_Flag != 0)
	{
		if (HMI_Point == 3)
		{
			if (HMI_Buffer[0] == 0x5A && HMI_Buffer[2] == 0x0D)
			{
				cmd = HMI_Buffer[1];
				switch (cmd)
				{
					case 0x01:
						// RUN/PAUSE
 						if (POWER_Run == 0 && _KEY_4 == 0)
						{
							BEEP_Ok();
							DEVICE_Start();
						}
						break;
					case 0x02:
						// STOP
						if (POWER_Run != 0)
						{
							BEEP_Ok();
							DEVICE_Stop();
							PARAMETER_Write();
							TIMER_SaveCount = 0;
						}
						break;
					case 0x03:
						// CLEAR
						TIMER_SetSec = 0;
						HMI_SetValue("nset", (TIMER_SetSec/60));
						TIMER_RunSec = 0;
						HMI_SetValue("nrun", TIMER_RunSec);
						BEEP_Message();
						if(TOTAL_ResetTime==4)
						{
							TOTAL_Sec=0;
							HMI_SetValue("nall", 0);
							PARAMETER_Write();
							TIMER_SaveCount = 0;
						}
						else
						{
							TIMER_SaveCount = 30;
						}					
						break;
					case 0x05:
						// +10
						if (TIMER_SetSec < 65000)
						{
							TIMER_SetSec += 600;
							HMI_SetValue("nset", (TIMER_SetSec/60));
							BEEP_Key();
							TIMER_SaveCount = 30;
						}
						break;
					case 0x06:
						// -10
						if (TIMER_SetSec >= 600)
						{
							TIMER_SetSec -= 600;
							HMI_SetValue("nset", (TIMER_SetSec/60));
							BEEP_Key();
							TIMER_SaveCount = 30;
						}
						break;
					case 0x07:
						// +1
						if (TIMER_SetSec < 65000)
						{
							TIMER_SetSec += 60;
							HMI_SetValue("nset", (TIMER_SetSec/60));
							BEEP_Key();
							TIMER_SaveCount = 30;
						}
						break;
					case 0x08:
						// -1
						if (TIMER_SetSec >= 60)
						{
							TIMER_SetSec -= 60;
							HMI_SetValue("nset", (TIMER_SetSec/60));
							BEEP_Key();
							TIMER_SaveCount = 30;
						}
						break;
					case 0x09:
						// 電壓/電流
						BEEP_Key();
						if(METER_Flag==1)
						{
							METER_Flag=2;
							HMI_SetVisible("tv", 1);
							HMI_SetVisible("ta", 1);
							DEVICE_ShowMeter();
						}						
						else
						{
							METER_Flag=1;
							HMI_SetVisible("tv", 0);
							HMI_SetVisible("ta", 0);
						}
						break;
					case 0x0A:
						// TOTAL
						TOTAL_ResetCount=0;
						TOTAL_ResetTime++;
						BEEP_Key();
						break;
				}
			}
		}
		HMI_Clear();
	}
}
