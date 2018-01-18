
void TempPlayPauseMain()
{
	if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
	{
		if (Settings.EffectNumber <= White2)
		{
			//set next color temp
			SetColorTemp();
			SettingsNow.ChangesToEffectMade = true;
		}
		else
		{
			//when not in White Modes Play Pause for the Effects
			SettingsNow.PlayPause = !SettingsNow.PlayPause;
		}
		ReadValues.newValues = 0;
		SettingsNow.ShowACK = 1;
	}
}

void SetColorTemp()
{
	switch (Settings.LedEffects[Settings.EffectNumber].Temperature)
	{
	case Candle2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = Candle3;
		break;
	case Candle3:
		Settings.LedEffects[Settings.EffectNumber].Temperature = Tungsten40W2;
		break;
	case Tungsten40W2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = Tungsten100W2;
		break;
	case Tungsten100W2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = Halogen2;
		break;
	case Halogen2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = CarbonArc2;
		break;
	case CarbonArc2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = HighNoonSun2;
		break;
	case HighNoonSun2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = DirectSunlight2;
		break;
	case DirectSunlight2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = OvercastSky2;
		break;
	case OvercastSky2:
		Settings.LedEffects[Settings.EffectNumber].Temperature = ClearBlueSky2;
		break;
	default:
		Settings.LedEffects[Settings.EffectNumber].Temperature = Candle2;
	}
	#if defined(DEBUGMODE)
		Serial.print("SetColorTemp to: ");
		Serial.println(Settings.LedEffects[Settings.EffectNumber].Temperature);
	#endif
}
