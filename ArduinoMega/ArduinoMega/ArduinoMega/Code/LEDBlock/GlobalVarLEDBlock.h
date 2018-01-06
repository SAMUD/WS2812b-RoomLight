

//FastLed-library
#define NUM_LEDS 290
#define DATA_PIN 37
static CRGB leds[NUM_LEDS];
static CRGB ledstemp[NUM_LEDS];

//In Out Pins used on my Arduino
#define PINRelais 53						//Output to the Relais --> enable Power to LEDs

//used for WhiteLeft and WhiteRight
#define NumberLEDLeft 108
#define NumberLEDRight 96
#define ValueLEDDarkside 75

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

//enum with all possible Display-Modes
enum Mode
{
	None,
	White,White2,
	RainbowMarch, RainbowBeat, ColorPalBeat,
	Fade,RGBFade,
	Confetti,ConfettiColorfull,Strobe,
	FixedColor, FixedColor2, FixedColor3,
	Ball,
	AudioMeter
};

//enum active LEDs
enum eDisplay
{
	Left,Right,All,Night
};

static struct ModeSetLedBlock
{
	uint8_t BrightnessSetpoint;			//
	uint8_t Saturation;					//
	uint8_t SpeedColor;					//
	eDisplay DisplayMode;				//Left,Right,All,Night
	ColTemp Temperature;				//ColorTemp --> used in white mode
	uint8_t NightNumber;				//number of leds to display in night mode
	uint8_t Set;						//can be used for various SetLedBlock. Acessed on the Remote with Set+ and Set-
}ModeSett;

//this one will be saved in EEPROM
static struct StoreStruct
{
	uint8_t MemoryVersion;
	ModeSetLedBlock FixedColor;
	ModeSetLedBlock RainbowMarch;
	ModeSetLedBlock RainbowBeat;
	ModeSetLedBlock ColorPalBeat;
	ModeSetLedBlock Fade;
	ModeSetLedBlock RGBFade;
	ModeSetLedBlock White;
	ModeSetLedBlock Confetti;
	ModeSetLedBlock ConfettiColorfull;
	ModeSetLedBlock Strobe;
	ModeSetLedBlock FixedColor2;
	ModeSetLedBlock FixedColor3;
	ModeSetLedBlock White2;
	ModeSetLedBlock Ball;
	ModeSetLedBlock AudioMeter;

	ModeSetLedBlock Current;


	bool PowerState;				//true=On False=off
	Mode DisplayMode;			//the Actual Mode
	Mode DisplayModeOld;			//the Old mode

	uint8_t ChangesToEffectMade;	//when the LEDS need to be redrwan, cause there were changes to the effects 
	bool PlayPause;
}SetLedBlock;

static struct sDisplayInfo
{
	bool ShowACK;
	uint8_t ShowPercentage;
}DisplayInfo;

static bool memValid = true;

