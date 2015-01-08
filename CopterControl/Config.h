//Copyright 2014, Alex Khilko.
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef COPTER_CONFIG
#define COPTER_CONFIG

#define DEBUG_FUNC
#define SERIAL_BAUD 9600

#define TIMER_START_STOP 2000	//Time in milliseconds to start/stop engines
#define TIMER_CONFIG_TOGGLE 2000

//Joysticks configuration
//Left thumb
#define PIN_THUMB_LEFT_X 2 //Analog pin
#define PIN_THUMB_LEFT_Y 3 //Analog pin
#define PIN_THUMB_LEFT_BTN 6 //Digital pin with PULLUP
#define THUMB_LEFT_OFF_X 496 //Default value while in the middle
#define THUMB_LEFT_OFF_Y 507 //Default value while in the middle
//Right thumb
#define PIN_THUMB_RIGHT_X 0 //Analog pin
#define PIN_THUMB_RIGHT_Y 1 //Analog pin
#define PIN_THUMB_RIGHT_BTN 7 //Digital pin with PULLUP
#define THUMB_RIGHT_OFF_X 479 //Default value while in the middle
#define THUMB_RIGHT_OFF_Y 502 //Default value while in the middle

//Wireless module
#define WIRELESS_AUTH 820365123
#define WIRELESS_QUAD_ADDR "quadr"
#define WIRELESS_QUAD_CTRL "quadc"
#define WIRELESS_PING_INTERVAL 100
#define WIRELESS_TRANSFER
//#define USE_NRF24L
//#define WIRELESS_NRF24L_CHANNEL 50 //Channel 0 - 127 or 0 - 84 in the US.
//#define WIRELESS_NRF24L_MISO 12	//Those can't be changed!
//#define WIRELESS_NRF24L_MOSI 11 //Those can't be changed!
//#define WIRELESS_NRF24L_SCK 13  //Those can't be changed!
//#define WIRELESS_NRF24L_CE 8
//#define WIRELESS_NRF24L_CSN 9
/* Module PINs
GND	1
VCC	2
CE	3
CSN	4
SCK	5
MOSI	6
MISO	7
IRQ	8
*/

//#define USE_433MHZ
//#define WIRELESS_SPEED 4096
//#define WIRELESS_433MHZ_TRANSFER_PIN 8
//#define WIRELESS_433MHZ_RECEIVE_PIN 4

#define USE_APC_220
#define WIRELESS_SPEED 9600
#define WIRELESS_APC220_TX 3
#define WIRELESS_APC220_RX 2


#endif