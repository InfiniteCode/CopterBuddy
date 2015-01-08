//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _SONICSENSOR_h
#define _SONICSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//TODO Implement SonicSensor support to prevent collisions
/*
class SonicSensorClass
{
protected:
	uint8_t pinTrig, pinEch;
	long distance;

public:
	void init(uint8_t pinTrigger, uint8_t pinEcho);
	void measureDistance();
	void measureDistanceAverage();
	long getDistanceInches();
	long getDistanceCentimeters();
};

extern SonicSensorClass SonicSensor;
*/
#endif

