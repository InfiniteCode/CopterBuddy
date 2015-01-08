//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _MOTORSMANAGER_h
#define _MOTORSMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"

class MotorsManagerClass
{
 protected:
	 uint16_t throttle1, throttle2, throttle3, throttle4;

 public:
	void init();
	void start();
	void stop();
	void update();
#ifdef MOTOR_CONFIG_4X
	void setThrottle(uint16_t pwr1, uint16_t pwr2, uint16_t pwr3, uint16_t pwr4);
#endif
};

extern MotorsManagerClass MotorsManager;

#endif

