//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "SonicSensor.h"
/*
#ifdef USE_HC_SR04
#include <NewPing\NewPing.h>

struct {
	NewPing module;
} module_NewPing;
#endif

void SonicSensorClass::init(uint8_t pinTrigger, uint8_t pinEcho)
{
	pinTrig = pinTrigger;
	pinEch = pinEcho;
	module_NewPing.module.
	distance = -1;
	pinMode(pinTrig, OUTPUT);
	pinMode(pinEch, INPUT);
}

void SonicSensorClass::measureDistance()
{
	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(pinTrig, LOW);
	delayMicroseconds(4);
	digitalWrite(pinTrig, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinTrig, LOW);

	// The same pin is used to read the signal from the PING))): a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	distance = pulseIn(pinEch, HIGH);
}

void SonicSensorClass::measureDistanceAverage()
{
	long total = 0;
	for (uint8_t i = 0; i < 5; ++i)
	{
		measureDistance();
		total += distance;
	}

	distance = total / 5;
}

long SonicSensorClass::getDistanceInches()
{
	// 73.746 microseconds per inch. This gives the distance travelled by the ping, 
	// outbound and return, so we divide by 2 to get the distance of the obstacle.
	// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
	return distance / 74 / 2;
}

long SonicSensorClass::getDistanceCentimeters()
{
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return distance / 29 / 2;
}

SonicSensorClass SonicSensor;

*/