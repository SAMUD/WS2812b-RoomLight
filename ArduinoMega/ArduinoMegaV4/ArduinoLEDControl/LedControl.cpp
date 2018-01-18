 
#include "LedControl.h"
#include "GlobalVarLEDControl.h"
#include "MyEEPROM.h"

LedControlClass::LedControlClass()
{

}


void LedControlClass::Init(int NumberLEDs, bool SetDither)
{
	#if defined(DEBUGMODE)
		Serial.print("LED-Control Library: V");
		Serial.println(ClassVersion);
	#endif
	
	FastLED.addLeds <NEOPIXEL, DATA_PIN>(leds, NumberLEDs);
	FastLED.setBrightness(0);
	FastLED.setDither(SetDither);

	//setup Relais for main Power supply
	pinMode(PIN_RELAIS, OUTPUT);

	//prepare EEPROM
	EEPROMStart();

	//Turn on LEDs
	digitalWrite(PIN_RELAIS, 0);
	SettingsNow.PowerState = true;
	SettingsNow.ChangesToEffectMade = true;
	SettingsNow.PlayPause = true;

}

// Public Methods implementation
void LedControlClass::Loop()
{
	if (SettingsNow.PowerState)
		BrightnessFade(Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint);		//call the fading function for the Brightness

																	//Display Effect
	//DisplayEffectMain();
	DisplayEffectWhite();

	fill_solid(ledstemp, 50, CRGB::Red);
	//FastLED.setBrightness(255);

	OutputToLed();
	
}

//Turning on or off the LED-Strip
void LedControlClass::SetOnOff(bool NewState)
{
	if (SettingsNow.PowerState != NewState)
	{
		//someone turned on or off the LEDs
		SettingsNow.PowerState = NewState;

		if (!SettingsNow.PowerState)
		{
			#ifdef DEBUGMODE
				Serial.println("LEDControl.SetOnOff to off");
			#endif
			EEPROMsave();
			BrightnessTurnOff();
		}
		else
		{
			#ifdef DEBUGMODE
				Serial.println("LEDControl.SetOnOff to on");
			#endif
			BrightnessTurnOn();
			SettingsNow.ChangesToEffectMade = 1;
		}
	}
}

//check if the LEDs are on or off at the moment
bool LedControlClass::GetOnOffState()
{
	return SettingsNow.PowerState;
}

bool LedControlClass::ToggleOnOff()
{
	if (GetOnOffState())
		//It's on. we should turn it off
		SetOnOff(false);
	else
		//It's off. we should turn it on
		SetOnOff(true);

	//now return the new state
	return SettingsNow.PowerState;
}

//Play/Pause on the LED-Strip
void LedControlClass::SetPause(bool NewState)
{
	SettingsNow.PlayPause = NewState;
}

bool LedControlClass::GetPauseState()
{
	return SettingsNow.PlayPause;
}

bool LedControlClass::TogglePause()
{
	SettingsNow.PlayPause != SettingsNow.PlayPause;

	//now return the new state
	return SettingsNow.PlayPause;

}

void LedControlClass::SetBrightness(uint8_t NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint = NewValue;
	SettingsNow.ChangesToEffectMade = 1;
	SettingsNow.ShowACK = 0;
	SettingsNow.ShowPercentage = NewValue;

}

uint8_t LedControlClass::GetBrightness()
{
	return Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint;
}

void LedControlClass::SetNightNumber(uint8_t NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].NightNumber = NewValue;
}

void LedControlClass::SetDisplayMode(eDisplay NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].DisplayMode = NewValue;
}

void LedControlClass::SetNextDisplayMode()
{
	#if defined(DEBUGMODE)
		Serial.print("DisplayMode | Changed to: ");
	#endif

	switch (Settings.LedEffects[Settings.EffectNumber].DisplayMode)
	{
	case Left:
		Settings.LedEffects[Settings.EffectNumber].DisplayMode == Right;
		#if defined(DEBUGMODE)
			Serial.println("Right");
		#endif
		break;
	case Right:
		Settings.LedEffects[Settings.EffectNumber].DisplayMode == Night;
		#if defined(DEBUGMODE)
			Serial.println("Night");
		#endif
		break;
	case Night:
		Settings.LedEffects[Settings.EffectNumber].DisplayMode == All;
		#if defined(DEBUGMODE)
			Serial.println("All");
		#endif
		break;
	case All:
		Settings.LedEffects[Settings.EffectNumber].DisplayMode == Left;
		#if defined(DEBUGMODE)
			Serial.println("Left");
		#endif
		break;
	default:
		Settings.LedEffects[Settings.EffectNumber].DisplayMode == Left;
		#if defined(DEBUGMODE)
			Serial.println("Left (default)");
		#endif
		break;
	}

	SettingsNow.ChangesToEffectMade = 1;

	//show status update
	SettingsNow.ShowACK = 1;
	SettingsNow.ShowPercentage = 0;
}

void LedControlClass::SetSaturation(uint8_t NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].Saturation = NewValue;
}

void LedControlClass::SetSet(uint8_t NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].Set = NewValue;
}

void LedControlClass::SetSpeed(uint8_t NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].Speed = NewValue;
}

void LedControlClass::SetTemp(ColTemp NewValue)
{
	Settings.LedEffects[Settings.EffectNumber].Temperature = NewValue;
	SettingsNow.ChangesToEffectMade = true;
}

ColTemp LedControlClass::GetTemp()
{
	return Settings.LedEffects[Settings.EffectNumber].Temperature;
}

void LedControlClass::SetNextTemp()
{
	
	#if defined(DEBUGMODE)
		Serial.print("LEDClass.SetColorTemp from ");
		Serial.print( int(GetTemp()) );
		Serial.print(" to ");
	#endif
	switch (GetTemp())
	{
	case Candle2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == Candle3;
		break;
	case Candle3:
		Settings.LedEffects[Settings.EffectNumber].Temperature == Tungsten40W2;
		break;
	case Tungsten40W2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == Tungsten100W2;
		break;
	case Tungsten100W2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == Halogen2;
		break;
	case Halogen2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == CarbonArc2;
		break;
	case CarbonArc2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == HighNoonSun2;
		break;
	case HighNoonSun2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == DirectSunlight2;
		break;
	case DirectSunlight2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == OvercastSky2;
		break;
	case OvercastSky2:
		Settings.LedEffects[Settings.EffectNumber].Temperature == ClearBlueSky2;
		break;
	default:
		Settings.LedEffects[Settings.EffectNumber].Temperature == Candle2;
	}
	#if defined(DEBUGMODE)
		Serial.println(int(Settings.LedEffects[Settings.EffectNumber].Temperature));
	#endif

		SettingsNow.ChangesToEffectMade = true;
}

void LedControlClass::SetNewMode(int Effect)
{
	
	//Select new Mode
	Settings.EffectNumber = Effect;

	#ifdef DEBUGMODE
		Serial.print("LEDClass.SetNewMode to ");
		Serial.println(Effect);
	#endif // DEBUGMODE


	//Turn on LEDs at the end
	LedControlClass::SetOnOff(true);

	SettingsNow.ChangesToEffectMade = 1;

	//show status update
	SettingsNow.ShowACK = 1;
	SettingsNow.ShowPercentage = 0;
}

int LedControlClass::GetMode()
{
	return Settings.EffectNumber;
}

void LedControlClass::OutputToLed()
{
	memmove(&leds[0], &ledstemp[0], NUMleds * sizeof(CRGB));

	static uint16_t dot = 0;
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Left)
		fill_solid(&leds[NUMleds_Left], NUMleds - NUMleds_Left, CHSV(0, 0, 0));
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Right)
		fill_solid(leds, NUMleds - (NUMleds_Right - 1), CHSV(0, 0, 0));
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Night)
	{
		for (dot = 0; dot < NUMleds; dot = dot + 1)
		{
			if (dot%Settings.LedEffects[Settings.EffectNumber].NightNumber)
				leds[dot] = CRGB::Black;
		}
	}

	static uint8_t counter = 0;

	//if the state of the variable to show infos on the LEDs went true
	if (SettingsNow.ShowACK)
	{
		counter = 25;
		SettingsNow.ShowACK = 0;

#ifdef DEBUGMODE
		Serial.println("OutputToLED | DisplayInfo updated ");
#endif // DEBUGMODE

	}

	if (counter > 0)
	{
		//display info
		if (SettingsNow.ShowPercentage > 0)
		{
			fill_solid(leds, SettingsNow.ShowPercentage / 10, CRGB::Green);
			fill_solid(&(leds[SettingsNow.ShowPercentage / 10]), 25 - (SettingsNow.ShowPercentage / 10), CRGB::Black);
			leds[25] = CRGB::Red;
		}
		else
		{
			leds[1] = CRGB::Green;
			leds[2] = CRGB::Red;
		}
		leds[0] = CRGB::Red;

		//decrease the counter-display time
		EVERY_N_MILLISECONDS(100)
		{
			counter = counter - 1;
			if (counter == 0)
				SettingsNow.ShowPercentage = 0;
		}

	}

	FastLED.show();
		
}

void LedControlClass::DisplayEffectMain()
{
	//DisplayMode has changed.
	if (Settings.EffectNumber != Settings.EffectNumberOld)
	{
		DisplayEffectTransition();								//show a transition from one to the other effect

#ifdef DEBUGMODE
		Serial.print("DisplyEffect: has changed from");
		Serial.print(Settings.EffectNumberOld);
		Serial.print("to");
		Serial.println(Settings.EffectNumber);
#endif // DEBUGMODE

		Settings.EffectNumberOld = Settings.EffectNumber;
		SettingsNow.ChangesToEffectMade = true;
	}


	//Select the right effect from the list
	if (Settings.EffectNumber <= White2)
		DisplayEffectWhite();
	else if (Settings.EffectNumber <= FixedColor3 && SettingsNow.ChangesToEffectMade)
		DisplayEffectFixedColor();
	else if (Settings.EffectNumber <= Confetti1 && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectConfettiColorfull();
	else if (Settings.EffectNumber = RainbowMarch && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRainbowMarch();
	else if (Settings.EffectNumber = RainbowBeat && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRainbowBeat();
	else if (Settings.EffectNumber = ColorPalBeat && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectColorPalBeat();
	else if (Settings.EffectNumber = Fade && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectFade();
	else if (Settings.EffectNumber = RGBFade && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRGBFade();
	else if (Settings.EffectNumber = Strobe && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectStrobe();
	else if (Settings.EffectNumber = Ball && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectBall();
	else
	{
#ifdef DEBUGMODE
		Serial.print("DisplyEffect: Error. EffectNumber: ");
		Serial.println(Settings.EffectNumber);
#endif // DEBUGMODE		
	}
}

//Transition
void LedControlClass::DisplayEffectTransition()
{
	//currently not used
}

//Showing all LEDs in white
void LedControlClass::DisplayEffectWhite()
{
	fill_solid(ledstemp, NUMleds, Settings.LedEffects[Settings.EffectNumber].Temperature);
	SettingsNow.ChangesToEffectMade = 0;
}

//displaying Confetti-Effect
void LedControlClass::DisplayEffectConfetti()
{
#define huediff 510													
	static int					thishue = 0;                               // Starting hue.
	static int8_t				thisinc = 3;                               // Incremental value for rotating hues

	uint8_t secondHand = (millis() / 1000) % 15;							// Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;

	if (lastSecond != secondHand)
	{
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thisinc = 0; break;
		case  5: thisinc = 3; break;
		case 10: thisinc = 1; break;
		case 15: thisinc = 1; break;
		}
	}

	EVERY_N_MILLISECONDS(40)
	{
		fadeToBlackBy(ledstemp, NUMleds, beatsin8(5, Settings.LedEffects[Settings.EffectNumber].Speed / 2, Settings.LedEffects[Settings.EffectNumber].Speed * 2));
		int pos = random16(NUMleds);									// Pick an LED at random.
		ledstemp[pos] += CHSV((thishue + random16(huediff)) / 4, 255, 255);
		thishue = thishue + thisinc;
	}

	SettingsNow.ChangesToEffectMade = 1; //periodic update needed
}

void LedControlClass::DisplayEffectConfettiColorfull()
{
#define huediff 255														
	static int					thissat = 255;                               // Starting hue.

	uint8_t secondHand = (millis() / 1000) % 15;							// Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;

	if (lastSecond != secondHand)
	{
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thissat = 50; break;
		case  5: thissat = 255; break;
		case 10: thissat = 255; break;
		case 15: thissat = 170; break;
		}
	}

	EVERY_N_MILLISECONDS(40)
	{
		fadeToBlackBy(ledstemp, NUMleds, beatsin8(5, Settings.LedEffects[Settings.EffectNumber].Speed / 2, Settings.LedEffects[Settings.EffectNumber].Speed * 2));
		int pos = random16(NUMleds);									// Pick an LED at random.
		ledstemp[pos] += CHSV(random16(huediff), thissat, 255);
	}

	SettingsNow.ChangesToEffectMade = 1;								//periodic update needed
}

//display a marching rainbow
void LedControlClass::DisplayEffectRainbowMarch()
{
	static uint8_t start = 0;
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter;

	EVERY_N_MILLISECONDS(40)
	{

		fill_gradient(ledstemp, NUMleds, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
			start2 = start2 + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
			{
				counter = 129;
				++start;
				++start2;
			}
			--counter;
		}

		if (start > 255)
			start = start - 255;
		if (start2 > 255)
			start2 = start2 - 255;
	}
	SettingsNow.ChangesToEffectMade = 1;	//periodic update needed
}

//display a Rainbow going back and forth using a sinus curve
void LedControlClass::DisplayEffectRainbowBeat()
{
	static uint8_t start = 0;
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter = 0;

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUMleds, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + beatsin16(5, (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1), (((Settings.LedEffects[Settings.EffectNumber].Speed - 75) / 10) + 1));
			start2 = start2 + beatsin16(5, (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1), (((Settings.LedEffects[Settings.EffectNumber].Speed - 75) / 10) + 1));
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
			{
				counter = 129;
				start = start + beatsin16(3, 1, 4);
				start2 = start2 + beatsin16(3, 1, 4);
			}
			--counter;
		}

		if (start > 255)
			start = start - 255;
		if (start2 > 255)
			start2 = start2 - 255;
	}
	SettingsNow.ChangesToEffectMade = 1;	//periodic update needed
}

//testing
void LedControlClass::DisplayEffectColorPalBeat()
{
	EVERY_N_MILLISECONDS(20)
	{
		uint8_t CurrentSpeed = Settings.LedEffects[Settings.EffectNumber].Speed;

		if (CurrentSpeed < 10)
			CurrentSpeed = 10;

		/*uint8_t beatA = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/4, 0, 255);								// Starting hue
		uint8_t beatB = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/6, 0, 255);
		uint8_t beatC = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/10, 0, 255);
		fill_rainbow(ledstemp, NUMleds, (beatA + beatB+ beatC) / 3, Settings.LedEffects[Settings.EffectNumber].Saturation/15);   // Use FastLED's fill_rainbow routine.*/
		//Simplified to:
		fill_rainbow(ledstemp, NUMleds, (beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 4, 0, 255) +
			beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 6, 0, 255) +
			beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 10, 0, 255)) / 3, Settings.LedEffects[Settings.EffectNumber].Saturation / 15);   // Use FastLED's fill_rainbow routine.
	}

	SettingsNow.ChangesToEffectMade = 1;	//periodic update needed

}

//filling all the leds with the same color and fading between
void LedControlClass::DisplayEffectFade()
{
	static uint8_t counter = 128;
	static uint8_t start = 0;
	static uint8_t start2 = 15; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUMleds, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
			start2 = start2 + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
			{
				counter = 129;
				++start;
				++start2;
			}
			--counter;
		}

		if (start > 255)
			start = start - 255;
		if (start2 > 255)
			start2 = start2 - 255;
	}
	SettingsNow.ChangesToEffectMade = 1;
}

void LedControlClass::DisplayEffectRGBFade()
{
	static int16_t Counter = 0;
	static uint8_t counter = 128;
	static uint8_t start;
	static uint8_t state = 0;
	CRGB temp;
	EVERY_N_MILLISECONDS(40)
	{

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
			{
				counter = 129;
				++start;
			}
			--counter;
		}

		switch (state)
		{
		case 0:
			temp.setRGB(Counter, 0, 0);
			Counter = Counter + start;
			break;
		case 1:
			temp.setRGB(Counter, 0, 0);
			Counter = Counter - start;
			break;
		case 2:
			temp.setRGB(0, Counter, 0);
			Counter = Counter + start;
			break;
		case 3:
			temp.setRGB(0, Counter, 0);
			Counter = Counter - start;
			break;
		case 4:
			temp.setRGB(0, 0, Counter);
			Counter = Counter + start;
			break;
		case 5:
			temp.setRGB(0, 0, Counter);
			Counter = Counter - start;
			break;
		}

		if (Counter > 255)
		{
			Counter = 255;
			++state;
		}
		if (Counter < 0)
		{
			Counter = 0;
			++state;
		}
		if (state >= 6)
			state = 0;

		fill_solid(ledstemp, NUMleds, temp);

	}
	SettingsNow.ChangesToEffectMade = 1;
}

void LedControlClass::DisplayEffectStrobe()
{
	static uint8_t counter = 0;

	if (counter < 12)
	{
		if (counter == 0 || counter == 2 || counter == 4 || counter == 6 || counter == 8 || counter == 10 || counter == 12)
		{
			EVERY_N_MILLISECONDS(50)
			{
				fill_solid(ledstemp, NUMleds, CRGB::White);
				++counter;
			}
		}
		else
		{
			EVERY_N_MILLISECONDS(50)
			{
				fill_solid(ledstemp, NUMleds, CRGB::Black);
				++counter;
			}
		}
	}
	else
	{
		EVERY_N_MILLISECONDS(50)
		{
			counter = counter + random16(255);
			if (counter > 200)
				counter = 0;
			else
				counter = 15;
		}
	}


}

void LedControlClass::DisplayEffectFixedColor()
{
	fill_solid(ledstemp, NUMleds, CHSV(Settings.LedEffects[Settings.EffectNumber].Speed, Settings.LedEffects[Settings.EffectNumber].Saturation, 255));
	Serial.print("Color and Saturation:");
	Serial.print(Settings.LedEffects[Settings.EffectNumber].Speed);
	Serial.print("  ");
	Serial.println(Settings.LedEffects[Settings.EffectNumber].Saturation);
	SettingsNow.ChangesToEffectMade = 0;
}

void LedControlClass::DisplayEffectBall()
{

	/*static CRGBPalette16 currentPalette;

	static uint32_t xscale = 5;                                          // How far apart they are
	static uint32_t yscale = 1;                                           // How fast they move
	static uint8_t index = 0;

	currentPalette = CRGBPalette16(
	CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
	CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
	CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
	CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

	EVERY_N_MILLISECONDS(40)
	{
	for (int i = 0; i < NUMleds; i++) {
	index = inoise8(i*xscale, millis()*yscale*NUMleds / 255);                                           // X location is constant, but we move along the Y at the rate of millis()
	ledstemp[i] = ColorFromPalette(currentPalette, min(i*(index) >> 6, 255), i * 255 / NUMleds, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
	}
	}*/

	EVERY_N_MILLISECONDS(40)
	{
		uint8_t CurrentSpeed = Settings.LedEffects[Settings.EffectNumber].Speed;
		static uint8_t ColorWheel = 0;

		if (CurrentSpeed < 6)
			CurrentSpeed = 6;
		EVERY_N_MILLISECONDS(1000)
		{
			if (SettingsNow.PlayPause == true)
				ColorWheel = ColorWheel + beatsin8(CurrentSpeed / 10, 1, 10);
		}

		uint16_t inner = beatsin16(CurrentSpeed / 6, NUMleds / 4, NUMleds / 4 * 3);    // Move 1/4 to 3/4
		uint16_t outer = beatsin16(CurrentSpeed / 6, 0, NUMleds - 1);               // Move entire length
		uint16_t middle = beatsin16(CurrentSpeed / 6, NUMleds / 3, NUMleds / 3 * 2);   // Move 1/3 to 2/3

		ledstemp[middle] = CHSV(ColorWheel + 40, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);
		ledstemp[inner] = CHSV(ColorWheel + 20, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);
		ledstemp[outer] = CHSV(ColorWheel, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);

		nscale8(ledstemp, NUMleds, Settings.LedEffects[Settings.EffectNumber].Set + 250);
	}

	SettingsNow.ChangesToEffectMade = 1;
}

//Fading the Brightness to the Value specified in LEDSetLedBlock.BrightnessSetpoint
void LedControlClass::BrightnessFade(uint8_t Setpoint)
{
	EVERY_N_MILLISECONDS(40)
	{
		uint8_t incrementor = 0;

		//when Setpoint is not the same as actual brightness
		incrementor = 1;
		if (FastLED.getBrightness() - Setpoint > 10 || FastLED.getBrightness() - Setpoint < -10)
			incrementor = 2;
		if (FastLED.getBrightness() - Setpoint > 20 || FastLED.getBrightness() - Setpoint < -20)
			incrementor = 4;
		if (FastLED.getBrightness() - Setpoint > 30 || FastLED.getBrightness() - Setpoint < -30)
			incrementor = 8;
		if (FastLED.getBrightness() - Setpoint > 40 || FastLED.getBrightness() - Setpoint < -40)
			incrementor = 16;
		if (FastLED.getBrightness() - Setpoint > 70 || FastLED.getBrightness() - Setpoint < -70)
			incrementor = 32;

		if (FastLED.getBrightness() < Setpoint)
			FastLED.setBrightness(FastLED.getBrightness() + incrementor);

		if (FastLED.getBrightness() > Setpoint)
			FastLED.setBrightness(FastLED.getBrightness() - incrementor);
	}
}

//Turning off the LED-Strip
void LedControlClass::BrightnessTurnOff()
{

	while (FastLED.getBrightness() > 0)
	{
		//run BrightnessFade until brightness is 0
		EVERY_N_MILLISECONDS(30)
		{
			BrightnessFade(0);
			OutputToLed();
		}
	}
#ifdef DEBUGMODE
	Serial.println("BrightnessTurnOff | Powered down now");
#endif // DEBUGMODE


	digitalWrite(PIN_RELAIS, 1);
}

//Turning on the LED-Strip
void LedControlClass::BrightnessTurnOn()
{
	digitalWrite(PIN_RELAIS, 0);
}
