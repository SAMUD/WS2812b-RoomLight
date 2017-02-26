void SpeedMain()
{

}

void ForwardBackwardMain()
{
	EVERY_N_MILLISECONDS(53)
	{
		if ((ReadValues.newValues == 1 || ReadValues.Repeat == 1) && ReadValues.ButtonPressed == Reward)
		{
			if (Settings.DisplayMode == (White || White2))
			{
				//set next color temp
				//SetColorTemp();
				//Settings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes set the speed up
				if (ReadValues.Repeat == 1)  //Fast scaling
				{
					if (Settings.Current.SpeedColor > 1)
					{
						--Settings.Current.SpeedColor;
						#if defined(DEBUGMODE)
							Serial.print("----  ");
						#endif
					}
					else
					{
						Settings.Current.SpeedColor = 1;
						#if defined(DEBUGMODE)
							Serial.print("oo    ");
						#endif			
					}
				}
				else //Slow scaling
				{
					if (Settings.Current.SpeedColor > 1)
					{
						--Settings.Current.SpeedColor;
						#if defined(DEBUGMODE)
							Serial.print("--    ");
						#endif
					}
					else
					{
						Settings.Current.SpeedColor = 1;
						#if defined(DEBUGMODE)
							Serial.print("oo    ");
						#endif
					}
				}
			}
			#if defined(DEBUGMODE)
				Serial.print("ForwardBackwardMain | delay to: ");
				Serial.println(Settings.Current.SpeedColor);
			#endif
			ReadValues.newValues = 0;
			Settings.ChangesToEffectMade = 1;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.SpeedColor;
		}

		if ((ReadValues.newValues == 1 || ReadValues.Repeat == 1) && ReadValues.ButtonPressed == Forward)
		{
			if (Settings.DisplayMode == (White || White2))
			{
				//set next color temp
				//SetColorTemp();
				//Settings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes set the speed up
				if (ReadValues.Repeat == 1)  //Fast scaling
				{
					if (Settings.Current.SpeedColor < 255)
					{
						++Settings.Current.SpeedColor;
						#if defined(DEBUGMODE)
							Serial.print("++++  ");
						#endif
					}
					else
					{
						Settings.Current.SpeedColor = 255;
						#if defined(DEBUGMODE)
							Serial.print("oo    ");
						#endif			
					}
				}
				else //Slow scaling
				{
					if (Settings.Current.SpeedColor < 255)
					{
						++Settings.Current.SpeedColor;
						#if defined(DEBUGMODE)
							Serial.print("++    ");
						#endif
					}
					else
					{
						Settings.Current.SpeedColor = 255;
						#if defined(DEBUGMODE)
						Serial.print("oo    ");
						#endif
					}
				}
			}
			#if defined(DEBUGMODE)
				Serial.print("ForwardBackwardMain | delay to: ");
				Serial.println(Settings.Current.SpeedColor);
			#endif
			ReadValues.newValues = 0;
			Settings.ChangesToEffectMade = 1;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.SpeedColor;
		}
	}
}
