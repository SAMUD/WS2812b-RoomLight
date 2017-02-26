

void TempPlayPauseMain()
{
	EVERY_N_MILLISECONDS(54)
	{
		if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
		{
			if (Settings.DisplayMode == White)
			{
				//set next color temp
				SetColorTemp();
				Settings.ChangesToEffectMade = 1;
			}
			else
			{
				//when not in White Modes Play Pause for the Effects
				Settings.PlayPause = !Settings.PlayPause;
			}
			ReadValues.newValues = 0;
			//show status update
			DisplayInfo.ShowACK = 1;
		}
	}
}

void SetColorTemp()
{
	switch (Settings.Current.Temperature)
	{
	case Candle2:
		Settings.Current.Temperature = Candle3;
		break;
	case Candle3:
		Settings.Current.Temperature = Tungsten40W2;
		break;
	case Tungsten40W2:
		Settings.Current.Temperature = Tungsten100W2;
		break;
	case Tungsten100W2:
		Settings.Current.Temperature = Halogen2;
		break;
	case Halogen2:
		Settings.Current.Temperature = CarbonArc2;
		break;
	case CarbonArc2:
		Settings.Current.Temperature = HighNoonSun2;
		break;
	case HighNoonSun2:
		Settings.Current.Temperature = DirectSunlight2;
		break;
	case DirectSunlight2:
		Settings.Current.Temperature = OvercastSky2;
		break;
	case OvercastSky2:
		Settings.Current.Temperature = ClearBlueSky2;
		break;
	default:
		Settings.Current.Temperature = Candle2;
	}
	#if defined(DEBUGMODE)
		Serial.print("SetColorTemp to: ");
		Serial.println(Settings.Current.Temperature);
	#endif
}
