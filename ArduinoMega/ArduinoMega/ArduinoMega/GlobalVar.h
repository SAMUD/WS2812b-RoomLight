


//defines
#define DEBUGMODE

//In Out Pins used on my Arduino
#define PINValueChanged 36
#define PINMultiplePresses 34
#define PINInput1 30						//The LSB-Bit coming from the other Arduino
#define PINInput2 28
#define PINInput3 26
#define PINInput4 24
#define PINInput5 22						//The MSB-Bit coming from the other Arduino

//used for WhiteLeft and WhiteRight
#define NumberLEDLeft 109
#define NumberLEDRight 96
#define NumberLEDTransition 10
#define ValueLEDDarkside 75

//The Buttons which are availaible on my Transmitter
/*	Zero=
	Zero= 
	One= 
	Two=
	Three=
	Four=
	Five=
	Six=
	Seven=
	Eight=
	Nine=		turn all leds on at full brightness even when other settings where specified before
	Power=		Turn the strip on/off
	VolUp=		Brightness+
	FuncStop=	change Between White Modes --> White All, WhiteLeft, WhiteRight
	Reward=		in all White-Modes: Temperature-
	PlayPause=
	Forward=	in all White-Modes: Temperature+
	Down=
	VolDown=	Brightness-
	Up=
	Eq=
	StRept=
	Nothing=Enum default state at bootup
*/
enum Buttons
{
	Zero, One, Two, Three, Four, Five, Six,Seven, Eight, Nine,
	Power, VolUp, FuncStop, Reward, PlayPause, Forward, Down, VolDown, Up, Eq, StRept,
	Nothing
};

 enum ColTemp{
	/// 1900 Kelvin
	Candle2 = 0xFF9329 /* 1900 K, 255, 147, 41 */,
	Candle3 = 0xFFAC5C,
	/// 2600 Kelvin
	Tungsten40W2 = 0xFFC58F /* 2600 K, 255, 197, 143 */,
	/// 2850 Kelvin
	Tungsten100W2 = 0xFFD6AA /* 2850 K, 255, 214, 170 */,
	/// 3200 Kelvin
	Halogen2 = 0xFFF1E0 /* 3200 K, 255, 241, 224 */,
	/// 5200 Kelvin
	CarbonArc2 = 0xFFFAF4 /* 5200 K, 255, 250, 244 */,
	/// 5400 Kelvin
	HighNoonSun2 = 0xFFFFFB /* 5400 K, 255, 255, 251 */,
	/// 6000 Kelvin
	DirectSunlight2 = 0xFFFFFF /* 6000 K, 255, 255, 255 */,
	/// 7000 Kelvin
	OvercastSky2 = 0xC9E2FF /* 7000 K, 201, 226, 255 */,
	/// 20000 Kelvin
	ClearBlueSky2 = 0x409CFF /* 20000 K, 64, 156, 255 */,
	///@}

	/// @name Gaseous light sources
	/// Gaseous light sources emit discrete spectral bands, and while we can
	/// approximate their aggregate hue with RGB values, they don't actually
	/// have a proper Kelvin temperature.
	///@{
	WarmFluorescent2 = 0xFFF4E5 /* 0 K, 255, 244, 229 */,
	StandardFluorescent2 = 0xF4FFFA /* 0 K, 244, 255, 250 */,
	CoolWhiteFluorescent2 = 0xD4EBFF /* 0 K, 212, 235, 255 */,
	FullSpectrumFluorescent2 = 0xFFF4F2 /* 0 K, 255, 244, 242 */,
	GrowLightFluorescent2 = 0xFFEFF7 /* 0 K, 255, 239, 247 */,
	BlackLightFluorescent2 = 0xA700FF /* 0 K, 167, 0, 255 */,
	MercuryVapor2 = 0xD8F7FF /* 0 K, 216, 247, 255 */,
	SodiumVapor2 = 0xFFD1B2 /* 0 K, 255, 209, 178 */,
	MetalHalide2 = 0xF2FCFF /* 0 K, 242, 252, 255 */,
	HighPressureSodium2 = 0xFFB74C /* 0 K, 255, 183, 76 */,
	///@}

	/// Uncorrected temperature 0xFFFFFF
	Normal2 = 0xFFFFFF
};

//enum with the actual Mode
enum Mode
{
	None,
	WhiteLeft,WhiteRight,WhiteAll,
	Confetti, RainbowMarch, RainbowBeat, ColorPalBeat,
	Fade
};

//structure with the values read from the other Arduino
static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;



//All Settings used at the moment
//will later be saved in the EEPROM
static struct Settings
{
	ColTemp Temperature;
	uint8_t BrightnessSetpoint;		//Setpoint for the Brightness
	bool PowerState;				//true=On False=off
	Mode DisplayMode;				//the Actual Mode
	Mode DisplayModeOld;			//the Old mode
	uint8_t Hue;					//used in Temperature Settings
	uint8_t Saturation;				//used in Temperature Settings
	uint8_t ChangesToEffectMade;		//when the LEDS need to be redrwan, cause there were changes to the effects 
	bool PlayPause;
}LEDSettings;

