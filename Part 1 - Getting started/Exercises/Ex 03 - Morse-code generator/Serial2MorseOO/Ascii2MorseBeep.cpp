#include "Ascii2MorseBeep.h"
#include "Arduino.h"

Ascii2Morse::Ascii2Morse(int anOutPin, int aDurationShort)
	{
	// initialize this instance
	outPin = anOutPin;
					// remember on which hardware pin to send the code
	pinMode(outPin, OUTPUT);
					// put this pin in OUTPUT mode
	durationShort = aDurationShort;
					// remember the duration of pulses..
	durationLong = aDurationShort + aDurationShort + aDurationShort;
					// calculate a long, as three times a short
  }

void Ascii2Morse::send(char aChar)
	{
	unsigned int len = 0;	// length of the morse-representation of the character, eg "B" is represented as "LSSS" and has length = 4
	unsigned int pos = 0;	// zero-based index of character in the morse-code representation of a character, eg. the 'L' in "SLS" is at pos = 1
	unsigned int index = 0;	// one-based index of a character in the 'alfabet' string with existing Morse characters, eg A=1, 1=28
	
    index = alfabet.indexOf(toupper(aChar));
					// take the character and convert to upper case.. (Morse-code doesn't seem to distinguish lower and upper case)
					// then search if it exists in 'alfabet', and if so return its one-based position index
    len = strlen(morseCodes[index]);
					// then take the MorseCode representation at the same index in the array morseCodes and store the length of this
					// Now iterate over all chars of this MorseCode representation
    for (pos = 0; pos<len; pos++)
    	{
    	beep(morseCodes[index][pos]);
					// send a Short or Long beep
    	delay(durationLong);
					// send a pause between the characters. Pause between characters has a 'long' duration
    	}
	}


void Ascii2Morse::beep(char aBeep)
	{
	digitalWrite(outPin, HIGH);
					// set output pin signal to HIGH = buzzer or light goes ON
	switch (aBeep)
					// wait short or long..
		{
		case 'S':
			delay(durationShort);
			break;
		case 'L':
			delay(durationLong);
			break;
		}
		digitalWrite(outPin, LOW);
					// set signal back to inactive = light or buzzer goed OFF
		delay(durationShort);
					// wait one 'short' after every character..
	}	
	
