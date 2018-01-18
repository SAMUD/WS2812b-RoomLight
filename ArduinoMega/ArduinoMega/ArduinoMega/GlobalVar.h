
//defines
#define DEBUGMODE
//#define ETHERNET

//In Out Pins used on my Arduino
#define PINValueChanged 36
#define PINMultiplePresses 34
#define PINInput1 30						//The LSB-Bit coming from the other Arduino
#define PINInput2 28
#define PINInput3 26
#define PINInput4 24
#define PINInput5 22						//The MSB-Bit coming from the other Arduino
#define MIC_PIN   5  // Microphone is attached to this analog pin
#define PIN_RELAIS 53			//Output to the Relais --> enable Power to LEDs

//used for WhiteLeft and WhiteRight
#define NumberLEDLeft 109
#define NumberLEDRight 96
#define ValueLEDDarkside 75

#define NUMBEREFFECTS 15


//The Buttons which are availaible on my Transmitter
/*	Zero= 
	One= 
	Two=		effect modes like Confetti+Strobe
	Three=
	Four=
	Five=		fading, butt all leds have the same color
	Six=		turn on white
	Seven=		fixed color
	Eight=		fading modes with different colors for each LED
	Nine=		turn all leds on at full brightness even when other settings where specified before
	Power=		Turn the strip on/off
	VolUp=		Brightness+
	FuncStop=	change Between Modes --> All,Left,Right,Night
	Reward=		slow down effects / previous color
	PlayPause=	in WhiteModes: Temperature | else: PlayPause
	Forward=	Speed up effects / next color
	Down=		Sturation -
	VolDown=	Brightness-
	Up=			Saturation +
	Eq=			
	StRept=
	Nothing=	Enum default state at bootup
*/



enum Buttons
{
	Zero, One, Two, Three, Four, Five, Six,Seven, Eight, Nine,
	Power, VolUp, FuncStop, Reward, PlayPause, Forward, Down, VolDown, Up, Eq, StRept,
	Nothing
};

/// <summary>
/// Different Color Temperatures for displaying White on the LEDs
/// </summary>
enum ColTemp {
	///<summary>1900K</summary>
	Candle2 = 0xFF9329						/* 1900 K, 255, 147, 41 */,
	///<summary>ca. 2300 Kelvin</summary>
	Candle3 = 0xFFAC5C,
	///<summary>2600 Kelvin</summary>
	Tungsten40W2 = 0xFFC58F					/* 255, 197, 143 */,
	///<summary>2850 Kelvin</summary>
	Tungsten100W2 = 0xFFD6AA				/* 255, 214, 170 */,
	///<summary>3200 Kelvin</summary>
	Halogen2 = 0xFFF1E0						/* 255, 241, 224 */,
	///<summary>5200 Kelvin</summary>
	CarbonArc2 = 0xFFFAF4					/* 255, 250, 244 */,
	///<summary>5400 Kelvin</summary>
	HighNoonSun2 = 0xFFFFFB					/* 255, 255, 251 */,
	///<summary>6000 Kelvin. The maximum possible Brightness.</summary>
	DirectSunlight2 = 0xFFFFFF				/* 255, 255, 255 */,
	///<summary>7000 Kelvin</summary>
	OvercastSky2 = 0xC9E2FF					/* 201, 226, 255 */,
	///<summary>20 000 Kelvin</summary>
	ClearBlueSky2 = 0x409CFF				/* 64, 156, 255 */,

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
};

//enum with the actual Mode
enum Mode
{
	White0, White1, White2,
	FixedColor0, FixedColor1, FixedColor2, FixedColor3,
	Confetti0, Confetti1,
	RainbowMarch, RainbowBeat, ColorPalBeat,
	Fade, RGBFade,
	Strobe,
	Ball
};

/// <summary>
/// Active Displaying-Mode
/// </summary>
enum eDisplay
{
	///<summary>Show LEDs only from start of the strip until NumberLEDLeft </summary>
	Left,
	///<summary>Show LEDs only at the end of the Strip for NumberLEDRight </summary>
	Right,
	///<summary>Turn on all LEDs </summary>
	All,
	///<summary>Only turn on each ModeSetLEDBlock.NightNumber LED  </summary>
	Night
};

//structure with the values read from the other Arduino
static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;

/// <summary>
/// Saving all relevant data for one Display-Mode
/// </summary>
static struct ModeSetLedBlock
{
	///<summary>Target Brightness for LEDs  </summary>
	uint8_t BrightnessSetpoint;
	///<summary>Setup Color Saturation (for example in rainbow mode)</summary>
	uint8_t Saturation;
	///<summary>Setting up Speed of animation</summary>
	uint8_t Speed;
	///<summary>Current Color (in fixed color mode for example)</summary>
	uint8_t Color;
	///<summary>Select which LEDs to use for Displaying</summary>
	eDisplay DisplayMode;
	///<summary>Temperature of LEDs (in White-Mode)</summary>
	ColTemp Temperature;
	///<summary>When DisplayMode is set to "Night", we can select which LEDs to turn on</summary>
	uint8_t NightNumber;
	///<summary>Different Settings</summary>
	uint8_t Set;
	///<summary>EffectNumber corresponding to the enum</summary>
	int NumberEffect;
} ModeSetLedBlock2;


/// <summary>
/// All Settings for LEDs. This one will also be saved in EEPROM.
/// </summary>
static struct StoreStruct
{
	uint8_t MemoryVersion;
	ModeSetLedBlock LedEffects[NUMBEREFFECTS];

	uint8_t EffectNumber = 0;
	uint8_t EffectNumberOld = 127;

}Settings;

static struct StatusVariables
{
	bool Connected = 0;

} Status;


/// <summary>
/// Volatile Settings and Information Bytes
/// </summary>
static struct sDisplayInfo
{
	bool ShowACK;				//Turning on the ACK-Light
	uint8_t ShowPercentage;		//Show setting Percentage
	bool PowerState;			//true=On False=off
	bool ChangesToEffectMade;	//when the LEDS need to be redrwan, cause there were changes to the effects 
	bool PlayPause;
}SettingsNow;

