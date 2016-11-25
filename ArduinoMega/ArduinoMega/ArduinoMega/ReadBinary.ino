static bool ValueChanged = 0;


void ReadBinaryMain()
{
	EVERY_N_MILLISECONDS(50) //run only each 50ms = 20Hz
	{
		if (digitalRead(PINValueChanged) != ValueChanged)
		{
			//there is something new at the input pins
			Serial.println("Reading new values from other Arduino");
			ValueChanged = !ValueChanged;
			ReadButton();
			ReadValues.newValues = 1;
		}

		ReadValues.Repeat = digitalRead(PINMultiplePresses);
	}
	
}


 void ReadButton()
{
	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
	 {
		 ReadValues.ButtonPressed = Power;
		 Serial.println("Power");
	 }

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = VolUp;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = FuncStop;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Reward;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = PlayPause;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Forward;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Down;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = VolDown;


	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Up;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Zero;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Eq;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = StRept;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = One;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Two;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Three;

	 if (digitalRead(PINInput5) == 0 && digitalRead(PINInput4) == 1 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Four;

	 if (digitalRead(PINInput5) == 1 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Five;

	 if (digitalRead(PINInput5) == 1 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Six;

	 if (digitalRead(PINInput5) == 1 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Seven;

	 if (digitalRead(PINInput5) == 1 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 0 && digitalRead(PINInput2) == 1 && digitalRead(PINInput1) == 1)
		 ReadValues.ButtonPressed = Eight;

	 if (digitalRead(PINInput5) == 1 && digitalRead(PINInput4) == 0 && digitalRead(PINInput3) == 1 && digitalRead(PINInput2) == 0 && digitalRead(PINInput1) == 0)
		 ReadValues.ButtonPressed = Nine;

}