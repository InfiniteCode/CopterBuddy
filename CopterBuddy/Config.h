//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#ifndef COPTER_CONFIG
#define COPTER_CONFIG

#define DEBUG_OUTPUT
//#define DEBUG_FLIGHTMETRICS

#define SERIAL_BAUD 115200
#define DISPLAY_UPDATE_INTERVAL 2000

//Turn on necessary sensors depending on what is available
//#define USE_BMP085 //Barometric sensor
#define USE_HMC5883L //Magnetometer, Compass, analog is also HMC5893 
//#define USE_HC_SR04 //Ultrasonic Distance sensor
#define USE_MPU6050 //Accelerometer and Gyroscope
#define USE_MPU6050_DMP //USE_MPU6050 must be also defined, this define only for DMP chip on board

//------- ILI 9341 --------
//#define USE_LCD_ILI9341
#define DISPLAY_PIN_SCLK 13
#define DISPLAY_PIN_DC   8
#define DISPLAY_PIN_CS   10
#define DISPLAY_PIN_RST   9
#define DISPLAY_PIN_MOSI  11
#define DISPLAY_PIN_MISO  12
//SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK)

#define DISPLAY_COLOR_TEXT displayILI9341.color565(0, 0, 0)
#define DISPLAY_COLOR_BG   displayILI9341.color565(255, 255, 255)
//------- ILI 9341 --------

//------- NOKIA 5110 --------
#define USE_LCD_NOKIA_5110
#define DISPLAY_CONTRAST  60
#define DISPLAY_PIN_SCLK  22
#define DISPLAY_PIN_DIN   23
#define DISPLAY_PIN_DC    24
#define DISPLAY_PIN_CS    25
#define DISPLAY_PIN_RST   26
//------- NOKIA 5110 --------

//Wireless module
#define WIRELESS_AUTH 820365123
#define WIRELESS_QUAD_ADDR "quadr"
#define WIRELESS_QUAD_CTRL "quadc"
#define WIRELESS_PING_INTERVAL 250
#define WIRELESS_RECEIVE
//#define USE_NRF24L
//Arduno MEGA 2560
//SPI : 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS).These pins support SPI communication using the SPI library.The SPI pins are also broken out on the ICSP header, which is physically compatible with the Uno, Duemilanove and Diecimila.
//#define WIRELESS_NRF24L_CHANNEL 50 //Channel 0 - 127 or 0 - 84 in the US.
//#define WIRELESS_NRF24L_MISO 50	//Those can't be changed!
//#define WIRELESS_NRF24L_MOSI 51 //Those can't be changed!
//#define WIRELESS_NRF24L_SCK 52  //Those can't be changed!
//#define WIRELESS_NRF24L_CE 48
//#define WIRELESS_NRF24L_CSN 53
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

#define USE_433MHZ
#define WIRELESS_SPEED 4096
//#define WIRELESS_433MHZ_TRANSFER_PIN 12
#define WIRELESS_433MHZ_RECEIVE_PIN 2


//--------- Motors Configuration
//     Front
//   1       2
//   4       3
#define MOTOR_ARM_INTERVAL 2000
#define MOTOR_DISARM_INTERVAL 1000
#define MOTOR_CONFIG_4X
#define MOTOR_ARM			80
#define MOTOR_MIN_THROTTLE 100
#define MOTOR_MAX_THROTTLE 254
#define MOTOR_SAFE_MAX_THROTTLE 180
#define USE_SAFE_MAX_THROTTLE
#define MOTOR_4X_1_PIN 5
#define MOTOR_4X_2_PIN 6
#define MOTOR_4X_3_PIN 7
#define MOTOR_4X_4_PIN 8
#define USE_LOST_COMM_SHUTDOWN 
#define LOST_COMM_TOLERANCE 1000
#define PRE_CONTROL_INTERVAL 2000

//Flight configuration
#define PID_CONFIG_INTERVAL 2000
#define PID_SAMPLE_TIME 10
#define PID_ROLL_KP 30.000
#define PID_ROLL_KI 0.000
#define PID_ROLL_KD 0.000

#define PID_PITCH_KP 30.000
#define PID_PITCH_KI 0.000
#define PID_PITCH_KD 0.000

#define PID_YAW_KP 5.0000
#define PID_YAW_KI 0.0000
#define PID_YAW_KD 0.0000

//Test Flight Params
#define TFS_ACCEL_MAX 45 //In percents
#define TFS_WARMUP_TIME 10
#define TFS_ENGSTART_TIME 13
#define TFS_ACCEL_TIME 5 //In seconds
#define TFS_DECEL_TIME 2 //In seconds


#endif