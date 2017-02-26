void DisplayModeMain()
{
	EVERY_N_MILLISECONDS(101)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == FuncStop)
		{
			#if defined(DEBUGMODE)
				Serial.print("DisplayMode | Changed to: ");
			#endif
			switch (Settings.Current.DisplayMode)
			{
			case Left:
				Settings.Current.DisplayMode = Right;
				#if defined(DEBUGMODE)
					Serial.println("Right");
				#endif
				break;
			case Right :
				Settings.Current.DisplayMode = Night;
				#if defined(DEBUGMODE)
					Serial.println("Night");
				#endif
				break;
			case Night:
				Settings.Current.DisplayMode = All;
				#if defined(DEBUGMODE)
					Serial.println("All");
				#endif
				break;
			case All:
				Settings.Current.DisplayMode = Left;
				#if defined(DEBUGMODE)
					Serial.println("Left");
				#endif
				break;
			default:
				Settings.Current.DisplayMode = Left;
				#if defined(DEBUGMODE)
					Serial.println("Left (default)");
				#endif
				break;
			}

			
			ReadValues.newValues = 0;
			Settings.ChangesToEffectMade = 1;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = 0;
		}

	}
}
