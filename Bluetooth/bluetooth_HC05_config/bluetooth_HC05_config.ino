//Programa : Modulo Arduino Bluetooth HC-05 - Programacao
//Autor : FILIPEFLOP
 
//Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>
   
//Define os pinos para a serial   
SoftwareSerial bluetooth(6, 7); // RX, TX  
  
   
void setup()   
{  
  //Inicia a serial - baud default para AT Mode eh 38400 
  Serial.begin(9600);  
  Serial.println("Digite os comandos AT :");  
  //Inicia a serial configurada nas portas 6 e 7
  bluetooth.begin(38400);
  pinMode(6, INPUT);  //SwSerial Rx
  pinMode(7, OUTPUT); //SwSerial Tx
}  
   
void loop()  
{  
  // Read device output if available.  
  if (bluetooth.available()) 
  {  
    delay(10); // The DELAY!
    int inByte = bluetooth.read();
    Serial.write((char)inByte);
  }  
  
  // Read user input if available.  
  if (Serial.available())
  {  
    delay(10); // The DELAY!
    int inByte = Serial.read();
    bluetooth.write((char)inByte);  
  }  
}
