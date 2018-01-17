#include "LEDControl.h"

#include "./EEPROMLib.h"




LEDControl::LEDControl(int NumberLEDs, int MemoryStartAdress, bool Debugging, bool SetDither )
{
	FastLED.addLeds <NEOPIXEL, DATA_PIN> (_leds, NumberLEDs);
	FastLED.setBrightness(0);
	FastLED.setDither(SetDither);

	//setup Relais for main Power supply
	pinMode(PIN_RELAIS, OUTPUT);

	//prepare EEPROM
	EEPROMinit(&Settings);

	//Turn on LEDs
	digitalWrite(PIN_RELAIS, 0);
	SettingsNow.PowerState = true;
	SettingsNow.ChangesToEffectMade = true;
	SettingsNow.PlayPause = true;

	//Set other parameters
	SettingsNow.DebuggingOn = Debugging;

}

// Public Methods implementation
void LEDControl::Loop()
{
	if (SettingsNow.PowerState)
		BrightnessFade(Settings.Current->BrightnessSetpoint);		//call the fading function for the Brightness
		
	//Display Effect
	DisplayEffectMain();

	//print out
	OutputToLEDMain();
}

//Turning on or off the LED-Strip
void LEDControl::SetOnOff(bool NewState)
{
	if (SettingsNow.PowerState != NewState)
	{
		//someone turned on or off the LEDs
		SettingsNow.PowerState = NewState;

		if (!SettingsNow.PowerState)
		{
			if (SettingsNow.DebuggingOn)
				Serial.print("Power button pressed - Turning off");
			EEPROMsave();
			BrightnessTurnOff();
		}
		else
		{
			if (SettingsNow.DebuggingOn)
				Serial.print("Power button pressed - Turning on: ");
			BrightnessTurnOn();
			SettingsNow.ChangesToEffectMade = 1;
		}
	}
}

