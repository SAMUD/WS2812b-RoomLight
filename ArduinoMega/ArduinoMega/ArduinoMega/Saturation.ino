
void SaturationMain()
{
	EVERY_N_MILLISECONDS(51)
	{
		if (ReadValues.ButtonPressed == Down && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1)  //Fast scaling
			{
				if (Settings.Current.Saturation > 20)
				{
					Settings.Current.Saturation = Settings.Current.Saturation - 10;
					#if defined(DEBUGMODE)
					Serial.print("----  ");
					#endif
				}
				else
				{
					Settings.Current.Saturation = 10;
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif			
				}
			}
			else //Slow scaling
			{
				if (Settings.Current.Saturation > 15)
				{
					Settings.Current.Saturation = Settings.Current.Saturation - 5;
					#if defined(DEBUGMODE)
					Serial.print("--    ");
					#endif
				}
				else
				{
					Settings.Current.Saturation = 10;
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif
				}
			}

			Settings.ChangesToEffectMade = 1;
			#if defined(DEBUGMODE)
			Serial.print("SaturationMain | Down :");
			Serial.println(Settings.Current.Saturation);

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.Saturation;

			#endif
			ReadValues.newValues = 0;
		}
		if (ReadValues.ButtonPressed == Up && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1) //Fast scaling
			{

				if (Settings.Current.Saturation < 246)
				{
					Settings.Current.Saturation = Settings.Current.Saturation + 10;
#if defined(DEBUGMODE)
					Serial.print("++++  ");
#endif
				}
				else
				{
					Settings.Current.Saturation = 255;
#if defined(DEBUGMODE)
					Serial.print("oo    ");
#endif
				}
			}
			else
			{
				if (Settings.Current.Saturation < 240)
				{
					Settings.Current.Saturation = Settings.Current.Saturation + 5; //Slow scaling
#if defined(DEBUGMODE)
					Serial.print("++    ");
#endif
				}
				else
				{
					Settings.Current.Saturation = 255; //Slow scaling
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif
				}

			}

			Settings.ChangesToEffectMade = 1;
			#if defined(DEBUGMODE)
			Serial.print("SaturationMain | Up  ");
			Serial.println(Settings.Current.Saturation);
			#endif
			ReadValues.newValues = 0;

			//show status update
			DisplayInfo.ShowACK = 1;
			DisplayInfo.ShowPercentage = Settings.Current.Saturation;
		}
	}


}

