
void TempPlayPauseMain()
{
	if (ReadValues.newValues == 1 && ReadValues.Repeat == 0 && ReadValues.ButtonPressed == PlayPause)
	{
		myLEDs.TogglePause();
		myLEDs.SetNextTemp();
		ReadValues.newValues = 0;
	}
}


