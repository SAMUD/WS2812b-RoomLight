

void TempPlayPauseMain()
{
	if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
	{
		if (Settings.DisplayMode == White || Settings.DisplayMode == White2)
		{
			//set next color temp
			LEDBlockSetNextTemp();
		}
		else
		{
			//when not in White Modes Play Pause for the Effects
			LEDBlockSetPauseToggle();
		}
		ReadValues.newValues = 0;
	}
}


