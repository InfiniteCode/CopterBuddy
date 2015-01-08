//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Helper3DMath.h"

class DisplayClass
{
 public:
	void init();
	void clear();
	void display();

	//posY = -1 will not update cursor pos
	void printMotionMetrics(const VectorFloat& yawPitchRoll, int16_t posY, bool oneLiner = false);
	void printCompassMetrics(const float heading, int16_t posY);
	void printUptime(int16_t posY);
	void printCycleTime(const unsigned long cycle, const uint16_t longestCycle, int16_t posY);
	void printAtmosData(const float pressure, const float temperature, int16_t posY);
	void printDistanceCm(long distance, int16_t posY);
	void printPIDs(int16_t posY, double rollKP, double pitchKP, double yawKP,
		double rollKI, double pitchKI, double yawKI,
		double rollKD, double pitchKD, double yawKD);
	void printThrottle(int throttle, int frontLeft, int frontRight, int backLeft, int backRight, int16_t posY);


protected:

};

extern DisplayClass Display;

#endif

