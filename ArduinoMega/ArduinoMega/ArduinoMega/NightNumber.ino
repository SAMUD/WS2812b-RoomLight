void NightNumberMain()
{
	EVERY_N_MILLISECONDS(50)
	{
		if (ReadValues.ButtonPressed == Zero && ReadValues.newValues && Settings.Current.DisplayMode == Night)
		{

			if (Settings.Current.NightNumber > 3)
			{
				Settings.Current.NightNumber = Settings.Current.NightNumber - 1;
#if defined(DEBUGMODE)
				Serial.print("--    ");
#endif
			}
			else
			{
				Settings.Current.NightNumber = 2;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif
			}

			Settings.ChangesToEffectMade = 1;
#if defined(DEBUGMODE)
			Serial.print("NightNumber | Down:");
			Serial.println(Settings.Current.NightNumber);
#endif
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.NightNumber * 10;

		}
		if (ReadValues.ButtonPressed == StRept && ReadValues.newValues && Settings.Current.DisplayMode == Night)
		{
			if (Settings.Current.NightNumber < 25)
			{
				Settings.Current.NightNumber = Settings.Current.NightNumber + 1;
#if defined(DEBUGMODE)
				Serial.print("++    ");
#endif
			}
			else
			{
				Settings.Current.NightNumber = 25;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif
			}

			Settings.ChangesToEffectMade = 1;
#if defined(DEBUGMODE)
			Serial.print("NightNumber | Up:");
			Serial.println(Settings.Current.NightNumber);
#endif
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.NightNumber * 10;
		}
	}
}
