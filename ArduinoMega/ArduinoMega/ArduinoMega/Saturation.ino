
void SaturationMain()
{
	EVERY_N_MILLISECONDS(51)
	{
		if (ReadValues.ButtonPressed == Down && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1)  //Fast scaling
			{
				if (LEDSettings.Saturation > 20)
				{
					LEDSettings.Saturation = LEDSettings.Saturation - 10;
#if defined(DEBUGMODE)
					Serial.print("----  ");
#endif
				}
				else
				{
					LEDSettings.Saturation = 10;
#if defined(DEBUGMODE)
					Serial.print("oo    ");
#endif			
				}
			}
			else //Slow scaling
			{
				if (LEDSettings.Saturation > 15)
				{
					LEDSettings.Saturation = LEDSettings.Saturation - 5;
#if defined(DEBUGMODE)
					Serial.print("--    ");
#endif
				}
				else
				{
					LEDSettings.Saturation = 10;
#if defined(DEBUGMODE)
					Serial.print("oo    ");
#endif
				}
			}

			LEDSettings.ChangesToEffectMade = 1;
#if defined(DEBUGMODE)
			Serial.print("SaturationMain | Down :");
			Serial.println(LEDSettings.Saturation);

#endif
			ReadValues.newValues = 0;
		}
		if (ReadValues.ButtonPressed == Up && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1) //Fast scaling
			{

				if (LEDSettings.Saturation < 246)
				{
					LEDSettings.Saturation = LEDSettings.Saturation + 10;
#if defined(DEBUGMODE)
					Serial.print("++++  ");
#endif
				}
				else
				{
					LEDSettings.Saturation = 255;
#if defined(DEBUGMODE)
					Serial.print("oo    ");
#endif
				}
			}
			else
			{
				if (LEDSettings.Saturation < 240)
				{
					LEDSettings.Saturation = LEDSettings.Saturation + 5; //Slow scaling
#if defined(DEBUGMODE)
					Serial.print("++    ");
#endif
				}
				else
				{
					LEDSettings.Saturation = 255; //Slow scaling
#if defined(DEBUGMODE)
					Serial.print("oo    ");
#endif
				}

			}

			LEDSettings.ChangesToEffectMade = 1;
#if defined(DEBUGMODE)
			Serial.print("SaturationMain | Up  ");
			Serial.println(LEDSettings.Saturation);
#endif
			ReadValues.newValues = 0;
		}
	}

	BrightnessFade(LEDSettings.Saturation);


}

