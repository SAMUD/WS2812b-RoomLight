void ModeSelectionMain()
{
	
	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Six)
	{
		//switching to the next mode (White)
		#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to White0-2");
		#endif
		switch (Settings.EffectNumber)
		{
		case White0:
			Settings.EffectNumber= White1;
			break;
		case White1:
			Settings.EffectNumber= White2;
			break;
		case White2:
			Settings.EffectNumber= White0;
			break;
		default:
			Settings.EffectNumber= White0;
			break;
		}
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Nine)
	{
		//switching to the next mode (White-Full)
		#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to TotalWhite");
		#endif
		Settings.EffectNumber = TotalWhite;
		Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint = 255;
		Settings.LedEffects[Settings.EffectNumber].DisplayMode = All;
		Settings.LedEffects[Settings.EffectNumber].Temperature = DirectSunlight2;
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Four)
	{
		//switching to the next mode (White)
		#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to Ball");
		#endif
		Settings.EffectNumber= Ball;
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
	{
		//switching to the next mode (White)
		#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to Rainbow");
		#endif
		switch (Settings.EffectNumber)
		{
		case RainbowBeat:
			Settings.EffectNumber= ColorPalBeat;
			break;
		case RainbowMarch:
			Settings.EffectNumber= RainbowBeat;
			break;
		case ColorPalBeat:
			Settings.EffectNumber= RainbowMarch;
			break;
		default:
			Settings.EffectNumber= RainbowMarch;
			break;
		}
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Five)
	{
		//switching to the next mode (White)
#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to Fade");
#endif
		switch (Settings.EffectNumber)
		{
		case Fade:
			Settings.EffectNumber= RGBFade;
			break;
		default:
			Settings.EffectNumber= Fade;
			break;
		}
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Two)
	{
		//switching to the next mode (White)
#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to Effect1");
#endif
		switch (Settings.EffectNumber)
		{
		case Confetti0:
			Settings.EffectNumber= Confetti1;
			break;
		case Confetti1:
			Settings.EffectNumber= Strobe;
			break;
		default:
			Settings.EffectNumber= Confetti0;
			break;
		}
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Seven)
	{
		//switching to the next mode (White)
#if defined(DEBUGMODE)
		Serial.print("ModeSelectionMain | Changed to FixedColor");
#endif
		switch (Settings.EffectNumber)
		{
		case FixedColor0:
			Settings.EffectNumber = FixedColor1;
			break;
		case FixedColor1:
			Settings.EffectNumber = FixedColor2;
			break;
		case FixedColor2:
			Settings.EffectNumber = FixedColor3;
			break;
		default:
			Settings.EffectNumber = FixedColor0;
			break;
		}
	}

	if (Settings.EffectNumber != Settings.EffectNumberOld)
	{
		//Effect has been changed
		if(SettingsNow.PowerState==false)
			ModeSelectionTurnOn();
		
		SettingsNow.ChangesToEffectMade = true;
		SettingsNow.PlayPause = true;
		ReadValues.newValues = 0;

		//show status update
		SettingsNow.ShowACK = 1;
		SettingsNow.ShowPercentage = 0;

		

		#if defined(DEBUGMODE)
		Serial.print(" new Mode: ");
		Serial.println(Settings.EffectNumber);
		#endif
	}	
}

//used to turn on the LEDs if they are off and I press a mode button
void ModeSelectionTurnOn()
{
	digitalWrite(PIN_RELAIS, 0);
	delay(50);
	#if defined(DEBUGMODE)
		Serial.println("ModeSelectionTurnOn | Turned on LEDs");
	#endif
	SettingsNow.PowerState = true;
	Settings.EffectNumberOld = Settings.EffectNumber;
	
}
