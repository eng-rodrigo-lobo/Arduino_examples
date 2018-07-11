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

/* Esquema para ligação do MFRC522 ao Arduino 
RST     = GPIO 09
SDA(SS) = GPIO 10
MOSI    = GPIO 11
MISO    = GPIO 12
SCK     = GPIO 13
GND     = GND
3.3V    = 3.3V
*/

#define RST_PIN  9
#define SS_PIN   10  

// Cria a instância para o MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Aqui colocamos as Tags que desejamos autorizar
String tagsCadastradas[2] ={"36 7B 36 9E","FF CC 8B 28"};

//Pino de acionamento do relé
int relay = 7;

void setup() {  
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // Inicializa o SPI Bus
  SPI.begin();
  
  // Inicializa a instância do MFRC522
  mfrc522.PCD_Init();

  //Setando o pino do relay para output
  pinMode(relay, OUTPUT);
  
  Serial.println(F("======================================================")); 
  Serial.println(F("              Fazendo leitura das tags:"));
  Serial.println(F("======================================================"));
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
   
  //String que armazenará o UID do cartão
  String conteudo= "";
  //variavel que coletará os bytes lidos
  byte letra;

  //dentro deste FOR, armazena byte a byte e concatena na variavel conteudo
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  
  //booleana que valida a tag lida como autorizada ou não
  boolean tagVerificada = false;

  Serial.print("Leitura : ");
  
  //coloca o valor da variavel conteudo toda em Maisculo
  conteudo.toUpperCase();
  
  //verifica se a tag lida coincide com uma das tags cadastada no array
 for(int indice =0; indice < sizeof(tagsCadastradas); indice++){
  //checa se a leitura é igaul ao código hex do chaveiro (36 7B 36 9E) 
   if (conteudo.substring(1) == tagsCadastradas[0]) //UID 1
  {
   //Se sim imprime na Serial
    Serial.println("Chaveiro RFID cadastrado. Acesso Liberado!");
          
    //tag encontrada
    tagVerificada = true;
    //este metodo acende o led verde (autorizado)
    //e liga o rele
    tagValida();
    delay(3000);
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo= "";
    
    
  }
     
  //verifica se a tag lida coincide com uma das tags cadastada no array
  if (conteudo.substring(1) == tagsCadastradas[1]) //UID 1
  {
    //Se sim imprime na Serial
    Serial.println("Cartao RFID cadastrado. Acesso Liberado!");
    
    //tag encontrada
    tagVerificada = true;
    //este metodo acende o led verde (autorizado)
    //e liga o rele   
    tagValida();
    delay(3000);
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo= "";
  }
  
  //caso o conteudo não seja "" e a tag Verficada esteja falsa.
  //Informa o usuario que não tem acesso
  if((tagVerificada == false)&&(conteudo != "")){
    
    //Se ambas condições forem verdadeira 
    //imprime no LCD e na Serial uma mensagem de negação ao usuario
    Serial.println("Usuario Desconhecido! Acesso Negado!");
        
    //este metodo acende o led vermelho (não autorizado) e matem o rele desligado 
    tagInvalida();
    delay(3000);  
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo= "";
  }
}

  
}


//Metodo Inicial que informa ao usuario o que deve ser feito  
void mensageminicial()
{
  Serial.println();
  Serial.println("Aproxime o seu cartao de leitor");
  
  digitalWrite(relay, HIGH);
  Serial.println();

}

//Metodo chamado quando a tag é valida e cadastrada
void tagValida()
{
   digitalWrite(relay, LOW);
}

//Metodo chamado quando a tag invalida / desconhecida
void tagInvalida()
{
  digitalWrite(relay, HIGH);
}


