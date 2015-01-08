//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "KeyesRGB.h"
#include "Config.h"

void KeyesRGBClass::init(uint8_t pinR, uint8_t pinG, uint8_t pinB)
{
	r = pinR;
	g = pinG;
	b = pinB;
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);
	turnOff();
}

void KeyesRGBClass::setOn(bool R, bool G, bool B)
{
	digitalWrite(r, R ? HIGH : LOW);
	digitalWrite(g, G ? HIGH : LOW);
	digitalWrite(b, B ? HIGH : LOW);
}

void KeyesRGBClass::setColor(RGBColor color)
{
	switch (color)
	{
	case RED: setOn(true, false, false); break;
	case GREEN: setOn(false, true, false); break;
	case BLUE: setOn(false, false, true); break;
	case YELLOW: setOn(true, true, false); break;
	case PURPLE: setOn(true, false, true); break;
	case AQUA: setOn(false, true, true); break;
	default: turnOff();
	}
}

void KeyesRGBClass::turnOff()
{
	setOn(false, false, false);
}


KeyesRGBClass KeyesRGB;

