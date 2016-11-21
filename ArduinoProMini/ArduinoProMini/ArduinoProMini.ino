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
unsigned long tempmillis;


void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();					// Start the receiver
	Serial.println("Started - Waiting - V1.0");
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
	}

	//write the ValueChanged pin and set the LED
	digitalWrite(PINValueChanged, ValueChanged);
	digitalWrite(PINLED, ValueChanged);

	//write the repeat PIN
	digitalWrite(PINMultiplePresses, multiplePresses);
	
	//printing status
	if (tempresult != 0)
	{
		Serial.print("Key: ");
		Serial.print(tempresult, HEX);
		Serial.print("  multiple presses: ");
		Serial.print(multiplePresses);
		Serial.print("  ValueChanged: ");
		Serial.println(ValueChanged);
	}
	
	//Translating results in binary outputs
	Translate();
	
	//checking for key hold down - multiplePresses
	if (millis() - tempmillis < 500)
	{
		multiplePresses = 1;
	}
	else
		multiplePresses = 0;
	if (tempresult == 0xFFFFFFFF)
	{
		tempmillis = millis();
	}	

	//checking for changed value - ValueChanged
	if (tempresult != 0 && tempresult != 0xFFFFFFFF)
		ValueChanged = !ValueChanged;
	
	//reseting to 0 and waiting for the next keypress
	tempresult = 0;
}

void Translate()
{
	if (tempresult == 0xFD00FF) // Power
	{
		Serial.println("Detected: Power");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD807F) // Vol+
	{
		Serial.println("Detected: Vol+");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD40BF) // FUNC/Stop
	{
		Serial.println("Detected: FUNC/STOP");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD20DF) // Reward
	{
		Serial.println("Detected: <--");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFDA05F) // Play/Pause
	{
		Serial.println("Detected: Play/Pause");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD609F) // Forward
	{
		Serial.println("Detected: -->");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD10EF) // Down
	{
		Serial.println("Detected: Down");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD906F) // Vol-
	{
		Serial.println("Detected: Vol-");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD50AF) // Up
	{
		Serial.println("Detected: Up");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD30CF) // 0
	{
		Serial.println("Detected: 0");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFDB04F) // EQ
	{
		Serial.println("Detected: EQ");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD708F) // ST/REPT
	{
		Serial.println("Detected: ST/REPT");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD08F7) // 1
	{
		Serial.println("Detected: 1");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD8877) // 2
	{
		Serial.println("Detected: 2");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD48B7) // 3
	{
		Serial.println("Detected: 3");
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFD28D7) // 4
	{
		Serial.println("Detected: 4"); 
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 1);
		digitalWrite(PINOutput5, 0);
	}
	if (tempresult == 0xFDA857) // 5
	{
		Serial.println("Detected: 5"); 
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
	}
	if (tempresult == 0xFD6897) // 6
	{
		Serial.println("Detected: 6"); 
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
	}
	if (tempresult == 0xFD18E7) // 7
	{
		Serial.println("Detected: 7"); 
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
	}
	if (tempresult == 0xFD9867) // 8
	{
		Serial.println("Detected: 8");
		digitalWrite(PINOutput1, 1);
		digitalWrite(PINOutput2, 1);
		digitalWrite(PINOutput3, 0);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
	}
	if (tempresult == 0xFD58A7) // 9
	{
		Serial.println("Detected: 9"); 
		digitalWrite(PINOutput1, 0);
		digitalWrite(PINOutput2, 0);
		digitalWrite(PINOutput3, 1);
		digitalWrite(PINOutput4, 0);
		digitalWrite(PINOutput5, 1);
	}

}
