//Programa : Modulo Arduino Bluetooth HC-05 - Programacao
//Autor : FILIPEFLOP
 
//Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>
   
//Define os pinos para a serial   
SoftwareSerial bluetooth(6, 7); // RX, TX  

// Constantes
volatile char inByte = '0';
const int led01 = 8;
const int led02 = 9;

void setup()   
{  
  Serial.begin(9600);    //Inicia o monitor serial
  bluetooth.begin(9600); //baud default do HC-05
  pinMode(led01, OUTPUT); digitalWrite(led01, LOW);
  pinMode(led02, OUTPUT); digitalWrite(led02, LOW); 

}  
   
void loop()  
{  
  // Read device output if available.  
  if (bluetooth.available()) 
  {  
    inByte = bluetooth.read();
    Serial.println("");
    Serial.println(inByte);
    delay(100); // The DELAY!

    switch(inByte){

    case '1': digitalWrite(led01, HIGH); bluetooth.write("LED 01 ON!\n") ; break;
    case '2': digitalWrite(led01, LOW) ; bluetooth.write("LED 01 OFF!\n"); break;
    case '3': digitalWrite(led02, HIGH); bluetooth.write("LED 02 ON!\n") ; break;
    case '4': digitalWrite(led02, LOW) ; bluetooth.write("LED 02 OFF!\n"); break;
    case 'A': digitalWrite(led01, HIGH); digitalWrite(led02, HIGH); bluetooth.write("All LEDs ON!\n") ;  break;
    case 'B': digitalWrite(led01, LOW) ; digitalWrite(led02, LOW) ; bluetooth.write("All LEDs OFF!\n");  break;
    
    
    }
  }  
  
  
}
