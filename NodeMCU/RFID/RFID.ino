/*
  Este programa irá utilizar RFID MFRC522 Mifare

  Autores: Norberto Hideaki Enomoto - norberto.enomoto@gmail.com
           Vitor Mazuco             - vitor.mazuco@gmail.com.com

  Data criação: 15/11/2016

  Repositório para a biblioteca: https://github.com/miguelbalboa/rfid
  Versão: 1.1.9
*/
#include <Wire.h> 
#include <SPI.h>
#include <MFRC522.h>

/* Esquema para ligação do MFRC522 ao ESP8266 (ESP-12)
RST     = GPIO 15  -> D8
SDA(SS) = GPIO 02  -> D4

MOSI    = GPIO 13 -> D7
MISO    = GPIO 12 -> D6
SCK     = GPIO 14 -> D5
GND     = GND
3.3V    = 3.3V
*/

// GPIO5 -> D1
#define RST_PIN  15
// GPIO4 -> D2 
#define SS_PIN   2  

// Cria a instância para o MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {  
  Serial.begin(9600);

  // Inicializa o SPI Bus
  SPI.begin();
  
  // Inicializa a instância do MFRC522
  mfrc522.PCD_Init(); 
  
  Serial.println(F("======================================================")); 
  Serial.println(F("Scan for Card and print UID:"));
}

/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {        
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);  
  }
}  

void loop() { 

  if (!mfrc522.PICC_IsNewCardPresent()) {
      delay(500);
      return;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID Hex:"));
  printHex(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();  
  
  Serial.print(F("Card UID Dec:"));
  printDec(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();  
}


