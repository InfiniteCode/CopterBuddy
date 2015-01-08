//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "I2CBus.h"

#include "Config.h"
#include "Consts.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

void I2CBusClass::init()
{
	DEBUG_PRINT(CS::CONST_I2C_INIT);
	// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();

	// test the connection to the I2C bus, sometimes it doesn't connect
	// keep trying to connect to I2C bus if we get an error
	/*
#ifdef USE_MPU6050
	boolean error = true;
	while (error) {
		Wire.beginTransmission(0x68);
		error = Wire.endTransmission(); // if error = 0, we are properly connected
		if (error) { // if we aren't properly connected, try connecting again and loop
			Serial.println("  ");
			Serial.println("Not properly connected to I2C, trying again");
			Serial.println(" ");
			Wire.begin();
			TWBR = 24; // 400kHz I2C clock
		}
	}
	Serial.println("Properly connected to I2C");
	
#endif
	*/
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif


	DEBUG_PRINTLN(CS::CONST_GENERAL_OK);
}


I2CBusClass I2CBus;

