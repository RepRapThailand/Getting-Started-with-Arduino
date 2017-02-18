int inputPin = 0;
int val;

void setup()
{
 Serial.begin(9600);          //  setup serial	
 pinMode(3, OUTPUT);
 digitalWrite(3, LOW);
}

void loop()
{
val = analogRead(inputPin);    // read the input pin
//val = 256 - (val>>2);
 val = 256 - (val/8);

Serial.println(val);             // debug value
analogWrite(3, val);
delay(1000);


}
