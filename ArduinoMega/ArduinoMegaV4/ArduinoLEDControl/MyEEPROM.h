// MyEEPROM.h

#ifndef _MYEEPROM_h
#define _MYEEPROM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GlobalVarLEDControl.h"

void EEPROMStart();
bool EEPROMloadConfig();
void EEPROMsaveDefaultValues();
void EEPROMsave();

#endif

