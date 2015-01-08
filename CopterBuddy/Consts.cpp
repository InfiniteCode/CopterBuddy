//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Consts.h"

//To avoid keeping strings in RAM we use this helper
#define DefineStatic(name) const __FlashStringHelper* CS::name;


DefineStatic(CONST_GENERAL_TAB)
DefineStatic(CONST_GENERAL_SPACE)
DefineStatic(CONST_GENERAL_NEWLINE)
DefineStatic(CONST_GENERAL_DELIM)
DefineStatic(CONST_GENERAL_OK)
DefineStatic(CONST_GENERAL_FAILED)
DefineStatic(CONST_GENERAL_YAW)
DefineStatic(CONST_GENERAL_PITCH)
DefineStatic(CONST_GENERAL_ROLL)
DefineStatic(CONST_GENERAL_UPTIME)
DefineStatic(CONST_GENERAL_DAY)
DefineStatic(CONST_GENERAL_HOUR)
DefineStatic(CONST_GENERAL_MIN)
DefineStatic(CONST_GENERAL_SEC)
DefineStatic(CONST_GENERAL_CYCLE)
DefineStatic(CONST_GENERAL_PRESSURE)
DefineStatic(CONST_GENERAL_PRESSURE_HPA)
DefineStatic(CONST_GENERAL_TEMP)
DefineStatic(CONST_GENERAL_COMPASS)
DefineStatic(CONST_GENERAL_DISTANCE)
DefineStatic(CONST_GENERAL_CM)

#ifdef DEBUG_OUTPUT
DefineStatic(CONST_DISPLAY_INIT)
#ifdef USE_LCD_NOKIA_5110
DefineStatic(CONST_DISPLAY_NOKIA5110)
#endif
#ifdef USE_LCD_ILI9341
DefineStatic(CONST_DISPLAY_ILI9341)
#endif
DefineStatic(CONST_DISPLAY_INITDONE)

DefineStatic(CONST_I2C_INIT)

DefineStatic(CONST_MOTSEN_INIT)
DefineStatic(CONST_MOTSEN_ACCELXYZ)
DefineStatic(CONST_MOTSEN_GYROXYZ)
DefineStatic(CONST_MOTSEN_INITDONE)

#ifdef USE_MPU6050
DefineStatic(CONST_MOTSEN_MPU6050)
#endif
#ifdef USE_MPU6050_DMP
DefineStatic(CONST_MOTSEN_MPU6050_OFFSETS)
DefineStatic(CONST_MOTSEN_MPU6050_DMPINIT)
DefineStatic(CONST_MOTSEN_MPU6050_DMPPACK)
DefineStatic(CONST_MOTSEN_MPU6050_MEMFAIL)
DefineStatic(CONST_MOTSEN_MPU6050_CFGFAIL)
DefineStatic(CONST_MOTSEN_MPU6050_OVERFLOW)
#endif

#ifdef USE_BMP085
DefineStatic(CONST_MOTSEN_BMP085)
#endif

#ifdef USE_HMC5883L
DefineStatic(CONST_MOTSEN_HMC5883L)
#endif

#endif //DEBUG_OUTPUT

void CS::init()
{
	CONST_GENERAL_TAB = F("\t");
	CONST_GENERAL_SPACE = F(" ");
	CONST_GENERAL_NEWLINE = F("\n");
	CONST_GENERAL_DELIM = F("=========");
	CONST_GENERAL_OK = F("OK");
	CONST_GENERAL_FAILED = F("FAILED");
	CONST_GENERAL_YAW = F("Yaw: ");
	CONST_GENERAL_PITCH = F("Pitch: ");
	CONST_GENERAL_ROLL = F("Roll: ");
	CONST_GENERAL_UPTIME = F("Up: ");
	CONST_GENERAL_DAY = F("d");
	CONST_GENERAL_HOUR = F("h");
	CONST_GENERAL_MIN = F("m");
	CONST_GENERAL_SEC = F("s");
	CONST_GENERAL_CYCLE = F("Cycle: ");
	CONST_GENERAL_PRESSURE = F("Pressure: ");
	CONST_GENERAL_PRESSURE_HPA = F("hPa");
	CONST_GENERAL_TEMP = F("Temp: ");
	CONST_GENERAL_COMPASS = F("Compass: ");
	CONST_GENERAL_DISTANCE = F("Dist: ");
	CONST_GENERAL_CM = F("cm");

#ifdef DEBUG_OUTPUT
	CONST_DISPLAY_INIT = F("Initializing Display");
#ifdef USE_LCD_NOKIA_5110
	CONST_DISPLAY_NOKIA5110 = F("LCD NOKIA_5110 has been selected.");
#endif
#ifdef USE_LCD_ILI9341
	CONST_DISPLAY_ILI9341 = F("LCD ILI9341 has been selected.");
#endif
	CONST_DISPLAY_INITDONE = F("Display Initialization is finished.");

	CONST_I2C_INIT = F("Initializing I2C bus...");

	CONST_MOTSEN_INIT = F("Initializing Motion Sensors");
	CONST_MOTSEN_ACCELXYZ = F("Accel xyz: ");
	CONST_MOTSEN_GYROXYZ = F("Gyro xyz: ");
	CONST_MOTSEN_INITDONE = F("Motion Sensors Initialization is finished.");

#ifdef USE_MPU6050
	CONST_MOTSEN_MPU6050 = F("MPU6050...");
#endif
#ifdef USE_MPU6050_DMP
	CONST_MOTSEN_MPU6050_OFFSETS = F("MPU6050 internal sensor offsets:");
	CONST_MOTSEN_MPU6050_DMPINIT = F("Initializing MPU6050 DMP... ");
	CONST_MOTSEN_MPU6050_DMPPACK = F("MPU6050 DMP Packet Size: ");
	CONST_MOTSEN_MPU6050_MEMFAIL = F(" - Initial memory load failed.");
	CONST_MOTSEN_MPU6050_CFGFAIL = F(" - DMP Config updates failed.");
	CONST_MOTSEN_MPU6050_OVERFLOW = F("MPU6050 DMP Overflow!");
#endif
#ifdef USE_BMP085
	CONST_MOTSEN_BMP085 = F("BMP085...");
#endif
#ifdef USE_HMC5883L
	CONST_MOTSEN_HMC5883L = F("HMC5883L...");
#endif

#endif //DEBUG_OUTPUT
}

