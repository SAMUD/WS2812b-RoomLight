void ModeSelectionMain()
{
	
	//needs only to be run every 50ms because values from other Arduino are also only read each 50ms
	EVERY_N_MILLISECONDS(75)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == FuncStop)
		{
			//If LEDS are off, turn them on and after that change mode.
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (LEDSettings.DisplayMode)
			{
			case WhiteAll:
				LEDSettings.DisplayMode = WhiteLeft;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to WhiteLeft");
				#endif
				break;
			case WhiteLeft:
				LEDSettings.DisplayMode = WhiteRight;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to WhiteRight");
				#endif
				break;
			default:
				LEDSettings.DisplayMode = WhiteAll;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to WhiteAll");
				#endif
				break;
			}
			LEDSettings.ChangesToEffectMade = 1;
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (LEDSettings.DisplayMode)
			{
			case RainbowBeat:
				LEDSettings.DisplayMode = ColorPalBeat;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to ColorPalBeat");
				#endif
				break;
			case RainbowMarch:
				LEDSettings.DisplayMode = RainbowBeat;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to RainbowBeat");
				#endif
				break;
			case Heat:
				LEDSettings.DisplayMode = RainbowMarch;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to RainbowMarch");
				#endif
				break;
			default:
				LEDSettings.DisplayMode = Heat;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Heat");
				#endif
				break;
			}

			LEDSettings.ChangesToEffectMade = 1;
			LEDSettings.PlayPause = 1; 
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Five)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (LEDSettings.DisplayMode)
			{
			case Fade:
				LEDSettings.DisplayMode = RGBFade;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to RGBFade");
				#endif
				break;
			default:
				LEDSettings.DisplayMode = Fade;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Fade");
				#endif
				break;
			}

			LEDSettings.ChangesToEffectMade = 1;
			LEDSettings.PlayPause = 1;
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Two)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (LEDSettings.DisplayMode)
			{
			case ConfettiColorfull:
				LEDSettings.DisplayMode = Strobe;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Strobe");
				#endif
				break;
			case Confetti:
				LEDSettings.DisplayMode = ConfettiColorfull;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Colorfull Confetti");
				#endif
				break;
			default:
				LEDSettings.DisplayMode = Confetti;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Confetti");
				#endif
				break;
			}

			LEDSettings.ChangesToEffectMade = 1;
			LEDSettings.PlayPause = 1;
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Three)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (LEDSettings.DisplayMode)
			{
			default:
				LEDSettings.DisplayMode = Night;
				LEDSettings.BrightnessSetpoint = 60;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Night");
				#endif
				break;
			}

			LEDSettings.ChangesToEffectMade = 1;
			LEDSettings.PlayPause = 1;
			ReadValues.newValues = 0;
		}

		//change to turn all on
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Nine)
		{
			//making full white
			LEDSettings.DisplayMode = WhiteAll;
			LEDSettings.BrightnessSetpoint = 255;
			LEDSettings.ChangesToEffectMade = 1;
			LEDSettings.Temperature = DirectSunlight2;
			if (!LEDSettings.PowerState)
				LEDSettings.PowerState = 1;
			ReadValues.newValues = 0;
		}
		
	}
	
}

//used to turn on the LEDs if they are off and I press a mode button
void ModeSelectionTurnOn()
{
	#if defined(DEBUGMODE)
	Serial.println("ModeSelectionTurnOn | Turned on LEDs");
	#endif
	LEDSettings.PowerState = 1;
	LEDSettings.DisplayMode = LEDSettings.DisplayModeOld;
}
