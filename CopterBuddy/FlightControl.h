//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _FLIGHTCONTROL_h
#define _FLIGHTCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class FlightControlClass
{
 public:

	 enum TestFlightState
	 {
		 TFS_WARMUP,
		 TFS_ENGINES_START,
		 TFS_ENGINES_PROGRAMMING,
		 TFS_ENGINES_ACCELERATE,
		 TFS_ENGINES_DECELERATE,
		 TFS_ENGINES_STOP
	 };

	 enum FlightState
	 {
		 FS_INACTIVE,
		 FS_ACTIVE,
		 FS_PRE_CONTROL,
		 FS_TESTFLIGHT,
		 FS_CONTROL,
		 FS_PID_CONFIG,
		 FS_AUTO_RETHOME,
		 FS_AUTO_PILOT
	 } state;

	void init();
	void update();
	void testFlight();

protected:
	unsigned long displayUpdateTime;
	void displayUpdate();

	unsigned long preControlTime;
	unsigned long enginesToggleTime;
	unsigned long configToggleTime;
#ifdef USE_LOST_COMM_SHUTDOWN
	unsigned long lastCommTime;
#endif
	void controlMotion();
	void applyThrottle();
	int  motionThrottle, mt1, mt2, mt3, mt4;

	TestFlightState tfs;
	void processTestFlight(unsigned long time);

#ifdef DEBUG_FLIGHTMETRICS
	unsigned long debugDataAddress = 0;
#endif
};

extern FlightControlClass FlightControl;

#endif

