int incomingByte;

String alfabet = String("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@");
const char *itu[] = {"SL","LSSS","LSLS","LSS","S","SSLS","LLS","SSSS","SS","SLLL","LSL","SLSS","LL","LS","LLL","SLLS","LLSL","SLS","SSS","L","SSL","SSSL","SLL","LSSL","LSLL","LLSS","LLLLL","SLLLL","SSLLL","SSSLL","SSSSL","SSSSS","LSSSS","LLSSS","LLLSS","LLLLS","SLSLSL","LLSSLL","SSLLSS","SLLLLS","LSLSLL","LSSLS","LSLLS","LSLLSL","SLSSS","LLLSSS","LSLSLS","LSSSL","SLSLS","LSSSSL","SSLLSL","SLSSLS","SSSLSSL","SLLSLS"  };

int pin = 13;


void setup()
	{
	pinMode(pin, OUTPUT);
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps	
	}

void loop()
	{
    if (Serial.available() > 0)
    	{
        incomingByte = Serial.read();
        sendMorse(incomingByte);
        }	
	}

void sendMorse(byte aLetter)
	{
	int pos = 0;	// index of dits and dahs in morse-code representation of a character "SLS"
	int index = 0;	// index of a character in the string with existing Morse characters, eg A=1
	int len = 0;
	
    index = alfabet.indexOf(incomingByte);
    len = strlen(itu[index]);
    for (pos = 0; pos<len; pos++)
    	{
    	beep(itu[index][pos]);
    	delay(300);
    	}
	}


void beep(byte shortLong)
	{
	digitalWrite(pin, HIGH);
	switch (shortLong)
		{
		case 'S':
			delay(100);
			break;
		case 'L':
			delay(300);
			break;
		}
		digitalWrite(pin, LOW);
		delay(100);
	}