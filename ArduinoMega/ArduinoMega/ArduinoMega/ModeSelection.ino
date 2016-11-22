void ModeSelectionMain()
{
	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed==FuncStop)
	{
		if (LEDSettings.DisplayMode == WhiteAll)
			LEDSettings.DisplayMode = WhiteLeft;
		else if (LEDSettings.DisplayMode == WhiteLeft)
			LEDSettings.DisplayMode = WhiteRight;
		else
			LEDSettings.DisplayMode = WhiteAll;

		if (!LEDSettings.PowerState)
		{
			LEDSettings.PowerState = 1;
			LEDSettings.DisplayMode = LEDSettings.DisplayModeOld;
			//BrightnessTurnOn();
		}
	}

	if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Nine)
	{
		//making full white
		LEDSettings.DisplayMode = WhiteAll;
		LEDSettings.BrightnessSetpoint = 255;
		LEDSettings.Saturation = 0;
		LEDSettings.Hue = 0;
		if (!LEDSettings.PowerState)
			LEDSettings.PowerState = 1;

	}
}
