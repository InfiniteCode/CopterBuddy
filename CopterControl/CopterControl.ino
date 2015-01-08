//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Config.h"

#ifdef USE_APC_220
#ifdef WIRELESS_TRANSFER
#include <SoftwareSerial.h>
#endif
#endif

#ifdef USE_433MHZ
#include <VirtualWire.h>
#endif

#ifdef USE_NRF24L
#include <SPI.h>
#include <RF24_config.h>
#include <RF24.h>
#endif

#include "Comm.h"
#include "KeyesJoystick.h"

#define LED_PIN 13
KeyesJoystick leftThumb, rightThumb;
unsigned long leftThumbPressTime = 0;
unsigned long doubleThumbPressTime = 0;
unsigned long lastPingTime = 0;

void setup()
{
	Serial.begin(SERIAL_BAUD);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	//Initialize devices
	leftThumb.init(PIN_THUMB_LEFT_X, PIN_THUMB_LEFT_Y, PIN_THUMB_LEFT_BTN, THUMB_LEFT_OFF_X, THUMB_LEFT_OFF_Y, true);
	rightThumb.init(PIN_THUMB_RIGHT_X, PIN_THUMB_RIGHT_Y, PIN_THUMB_RIGHT_BTN, THUMB_RIGHT_OFF_X, THUMB_RIGHT_OFF_Y, false);
	Comm.init();
	
	//Ready for control
	Serial.println(F("Initialization is done."));
}

void loop()
{
	//Comm.update();

	leftThumb.update();
	rightThumb.update();
	unsigned long curTime = millis();

	//Look if we need to start/stop engines
	bool bothThumbsPressed = leftThumb.isButtonPressed() && rightThumb.isButtonPressed();
	if (bothThumbsPressed)
	{
		unsigned long currentMillis = millis();
		if (doubleThumbPressTime == 0)
			doubleThumbPressTime = currentMillis;
		else
		{
			if (currentMillis - doubleThumbPressTime >= TIMER_START_STOP)
			{
				Serial.println(F("Sending start/stop engines command."));
				Comm.sendCommand(CommClass::CommCommand(COMM_CMD_TOGGLE_ENGINES));
				lastPingTime = curTime;
			}
		}

	}
	else
		doubleThumbPressTime = 0;

	
	if (!bothThumbsPressed)
	{
		//Look if we need to enter configuration mode
		if (leftThumb.isButtonPressed()) {
			unsigned long currentMillis = millis();
			if (leftThumbPressTime == 0)
				leftThumbPressTime = currentMillis;
			else
			{
				if (currentMillis - leftThumbPressTime >= TIMER_CONFIG_TOGGLE)
				{
					Serial.println(F("Sending config command."));
					Comm.sendCommand(CommClass::CommCommand(COMM_CMD_TOGGLE_CONFIG));
					lastPingTime = curTime;
				}
			}
		}
		else {
			//We don't want to send anything else except the Toggle Engines if both thumbs are pressed.
			//Check thumb states, if we have some shift - send it, if not then send ping
			const CommClass::CommControl controlValues = CommClass::CommControl(leftThumb.getValueX(), leftThumb.getValueY(),
				rightThumb.getValueX(), rightThumb.getValueY());
			if (!controlValues.isZero())
			{
				Comm.sendControl(controlValues);
				
				Serial.print(F("Control: RPY "));
				Serial.print(controlValues.roll);
				Serial.print(F(" "));
				Serial.print(controlValues.pitch);
				Serial.print(F(" "));
				Serial.print(controlValues.yaw);
				Serial.print(F(" Throttle "));
				Serial.println(controlValues.throttle);
				lastPingTime = curTime;
			}
			else
			{
				//If we don't send ping, copter will consider that control is lost and will return
				//to the start location. If location is unknown, it will hover over the same
				//spot without movement and wait for the connection to be re-established.
				if (curTime - lastPingTime >= WIRELESS_PING_INTERVAL)
				{
					Comm.sendControl(controlValues);
					//Comm.sendCommand(CommClass::CommCommand(COMM_CMD_PING));
					//Serial.println(F("Ping."));
				}
			}

		}
	}

	//Serial.print("Left: "); leftThumb.printRaw();
	//Serial.print("Right: "); rightThumb.printRaw();
}
