#define thePin 16

bool state;
uint32_t count;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "20748399de764fa7b825da5b53c4a9ae";
char ssid[] = "321";
char pass[] = "strooommooorts";

void setup() 
    {
    state = false;
    count = 0;
    Serial.begin(38400);
    pinMode(thePin, INPUT);
    Blynk.begin(auth, ssid, pass);
    }

void loop()
    {
    switch (state)
        {
        case true:
            if (digitalRead(thePin))
                {
                }
            else
                {
                state = false;
                }
            break;
        case false:
            if (digitalRead(thePin))
                {
                state = true;
                count++;
                Serial.println(count);
                Blynk.virtualWrite(V0, count);
                }
            else
                {
                }
            break;
        }
    delay(1);
    Blynk.run();
    }
