/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;
unsigned int  rawData[99] = {4400,4300, 550,1600, 550,550, 550,1600, 550,1600, 550,550, 550,500, 600,1600, 550,500, 600,500, 600,1550, 600,500, 600,500, 550,1600, 550,1600, 600,500, 550,1600, 600,500, 550,1600, 600,1550, 600,1550, 600,1600, 550,500, 600,1550, 600,1600, 550,1600, 600,500, 550,500, 650,450, 600,500, 600,1550, 600,500, 600,450, 650,1550, 600,1550, 600,1550, 600,450, 650,450, 650,450, 600,500, 600,450, 650,450, 600,500, 600,450, 650,1500, 650,1550, 600,1550, 600,1550, 650,1550, 550};

void setup()
{
  Serial.begin(9600);
  
}

void loop() {

  switch (Serial.read()){

      case 'o':
      irsend.sendSAMSUNG(0xB24D7B84, 32);
      Serial.println("ON / OFF");
      delay(1000); //5 second delay between each signal burst
      break;

      case 't':
      irsend.sendRaw(rawData, sizeof (rawData)/sizeof (rawData[0]), 38);
      Serial.println("ON / OFF");
      delay(1000); //5 second delay between each signal burst
      break;
      
      case 'u':
      irsend.sendSAMSUNG(0xB24D1FE0, 32);
      Serial.println("Temp. UP");
      delay(1000); //5 second delay between each signal burst
      break;

      case 'd':
      irsend.sendSAMSUNG(0xB24D1FE0, 32);
      Serial.println("Temp. DOWN");
      delay(1000); //5 second delay between each signal burst
      break;
    
  }
}
