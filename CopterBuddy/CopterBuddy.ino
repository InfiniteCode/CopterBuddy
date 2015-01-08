//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Consts.h"
#include "Config.h"

#ifdef USE_LCD_NOKIA_5110
	#include <SPI.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_PCD8544.h>
#endif //USE_LCD_NOKIA_5110

#ifdef USE_LCD_ILI9341
	#include <SPI.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_ILI9341.h>
#endif

#ifdef USE_MPU6050_DMP 
	//#include <MPU6050_6Axis_MotionApps20.h> //Not needed to compile
#else
	#ifdef USE_MPU6050
		#include <MPU6050.h>
	#endif
#endif //USE_MPU6050_DMP

#ifdef USE_BMP085
	#include <BMP085.h>
#endif //USE_BMP085

#ifdef USE_HMC5883L
	#include <HMC5883L.h>
#endif //USE_HMC5883L

#ifdef USE_HC_SR04
#include <NewPing.h>
#endif //USE_HC_SR04

#ifdef USE_433MHZ
#include <VirtualWire.h>
#endif //USE_433MHZ

#ifdef USE_NRF24L
#include <SPI.h>
#include <RF24_config.h>
#include <RF24.h>
#endif

#include <I2Cdev.h>
#include <PID_v1.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif

#include "Config.h"
#include "Consts.h"
#include "Helper3DMath.h"
#include "I2CBus.h"

#include "UpTime.h"
#include "Display.h"
#include "FlightControl.h"
#include "Comm.h"
#include "MotorsManager.h"
#include "MotionSensors.h"

void setup()
{
	CS::init();
	Serial.begin(SERIAL_BAUD);

	UpTime.init();
	I2CBus.init();

	FlightControl.init();
}

void loop()
{
	UpTime.update();
	FlightControl.update();
}

