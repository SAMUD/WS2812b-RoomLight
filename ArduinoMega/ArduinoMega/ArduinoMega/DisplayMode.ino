void DisplayModeMain()
{
	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == FuncStop)
	{
		#if defined(DEBUGMODE)
			Serial.print("DisplayMode | Changed to: ");
		#endif
		switch (Settings.LedEffects[Settings.EffectNumber].DisplayMode)
		{
		case Left:
			Settings.LedEffects[Settings.EffectNumber].DisplayMode = Right;
			#if defined(DEBUGMODE)
				Serial.println("Right");
			#endif
			break;
		case Right :
			Settings.LedEffects[Settings.EffectNumber].DisplayMode = Night;
			#if defined(DEBUGMODE)
				Serial.println("Night");
			#endif
			break;
		case Night:
			Settings.LedEffects[Settings.EffectNumber].DisplayMode = All;
			#if defined(DEBUGMODE)
				Serial.println("All");
			#endif
			break;
		case All:
			Settings.LedEffects[Settings.EffectNumber].DisplayMode = Left;
			#if defined(DEBUGMODE)
				Serial.println("Left");
			#endif
			break;
		default:
			Settings.LedEffects[Settings.EffectNumber].DisplayMode = Left;
			#if defined(DEBUGMODE)
				Serial.println("Left (default)");
			#endif
			break;
		}

			
		ReadValues.newValues = 0;
		SettingsNow.ChangesToEffectMade = true;

		//show status update
		SettingsNow.ShowACK = 1;
		SettingsNow.ShowPercentage = 0;
	}
}
