//Copyright 2014, Alex Khilko.
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Comm.h"
#include "Config.h"

#ifdef USE_433MHZ
#include <VirtualWire\VirtualWire.h>
#define SEND_WITH_WAIT(data) { vw_send((uint8_t *)&data, sizeof(data)); vw_wait_tx(); }
#endif

#ifdef USE_NRF24L
#include <SPI\SPI.h>
#include <RF24\RF24.h>
#include <RF24\RF24_config.h>

RF24 rf24_module(WIRELESS_NRF24L_CE, WIRELESS_NRF24L_CSN);
#define MAX_PAYLOAD sizeof(CommClass::CommControl)
#define SEND_WITH_WAIT(data) { rf24_module.stopListening(); rf24_module.write(&data, sizeof(data)); rf24_module.startListening(); }
#endif

#ifdef USE_APC_220
#ifdef WIRELESS_TRANSFER
#include <SoftwareSerial.h>
//SoftwareSerial apc220(WIRELESS_APC220_RX, WIRELESS_APC220_TX);
//#define SEND_WITH_WAIT(data) { apc220.write( (const uint8_t *)(&data), sizeof(data)); }
#define SEND_WITH_WAIT(data) { Serial.write( (const uint8_t *)(&data), sizeof(data)); }
#endif
#ifdef WIRELESS_RECEIVE
#define SEND_WITH_WAIT(data) { Serial1.write( (const uint8_t *)(&data), sizeof(data)); }
#endif
#endif


void CommClass::init()
{
#ifdef USE_433MHZ
#ifdef WIRELESS_TRANSFER
	vw_set_ptt_inverted(true);
	vw_set_tx_pin(WIRELESS_433MHZ_TRANSFER_PIN);
	vw_setup(WIRELESS_SPEED);// speed of data transfer bits per second
#endif
#ifdef WIRELESS_RECEIVE
	vw_set_ptt_inverted(true);
	vw_set_rx_pin(WIRELESS_433MHZ_RECEIVE_PIN);
	vw_setup(WIRELESS_SPEED);  // Bits per sec
	vw_rx_start();       // Start the receiver PLL running
	latestDataType = TYPE_NONE;
#endif
#endif //USE_433MHZ

#ifdef USE_NRF24L
	rf24_module.begin();
	rf24_module.setAutoAck(1);							// Ensure autoACK is enabled
	rf24_module.enableAckPayload();						// Allow optional ack payloads
	rf24_module.setRetries(0, 10);						// Smallest time between retries, max no. of retries
	rf24_module.setPayloadSize(MAX_PAYLOAD);            // Here we are sending 1-byte payloads to test the call-response speed
	rf24_module.setDataRate(RF24_1MBPS);
	
#ifdef WIRELESS_TRANSFER
	rf24_module.openWritingPipe((uint8_t*)WIRELESS_QUAD_ADDR);   
	rf24_module.openReadingPipe(1, (uint8_t*)WIRELESS_QUAD_CTRL);
#endif
#ifdef WIRELESS_RECEIVE
	rf24_module.openWritingPipe((uint8_t*)WIRELESS_QUAD_CTRL);   
	rf24_module.openReadingPipe(1, (uint8_t*)WIRELESS_QUAD_ADDR);
#endif

	rf24_module.startListening();						// Start listening
	rf24_module.powerUp();
	rf24_module.printDetails();							// Dump the configuration of the rf unit for debugging
#endif //USE_NRF24L

#ifdef USE_APC_220
	//apc220.begin(WIRELESS_SPEED);
#endif //USE_APC_220
}


void CommClass::sendCommand(const CommCommand& cmd)
{
	SEND_WITH_WAIT(cmd);
}

void CommClass::sendCommand(const CommCommand8& cmd)
{
	SEND_WITH_WAIT(cmd);
}

void CommClass::sendControl(const CommControl& ctrl)
{
	SEND_WITH_WAIT(ctrl);
}

void CommClass::sendState(const CommState& ctrl)
{
	SEND_WITH_WAIT(ctrl);
}

#ifdef USE_NRF24L
void CommClass::update(bool clearLatest)
{
	if (clearLatest) latestDataType = TYPE_NONE;

#ifdef WIRELESS_RECEIVE
	if (rf24_module.available((uint8_t*)WIRELESS_QUAD_ADDR))
#endif
#ifdef WIRELESS_TRANSFER
	if (rf24_module.available((uint8_t*)WIRELESS_QUAD_CTRL))
#endif
	{
		uint8_t buf[MAX_PAYLOAD];
		rf24_module.read(buf, MAX_PAYLOAD);
		//Authorize first
		auth_t authToken = ((auth_t*)buf)[0];
		if (authToken == WIRELESS_AUTH)
		{
			latestDataType = (CommDataType)buf[sizeof(auth_t)];
			if (latestDataType == TYPE_STATE)
			{
				Serial.print("YPR: ");
				CommState state(0, 0, 0);
				memcpy(&state, buf, sizeof(CommState));
				Serial.print(state.yaw);
				Serial.print(" ");
				Serial.print(state.pitch);
				Serial.print(" ");
				Serial.println(state.roll);
			}
				
#ifdef WIRELESS_RECEIVE
			switch (latestDataType)
			{
			case TYPE_COMMAND: memcpy(&latestData.command, buf, sizeof(CommCommand)); break;
			case TYPE_COMMAND8: memcpy(&latestData.command8, buf, sizeof(CommCommand8)); break;
			case TYPE_CONTROL: memcpy(&latestData.control, buf, sizeof(CommControl)); break;
			default:
				latestDataType = TYPE_NONE;
			}
#endif //WIRELESS_RECEIVE
		}
	}
}
#endif //USE_NRF24L

#ifdef USE_433MHZ

#ifdef WIRELESS_RECEIVE
void CommClass::update(bool clearLatest)
{
	if (clearLatest) latestDataType = TYPE_NONE;

	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;
	if (vw_get_message(buf, &buflen)) // Non-blocking
	{
		//Authorize first
		if (buflen > sizeof(auth_t))
		{
			auth_t authToken = *((auth_t*)buf);
			if (authToken == WIRELESS_AUTH)
			{
				latestDataType = (CommDataType)buf[sizeof(auth_t)];
				switch (latestDataType)
				{
				case TYPE_COMMAND: memcpy(&latestData.command, buf, sizeof(CommCommand)); break;
				case TYPE_COMMAND8: memcpy(&latestData.command8, buf, sizeof(CommCommand8)); break;
				case TYPE_CONTROL: memcpy(&latestData.control, buf, sizeof(CommControl)); break;
				default:
					latestDataType = TYPE_NONE;
				}
			}
		}
	}
}
#endif //WIRELESS_RECEIVE

#endif //USE_433MHZ

#ifdef USE_APC_220
#ifdef WIRELESS_RECEIVE
void CommClass::update(bool clearLatest)
{
	if (clearLatest) latestDataType = TYPE_NONE;
	
	if (apc220.available() > 0){
		Serial.print("In: ");
		Serial.println(apc220.read());
	} 
	
	//TODO Add support for APC220
}
#endif //WIRELESS_RECEIVE
#endif //USE_APC_220

CommClass Comm;

