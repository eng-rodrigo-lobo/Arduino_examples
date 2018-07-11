/*

  Programa que controla o LED na porta D1 através do "interruptor" na porta D0

  Implementação de interruptor com push button

*/


int LED = D1; // D1(gpio5)
int BUTTON = D0; // D0(gpio16)

int switchState = 0; // actual read value from pin4
int oldSwitchState = 0; // last read value from pin4
int lightsOn = 0; // is the switch on = 1 or off = 0

void setup() { 
 Serial.begin(9600);
 pinMode(BUTTON, INPUT); // push button 
 pinMode(LED, OUTPUT); // anything you want to control using a switch e.g. a Led
}
void loop() {
 switchState = digitalRead(BUTTON); // read the pushButton State
 if (switchState != oldSwitchState) // catch change
 {
 oldSwitchState = switchState;
 if (switchState == HIGH)
 {
 // toggle
 lightsOn = !lightsOn;
 }
 }
 if(lightsOn)
 {
 digitalWrite(LED, HIGH); // set the LED on
 Serial.println("LED ligado!");
 } else {
 digitalWrite(LED, LOW); // set the LED off
 Serial.println("LED DESligado!");
 }
 }
