void ModeSelectionMain()
{
	
	//needs only to be run every 40ms because values from other Arduino are also only read each 50ms
	EVERY_N_MILLISECONDS(40)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Six)
		{
			//save current Settings
			SaveCurrentSettings();

			//If LEDS are off, turn them on and after that change mode.
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (White)
			switch (Settings.DisplayMode)
			{
			case White:
				Settings.DisplayMode = White2;
				Settings.Current = Settings.White2;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to White2");
				#endif
				break;
			default:
				Settings.DisplayMode = White;
				Settings.Current = Settings.White;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to White");
				#endif
				break;
			}
			Settings.ChangesToEffectMade = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Four)
		{
			//save current Settings
			SaveCurrentSettings();

			//If LEDS are off, turn them on and after that change mode.
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (White)
			switch (Settings.DisplayMode)
			{
			/*case White:
				Settings.DisplayMode = White2;
				Settings.Current = Settings.White2;
#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to White2");
#endif
				break;*/
			default:
				Settings.DisplayMode = Ball;
				Settings.Current = Settings.Ball;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Ball");
				#endif
				break;
			}
			Settings.ChangesToEffectMade = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
		{
			//save current Settings
			SaveCurrentSettings();
			
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case RainbowBeat:
				Settings.DisplayMode = ColorPalBeat;
				Settings.Current = Settings.ColorPalBeat;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to ColorPalBeat");
				#endif
				break;
			case RainbowMarch:
				Settings.DisplayMode = RainbowBeat;
				Settings.Current = Settings.RainbowBeat;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowBeat");
				#endif
				break;
			case ColorPalBeat:
				Settings.DisplayMode = RainbowMarch;
				Settings.Current = Settings.RainbowMarch;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowMarch");
				#endif
				break;
			default:
				Settings.DisplayMode = RainbowMarch;
				Settings.Current = Settings.RainbowMarch;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowMarch");
				#endif
				break;
			}

			Settings.ChangesToEffectMade = 1;
			Settings.PlayPause = 1; 
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Five)
		{
			//save current Settings
			SaveCurrentSettings();
			
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case Fade:
				Settings.DisplayMode = RGBFade;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RGBFade");
				#endif
				Settings.Current = Settings.RGBFade;
				break;
			default:
				Settings.DisplayMode = Fade;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Fade");
				#endif
				Settings.Current = Settings.Fade;
				break;
			}

			Settings.ChangesToEffectMade = 1;
			Settings.PlayPause = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == One)
		{
			//save current Settings
			SaveCurrentSettings();

			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (Audio1)
			switch (Settings.DisplayMode)
			{
			
			default:
				Settings.DisplayMode = AudioMeter;
				Settings.Current = Settings.AudioMeter;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to AudioMeter");
				#endif
				break;
			}

			Settings.ChangesToEffectMade = 1;
			Settings.PlayPause = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Two)
		{
			//save current Settings
			SaveCurrentSettings();
			
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case ConfettiColorfull:
				Settings.DisplayMode = Strobe;
				Settings.Current = Settings.Strobe;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Strobe");
				#endif
				break;
			case Confetti:
				Settings.DisplayMode = ConfettiColorfull;
				Settings.Current = Settings.ConfettiColorfull;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Colorfull Confetti");
				#endif
				break;
			default:
				Settings.DisplayMode = Confetti;
				Settings.Current = Settings.Confetti;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Confetti");
				#endif
				break;
			}

			Settings.ChangesToEffectMade = 1;
			Settings.PlayPause = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Seven)
		{
			//save current Settings
			SaveCurrentSettings();

			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!Settings.PowerState)
				ModeSelectionTurnOn();

			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case FixedColor:
				Settings.DisplayMode = FixedColor2;
				Settings.Current = Settings.FixedColor2;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to FixedColor2");
				#endif
				break;
			case FixedColor2:
				Settings.DisplayMode = FixedColor3;
				Settings.Current = Settings.FixedColor3;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to FixedColor3");
				#endif
				break;
			default:
				Settings.DisplayMode = FixedColor;
				Settings.Current = Settings.FixedColor;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to FixedColor");
				#endif
				break;
			}

			Settings.ChangesToEffectMade = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

		//change to turn all on
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Nine)
		{
			//save current Settings
			SaveCurrentSettings();
			
			//making full white
			Settings.DisplayMode = White;
			Settings.Current = Settings.White;
			Settings.Current.BrightnessSetpoint = 255;
			Settings.ChangesToEffectMade = 1;
			Settings.Current.Temperature = DirectSunlight2;
			if (!Settings.PowerState)
				Settings.PowerState = 1;
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}
		
	}
	
}

//used to turn on the LEDs if they are off and I press a mode button
void ModeSelectionTurnOn()
{
	#if defined(DEBUGMODE)
		Serial.println("ModeSelectionTurnOn | Turned on LEDs");
	#endif
	Settings.PowerState = 1;
	Settings.DisplayMode = Settings.DisplayModeOld;
	digitalWrite(PIN_RELAIS, 0);
}

//save Current Settings
void SaveCurrentSettings()
{
	Serial.print("ModeSelection | Saving settings for:");
	Serial.println(Settings.DisplayMode);
	if (Settings.DisplayMode == FixedColor)
		Settings.FixedColor = Settings.Current;
	if (Settings.DisplayMode == RainbowBeat)
		Settings.RainbowBeat = Settings.Current;
	if (Settings.DisplayMode == RainbowMarch)
		Settings.RainbowMarch = Settings.Current;
	if (Settings.DisplayMode == ColorPalBeat)
		Settings.ColorPalBeat = Settings.Current;
	if (Settings.DisplayMode == Fade)
		Settings.Fade = Settings.Current;
	if (Settings.DisplayMode == RGBFade)
		Settings.RGBFade = Settings.Current;
	if (Settings.DisplayMode == Confetti)
		Settings.Confetti = Settings.Current;
	if (Settings.DisplayMode == ConfettiColorfull)
		Settings.ConfettiColorfull = Settings.Current;
	if (Settings.DisplayMode == Strobe)
		Settings.Strobe = Settings.Current;
	if (Settings.DisplayMode == White)
		Settings.White = Settings.Current;
	if (Settings.DisplayMode == White2)
		Settings.White2 = Settings.Current;
	if (Settings.DisplayMode == FixedColor2)
		Settings.FixedColor2 = Settings.Current;
	if (Settings.DisplayMode == FixedColor3)
		Settings.FixedColor3 = Settings.Current;
	if (Settings.DisplayMode == Ball)
		Settings.Ball = Settings.Current;
	if (Settings.DisplayMode == AudioMeter)
		Settings.AudioMeter = Settings.Current;

}
