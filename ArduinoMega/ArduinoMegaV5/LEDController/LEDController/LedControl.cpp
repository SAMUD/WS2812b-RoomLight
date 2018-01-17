// 
// 
// 

#include "LedControl.h"
#include "GlobalVarLEDControl.h"
#include "MyEEPROM.h"
//#include "Brightness.h"
//#include "DisplayEffect.h"
//#include "OutputToLED.h"

LedControlClass::LedControlClass(int NumberLEDs, bool SetDither)
{
	FastLED.addLeds <NEOPIXEL, DATA_PIN>(_leds, NumberLEDs);
	FastLED.setBrightness(0);
	FastLED.setDither(SetDither);

	//setup Relais for main Power supply
	pinMode(PIN_RELAIS, OUTPUT);

	//prepare EEPROM
	EEPROMStart();

	//Turn on LEDs
	digitalWrite(PIN_RELAIS, 0);
	SettingsNow.PowerState = true;
	SettingsNow.ChangesToEffectMade = true;
	SettingsNow.PlayPause = true;

}

// Public Methods implementation
void LedControlClass::Loop()
{
	//if (SettingsNow.PowerState)
		//BrightnessFade(Settings.Current->BrightnessSetpoint);		//call the fading function for the Brightness

																	//Display Effect
	//DisplayEffectMain();

	//print out
	//OutputToLEDMain();
}

//Turning on or off the LED-Strip
void LedControlClass::SetOnOff(bool NewState)
{
	if (SettingsNow.PowerState != NewState)
	{
		//someone turned on or off the LEDs
		SettingsNow.PowerState = NewState;

		if (!SettingsNow.PowerState)
		{
			#ifdef DEBUGMODE
				Serial.print("Power button pressed - Turning off");
			#endif
			//EEPROMsave();
			//BrightnessTurnOff();
		}
		else
		{
			#ifdef DEBUGMODE
				Serial.print("Power button pressed - Turning on: ");
			#endif
			//BrightnessTurnOn();
			SettingsNow.ChangesToEffectMade = 1;
		}
	}
}

//check if the LEDs are on or off at the moment
bool LedControlClass::GetOnOffState()
{
	return SettingsNow.PowerState;
}

bool LedControlClass::ToggleOnOff()
{
	if (GetOnOffState())
		//It's on. we should turn it off
		SetOnOff(false);
	else
		//It's off. we should turn it on
		SetOnOff(true);

	//now return the new state
	return SettingsNow.PowerState;
}

//Play/Pause on the LED-Strip
void LedControlClass::SetPause(bool NewState)
{
	SettingsNow.PlayPause = NewState;
}

bool LedControlClass::GetPauseState()
{
	return SettingsNow.PlayPause;
}

bool LedControlClass::TogglePause()
{
	SettingsNow.PlayPause != SettingsNow.PlayPause;

	//now return the new state
	return SettingsNow.PlayPause;

}

void LedControlClass::SetBrightness(uint8_t NewValue)
{
	Settings.Current->BrightnessSetpoint = NewValue;
}

void LedControlClass::SetNightNumber(uint8_t NewValue)
{
	Settings.Current->NightNumber = NewValue;
}

void LedControlClass::SetDisplayMode(eDisplay NewValue)
{
	Settings.Current->DisplayMode = NewValue;
}

void LedControlClass::SetNextDisplayMode()
{
	#if defined(DEBUGMODE)
		Serial.print("DisplayMode | Changed to: ");
	#endif

	switch (Settings.Current->DisplayMode)
	{
	case Left:
		Settings.Current->DisplayMode == Right;
		#if defined(DEBUGMODE)
			Serial.println("Right");
		#endif
		break;
	case Right:
		Settings.Current->DisplayMode == Night;
		#if defined(DEBUGMODE)
			Serial.println("Night");
		#endif
		break;
	case Night:
		Settings.Current->DisplayMode == All;
		#if defined(DEBUGMODE)
			Serial.println("All");
		#endif
		break;
	case All:
		Settings.Current->DisplayMode == Left;
		#if defined(DEBUGMODE)
			Serial.println("Left");
		#endif
		break;
	default:
		Settings.Current->DisplayMode == Left;
		#if defined(DEBUGMODE)
			Serial.println("Left (default)");
		#endif
		break;
	}

	SettingsNow.ChangesToEffectMade = 1;

	//show status update
	SettingsNow.ShowACK = 1;
	SettingsNow.ShowPercentage = 0;
}

void LedControlClass::SetSaturation(uint8_t NewValue)
{
	Settings.Current->Saturation = NewValue;
}

void LedControlClass::SetSet(uint8_t NewValue)
{
	Settings.Current->Set = NewValue;
}

void LedControlClass::SetSpeed(uint8_t NewValue)
{
	Settings.Current->Speed = NewValue;
}

void LedControlClass::SetTemp(ColTemp NewValue)
{
	Settings.Current->Temperature = NewValue;
}

ColTemp LedControlClass::GetTemp()
{
	return Settings.Current->Temperature;
}

void LedControlClass::SetNextTemp()
{
	switch (LedControlClass::GetTemp())
	{
	case Candle2:
		Settings.Current->Temperature == Candle3;
		break;
	case Candle3:
		Settings.Current->Temperature == Tungsten40W2;
		break;
	case Tungsten40W2:
		Settings.Current->Temperature == Tungsten100W2;
		break;
	case Tungsten100W2:
		Settings.Current->Temperature == Halogen2;
		break;
	case Halogen2:
		Settings.Current->Temperature == CarbonArc2;
		break;
	case CarbonArc2:
		Settings.Current->Temperature == HighNoonSun2;
		break;
	case HighNoonSun2:
		Settings.Current->Temperature == DirectSunlight2;
		break;
	case DirectSunlight2:
		Settings.Current->Temperature == OvercastSky2;
		break;
	case OvercastSky2:
		Settings.Current->Temperature == ClearBlueSky2;
		break;
	default:
		Settings.Current->Temperature == Candle2;
	}
	#if defined(DEBUGMODE)
		Serial.print("SetColorTemp to: ");
		Serial.println(LedControlClass::GetTemp());
	#endif
}

void LedControlClass::SetNewMode(String Mode)
{
	
	/*//load new Settings
	switch (Settings.DisplayMode)
	{
	case White:
		Settings.Current = Settings.White;
		break;
	case FixedColor:
		Settings.Current = Settings.FixedColor;
		break;
	case RainbowMarch:
		Settings.Current = Settings.RainbowMarch;
		break;
	case RainbowBeat:
		Settings.Current = Settings.RainbowBeat;
		break;
	case ColorPalBeat:
		Settings.Current = Settings.ColorPalBeat;
		break;
	case Fade:
		Settings.Current = Settings.Fade;
		break;
	case RGBFade:
		Settings.Current = Settings.RGBFade;
		break;
	case Confetti:
		Settings.Current = Settings.Confetti;
		break;
	case ConfettiColorfull:
		Settings.Current = Settings.ConfettiColorfull;
		break;
	case Strobe:
		Settings.Current = Settings.Strobe;
		break;
	case FixedColor2:
		Settings.Current = Settings.FixedColor2;
		break;
	case White2:
		Settings.Current = Settings.White2;
		break;
	case Ball:
		Settings.Current = Settings.Ball;
		break;
	case AudioMeter:
		Settings.Current = Settings.AudioMeter;
		break;
	}

	//Turn on LEDs at the end
	LedControlClass::SetOnOff(true);

	Settings.ChangesToEffectMade = 1;

	//show status update
	DisplayInfo.ShowACK = 1;
	DisplayInfo.ShowPercentage = 0;*/
}

