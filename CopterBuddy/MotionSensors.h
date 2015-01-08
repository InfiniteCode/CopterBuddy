//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _MOTIONSENSORS_h
#define _MOTIONSENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Helper3DMath.h"

class MotionSensorsClass
{
  public:
	void init();
	void update();

	const VectorInt16& getGyroData();
	const VectorInt16& getAccelData();
	const Quaternion&  getOrientationQuat();
	const VectorFloat& getYawPitchRoll();
	const VectorFloat& getEulerAngles();
	const bool isMotionUpdateAvailable(); //Automatically resets during the next update call

	const float getAtmosPressure();
	const float getAtmosTemperature();
	const float getAtmosAltitude();

	const VectorInt16& getCompassRaw();
	const float getCompassHeading(); //0 degrees - North

  protected:
	  VectorInt16 gyroCurrent;
	  VectorInt16 accelCurrent;
	  Quaternion  orientationQuat;
	  VectorFloat yawPitchRoll;
	  VectorFloat eulerAngles;
	  bool		  motionUpdateAvailable;
	  
	  unsigned long atmosMeasureStart;
	  float		  atmosPressure;
	  float		  atmosTemp;
	  float		  atmosAlt;

	  VectorInt16 compassRaw;
	  float		  compassHeading;

};

extern MotionSensorsClass MotionSensors;

#endif

