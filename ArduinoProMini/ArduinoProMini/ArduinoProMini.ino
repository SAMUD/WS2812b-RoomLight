/*
 Name:		ArduinoProMini.ino
 Created:	19.11.2016 15:25:33
 Author:	sdaur
*/

#include <IRremote.h>

#define PINValueChanged 2
#define PINMultiplePresses 3
#define PINOutput1 5						//The LSB-Bit
#define PINOutput2 6
#define PINOutput3 7
#define PINOutput4 8
#define PINOutput5 9						//The MSB-Bit
#define PINLED 13


IRrecv irrecv(4);							// Receive on pin 4
decode_results results;
uint32_t tempresult;
bool ValueChanged;							//will change its state at every value change
bool multiplePresses;						//when holding down the key on the Remote
bool changeValueChanged;
unsigned long tempmillis;
uint8_t delayMultiple;



void setup()
{
	Serial.begin(115200);
	irrecv.enableIRIn();					// Start the receiver
	Serial.println("Started - Waiting - V1.2 RC");
	pinMode(PINLED, OUTPUT);				// set pins to Output
	pinMode(PINValueChanged, OUTPUT);
	pinMode(PINMultiplePresses, OUTPUT);
	pinMode(PINOutput1, OUTPUT);
	pinMode(PINOutput2, OUTPUT);
	pinMode(PINOutput3, OUTPUT);
	pinMode(PINOutput4, OUTPUT);
	pinMode(PINOutput5, OUTPUT);
	
}

void loop() {
	
	//Receiving 
	if (irrecv.decode(&results)) {
		//Serial.println(results.value, HEX);
		tempresult = results.value;
		irrecv.resume(); // Continue receiving
		delayMultiple++;
	}
	

	//write the ValueChanged pin and set the LED
	digitalWrite(PINValueChanged, ValueChanged);

	//write the repeat PIN
	digitalWrite(PINMultiplePresses, multiplePresses);
	digitalWrite(PINLED, multiplePresses);
	
	//printing status
	/*if (tempresult != 0)
	{
		Serial.print("Key: ");
		Serial.print(tempresult, HEX);
		Serial.print("  multiple presses: ");
		Serial.print(multiplePresses);
		Serial.print(" i: ");
		Serial.print(delayMultiple);
		Serial.print("  ValueChanged: ");
		Serial.println(ValueChanged);
	}*/
	
	//Translating results in binary outputs
	Translate();
	
	//checking for key hold down - multiplePresses
	if (millis() - tempmillis < 500)
	{
		//delayMultiple++;
	}
	else
	{
		multiplePresses = 0;
		delayMultiple = 0;
	}
	if (tempresult == 0xFFFFFFFF)
	{
		tempmillis = millis();
	}

	if (delayMultiple == 3)
	{
		delayMultiple = 2;
		multiplePresses = 1;
	}

	//checking for changed value - ValueChanged
	if (tempresult != 0 && tempresult != 0xFFFFFFFF && changeValueChanged)
		ValueChanged = !ValueChanged;
	
	//reseting to 0 and waiting for the next keypress
	tempresult = 0;
}

void Translate()
{
	changeValueChanged = 1;
	switch (tempresult)
	{
	case 0xFD00FF:
		//Serial.println("Detected: Power");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD807F:
		//Serial.println("Detected: Vol+");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD40BF:
		//Serial.println("Detected: FUNC/STOP");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD20DF:
		//Serial.println("Detected: <--");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFDA05F:
		//Serial.println("Detected: Play/Pause");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD609F:
		//Serial.println("Detected: -->");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD10EF:
		//Serial.println("Detected: Down");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD906F:
		//Serial.println("Detected: Vol-");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD50AF:
		//Serial.println("Detected: Up");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD30CF:
		//Serial.println("Detected: 0");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFDB04F:
		//Serial.println("Detected: EQ");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD708F:
		//Serial.println("Detected: ST/REPT");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD08F7:
		//Serial.println("Detected: 1");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD8877:
		//Serial.println("Detected: 2");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD48B7:
		//Serial.println("Detected: 3");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFD28D7:
		//Serial.println("Detected: 4");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
		break;
	case 0xFDA857:
		//Serial.println("Detected: 5");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
		break;
	case 0xFD6897:
		//Serial.println("Detected: 6");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
		break;
	case 0xFD18E7:
		//Serial.println("Detected: 7");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
		break;
	case 0xFD9867:
		//Serial.println("Detected: 8");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
		break;
	case 0xFD58A7:
		//Serial.println("Detected: 9");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
		break;
	default:
		//Do nothing and block value changed var
		changeValueChanged = 0;
		break;
	}
}
