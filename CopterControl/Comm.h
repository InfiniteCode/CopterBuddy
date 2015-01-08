//Copyright 2014, Alex Khilko.
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef _COMM_h
#define _COMM_h

#include "Config.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define COMM_CMD_PING			0
#define COMM_CMD_TOGGLE_ENGINES 1
#define COMM_CMD_GOHOME			2

#define COMM_CMD_TOGGLE_CONFIG  3

#define COMM_CMD_FLYMODE		7		//Default FLY mode is HOLD_ALTITUDE
#define		FLYMODE_FREE		  0		//Will go down slowly unless Throttle is added
#define		FLYMODE_HOLD_ALTITUDE 1		//Hold altitude steady
#define		FLYMODE_HOLD_POSITION 2		//This includes Altitude as well

#define COMMCOMMAND(name, command) CommCommand name; name.dataType = TYPE_COMMAND; name.auth = WIRELESS_AUTH; name.cmd = command;

typedef uint32_t auth_t;

class CommClass
{
protected:
public:
	enum CommDataType
	{
		TYPE_NONE = 0,
		TYPE_COMMAND = 1,
		TYPE_COMMAND8 = 2,
		TYPE_CONTROL = 3,
		TYPE_STATE = 4
	};

	struct CommCommand
	{
		auth_t	 auth;
		uint8_t  dataType;
		uint16_t cmd;
#ifdef WIRELESS_TRANSFER
		CommCommand(const uint16_t& command)
		{
			dataType = TYPE_COMMAND;
			auth = WIRELESS_AUTH; cmd = command;
		}
#endif
	};

	struct CommCommand8
	{
		auth_t	auth;
		uint8_t dataType;
		uint16_t cmd;
		uint8_t  data;
#ifdef WIRELESS_TRANSFER
		CommCommand8(const uint16_t& command, const uint8_t& cmdData)
		{
			dataType = TYPE_COMMAND8;
			auth = WIRELESS_AUTH; cmd = command; data = cmdData;
		}
#endif
	};

	struct CommControl
	{
		auth_t	 auth;
		uint8_t  dataType;
		int16_t  roll;		//Left Thumb - X
		int16_t  pitch;		//Left Thumb - Y
		int16_t  yaw;		//Right Thumb - X
		int16_t  throttle; //Right Thumb - Y
#ifdef WIRELESS_TRANSFER
		CommControl(const int16_t& Roll, const int16_t& Pitch, const int16_t& Yaw, const int16_t& Throttle)
		{
			dataType = TYPE_CONTROL;
			auth = WIRELESS_AUTH; roll = Roll; pitch = Pitch; yaw = Yaw; throttle = Throttle;
		}

		bool isZero() const { return roll == 0 && pitch == 0 && yaw == 0 && throttle == 0; }
#endif
	};


	struct CommState
	{
		auth_t auth;
		uint8_t dataType;
		float	roll;
		float	pitch;
		float	yaw;
		CommState(const float Roll, const float Pitch, const float Yaw)
		{
			dataType = TYPE_STATE;
			auth = WIRELESS_AUTH;
			roll = Roll; pitch = Pitch; yaw = Yaw;
		}
	};


	void init();
	void sendCommand(const CommCommand& cmd);
	void sendCommand(const CommCommand8& cmd);
	void sendControl(const CommControl& ctrl);
	void sendState(const CommState& state);
	void update(bool clearLatest = true);

	CommDataType latestDataType;
#ifdef WIRELESS_RECEIVE
	union
	{
		CommCommand command;
		CommCommand8 command8;
		CommControl control;
	} latestData;
	
#endif
};

extern CommClass Comm;

#endif

