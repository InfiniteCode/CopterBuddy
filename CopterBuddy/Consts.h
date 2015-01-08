//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _CONSTS_h
#define _CONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"

#ifdef DEBUG_OUTPUT
#define DEBUG_PRINT(a) Serial.print(a);
#define DEBUG_PRINTLN(a) Serial.println(a);
#else
#define DEBUG_PRINT(a) 
#define DEBUG_PRINTLN(a)
#endif

#define ConstFlashString(name) static const __FlashStringHelper* name;

class CS
{
public:
	static void init();

	ConstFlashString(CONST_GENERAL_TAB)
	ConstFlashString(CONST_GENERAL_SPACE)
	ConstFlashString(CONST_GENERAL_NEWLINE)
	ConstFlashString(CONST_GENERAL_DELIM)
	ConstFlashString(CONST_GENERAL_OK)
	ConstFlashString(CONST_GENERAL_FAILED)
	ConstFlashString(CONST_GENERAL_YAW)
	ConstFlashString(CONST_GENERAL_PITCH)
	ConstFlashString(CONST_GENERAL_ROLL)
	ConstFlashString(CONST_GENERAL_UPTIME)
	ConstFlashString(CONST_GENERAL_DAY)
	ConstFlashString(CONST_GENERAL_HOUR)
	ConstFlashString(CONST_GENERAL_MIN)
	ConstFlashString(CONST_GENERAL_SEC)
	ConstFlashString(CONST_GENERAL_CYCLE)
	ConstFlashString(CONST_GENERAL_PRESSURE)
	ConstFlashString(CONST_GENERAL_PRESSURE_HPA)
	ConstFlashString(CONST_GENERAL_TEMP)
	ConstFlashString(CONST_GENERAL_COMPASS)
	ConstFlashString(CONST_GENERAL_DISTANCE)
	ConstFlashString(CONST_GENERAL_CM)
	
#ifdef DEBUG_OUTPUT
	ConstFlashString(CONST_DISPLAY_INIT)
#ifdef USE_LCD_NOKIA_5110
	ConstFlashString(CONST_DISPLAY_NOKIA5110)
#endif
#ifdef USE_LCD_ILI9341
	ConstFlashString(CONST_DISPLAY_ILI9341)
#endif
	ConstFlashString(CONST_DISPLAY_INITDONE)

	ConstFlashString(CONST_I2C_INIT)

	ConstFlashString(CONST_MOTSEN_INIT)
	ConstFlashString(CONST_MOTSEN_ACCELXYZ)
	ConstFlashString(CONST_MOTSEN_GYROXYZ)
	ConstFlashString(CONST_MOTSEN_INITDONE)

#ifdef USE_MPU6050
	ConstFlashString(CONST_MOTSEN_MPU6050)
#endif
#ifdef USE_MPU6050_DMP
	ConstFlashString(CONST_MOTSEN_MPU6050_OFFSETS)
	ConstFlashString(CONST_MOTSEN_MPU6050_DMPINIT)
	ConstFlashString(CONST_MOTSEN_MPU6050_DMPPACK)
	ConstFlashString(CONST_MOTSEN_MPU6050_MEMFAIL)
	ConstFlashString(CONST_MOTSEN_MPU6050_CFGFAIL)
	ConstFlashString(CONST_MOTSEN_MPU6050_OVERFLOW)
#endif

#ifdef USE_BMP085
	ConstFlashString(CONST_MOTSEN_BMP085)
#endif

#ifdef USE_HMC5883L
	ConstFlashString(CONST_MOTSEN_HMC5883L)
#endif

#endif //DEBUG_OUTPUT
};

#endif

