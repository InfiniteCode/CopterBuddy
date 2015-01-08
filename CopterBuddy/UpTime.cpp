//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "UpTime.h"

void UpTimeClass::init()
{
	timeMillis = 0;
	timeMicros = 0;
	millisCycle = 0;
	microsCycle = 0;
	longestCycleMS = 0;
}

void UpTimeClass::update()
{
	millisCycle = timeMillis;
	microsCycle = timeMicros;
	timeMillis = millis();
	timeMicros = micros();
	millisCycle = timeMillis - millisCycle;
	microsCycle = timeMicros - microsCycle;
	if (longestCycleMS < millisCycle) longestCycleMS = millisCycle;
}

void UpTimeClass::resetLongestMS()
{
	longestCycleMS = 0;
}

uint16_t UpTimeClass::getDays() {
	return timeMillis / 86400000; // (1000 * 60 * 60 * 24);
}

uint16_t UpTimeClass::getHours() {
	return timeMillis / 3600000; // (1000 * 60 * 60);
}

unsigned long UpTimeClass::getMinutes() {
	return timeMillis / 60000; // (1000 * 60);
}

unsigned long UpTimeClass::getSeconds() {
	return timeMillis / 1000;
}

unsigned long UpTimeClass::getMillis() {
	return timeMillis;
}

unsigned long UpTimeClass::getMicros(){
	return timeMicros;
}

long UpTimeClass::getHoursRemainder()
{
	return (timeMillis - getDays() * 86400000) / 3600000;
}

long UpTimeClass::getMinutesRemainder()
{
	return (timeMillis - getDays() * 86400000 - getHoursRemainder() * 3600000) / 60000;
}

long UpTimeClass::getSecondsRemainder()
{
	return (timeMillis - getDays() * 86400000 - getHoursRemainder() * 3600000 - getMinutesRemainder() * 60000) / 1000;
}

unsigned long UpTimeClass::getMillisCycle()
{
	return millisCycle;
}

unsigned long UpTimeClass::getMicrosCycle()
{
	return microsCycle;
}

uint16_t UpTimeClass::getLongestCycleMS()
{
	return longestCycleMS;
}

UpTimeClass UpTime;

