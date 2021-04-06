//-------------------------------------------------------------------
// Servo.cpp
//-------------------------------------------------------------------
#include "Servo.h"

Servo::Servo() {
}

uint8_t Servo::attach(int pin)
{
	int val,pwm;
	
	val=90;
	this->pin=pin;
	this->degrees=val;
	
	pwm=((val*2)/15)+5;
	if(pwm<6)
	{
		pwm=6;
	}
	if(pwm>28)
	{
		pwm=28;
	}
	analogWrite(this->pin, pwm); 
  return true;
}

void Servo::detach() {
}

void Servo::write(int val) {
	int pwm;

	this->degrees=val;	
	pwm=((val*2)/15)+5;
	if(pwm<6)
	{
		pwm=6;
	}
	if(pwm>28)
	{
		pwm=28;
	}
	analogWrite(this->pin, pwm); 
}

int Servo::read() {
    return this->degrees;
}
