

void HueSaturationMain()
{
	
	EVERY_N_MILLISECONDS(50)
	{
		if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
		{
			
			if (LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight)
			{
				//set next color temp
				switch (LEDSettings.Temperature)
				{
					case Candle2:
						LEDSettings.Temperature = Candle3;
						break;
					case Candle3:
						LEDSettings.Temperature = Tungsten40W2;
						break;
					case Tungsten40W2:
						LEDSettings.Temperature = Tungsten100W2;
						break;
					case Tungsten100W2:
						LEDSettings.Temperature = Halogen2;
						break;
					case Halogen2:
						LEDSettings.Temperature = CarbonArc2;
						break;
					case CarbonArc2:
						LEDSettings.Temperature = HighNoonSun2;
						break;
					case HighNoonSun2:
						LEDSettings.Temperature = DirectSunlight2;
						break;
					case DirectSunlight2:
						LEDSettings.Temperature = OvercastSky2;
						break;
					case OvercastSky2:
						LEDSettings.Temperature = ClearBlueSky2;
						break;
					default:
						LEDSettings.Temperature = Candle2;
					}
					LEDSettings.ChangesToEffectMade = 1;

					Serial.print("Changing ColorTemp to ");
					Serial.println(LEDSettings.Temperature);
			}
			else
			{

			}
			
			ReadValues.newValues = 0;
		}

		
	}
	

}
