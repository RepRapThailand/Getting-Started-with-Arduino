#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

char auth[] = "6930812368f94a8dbe54687fefea5ab5";
char ssid[] = "321";
char pass[] = "strooommooorts";

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

void setup()
    {
    Serial.begin(38400);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Blynk.begin(auth, ssid, pass);
    }

void loop()
    {
    Blynk.run();
    }


BLYNK_WRITE(V1)
    {
    int count = param.asInt(); // assigning incoming value from pin V0 to a variable
    Serial.println(count);
    int i;
    for(i=0; i<strip.numPixels(); i++)
        {
        if (i < (count + count))
            {
            strip.setPixelColor(i, strip.Color(255, 0, 0));
            Serial.print("1");
            }
        else
            {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
            Serial.println("0");
            }
        }
    strip.show();
    delay(5);
    Serial.println();
    
    }


