//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "MotorsManager.h"

void MotorsManagerClass::init()
{
#ifdef MOTOR_CONFIG_4X
	pinMode(MOTOR_4X_1_PIN, OUTPUT);
	pinMode(MOTOR_4X_2_PIN, OUTPUT);
	pinMode(MOTOR_4X_3_PIN, OUTPUT);
	pinMode(MOTOR_4X_4_PIN, OUTPUT);
	throttle1 = throttle2 = throttle3 = throttle4 = 0;
	update();
	setThrottle(MOTOR_ARM, MOTOR_ARM, MOTOR_ARM, MOTOR_ARM);
	delay(2000);
#endif
}

void MotorsManagerClass::update()
{
	analogWrite(MOTOR_4X_1_PIN, throttle1);
	analogWrite(MOTOR_4X_2_PIN, throttle2);
	analogWrite(MOTOR_4X_3_PIN, throttle3);
	analogWrite(MOTOR_4X_4_PIN, throttle4);
}

void MotorsManagerClass::start()
{
#ifdef MOTOR_CONFIG_4X
	setThrottle(MOTOR_MIN_THROTTLE, MOTOR_MIN_THROTTLE, MOTOR_MIN_THROTTLE, MOTOR_MIN_THROTTLE);
#endif
}

void MotorsManagerClass::stop()
{
#ifdef MOTOR_CONFIG_4X
	setThrottle(MOTOR_ARM, MOTOR_ARM, MOTOR_ARM, MOTOR_ARM);
#endif
}

#ifdef MOTOR_CONFIG_4X
void MotorsManagerClass::setThrottle(uint16_t pwr1, uint16_t pwr2, uint16_t pwr3, uint16_t pwr4)
{
	if (pwr1 == MOTOR_ARM) throttle1 = pwr1; else throttle1 = constrain(pwr1, MOTOR_MIN_THROTTLE, MOTOR_MAX_THROTTLE);
	if (pwr2 == MOTOR_ARM) throttle2 = pwr2; else throttle2 = constrain(pwr2, MOTOR_MIN_THROTTLE, MOTOR_MAX_THROTTLE);
	if (pwr3 == MOTOR_ARM) throttle3 = pwr3; else throttle3 = constrain(pwr3, MOTOR_MIN_THROTTLE, MOTOR_MAX_THROTTLE);
	if (pwr4 == MOTOR_ARM) throttle4 = pwr4; else throttle4 = constrain(pwr4, MOTOR_MIN_THROTTLE, MOTOR_MAX_THROTTLE);
	update();
}
#endif


MotorsManagerClass MotorsManager;

