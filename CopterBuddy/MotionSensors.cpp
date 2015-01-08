//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Config.h"
#include "MotionSensors.h"

#ifdef USE_MPU6050_DMP 
	#include <MPU6050\MPU6050_6Axis_MotionApps20.h>
#else
	#ifdef USE_MPU6050
		#include <MPU6050\MPU6050.h>
	#endif
#endif

#ifdef USE_BMP085
	#include <BMP085\BMP085.h>
#endif

#ifdef USE_HMC5883L
	#include <HMC5883L\HMC5883L.h>
#endif //USE_HMC5883L

#include "Consts.h"

#ifdef USE_MPU6050 || USE_MPU6050_DMP
struct ModuleMPU6050{
	MPU6050 module;
	bool active;
	bool dmpActive;
	uint16_t dmpPacketSize;		// expected DMP packet size (default is 42 bytes)
	uint16_t dmpFifoCount;		// count of all bytes currently in FIFO
	uint8_t dmpFifoBuffer[64];	// FIFO storage buffer
	ModuleMPU6050() { active = false; dmpActive = false; dmpFifoCount = 0; }
} module_mpu6050;
#endif

#ifdef USE_BMP085
struct ModuleBMP085 {
	BMP085 module;
	bool active;
} module_bmp085;
#endif

#ifdef USE_HMC5883L
struct ModuleHMC5883L {
	HMC5883L module;
	bool active;
} module_hmc5883l;
#endif

const VectorInt16& MotionSensorsClass::getGyroData()
{
	return gyroCurrent;
}

const VectorInt16& MotionSensorsClass::getAccelData()
{
	return accelCurrent;
}

const Quaternion& MotionSensorsClass::getOrientationQuat()
{
	return orientationQuat;
}

const VectorFloat& MotionSensorsClass::getYawPitchRoll()
{
	return yawPitchRoll;
}

const bool MotionSensorsClass::isMotionUpdateAvailable() {
	return motionUpdateAvailable;
}

const float MotionSensorsClass::getAtmosPressure() {
	return atmosPressure;
}

const float MotionSensorsClass::getAtmosTemperature() {
	return atmosTemp;
}

const float MotionSensorsClass::getAtmosAltitude() {
	return atmosAlt;
}

const VectorInt16& MotionSensorsClass::getCompassRaw()
{
	return compassRaw;
}

const float MotionSensorsClass::getCompassHeading()
{
	return compassHeading;
}

void MotionSensorsClass::init()
{
	motionUpdateAvailable = false;

	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINT(CS::CONST_MOTSEN_INIT);
	DEBUG_PRINTLN(CS::CONST_GENERAL_DELIM);
	/* enable Arduino interrupt detection
	Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
	attachInterrupt(0, dmpDataReady, RISING);
	mpuIntStatus = mpu.getIntStatus();
	*/

	/**************************************
				MPU 6050 Module
	**************************************/
#ifdef USE_MPU6050 || USE_MPU6050_DMP
	DEBUG_PRINT(CS::CONST_MOTSEN_MPU6050);
	module_mpu6050.module.initialize();
	module_mpu6050.active = module_mpu6050.module.testConnection();
	DEBUG_PRINTLN(module_mpu6050.active ? CS::CONST_GENERAL_OK : CS::CONST_GENERAL_FAILED);
	if (module_mpu6050.active) {
#ifdef _DEBUG
		DEBUG_PRINTLN(CS::CONST_MOTSEN_MPU6050_OFFSETS);
		// -76	-2359	1688	0	0	0
		DEBUG_PRINT(CS::CONST_MOTSEN_ACCELXYZ);
		DEBUG_PRINT(module_mpu6050.module.getXAccelOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // -76
		DEBUG_PRINT(module_mpu6050.module.getYAccelOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // -2359
		DEBUG_PRINT(module_mpu6050.module.getZAccelOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // 1688
		DEBUG_PRINT(CS::CONST_MOTSEN_GYROXYZ);
		DEBUG_PRINT(module_mpu6050.module.getXGyroOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // 0
		DEBUG_PRINT(module_mpu6050.module.getYGyroOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // 0
		DEBUG_PRINT(module_mpu6050.module.getZGyroOffset()); DEBUG_PRINT(CS::CONST_GENERAL_TAB); // 0
		DEBUG_PRINT(CS::CONST_GENERAL_NEWLINE);
#endif //_DEBUG
		/*
		accelgyro.setXGyroOffset(220);
		accelgyro.setYGyroOffset(76);
		accelgyro.setZGyroOffset(-85);
		Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
		Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
		Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
		Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
		Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
		Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
		Serial.print("\n");
		*/

#ifdef USE_MPU6050_DMP
		DEBUG_PRINT(CS::CONST_MOTSEN_MPU6050_DMPINIT);
		uint8_t dmpInitStatus = module_mpu6050.module.dmpInitialize();
		switch (dmpInitStatus) {
			case 0: 
				{
					  DEBUG_PRINTLN(CS::CONST_GENERAL_OK);
					module_mpu6050.module.setDMPEnabled(true);
					module_mpu6050.dmpActive = true;
					module_mpu6050.dmpPacketSize = module_mpu6050.module.dmpGetFIFOPacketSize();
					DEBUG_PRINT(CS::CONST_MOTSEN_MPU6050_DMPPACK);
					DEBUG_PRINTLN(module_mpu6050.dmpPacketSize);
				}; break;
			case 1: DEBUG_PRINT(CS::CONST_GENERAL_FAILED); DEBUG_PRINTLN(CS::CONST_MOTSEN_MPU6050_MEMFAIL); break;
			case 2: DEBUG_PRINT(CS::CONST_GENERAL_FAILED); DEBUG_PRINTLN(CS::CONST_MOTSEN_MPU6050_CFGFAIL); break;
		}
#endif //USE_MPU6050_DMP
	}

#endif //USE_MPU6050 || USE_MPU6050_DMP

#ifdef USE_BMP085
	/**************************************
				BMP085 Module
	**************************************/
	DEBUG_PRINT(CS::CONST_MOTSEN_BMP085);
	module_bmp085.module.initialize();
	module_bmp085.active = module_bmp085.module.testConnection();
	DEBUG_PRINTLN(module_bmp085.active ? CS::CONST_GENERAL_OK : CS::CONST_GENERAL_FAILED);
#endif //USE_BMP085

#ifdef USE_HMC5883L
	/**************************************
				HMC5883L Module
	**************************************/
	DEBUG_PRINT(CS::CONST_MOTSEN_HMC5883L);
	module_hmc5883l.module.initialize();
	module_hmc5883l.active = module_hmc5883l.module.testConnection();
	DEBUG_PRINTLN(module_hmc5883l.active ? CS::CONST_GENERAL_OK : CS::CONST_GENERAL_FAILED);
#endif

	DEBUG_PRINTLN(CS::CONST_MOTSEN_INITDONE);
	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINTLN(CS::CONST_GENERAL_DELIM);
}

void MotionSensorsClass::update() 
{
	motionUpdateAvailable = false;

#ifdef USE_MPU6050 || USE_MPU6050_DMP
	if (module_mpu6050.active) {
#ifndef USE_MPU6050_DMP
		module_mpu6050.module.getMotion6(&accelCurrent.x, &accelCurrent.y, &accelCurrent.z,
			&gyroCurrent.x, &gyroCurrent.y, &gyroCurrent.z);

		Serial.println("***************************************************************************");
		Serial.println("NOT IMPLEMENTED: Motion MPU6050 RawData Is not finished!");
		Serial.println("***************************************************************************");
#endif
#ifdef USE_MPU6050_DMP
		if (module_mpu6050.dmpActive) {
			module_mpu6050.dmpFifoCount = module_mpu6050.module.getFIFOCount();
			//Serial.print("DMP FIFO Count: "); Serial.print(module_mpu6050.dmpFifoCount);

			//Check for buffer overflow
			if ((module_mpu6050.module.getIntStatus() & 0x10) || (module_mpu6050.dmpFifoCount >= 1024)) {
				//Buffer overflow, reset and start from scratch
				DEBUG_PRINT(CS::CONST_MOTSEN_MPU6050_OVERFLOW);
				module_mpu6050.module.resetFIFO();
				module_mpu6050.dmpFifoCount = 0;
			}

			//Process data if any is available
			if (module_mpu6050.dmpFifoCount >= module_mpu6050.dmpPacketSize) {
				
				do {
					module_mpu6050.module.getFIFOBytes(module_mpu6050.dmpFifoBuffer, module_mpu6050.dmpPacketSize);
					module_mpu6050.dmpFifoCount -= module_mpu6050.dmpPacketSize;
					//Skip all packets until the last one. We need the most recent data only.
				} while (module_mpu6050.dmpFifoCount >= module_mpu6050.dmpPacketSize);

				VectorFloat gravity;    // [x, y, z]            gravity vector
				module_mpu6050.module.dmpGetQuaternion(&orientationQuat, module_mpu6050.dmpFifoBuffer);
				module_mpu6050.module.dmpGetEuler(eulerAngles.xyz, &orientationQuat);
				module_mpu6050.module.dmpGetGravity(&gravity, &orientationQuat);
				module_mpu6050.module.dmpGetYawPitchRoll(yawPitchRoll.xyz, &orientationQuat, &gravity);
				motionUpdateAvailable = true;
			}
		}
#endif //USE_MPU6050_DMP
	}
		
#endif //USE_MPU6050 || USE_MPU6050_DMP

#ifdef USE_BMP085
	if (module_bmp085.active) {
		module_bmp085.module.setControl(BMP085_MODE_TEMPERATURE);
		
		// wait appropriate time for conversion (4.5ms delay)
		//Temperature sampling example
		/*
		unsigned long lastMicros = micros();
		while (micros() - lastMicros < module_bmp085.module.getMeasureDelayMicroseconds());
		atmosTemp = module_bmp085.module.getTemperatureC();
		*/

		if (atmosMeasureStart == 0 || atmosMeasureStart >= module_bmp085.module.getMeasureDelayMilliseconds()) {
			if (atmosMeasureStart != 0)
			{
				// read calibrated pressure value in Pascals (Pa)
				atmosPressure = module_bmp085.module.getPressure();
				atmosAlt = module_bmp085.module.getAltitude(atmosPressure);
				/*
				Serial.print("Baro: ");
				Serial.print(atmosPressure);
				Serial.print(" temp: ");
				Serial.print(atmosTemp);
				Serial.print(" alt: ");
				Serial.println(atmosAlt);
				*/
			}
			module_bmp085.module.setControl(BMP085_MODE_PRESSURE_3); // request pressure (3x oversampling mode, high detail, 25.5ms delay)
			atmosMeasureStart = millis();
		}
	}
#endif //USE_BMP085

#ifdef USE_HMC5883L
	if (module_hmc5883l.active) {
		module_hmc5883l.module.getHeading(&compassRaw.x, &compassRaw.y, &compassRaw.z);
		compassHeading = atan2(compassRaw.y, compassRaw.x);
		if (compassHeading < 0) compassHeading += 2 * M_PI;

		/*
		Serial.print("Compass: ");
		Serial.println(compassHeading);
		*/
	}
#endif
}


MotionSensorsClass MotionSensors;

