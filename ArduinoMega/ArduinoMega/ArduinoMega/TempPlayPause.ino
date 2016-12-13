

void TempPlayPauseMain()
{
	EVERY_N_MILLISECONDS(54)
	{
		if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
		{
			if (LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight)
			{
				//set next color temp
				SetColorTemp();
				LEDSettings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes Play Pause for the Effects
				LEDSettings.PlayPause = !LEDSettings.PlayPause;
			}
			ReadValues.newValues = 0;
		}
	}
}

void SetColorTemp()
{
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
	#if defined(DEBUGMODE)
	Serial.print("SetColorTemp to: ");
	Serial.println(LEDSettings.Temperature);
	#endif
}
