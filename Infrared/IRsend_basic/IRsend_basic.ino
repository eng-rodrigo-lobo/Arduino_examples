/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  
}

void loop() {

  switch (Serial.read()){

      case 'u':
      irsend.sendNEC(0x20DF40BF, 32);
      Serial.println("Volume UP");
      delay(1000); //5 second delay between each signal burst
      break;

      case 'd':
      irsend.sendNEC(0x20DFC03F, 32);
      Serial.println("Volume DOWN");
      delay(1000); //5 second delay between each signal burst
      break;
    
  }
}
