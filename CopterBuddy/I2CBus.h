//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _I2CBUS_h
#define _I2CBUS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class I2CBusClass
{
 protected:


 public:
	void init();
};

extern I2CBusClass I2CBus;

#endif

