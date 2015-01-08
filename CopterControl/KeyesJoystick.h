//Copyright 2014, Alex Khilko.
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _KEYESJOYSTICK_h
#define _KEYESJOYSTICK_h

#include "Config.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class KeyesJoystick
{
 protected:
	 uint8_t xPin, yPin, btnPin;
	 int16_t xValue, yValue;
	 int16_t xOffset, yOffset;
	 bool buttonPressed, invertX;
 public:
	void init(const uint8_t& pinX, const uint8_t& pinY, const uint8_t& pinBtn, const int16_t& offsetX, const int16_t& offsetY, bool invertX = true);
	void update();
	const int16_t& getValueX() const;
	const int16_t& getValueY() const;
	const bool isButtonPressed() const;

#ifdef DEBUG_FUNC
	//If needed to find the middle position default value
	void printRaw();
#endif
};

#endif

