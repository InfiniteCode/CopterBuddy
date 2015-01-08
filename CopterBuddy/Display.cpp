//Copyright 2014, Alex Khilko. 
//This file is part of CopterBuddy which is released under MIT.
//See file LICENSE.TXT or go to www.alexkhilko.com for full license details. 

#include "Display.h"
#include "Config.h"
#include "Consts.h"
#include "UpTime.h"

#ifdef USE_LCD_NOKIA_5110
#include <Adafruit_GFX\Adafruit_GFX.h>
#include <Adafruit_PCD8544\Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 displayNokia5110 = Adafruit_PCD8544(DISPLAY_PIN_SCLK, DISPLAY_PIN_DIN, DISPLAY_PIN_DC, DISPLAY_PIN_CS, DISPLAY_PIN_RST);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!
#endif //USE_LCD_NOKIA_5110

#ifdef USE_LCD_ILI9341
#include <Adafruit-GFX\Adafruit_GFX.h>
#include <Adafruit-ILI9341\Adafruit_ILI9341.h>
Adafruit_ILI9341 displayILI9341 = Adafruit_ILI9341(DISPLAY_PIN_CS, DISPLAY_PIN_DC, DISPLAY_PIN_MOSI, DISPLAY_PIN_SCLK, DISPLAY_PIN_RST, DISPLAY_PIN_MISO);
#endif //USE_LCD_ILI9341

void DisplayClass::init()
{
	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINT(CS::CONST_DISPLAY_INIT);
	DEBUG_PRINTLN(CS::CONST_GENERAL_DELIM);
		
#ifdef USE_LCD_NOKIA_5110
	DEBUG_PRINTLN(CS::CONST_DISPLAY_NOKIA5110);
	displayNokia5110.begin();
	displayNokia5110.setContrast(DISPLAY_CONTRAST);
	displayNokia5110.clearDisplay();
	displayNokia5110.setTextSize(1);
	displayNokia5110.setTextColor(BLACK);
	displayNokia5110.setCursor(0, 0);
#endif

#ifdef USE_LCD_ILI9341
	DEBUG_PRINTLN(CS::CONST_DISPLAY_ILI9341);
	displayILI9341.begin();
	displayILI9341.fillScreen(ILI9341_BLACK);
	displayILI9341.setRotation(1);

	displayILI9341.setTextSize(5);
	displayILI9341.setTextColor(DISPLAY_COLOR_TEXT, DISPLAY_COLOR_BG);
	displayILI9341.setCursor(0, 0);

#endif

	DEBUG_PRINTLN(CS::CONST_DISPLAY_INITDONE);
	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINT(CS::CONST_GENERAL_DELIM);
	DEBUG_PRINTLN(CS::CONST_GENERAL_DELIM);
}

void DisplayClass::clear()
{
#ifdef USE_LCD_NOKIA_5110
	displayNokia5110.clearDisplay();
#endif
#ifdef USE_LCD_ILI9341
	displayILI9341.fillRect(0, 0, 320, 240, DISPLAY_COLOR_BG);
#endif
}

void DisplayClass::display()
{
#ifdef USE_LCD_NOKIA_5110
	displayNokia5110.display();
#endif
}

void DisplayClass::printPIDs(int16_t posY, double yawKP, double pitchKP, double rollKP,
	double yawKI, double pitchKI, double rollKI,
	double yawKD, double pitchKD, double rollKD)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);

	displayNokia5110.println(F("KP YPR:"));
	displayNokia5110.print(yawKP);
	displayNokia5110.print(" ");
	displayNokia5110.print(pitchKP);
	displayNokia5110.print(" ");
	displayNokia5110.println(rollKP);

	displayNokia5110.println(F("KI YPR:"));
	displayNokia5110.print(yawKI);
	displayNokia5110.print(" ");
	displayNokia5110.print(pitchKI);
	displayNokia5110.print(" ");
	displayNokia5110.println(rollKI);
#endif
}

void DisplayClass::printThrottle(int throttle, int frontLeft, int frontRight, int backLeft, int backRight, int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);

	displayNokia5110.print(F("Throttle: "));
	displayNokia5110.println(throttle);
	displayNokia5110.print(frontLeft);
	displayNokia5110.print("  ");
	displayNokia5110.println(frontRight);

	displayNokia5110.print(backLeft);
	displayNokia5110.print("  ");
	displayNokia5110.println(backRight);
#endif
}

void DisplayClass::printMotionMetrics(const VectorFloat& yawPitchRoll, int16_t posY, bool oneLiner)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	if (oneLiner)
	{
		displayNokia5110.print(F("YPR:"));
		displayNokia5110.print(yawPitchRoll.x);
		displayNokia5110.print(" ");
		displayNokia5110.print(yawPitchRoll.y);
		displayNokia5110.print(" ");
		displayNokia5110.println(yawPitchRoll.z);

	}
	else {
		displayNokia5110.print(CS::CONST_GENERAL_YAW);
		displayNokia5110.println(yawPitchRoll.x);
		displayNokia5110.print(CS::CONST_GENERAL_PITCH);
		displayNokia5110.println(yawPitchRoll.y);
		displayNokia5110.print(CS::CONST_GENERAL_ROLL);
		displayNokia5110.println(yawPitchRoll.z);
	}
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_YAW);
	displayILI9341.println(yawPitchRoll.x);
	displayILI9341.print(CS::CONST_GENERAL_PITCH);
	displayILI9341.println(yawPitchRoll.y);
	displayILI9341.print(CS::CONST_GENERAL_ROLL);
	displayILI9341.println(yawPitchRoll.z);
#endif
}

void DisplayClass::printCompassMetrics(const float heading, int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	displayNokia5110.print(CS::CONST_GENERAL_COMPASS);
	displayNokia5110.println(heading);
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_COMPASS);
	displayILI9341.println(heading);
#endif
}

void DisplayClass::printCycleTime(const unsigned long cycle, const uint16_t longestCycle, int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	displayNokia5110.print(CS::CONST_GENERAL_CYCLE);
	displayNokia5110.print(cycle);
	displayNokia5110.print(CS::CONST_GENERAL_SPACE);
	displayNokia5110.println(longestCycle);
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_CYCLE);
	displayILI9341.print(cycle);
	displayILI9341.print(CS::CONST_GENERAL_SPACE);
	displayILI9341.println(longestCycle);
#endif
}

void DisplayClass::printAtmosData(const float pressure, const float temperature, int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	displayNokia5110.print(CS::CONST_GENERAL_PRESSURE);
	displayNokia5110.print(pressure);
	displayNokia5110.println(CS::CONST_GENERAL_PRESSURE_HPA);
	displayNokia5110.print(CS::CONST_GENERAL_TEMP);
	displayNokia5110.print(temperature);
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_PRESSURE);
	displayILI9341.print(pressure);
	displayILI9341.println(CS::CONST_GENERAL_PRESSURE_HPA);
	displayILI9341.print(CS::CONST_GENERAL_TEMP);
	displayILI9341.print(temperature);
#endif
}

void DisplayClass::printDistanceCm(long distance, int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	displayNokia5110.print(CS::CONST_GENERAL_DISTANCE);
	displayNokia5110.print(distance);
	displayNokia5110.println(CS::CONST_GENERAL_CM);
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_DISTANCE);
	displayILI9341.print(distance);
	displayILI9341.println(CS::CONST_GENERAL_CM);
#endif
}

void DisplayClass::printUptime(int16_t posY)
{
#ifdef USE_LCD_NOKIA_5110
	if (posY >= 0) displayNokia5110.setCursor(0, posY);
	displayNokia5110.print(CS::CONST_GENERAL_UPTIME);
	
	unsigned long days = UpTime.getDays();
	long hours = UpTime.getHoursRemainder();
	long minutes = UpTime.getMinutesRemainder();
	long seconds = UpTime.getSecondsRemainder();

	if (days > 0) 
	{ 
		displayNokia5110.print(days); 
		displayNokia5110.print(CS::CONST_GENERAL_DAY);
		displayNokia5110.print(CS::CONST_GENERAL_SPACE);

		displayNokia5110.print(hours);
		displayNokia5110.println(CS::CONST_GENERAL_HOUR);
	} else 
	if (hours > 0)
	{
		displayNokia5110.print(hours);
		displayNokia5110.print(CS::CONST_GENERAL_HOUR);
		displayNokia5110.print(CS::CONST_GENERAL_SPACE);

		displayNokia5110.print(minutes);
		displayNokia5110.println(CS::CONST_GENERAL_MIN);
	}
	else
	if (minutes > 0)
	{
		displayNokia5110.print(minutes);
		displayNokia5110.print(CS::CONST_GENERAL_MIN);
		displayNokia5110.print(CS::CONST_GENERAL_SPACE);

		displayNokia5110.print(seconds);
		displayNokia5110.println(CS::CONST_GENERAL_SEC);
	} else
	{
		displayNokia5110.print(seconds);
		displayNokia5110.println(CS::CONST_GENERAL_SEC);
	}
#endif
#ifdef USE_LCD_ILI9341
	if (posY >= 0) displayILI9341.setCursor(0, posY);
	displayILI9341.print(CS::CONST_GENERAL_UPTIME);

	unsigned long days = UpTime.getDays();
	long hours = UpTime.getHoursRemainder();
	long minutes = UpTime.getMinutesRemainder();
	long seconds = UpTime.getSecondsRemainder();

	if (days > 0)
	{
		displayILI9341.print(days);
		displayILI9341.print(CS::CONST_GENERAL_DAY);
		displayILI9341.print(CS::CONST_GENERAL_SPACE);

		displayILI9341.print(hours);
		displayILI9341.println(CS::CONST_GENERAL_HOUR);
	}
	else
	if (hours > 0)
	{
		displayILI9341.print(hours);
		displayILI9341.print(CS::CONST_GENERAL_HOUR);
		displayILI9341.print(CS::CONST_GENERAL_SPACE);

		displayILI9341.print(minutes);
		displayILI9341.println(CS::CONST_GENERAL_MIN);
	}
	else
	if (minutes > 0)
	{
		displayILI9341.print(minutes);
		displayILI9341.print(CS::CONST_GENERAL_MIN);
		displayILI9341.print(CS::CONST_GENERAL_SPACE);

		displayILI9341.print(seconds);
		displayILI9341.println(CS::CONST_GENERAL_SEC);
	}
	else
	{
		displayILI9341.print(seconds);
		displayILI9341.println(CS::CONST_GENERAL_SEC);
	}
#endif
}


DisplayClass Display;

