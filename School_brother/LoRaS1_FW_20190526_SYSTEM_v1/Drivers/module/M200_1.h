//-------------------------------------------------------------------
// Filename: M200.h
// Description: hal M200 module library header file
//-------------------------------------------------------------------

extern uint16_t GND_M200_Humi;
extern uint16_t GND_M200_Temp;


//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
extern void GND_M200_Init(void);
extern void GND_M200_GetValue(void);
