//Copyright 2014, Alex Khilko.
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "KeyesJoystick.h"

#define JOYSTICK_READ_TIME 100 //microseconds
#define THUMB_IGNORE_THRESHHOLD 3
#define FILTER_BY_THRESHHOLD(v) if (v >= -THUMB_IGNORE_THRESHHOLD && v <= THUMB_IGNORE_THRESHHOLD) v = 0;

void KeyesJoystick::init(const uint8_t& pinX, const uint8_t& pinY, const uint8_t& pinBtn, const int16_t& offsetX, const int16_t& offsetY, bool invX)
{
	xPin = pinX;
	yPin = pinY;
	btnPin = pinBtn;
	xOffset = offsetX;
	yOffset = offsetY;
	pinMode(btnPin, INPUT_PULLUP);
	xValue = 0;
	yValue = 0;
	buttonPressed = false;
	invertX = invX;
}

void KeyesJoystick::update()
{
	buttonPressed = digitalRead(btnPin) == 0;

	delayMicroseconds(JOYSTICK_READ_TIME * 2);
	xValue = analogRead(xPin); 

	//correct values to be -512 to 512 instead of 0 to 1023
	if (xValue < xOffset) xValue = map(xValue, 0, xOffset, -512, 0); else
	if (xValue > xOffset) xValue = map(xValue, xOffset, 1023, 0, 512); else
		xValue = 0;
	if (invertX) xValue = -xValue;

	// this small pause is needed between reading
	// analog pins, otherwise we get the same value twice
	delayMicroseconds(JOYSTICK_READ_TIME * 2);
	yValue = analogRead(yPin); 

	//correct values to be -512 to 512 instead of 0 to 1023, also y is inverted so we want UP to be positive
	if (yValue < xOffset) yValue = map(yValue, 0, yOffset, -512, 0); else
	if (yValue > xOffset) yValue = map(yValue, yOffset, 1023, 0, 512); else
		yValue = 0;
	yValue = -yValue;

	FILTER_BY_THRESHHOLD(xValue);
	FILTER_BY_THRESHHOLD(yValue);
}

#ifdef DEBUG_FUNC
void KeyesJoystick::printRaw()
{
	Serial.print(F("Joystick. X: "));
	delayMicroseconds(JOYSTICK_READ_TIME * 2);
	Serial.print(analogRead(xPin));

	Serial.print(F(" Y: "));
	delayMicroseconds(JOYSTICK_READ_TIME * 2);
	Serial.println(analogRead(yPin));
}
#endif

const int16_t& KeyesJoystick::getValueX() const
{
	return xValue;
}

const int16_t& KeyesJoystick::getValueY() const
{
	return yValue;
}

const bool KeyesJoystick::isButtonPressed() const
{
	return buttonPressed;
}