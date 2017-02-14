int inputPin = 0;   // Pin waarop we een analoog signaal gaan 'meten'
int val;            // Integer getal waarin we de meting tijdelijk opslaan

void setup()
  {
  Serial.begin(9600);          //  initializeer de seriele poort op 9600 Baud
  }

void loop()
  {
  val = analogRead(inputPin); // read the input pin
  //val = 256 - (val>>2);
  val = 256 - (val/4);
  Serial.println(val);        // zend de waarde over de seriele poort
  // Serial.print(val);        // zend de waarde over de seriele poort
  delay(1000);                // wacht 1000 ms om niet teveel metingen te sturen
  }

