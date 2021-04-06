//-------------------------------------------------------------------
// Servo.h
//-------------------------------------------------------------------
#ifndef SERVO_H
#define SERVO_H
#include "HT32IO.h"

class Servo
{
public:
  Servo();
  uint8_t attach(int pin);
  void detach();
  void write(int degrees);
  int read();
  bool attached();
private:
   int pin;
   int degrees;
};

#endif
