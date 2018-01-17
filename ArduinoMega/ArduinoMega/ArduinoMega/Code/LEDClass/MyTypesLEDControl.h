
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
	///<summary>Name of this mode</summary>
	String Name;
} ModeSetLedBlock2;