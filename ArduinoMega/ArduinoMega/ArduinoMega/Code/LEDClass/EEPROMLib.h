// EEPROMLib.h

#ifndef EEPROMex.h
#include <EEPROMex.h>
#endif // !EEPROMex.h

#ifndef GlobalVarLEDControl.h
#include "GlobalVarLEDControl.h"
#endif // !EEPROMex.h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

void EEPROMinit();
bool EEPROMloadConfig();
void EEPROMsaveDefaultValues();
void EEPROMsave();



