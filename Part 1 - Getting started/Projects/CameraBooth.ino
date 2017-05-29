// ### LEDs ###
#define GROEN 0                                            // Groene LED komt op pin ..
#define ORANJE 1                                        // Oranje LED komt op pin ..
#define ROOD 2                                          // Rode LED komt op pin ..

void LED(uint8_t kleur, bool aanUit)
    {
    digitalWrite(kleur, aanUit);                        // stuur het signaal in 'aanUit' uit, op de pin met nr 'kleur'
    }


    // ### CAMERA ###
#define CAMERA 3

void foto(bool aanUit)
    {
    digitalWrite(CAMERA, aanUit);
    }

    
// ### BEEPER
#define BEEPER 4

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
    pinMode(GROEN, OUTPUT);                                 // zet deze pin als Output
    pinMode(ORANJE, OUTPUT);                                // zet deze pin als Output
    pinMode(ROOD, OUTPUT);                                  // zet deze pin als Output
    pinMode(CAMERA, OUTPUT);                                // zet deze pin als Output
    pinMode(BEEPER, OUTPUT);                                // zet deze pin als Output
    pinMode(PIR, INPUT);                                    // zet deze pin als ingang

    teller = 0;                                            // begintoestand - initialiseer...
    toestand = KLAAR;
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
                }
            break;

        case AFTELLEN:                                  // Bezig met aftellen
            beep(false);                                // zet de beeper uit..
            switch (teller)                             // naargelang hoever we zijn in het aftellen, neem een of meerder acties..
                {
                case 0:                                 // teller = 0 : aftellen is net gestart
                    beep(true);                         // zet beeper aan
                    LED(GROEN, false);                  // zet groene LED uit
                    LED(ORANJE, true);                  // zet oranje LED aan
                    break;

                case 10:
                case 20:
                case 30:
                case 40:
                case 50:
                case 60:
                    beep(true);                         // elke seconde : zet de beeper aan
                    break;

                case 70:
                    LED(ORANJE, false);                 // na 7 seconden : oranje led UIT
                    LED(ROOD, true);                    // RODE led AAN
                    beep(true);                         //
                    break;

                case 75:
                case 80:
                case 85:
                case 90:
                case 95:
                    beep(true);                         // van seconde 7 tot 10 komen de beepjes om de halve seconde, ipv om de seconde
                    break;

                case 100:
                    foto(true);                         // 10 seconden : maak nu de foto : sluit de sluiter
                    break;

                case 102:                               // 200 ms later :
                    foto(false);                        // laat de sluiterknop los,
                    LED(ROOD, false);                   // rode LED uit
                    toestand = WACHT;                   // klaar met aftellen, nu naar toestand WACHTen op geen beweging
                    teller = 0;                         // teller terug op 0, om 5 seconden geen beweging te meten
                    break;
                }
            break;

        case WACHT:
            if (beweging())
                {
                teller = 0;                             // elke keer dat er beweging is, start de teller terug op 0
                }
            else
                {
                teller++;                               // als er geen beweging is, loopt de teller op
                }

            if (teller > 50)                            // 5 seconden geen beweging...
                {
                toestand = KLAAR;                       // terug naar beginstoestand.
                }
            break;
        }

    delay(100);                                         // wacht 100 ms = 0.1 sec
    teller++;                                           // klaar met deze lus, verhoog de teller
    }
