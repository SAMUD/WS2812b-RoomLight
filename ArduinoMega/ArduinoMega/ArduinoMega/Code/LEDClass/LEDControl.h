// LEDControl.h


//First start including some stuff
#ifndef _LEDCONTROL_h
#define _LEDCONTROL_h

#ifndef GlobalVarLEDControl.h
#include "./GlobalVarLEDControl.h"
#endif

#include "./EEPROMLib.h";

class LEDControl
{
	
	public:

		

		

		LEDControl(int NumberLEDs, int MemoryStartAdress, bool Debugging, bool SetDither);

		void Loop();

		void SetOnOff(bool NewState);

};

extern LEDControl;

#endif

