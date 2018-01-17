// LEDControl.h

#ifndef _LEDCONTROL_h
#define _LEDCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class LEDControlClass
{
	//Writing Constructores
	public LEDControlClass()
 protected:


 public:
	void init();
};

extern LEDControlClass LEDControl;

#endif

