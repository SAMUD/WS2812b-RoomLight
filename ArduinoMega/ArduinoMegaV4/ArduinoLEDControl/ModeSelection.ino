void ModeSelectionMain()
{

	//needs only to be run every 40ms because values from other Arduino are also only read each 50ms
	EVERY_N_MILLISECONDS(40)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Six)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to White0-2");
			#endif
			switch ( int(myLEDs.GetMode()) )
			{
				case White0:
					myLEDs.SetNewMode(White1);

					break;
				case White1:
					myLEDs.SetNewMode(White2);
					break;
				case White2:
					myLEDs.SetNewMode(White0);
					break;
				default:
					myLEDs.SetNewMode(White0);
					break;
			}
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Four)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to Ball");
			#endif
			myLEDs.SetNewMode(Ball);
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to Rainbow");
			#endif
			switch ( int(myLEDs.GetMode()) )
			{
			case RainbowBeat:
				myLEDs.SetNewMode(ColorPalBeat);
				break;
			case RainbowMarch:
				myLEDs.SetNewMode(RainbowBeat);
				break;
			case ColorPalBeat:
				myLEDs.SetNewMode(RainbowMarch);
				break;
			default:
				myLEDs.SetNewMode(RainbowMarch);
				break;
			}
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Five)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to Fade");
			#endif
			switch ( int(myLEDs.GetMode()) )
			{
			case Fade:
				myLEDs.SetNewMode(RGBFade);
				break;
			default:
				myLEDs.SetNewMode(Fade);
				break;
			}
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Two)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to Effect1");
			#endif
			switch ( int(myLEDs.GetMode()) )
			{
			case Confetti0:
				myLEDs.SetNewMode(Confetti1);
				break;
			case Confetti1:
				myLEDs.SetNewMode(Strobe);
				break;
			default:
				myLEDs.SetNewMode(Confetti0);
				break;
			}
			ReadValues.newValues = 0;
		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Seven)
		{
			//switching to the next mode (White)
			#if defined(DEBUGMODE)
			Serial.println("ModeSelectionMain | Changed to FixedColor");
			#endif
			switch ( int(myLEDs.GetMode()) )
			{
			case FixedColor0:
				myLEDs.SetNewMode(FixedColor1);
				break;
			case FixedColor1:
				myLEDs.SetNewMode(FixedColor2);
				break;
			case FixedColor2:
				myLEDs.SetNewMode(FixedColor3);
				break;
			default:
				myLEDs.SetNewMode(FixedColor0);
				break;
			}
			ReadValues.newValues = 0;
		}
	}

}
