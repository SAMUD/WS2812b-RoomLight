
/**
* @brief This will test if the Button passed in parameters has been pressed and change values accordingly
*
* @param PassedPressedButton Which button has to be pressed to make -
* @param PassedPressedButtonPlus Which button has to be pressed to do +
* @param PassedRepeatAllowed Can this value be changed by holding down the Button?
* @param PassedValueToChange Pointer pointing to the Value which should be changed
* @param PassedMinAllowed The minimal value possible
* @param PassedMaxAllowed The maximal value allowed
* @param PassedSlowScaling The number of increments to do when doing a simle press
* @param PassedFastScaling The number of increments if fast scaling. Only needed when @p PassedRepeatAllowed is set to true
*/
uint8_t ChangeParamMain(uint8_t PassedPressedButton, uint8_t PassedPressedButtonPlus, bool PassedRepeatAllowed, uint8_t PassedValueCurrent, uint8_t PassedMinAllowed, uint8_t PassedMaxAllowed, uint8_t PassedSlowScaling, uint8_t PassedFastScaling)
{
	uint8_t ReturnValue = PassedValueCurrent;
	
	//Test if the Button has been Pressed
	if (ReadValues.ButtonPressed == PassedPressedButton && (ReadValues.newValues || (ReadValues.Repeat && PassedRepeatAllowed)))
	{
		//Do Fast Scaling when holding down the Button
		if (ReadValues.Repeat == 1)
		{
			if (PassedValueCurrent > (PassedMinAllowed + PassedFastScaling))
			{
				ReturnValue = PassedValueCurrent - PassedFastScaling;
#if defined(DEBUGMODE)
				Serial.print("----  ");
#endif
			}
			else
			{
				ReturnValue = PassedMinAllowed;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif			
			}
		}
		else //Slow scaling
		{
			if (PassedValueCurrent > (PassedMinAllowed + PassedSlowScaling))
			{
				ReturnValue = PassedValueCurrent - PassedSlowScaling;
#if defined(DEBUGMODE)
				Serial.print("--    ");
#endif
			}
			else
			{
				ReturnValue = PassedMinAllowed;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif
			}
		}
#if defined(DEBUGMODE)
		Serial.print("ChangeParam | :");
		Serial.print(PassedValueCurrent);
		Serial.print(" to ");
		Serial.println(ReturnValue);

#endif

		//show status update
		ReadValues.newValues = 0;
		
	}

	//Test if the + Button has been Pressed
	if (ReadValues.ButtonPressed == PassedPressedButtonPlus && (ReadValues.newValues || (ReadValues.Repeat && PassedRepeatAllowed)))
	{
		//Do Fast Scaling when holding down the Button
		if (ReadValues.Repeat == 1)
		{
			if (PassedValueCurrent < (PassedMaxAllowed - PassedFastScaling))
			{
				ReturnValue = PassedValueCurrent + PassedFastScaling;
#if defined(DEBUGMODE)
				Serial.print("++++  ");
#endif
			}
			else
			{
				ReturnValue = PassedMaxAllowed;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif			
			}
		}
		else //Slow scaling
		{
			if (PassedValueCurrent < (PassedMaxAllowed - PassedSlowScaling))
			{
				ReturnValue = PassedValueCurrent + PassedSlowScaling;
#if defined(DEBUGMODE)
				Serial.print("++    ");
#endif
			}
			else
			{
				ReturnValue = PassedMaxAllowed;
#if defined(DEBUGMODE)
				Serial.print("oo    ");
#endif
			}
		}
#if defined(DEBUGMODE)
		Serial.print("ChangeParam | :");
		Serial.print(PassedValueCurrent);
		Serial.print(" to ");
		Serial.println(ReturnValue);

#endif

		//show status update
		ReadValues.newValues = 0;
	}



	return ReturnValue;
}
