void ModeSelectionMain()
{
	
	//needs only to be run every 40ms because values from other Arduino are also only read each 50ms
	EVERY_N_MILLISECONDS(40)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Six)
		{

			//switching to the next mode (White)
			switch (Settings.DisplayMode)
			{
			case White:
				Settings.DisplayMode == White2;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to White2");
				#endif
				break;
			default:
				Settings.DisplayMode == White;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to White");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Four)
		{
			//switching to the next mode (White)
			switch (Settings.DisplayMode)
			{
			default:
				Settings.DisplayMode = Ball;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to Ball");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
		{
			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case RainbowBeat:
				Settings.DisplayMode = ColorPalBeat;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to ColorPalBeat");
				#endif
				break;
			case RainbowMarch:
				Settings.DisplayMode = RainbowBeat;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowBeat");
				#endif
				break;
			case ColorPalBeat:
				Settings.DisplayMode = RainbowMarch;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowMarch");
				#endif
				break;
			default:
				Settings.DisplayMode = RainbowMarch;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RainbowMarch");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Five)
		{
			switch (Settings.DisplayMode)
			{
			case Fade:
				Settings.DisplayMode = RGBFade;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to RGBFade");
				#endif
				break;
			default:
				Settings.DisplayMode = Fade;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Fade");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == One)
		{
			//switching to the next mode (Audio1)
			switch (Settings.DisplayMode)
			{
			default:
				Settings.DisplayMode = AudioMeter;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to AudioMeter");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Two)
		{
			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case ConfettiColorfull:
				Settings.DisplayMode = Strobe;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Strobe");
				#endif
				break;
			case Confetti:
				Settings.DisplayMode = ConfettiColorfull;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Colorfull Confetti");
				#endif
				break;
			default:
				Settings.DisplayMode = Confetti;
				#if defined(DEBUGMODE)
					Serial.println("ModeSelectionMain | Changed to Confetti");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Seven)
		{
			//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
			switch (Settings.DisplayMode)
			{
			case FixedColor:
				Settings.DisplayMode = FixedColor2;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to FixedColor2");
				#endif
				break;
			case FixedColor2:
				Settings.DisplayMode = FixedColor3;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to FixedColor3");
				#endif
				break;
			default:
				Settings.DisplayMode = FixedColor;
				#if defined(DEBUGMODE)
				Serial.println("ModeSelectionMain | Changed to FixedColor");
				#endif
				break;
			}
			ReadValues.newValues = 0;
			LEDBlockSetNewMode(Settings.DisplayMode);
		}
		
	}
	
}




