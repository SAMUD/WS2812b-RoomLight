// 
// 
// 

#include "Brightness.h"
#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"

//Fading the Brightness to the Value specified in LEDSetLedBlock.BrightnessSetpoint
void BrightnessFade(uint8_t Setpoint)
{
	EVERY_N_MILLISECONDS(40)
	{
		uint8_t incrementor = 0;

		//when Setpoint is not the same as actual brightness
		incrementor = 1;
		if (FastLED.getBrightness() - Setpoint > 10 || FastLED.getBrightness() - Setpoint < -10)
			incrementor = 2;
		if (FastLED.getBrightness() - Setpoint > 20 || FastLED.getBrightness() - Setpoint < -20)
			incrementor = 4;
		if (FastLED.getBrightness() - Setpoint > 30 || FastLED.getBrightness() - Setpoint < -30)
			incrementor = 8;
		if (FastLED.getBrightness() - Setpoint > 40 || FastLED.getBrightness() - Setpoint < -40)
			incrementor = 16;
		if (FastLED.getBrightness() - Setpoint > 70 || FastLED.getBrightness() - Setpoint < -70)
			incrementor = 32;

		if (FastLED.getBrightness() < Setpoint)
			FastLED.setBrightness(FastLED.getBrightness() + incrementor);

		if (FastLED.getBrightness() > Setpoint)
			FastLED.setBrightness(FastLED.getBrightness() - incrementor);
	}
}

//Turning off the LED-Strip
void BrightnessTurnOff()
{

	while (FastLED.getBrightness() > 0)
	{
		//run BrightnessFade until brightness is 0
		EVERY_N_MILLISECONDS(30)
		{
			BrightnessFade(0);
			//OutputToLEDMain();
		}
	}
	if (SettingsNow.DebuggingOn)
		Serial.println("BrightnessTurnOff | Powered down now");
	digitalWrite(PIN_RELAIS, 1);
}

//Turning on the LED-Strip
void BrightnessTurnOn()
{
	digitalWrite(PIN_RELAIS, 0);
}
