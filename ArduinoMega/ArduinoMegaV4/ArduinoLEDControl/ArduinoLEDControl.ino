/*
 Name:		ArduinoLEDControl.ino
 Created:	17.01.2018 14:52:13
 Author:	sdaur
*/

// the setup function runs once when you press reset or power the board

#include "OutputToLED.h"
#include "DisplayEffect.h"
#include "MyEEPROM.h"
#include "MyTypes.h"
#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"
#include "LedControl.h"
#include "Brightness.h"
#include "OutputToLED.h"


LedControlClass myLEDs(25, false);

void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
