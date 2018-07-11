#define LED01 13
#define LED02 12
#define BUTTON 9

// Variables will change:
int LED01_State = LOW;         // the current state of the output pin
int LED02_State = LOW;
int buttonState;             // the current reading from the input pin


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)



void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);

  // set initial LED state
  digitalWrite(LED01, LED01_State);
  digitalWrite(LED02, LED02_State);

}

void loop() {
 
  //************* CONTROLAR O LED 01 (PIN 13) COM O PUSH BUTTON *****************************************
  
  // put your main code here, to run repeatedly:
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LED01, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED01, LOW);
  }
  //*******************************************************************************************


  //**************************** BLINK DO LED02 A CADA 0,5 SEGUNDOS ***************************
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (LED02_State == LOW) {
      LED02_State = HIGH;
    } else {
      LED02_State = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED02, LED02_State);
  }
  

}
