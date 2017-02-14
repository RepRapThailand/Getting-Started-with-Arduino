/*
Ascci2MorseBeep : receives an ASCII character, and outputs the Morse-code for it on a selected hardware pin
Author : Pascal Roobrouck
History : 
	V1 - 03 march 2016
*/

#include "Arduino.h"

class Ascii2Morse
	{
	public:
		Ascii2Morse(int outPin, int durationShort);	
		// Constructor : 
		//	outPin is pin on which you want to beep. 
		//	durationShort = length of short beep..

		void send(char aChar);
    // Transmit aChar as MorseCode
		
	private:
		unsigned int outPin;
		// hardware pin on which the signal will be sent out
		
		unsigned int durationShort;	
		// duration of a 'short', measured in milliseconds. Long is always 3*short

    unsigned int durationLong;  
    // duration of a 'long', measured in milliseconds. Long is always 3*short

		String alfabet = String("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@");
		// String of all possible characters to be encoded in Morse

		char* morseCodes[54] = {"SL","LSSS","LSLS","LSS","S","SSLS","LLS","SSSS","SS","SLLL","LSL","SLSS","LL","LS","LLL","SLLS","LLSL","SLS","SSS","L","SSL","SSSL","SLL","LSSL","LSLL","LLSS","LLLLL","SLLLL","SSLLL","SSSLL","SSSSL","SSSSS","LSSSS","LLSSS","LLLSS","LLLLS","SLSLSL","LLSSLL","SSLLSS","SLLLLS","LSLSLL","LSSLS","LSLLS","LSLLSL","SLSSS","LLLSSS","LSLSLS","LSSSL","SLSLS","LSSSSL","SSLLSL","SLSSLS","SSSLSSL","SLLSLS"};
  	// Array of strings with Morsecode representation for all characters in alfabet. S is Short, L = Long

		void beep(char shortLong);
		// 
	};
	
