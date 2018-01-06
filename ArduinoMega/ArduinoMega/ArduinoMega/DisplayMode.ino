void DisplayModeMain()
{
	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == FuncStop)
	{
		LEDBlockSetNextDisplayMode();
		ReadValues.newValues = 0;
	}
}
