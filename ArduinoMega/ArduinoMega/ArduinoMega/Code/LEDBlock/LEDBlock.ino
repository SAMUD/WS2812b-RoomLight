#ifndef GlobalVarLEDBlock.h
#include "GlobalVarLEDBlock.h"
#endif // !"GlobalVarLEDBlock.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif



bool LEDBlockSetup()
{
	//Setup all stuff needed for the LEDs

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(0);

	FastLED.setDither(1);

	//Relais to turn on and off main power supply
	pinMode(PINRelais, OUTPUT);

	//Prepare EEPROM
	EEPROMinit();

	//Turn on LEDs
	digitalWrite(PINRelais, 0);
	SetLedBlock.ChangesToEffectMade = 1;
	SetLedBlock.PowerState = 1;

	return true;
}

void LEDBlockLoop()
{
	//Loop for the LED-Control

	EVERY_N_MILLISECONDS(40)
	{
		BrightnessFade(SetLedBlock.Current.BrightnessSetpoint);		//call the fading function for the Brightness
	}

	//Display Effect
	DisplayEffectMain();

	//print out
	OutputToLEDMain();

}

//Turning on or off the LED-Strip
void LEDBlockSetOnOff(bool NewState)
{
	if (SetLedBlock.PowerState != NewState)
	{
		//someone turned on or off the LEDs
		SetLedBlock.PowerState = NewState;

		if (!SetLedBlock.PowerState)
		{
#if defined(DEBUGMODE)							//initiate PowerOff
			Serial.print("Power button pressed - Turning off: ");
			Serial.println(SetLedBlock.PowerState);
#endif
			EEPROMsave();
			BrightnessTurnOff();

		}
		else
		{
#if defined(DEBUGMODE)							//initiatePowerOn
			Serial.print("Power button pressed - Turning on: ");
			Serial.println(SetLedBlock.PowerState);
#endif
			digitalWrite(PINRelais, 1);
			BrightnessTurnOn();
			SetLedBlock.ChangesToEffectMade = 1;
		}
		ReadValues.newValues = 0;
	}
}

//check if the LEDs are on or off at the moment
bool LEDBlockGetOnOffState()
{
	return SetLedBlock.PowerState;
}

bool LEDBlockSetOnOffToggle()
{
	if (LEDBlockGetOnOffState())
		//It's on. we should turn it off
		LEDBlockSetOnOff(false);
	else
		//It's off. we should turn it on
		LEDBlockSetOnOff(true);

	//now return the new state
	return SetLedBlock.PowerState;
}

//Play/Pause on the LED-Strip
void LEDBlockSetPause(bool NewState)
{
	SetLedBlock.PlayPause = NewState;
}

//check if the LEDs are on or off at the moment
bool LEDBlockGetPauseState()
{
	return SetLedBlock.PlayPause;
}

bool LEDBlockSetPauseToggle()
{
	SetLedBlock.PlayPause != SetLedBlock.PlayPause;

	//now return the new state
	return SetLedBlock.PlayPause;
	
}

void LEDBlockSetBrightness(uint8_t NewValue)
{
	SetLedBlock.Current.BrightnessSetpoint = NewValue;
}

void LEDBlockSetNightNumber(uint8_t NewValue)
{
	SetLedBlock.Current.NightNumber = NewValue;
}

void LEDBlockSetDisplayMode(eDisplay NewValue)
{
	SetLedBlock.Current.DisplayMode = NewValue;
}

void LEDBlockSetNextDisplayMode()
{
	#if defined(DEBUGMODE)
	Serial.print("DisplayMode | Changed to: ");
	#endif

	switch (SetLedBlock.Current.DisplayMode)
	{
	case Left:
		SetLedBlock.Current.DisplayMode == Right;
		#if defined(DEBUGMODE)
		Serial.println("Right");
		#endif
		break;
	case Right:
		SetLedBlock.Current.DisplayMode == Night;
		#if defined(DEBUGMODE)
		Serial.println("Night");
		#endif
		break;
	case Night:
		SetLedBlock.Current.DisplayMode == All;
		#if defined(DEBUGMODE)
		Serial.println("All");
		#endif
		break;
	case All:
		SetLedBlock.Current.DisplayMode == Left;
		#if defined(DEBUGMODE)
		Serial.println("Left");
		#endif
		break;
	default:
		SetLedBlock.Current.DisplayMode == Left;
		#if defined(DEBUGMODE)
		Serial.println("Left (default)");
		#endif
		break;
	}

	SetLedBlock.ChangesToEffectMade = 1;

	//show status update
	DisplayInfo.ShowACK = 1;
	DisplayInfo.ShowPercentage = 0;
}

void LEDBlockSetSaturation(uint8_t NewValue)
{
	SetLedBlock.Current.Saturation = NewValue;
}

void LEDBlockSetSet(uint8_t NewValue)
{
	SetLedBlock.Current.Set = NewValue;
}

void LEDBlockSetSpeed(uint8_t NewValue)
{
	SetLedBlock.Current.SpeedColor = NewValue;
}

void LEDBlockSetSpeed(ColTemp NewValue)
{
	SetLedBlock.Current.Temperature = NewValue;
}

void LEDBlockSetNewMode(Mode NewValue)
{
	//save current SetLedBlock
	Serial.print("ModeSelection | Saving SetLedBlock for:");
	Serial.println(SetLedBlock.DisplayMode);
	if (SetLedBlock.DisplayMode == FixedColor)
		SetLedBlock.FixedColor = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == RainbowBeat)
		SetLedBlock.RainbowBeat = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == RainbowMarch)
		SetLedBlock.RainbowMarch = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == ColorPalBeat)
		SetLedBlock.ColorPalBeat = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == Fade)
		SetLedBlock.Fade = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == RGBFade)
		SetLedBlock.RGBFade = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == Confetti)
		SetLedBlock.Confetti = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == ConfettiColorfull)
		SetLedBlock.ConfettiColorfull = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == Strobe)
		SetLedBlock.Strobe = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == White)
		SetLedBlock.White = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == White2)
		SetLedBlock.White2 = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == FixedColor2)
		SetLedBlock.FixedColor2 = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == FixedColor3)
		SetLedBlock.FixedColor3 = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == Ball)
		SetLedBlock.Ball = SetLedBlock.Current;
	if (SetLedBlock.DisplayMode == AudioMeter)
		SetLedBlock.AudioMeter = SetLedBlock.Current;

	SetLedBlock.DisplayMode = NewValue;
	//now load new SetLedBlock
	switch (SetLedBlock.DisplayMode)
	{
	case White:
		SetLedBlock.Current = SetLedBlock.White;
		break;
	case FixedColor:
		SetLedBlock.Current = SetLedBlock.FixedColor;
		break;
	case RainbowMarch:
		SetLedBlock.Current = SetLedBlock.RainbowMarch;
		break;
	case RainbowBeat:
		SetLedBlock.Current = SetLedBlock.RainbowBeat;
		break;
	case ColorPalBeat:
		SetLedBlock.Current = SetLedBlock.ColorPalBeat;
		break;
	case Fade:
		SetLedBlock.Current = SetLedBlock.Fade;
		break;
	case RGBFade:
		SetLedBlock.Current = SetLedBlock.RGBFade;
		break;
	case Confetti:
		SetLedBlock.Current = SetLedBlock.Confetti;
		break;
	case ConfettiColorfull:
		SetLedBlock.Current = SetLedBlock.ConfettiColorfull;
		break;
	case Strobe:
		SetLedBlock.Current = SetLedBlock.Strobe;
		break;
	case FixedColor2:
		SetLedBlock.Current = SetLedBlock.FixedColor2;
		break;
	case White2:
		SetLedBlock.Current = SetLedBlock.White2;
		break;
	case Ball:
		SetLedBlock.Current = SetLedBlock.Ball;
		break;
	case AudioMeter:
		SetLedBlock.Current = SetLedBlock.AudioMeter;
		break;
	}

	//Turn on LEDs at the end
	LEDBlockSetOnOff(true);

	SetLedBlock.ChangesToEffectMade = 1;

	//show status update
	DisplayInfo.ShowACK = 1;
	DisplayInfo.ShowPercentage = 0;
}



