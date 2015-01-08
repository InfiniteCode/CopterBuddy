//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class UpTimeClass
{
 public:
	void init();
	void update();

	uint16_t getDays();
	uint16_t getHours();
	unsigned long getMinutes();
	unsigned long getSeconds();
	unsigned long getMillis();
	unsigned long getMicros();
	unsigned long getMillisCycle();
	unsigned long getMicrosCycle();
	uint16_t getLongestCycleMS();
	void resetLongestMS();

	//Those calculate ONLY the remaining part of the time, so for example
	//for 25 hours uptime getHoursEx will return 1h instead of 25h
	//and so on till seconds
	long getHoursRemainder();
	long getMinutesRemainder();
	long getSecondsRemainder();

protected:
	unsigned long timeMillis;
	unsigned long timeMicros;
	unsigned long millisCycle;
	unsigned long microsCycle;
	uint16_t longestCycleMS;
};

extern UpTimeClass UpTime;

#endif

