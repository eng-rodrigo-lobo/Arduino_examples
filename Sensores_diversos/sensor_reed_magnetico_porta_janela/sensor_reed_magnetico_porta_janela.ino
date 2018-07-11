/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 12, when the magnetic sensor is triggered.


 The circuit:
 * LED attached from pin 12 to ground
 * magnetic sensor connected to pin 2
*/

// constants won't change. They're used here to
// set pin numbers:
const int sensor = 2;     // the number of the pushbutton pin
const int ledPin =  8;      // the number of the LED pin

// variables will change:
int sensorState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(sensor, INPUT);
  //activate pull-up resistor mode for 'sensor' input
  digitalWrite(sensor, HIGH);
  
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  sensorState = digitalRead(sensor);

  // check if the sensor is triggered.
  // if it is, the sensorState is LOW (because of the pull-up logic):
  if (sensorState == !HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    Serial.print("Valor sensor: ");
    Serial.println(sensorState);
    delay(500);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    Serial.print("Valor sensor: ");
    Serial.println(sensorState);
    delay(500);
  }
}
