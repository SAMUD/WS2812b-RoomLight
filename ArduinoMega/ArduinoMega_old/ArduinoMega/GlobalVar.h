
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
#define MIC_PIN   A0  // Microphone is attached to this analog pin



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

//enum with the actual Mode
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

//structure with the values read from the other Arduino
static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;

static struct ModeSettings
{
	uint8_t BrightnessSetpoint;			//
	uint8_t Saturation;					//
	uint8_t SpeedColor;					//
	eDisplay DisplayMode;				//Left,Right,All,Night
	ColTemp Temperature;				//ColorTemp --> used in white mode
	uint8_t NightNumber;				//number of leds to display in night mode
	uint8_t Set;						//can be used for various settings. Acessed on the Remote with Set+ and Set-
}ModeSett;

//this one will be saved in EEPROM
static struct StoreStruct
{
	uint8_t MemoryVersion;
	Mode DisplayMode;				//the Actual Mode
}Settings;

static struct sDisplayInfo
{
	bool ShowACK;
	uint8_t ShowPercentage;
}DisplayInfo;

static struct StatusVariables
{
	bool Connected = 0;

} Status;


static int configAdress = 0;
static bool memValid = true;

