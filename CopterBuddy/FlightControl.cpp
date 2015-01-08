//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Config.h"
#include "Consts.h"
#include "FlightControl.h"
#include "MotorsManager.h"
#include "MotionSensors.h"
#include "UpTime.h"
#include "Display.h"
#include "Comm.h"
#include "EEPROM\EEPROM.h"

#include <PID_v1\PID_v1.h>

//Specify the links and initial tuning parameters
double pidRollIn, pidRollOut, pidRollPoint;
double pidYawIn, pidYawOut, pidYawPoint;
double pidPitchIn, pidPitchOut, pidPitchPoint;
double CFG_ROLL_KP = PID_ROLL_KP, CFG_ROLL_KI = PID_ROLL_KI, CFG_ROLL_KD = PID_ROLL_KD,
		CFG_YAW_KP = PID_YAW_KP, CFG_YAW_KI = PID_YAW_KI, CFG_YAW_KD = PID_YAW_KD,
		CFG_PITCH_KP = PID_PITCH_KP, CFG_PITCH_KI = PID_PITCH_KI, CFG_PITCH_KD;
PID pidRoll(&pidRollIn, &pidRollOut, &pidRollPoint, CFG_ROLL_KP, CFG_ROLL_KI, CFG_ROLL_KD, DIRECT);
PID pidYaw(&pidYawIn, &pidYawOut, &pidYawPoint, CFG_YAW_KP, CFG_YAW_KI, CFG_YAW_KD, DIRECT);
PID pidPitch(&pidPitchIn, &pidPitchOut, &pidPitchPoint, CFG_PITCH_KP, CFG_PITCH_KI, CFG_PITCH_KD, DIRECT);

#ifdef USE_SAFE_MAX_THROTTLE
#define MOTOR_MAX_THROTTLE MOTOR_SAFE_MAX_THROTTLE
#endif

void FlightControlClass::init()
{
	state = FS_INACTIVE;
	Display.init();
	MotorsManager.init();
	MotionSensors.init();
	Comm.init();
	
	pidRoll.SetMode(AUTOMATIC);
	pidPitch.SetMode(AUTOMATIC);
	pidYaw.SetMode(AUTOMATIC);

	pidRoll.SetOutputLimits(-100, 100);
	pidPitch.SetOutputLimits(-100, 100);
	pidYaw.SetOutputLimits(-100, 100);

	pidRoll.SetSampleTime(PID_SAMPLE_TIME);
	pidPitch.SetSampleTime(PID_SAMPLE_TIME);
	pidYaw.SetSampleTime(PID_SAMPLE_TIME);

	pidRollPoint = 0;
	pidPitchPoint = 0;
	pidYawPoint = 0;

	pidRollOut = 0;
	pidPitchOut = 0;
	pidYawOut = 0;

	preControlTime = 0;
	enginesToggleTime = 0;
	configToggleTime = 0;
	displayUpdateTime = 0;
#ifdef USE_LOST_COMM_SHUTDOWN
	lastCommTime = 0;
#endif
	state = FS_ACTIVE;
}

void FlightControlClass::testFlight()
{
	state = FS_TESTFLIGHT;
	tfs = TFS_WARMUP;
	enginesToggleTime = UpTime.getMillis();
}

void FlightControlClass::update()
{
	MotionSensors.update();
	Comm.update(true);
	
	switch (state)
	{
	case FS_ACTIVE:
		if (Comm.latestDataType != CommClass::TYPE_NONE) {
			if (Comm.latestDataType == CommClass::TYPE_COMMAND) {
				switch (Comm.latestData.command.cmd) {
					case COMM_CMD_PING: DEBUG_PRINTLN(F("Got ping!")); break;
					case COMM_CMD_TOGGLE_ENGINES: if(enginesToggleTime == 0 || UpTime.getMillis() - enginesToggleTime > MOTOR_ARM_INTERVAL) {
						

						preControlTime = UpTime.getMillis();
						state = FS_PRE_CONTROL;
#ifdef USE_LOST_COMM_SHUTDOWN
						lastCommTime = UpTime.getMillis();
#endif
						DEBUG_PRINTLN(F("Switching to PreControl state!"));
					} break;
					case COMM_CMD_TOGGLE_CONFIG:  if (configToggleTime == 0 || UpTime.getMillis() - configToggleTime > PID_CONFIG_INTERVAL) {

						state = FS_PID_CONFIG;
						configToggleTime = UpTime.getMillis();
						DEBUG_PRINTLN(F("Switching to PID Config state!"));
					} break;
				}
			}
		} break;

	case FS_PID_CONFIG:
		{
			if (Comm.latestDataType != CommClass::TYPE_NONE) {
				if (Comm.latestDataType == CommClass::TYPE_COMMAND) {
					switch (Comm.latestData.command.cmd) {
					case COMM_CMD_TOGGLE_CONFIG:  if (UpTime.getMillis() - configToggleTime > PID_CONFIG_INTERVAL) {
						state = FS_ACTIVE;
						configToggleTime = UpTime.getMillis();
						DEBUG_PRINTLN(F("Switching to Active state!"));
					} break;
					}
				}
				else
				if (Comm.latestDataType == CommClass::TYPE_CONTROL)
				{
					const CommClass::CommControl& ctrl = Comm.latestData.control;
					if (ctrl.roll != 0) {
						CFG_ROLL_KP += ctrl.roll * 0.0005;
						pidRoll.SetTunings(CFG_ROLL_KP, CFG_ROLL_KI, CFG_ROLL_KD);
					}
					if (ctrl.pitch != 0) {
						CFG_PITCH_KP += ctrl.roll * 0.0005;
						pidPitch.SetTunings(CFG_PITCH_KP, CFG_PITCH_KI, CFG_PITCH_KD);
					}
				}
			}

			if ((MotionSensors.isMotionUpdateAvailable() || Comm.latestDataType == CommClass::TYPE_CONTROL) && state == FS_CONTROL)
				controlMotion();

		} break;

	case FS_PRE_CONTROL:
		if (UpTime.getMillis() - preControlTime >= PRE_CONTROL_INTERVAL) {
			motionThrottle = MOTOR_MIN_THROTTLE;
			MotorsManager.start();
			enginesToggleTime = UpTime.getMillis();
			state = FS_CONTROL;

#ifdef USE_LOST_COMM_SHUTDOWN
			lastCommTime = UpTime.getMillis();
#endif

			DEBUG_PRINTLN(F("Switching to Control state!"));
		} break;

	case FS_CONTROL:
#ifdef USE_LOST_COMM_SHUTDOWN
		if (UpTime.getMillis() - lastCommTime > LOST_COMM_TOLERANCE)
		{
			MotorsManager.stop();
			state = FS_ACTIVE;
			enginesToggleTime = UpTime.getMillis();
			DEBUG_PRINTLN(F("Emergency lost communication shutdown."));
		} else
#endif		

		if (Comm.latestDataType != CommClass::TYPE_NONE) {
#ifdef USE_LOST_COMM_SHUTDOWN
			lastCommTime = UpTime.getMillis();
#endif			
			if (Comm.latestDataType == CommClass::TYPE_COMMAND) {
				switch (Comm.latestData.command.cmd) {
					case COMM_CMD_PING: DEBUG_PRINTLN(F("Got ping!")); break;
					case COMM_CMD_TOGGLE_ENGINES:  if(UpTime.getMillis() - enginesToggleTime > MOTOR_DISARM_INTERVAL) {
						MotorsManager.stop();
						state = FS_ACTIVE;
						enginesToggleTime = UpTime.getMillis();
						DEBUG_PRINTLN(F("Switching to Active state!"));
					} break;
				}
			} else
			if (Comm.latestDataType == CommClass::TYPE_CONTROL)
			{
				const CommClass::CommControl& ctrl = Comm.latestData.control;
				int adjustedThrottle = map(ctrl.throttle, 0, 512, MOTOR_MIN_THROTTLE, MOTOR_MAX_THROTTLE);
				motionThrottle = adjustedThrottle;
				DEBUG_PRINT(F("Throttle: "));
				DEBUG_PRINTLN(motionThrottle);
			}
		} 

		if ((MotionSensors.isMotionUpdateAvailable() || Comm.latestDataType == CommClass::TYPE_CONTROL) && state == FS_CONTROL) //check state in case it was not moved to Active or Shutdown
			controlMotion();

		break; 

	case FS_TESTFLIGHT:
		{
			processTestFlight(UpTime.getMillis() - enginesToggleTime);
		} break;
	}

	displayUpdate();
}

void FlightControlClass::controlMotion()
{
	const VectorFloat& ypr = MotionSensors.getYawPitchRoll();
	pidRollIn = ypr.z;
	pidPitchIn = ypr.y;
	pidYawIn = ypr.x;

	pidRoll.Compute();
	pidPitch.Compute();
	pidYaw.Compute();

	applyThrottle();
}

void FlightControlClass::applyThrottle()
{
	//Configuration of the quad here is 4X 
	mt1 = motionThrottle + pidRollOut + pidPitchOut + pidYawOut;
	mt2 = motionThrottle - pidRollOut + pidPitchOut - pidYawOut;
	mt3 = motionThrottle - pidRollOut - pidPitchOut + pidYawOut;
	mt4 = motionThrottle + pidRollOut - pidPitchOut - pidYawOut;
	MotorsManager.setThrottle(mt1, mt2, mt3, mt4);
}

void FlightControlClass::displayUpdate()
{
	//Don't update display too many times if we fly
	if (UpTime.getMillis() - displayUpdateTime < DISPLAY_UPDATE_INTERVAL && state == FS_CONTROL) return;
	displayUpdateTime = UpTime.getMillis();

	Display.clear();

	switch (state)
	{
	case FS_ACTIVE:		
		Display.printUptime(0);
		Display.printCycleTime(UpTime.getMillisCycle(), UpTime.getLongestCycleMS(), -1);
		Display.printMotionMetrics(MotionSensors.getYawPitchRoll(), -1);
		break;
		
	case FS_PID_CONFIG:
		Display.printPIDs(0, CFG_YAW_KP, CFG_PITCH_KP, CFG_ROLL_KP, CFG_YAW_KI, CFG_PITCH_KI, CFG_ROLL_KI, CFG_YAW_KD, CFG_PITCH_KD, CFG_ROLL_KD);
		break;

	case FS_CONTROL:
		Display.printCycleTime(UpTime.getMillisCycle(), UpTime.getLongestCycleMS(), 0);
		Display.printMotionMetrics(MotionSensors.getYawPitchRoll(), -1, true);
		Display.printThrottle(motionThrottle, mt1, mt2, mt4, mt3, -1);
		break;
	}

	Display.display();
	UpTime.resetLongestMS();
}

void FlightControlClass::processTestFlight(unsigned long time)
{
	switch (tfs)
	{
		case TFS_WARMUP:
		{
			if (time / 1000 >= TFS_WARMUP_TIME) {
				MotorsManager.start();
				tfs = TFS_ENGINES_START;
				motionThrottle = MOTOR_MIN_THROTTLE;
				applyThrottle();
				DEBUG_PRINTLN(F("Warming up is done. Starting engines..."));
			}
		} break;
		case TFS_ENGINES_START:
		{
			if (time / 1000 >= TFS_ENGSTART_TIME) {
				//tfs = TFS_ENGINES_ACCELERATE;
				//DEBUG_PRINTLN(F("Accelerating"));
				tfs = TFS_ENGINES_PROGRAMMING;
				DEBUG_PRINTLN(F("Switching to programming mode."));
			}
		} break;

		case TFS_ENGINES_PROGRAMMING:
		{
			motionThrottle = (int)(MOTOR_MIN_THROTTLE + (MOTOR_MAX_THROTTLE - MOTOR_MIN_THROTTLE) * 0.1);
			/*
			if (Serial.available() > 0) {
				float f = Serial.parseFloat();
				if (f > 0.0)
				{
					pidPitch.SetTunings(f, pidPitch.GetKi(), pidPitch.GetKd());
					pidRoll.SetTunings(f, pidRoll.GetKi(), pidRoll.GetKd());

					//Updating
					Serial.print("KP value has been updated to: ");
					Serial.println(f);
					delay(1000);

				}
				 else
				 {
					 motionThrottle = MOTOR_ARM;
					 MotorsManager.stop();
					 tfs = TFS_ENGINES_STOP;
				 }
				
			}*/
		} break;

		case TFS_ENGINES_ACCELERATE:
		{
			if (time / 1000 >= TFS_ENGSTART_TIME + TFS_ACCEL_TIME) 
			{
				DEBUG_PRINTLN(F("Acceleration is finished, descending now..."));
				tfs = TFS_ENGINES_DECELERATE;
			} else
			{
				int accelRange = (MOTOR_MAX_THROTTLE - MOTOR_MIN_THROTTLE) * (TFS_ACCEL_MAX / 100.f);
				unsigned long elapsedAccelMillis = time - TFS_ENGSTART_TIME * 1000;
				int throttlePower = MOTOR_MIN_THROTTLE + accelRange * elapsedAccelMillis / (float)(TFS_ACCEL_TIME * 1000.f);

				motionThrottle = throttlePower;
				applyThrottle();
				//Engines throttle
				DEBUG_PRINT(F("Throttle: "));
				DEBUG_PRINTLN(throttlePower);
			}
		} break;

		case TFS_ENGINES_DECELERATE:
		{
			if (time / 1000 >= TFS_ENGSTART_TIME + TFS_ACCEL_TIME + TFS_DECEL_TIME)
			{
				DEBUG_PRINTLN(F("Deceleration is finished, stop now."));
				tfs = TFS_ENGINES_STOP;
				MotorsManager.stop();
			}
			else
			{				
				int decelRange = (MOTOR_MAX_THROTTLE - MOTOR_MIN_THROTTLE) * (TFS_ACCEL_MAX / 100.f);
				unsigned long elapsedDecelMillis = time - (TFS_ENGSTART_TIME + TFS_ACCEL_TIME) * 1000;
				int throttlePower = MOTOR_MIN_THROTTLE + decelRange * (1.0f - elapsedDecelMillis / (float)(TFS_DECEL_TIME * 1000.f));
				motionThrottle = throttlePower;
				applyThrottle();
				//Engines throttle
				DEBUG_PRINT(F("Throttle: "));
				DEBUG_PRINTLN(throttlePower);
			}
		} break;
		
	}
}


FlightControlClass FlightControl;

