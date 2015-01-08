//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _KEYESRGB_h
#define _KEYESRGB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum RGBColor
{
	RED,
	GREEN,
	BLUE,
	PURPLE,
	YELLOW,
	AQUA
};

class KeyesRGBClass
{
 protected:
	 uint8_t r;
	 uint8_t g;
	 uint8_t b;

 public:
	void init(uint8_t pinR, uint8_t pinG, uint8_t pinB);
	void setOn(bool R, bool G, bool B);
	void setColor(RGBColor color);
	void turnOff();
};

extern KeyesRGBClass KeyesRGB;

#endif

