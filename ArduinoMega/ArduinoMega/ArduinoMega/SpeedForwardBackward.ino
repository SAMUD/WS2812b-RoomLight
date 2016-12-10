void SpeedMain()
{

}

void ForwardBackwardMain()
{
	EVERY_N_MILLISECONDS(50)
	{
		if ((ReadValues.newValues == 1 || ReadValues.Repeat == 1) && ReadValues.ButtonPressed == Reward)
		{
			if (LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight)
			{
				//set next color temp
				SetColorTemp();
				LEDSettings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes set the speed up
				if (ReadValues.Repeat == 1)  //Fast scaling
				{
					if (LEDSettings.SpeedMultiplikator > 2)
					{
						--LEDSettings.SpeedMultiplikator;
						#if defined(DEBUGMODE)
						Serial.print("----  ");
						#endif
					}
					else
					{
						LEDSettings.SpeedMultiplikator = 2;
						#if defined(DEBUGMODE)
						Serial.print("oo    ");
						#endif			
					}
				}
				else //Slow scaling
				{
					if (LEDSettings.SpeedMultiplikator > 2)
					{
						--LEDSettings.SpeedMultiplikator;
						#if defined(DEBUGMODE)
						Serial.print("--    ");
						#endif
					}
					else
					{
						LEDSettings.SpeedMultiplikator = 2;
						#if defined(DEBUGMODE)
						Serial.print("oo    ");
						#endif
					}
				}
			}
			#if defined(DEBUGMODE)
			Serial.print("ForwardBackwardMain | delay to: ");
			Serial.println(LEDSettings.SpeedMultiplikator);
			#endif
			ReadValues.newValues = 0;
		}

		if ((ReadValues.newValues == 1 || ReadValues.Repeat == 1) && ReadValues.ButtonPressed == Forward)
		{
			if (LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight)
			{
				//set next color temp
				SetColorTemp();
				LEDSettings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes set the speed up
				if (ReadValues.Repeat == 1)  //Fast scaling
				{
					if (LEDSettings.SpeedMultiplikator < 50)
					{
						++LEDSettings.SpeedMultiplikator;
						#if defined(DEBUGMODE)
						Serial.print("++++  ");
						#endif
					}
					else
					{
						LEDSettings.SpeedMultiplikator = 50;
						#if defined(DEBUGMODE)
						Serial.print("oo    ");
						#endif			
					}
				}
				else //Slow scaling
				{
					if (LEDSettings.SpeedMultiplikator < 50)
					{
						++LEDSettings.SpeedMultiplikator;
						#if defined(DEBUGMODE)
						Serial.print("++    ");
						#endif
					}
					else
					{
						LEDSettings.SpeedMultiplikator = 50;
						#if defined(DEBUGMODE)
						Serial.print("oo    ");
						#endif
					}
				}
			}
			#if defined(DEBUGMODE)
			Serial.print("ForwardBackwardMain | delay to: ");
			Serial.println(LEDSettings.SpeedMultiplikator);
			#endif
			ReadValues.newValues = 0;
		}
	}
}
