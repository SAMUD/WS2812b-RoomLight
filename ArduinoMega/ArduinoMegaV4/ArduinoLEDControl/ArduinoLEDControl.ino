/*
 Name:		ArduinoLEDControl.ino
 Created:	17.01.2018 14:52:13
 Author:	sdaur
*/

// the setup function runs once when you press reset or power the board


#include "MyEEPROM.h"
#include "MyTypes.h"
#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"
#include "LedControl.h"


static LedControlClass myLEDs;

void setup()
{
	//Setup serial
	#if defined(DEBUGMODE)
	Serial.begin(115200);
	Serial.print("Started - Waiting - App: V");
	Serial.println(Version);
	Serial.print("LED Library: V");
	Serial.println(FASTLED_VERSION);
	#endif


	//Setting Pin-Modes
	pinMode(PINValueChanged, INPUT);
	pinMode(PINMultiplePresses, INPUT);
	pinMode(PINInput1, INPUT);
	pinMode(PINInput2, INPUT);
	pinMode(PINInput3, INPUT);
	pinMode(PINInput4, INPUT);
	pinMode(PINInput5, INPUT);
	pinMode(13, OUTPUT);

	myLEDs.Init(NUMleds, false);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	myLEDs.Loop();

	

	ReadBinaryMain();
	ModeSelectionMain();
	EVERY_N_MILLISECONDS(50)
	{
		myLEDs.SetBrightness(ChangeParamMain(VolDown, VolUp, true, myLEDs.GetBrightness(), 5, 255, 5, 10));
		TempPlayPauseMain();

		if (ReadValues.ButtonPressed == Power && ReadValues.newValues)
		{
			myLEDs.ToggleOnOff();
#if defined(DEBUGMODE)
			if (myLEDs.GetOnOffState())
				Serial.print("IR: Turned it on");
			else
				Serial.print("IR: Turned it off");
#endif
			ReadValues.newValues = false;
		}
	}
	

}
