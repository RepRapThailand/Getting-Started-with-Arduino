// ### LEDs ###
#define GROEN 10                                         // Groene LED komt op pin ..
#define ORANJE 11                                        // Oranje LED komt op pin ..
#define ROOD 12                                          // Rode LED komt op pin ..

void LED(uint8_t kleur, bool aanUit)
    {
    digitalWrite(kleur, aanUit);                        // stuur het signaal in 'aanUit' uit, op de pin met nr 'kleur'
    }


// ### CAMERA ###
#define CAMERA 2

void foto(bool aanUit)
    {
    digitalWrite(CAMERA, aanUit);
    }

    
// ### BEEPER
#define BEEPER 8

void beep(bool aanUit)
    {
    digitalWrite(BEEPER, aanUit);
    }

// ### PIR  
#define PIR 5                                           // verbind PIR met pin ..

bool beweging()
    {
    return digitalRead(PIR);                            // lees de waarde op de ingang en geef terug als logisch aan of uit
    }

#define KLAAR 0                                         // de drie toestanden die we gebruiken in de stateMachine
#define AFTELLEN 1
#define WACHT 2

// Globale variabelen
uint16_t teller;                                        // teller om de tijd te tellen, in 0.1s stapjes
uint8_t toestand;                                       // variabele die de toestand van de state-machine onthoudt

void setup()
    {
    Serial.begin(38400);                                // start seriele communicatie aan 38400 bits/seconde
    pinMode(GROEN, OUTPUT);                             // zet deze pin als Output
    pinMode(ORANJE, OUTPUT);                            // zet deze pin als Output
    pinMode(ROOD, OUTPUT);                              // zet deze pin als Output
    pinMode(CAMERA, OUTPUT);                            // zet deze pin als Output
    pinMode(BEEPER, OUTPUT);                            // zet deze pin als Output
    pinMode(PIR, INPUT);                                // zet deze pin als ingang

    LED(GROEN, false);                                  // zet groene LED uit
    LED(ORANJE, false);                                 // zet groene LED uit
    LED(ROOD, false);                                   // zet groene LED uit
    beep(false);                                        // zet de beeper uit..
    foto(false);                                        // laat de sluiterknop los,

    teller = 0;                                         // begintoestand - initialiseer...
    toestand = WACHT;
    }

void loop()
    {
    switch (toestand)
        {
        case KLAAR:                                     // Wachtend op detectie van beweging : groene LED
            teller = 0;                                 // houd de teller op 0 zolang er geen beweging is
            LED(GROEN, true);                           // zet de groene LED aan

            if (beweging())
                {
                toestand = AFTELLEN;                    // als er beweging gedetecteerd wordt (tijdens toestand KLAAR) start het aftellen
                Serial.println("Aftellen begonnen");
                }
            break;

        case AFTELLEN:                                  // Bezig met aftellen
            beep(false);                                // zet de beeper uit..
            switch (teller)                             // naargelang hoever we zijn in het aftellen, neem een of meerder acties..
                {
                case 1:                                 // teller = 1 : aftellen is net gestart
                    beep(true);                         // zet beeper aan
                    LED(GROEN, false);                  // zet groene LED uit
                    LED(ORANJE, true);                  // zet oranje LED aan
                    break;
                case 10:
                    Serial.print("9 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 20:
                    Serial.print("8 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 30:
                    Serial.print("7 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 40:
                    Serial.print("6 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 50:
                    Serial.print("5 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 60:
                    Serial.print("4 ");
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;
                case 70:
                    Serial.print("3 ");
                    LED(ORANJE, false);                 // na 7 seconden : oranje led UIT
                    LED(ROOD, true);                    // RODE led AAN
                    beep(true);                         //
                    break;
                case 75:
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;
                case 80:
                    Serial.print("2 ");
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;
                case 85:
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;
                case 90:
                    Serial.print("1 ");
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;
                case 95:
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;
                case 100:
                    Serial.println("Foto!");
                    foto(true);                         // 10 seconden : maak nu de foto : sluit de sluiter
                    break;
                case 103:                               // 300 ms later :
                    foto(false);                        // laat de sluiterknop los,
                    LED(ROOD, false);                   // rode LED uit
                    toestand = WACHT;                   // klaar met aftellen, nu naar toestand WACHTen op geen beweging
                    teller = 0;                         // teller terug op 0, om 5 seconden geen beweging te meten
                    Serial.println("Wachten...");
                    break;
                }
            break;

        case WACHT:
            if (beweging())
                {
                teller = 0;                             // elke keer dat er beweging is, start de teller terug op 0
                }

            if (teller > 50)                            // 5 seconden geen beweging...
                {
                toestand = KLAAR;                       // terug naar beginstoestand.
                Serial.println("Klaar");
                }
            break;
        }

    delay(100);                                         // wacht 100 ms = 0.1 sec
    teller++;                                           // klaar met deze lus, verhoog de teller
    }

