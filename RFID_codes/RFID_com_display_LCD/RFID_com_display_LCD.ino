//RFID - Controle de Acesso com leitor RFID 13.56

//Biblioteca do protocolo SPI 
#include <SPI.h>
//Biblioteca do RFID
#include <MFRC522.h>

/*-importacao Necessaria para LCD + I2C*/
#include <Wire.h>  
//#include <LiquidCrystal_I2C.h>


//Pinos de definição 
#define SS_PIN 10
#define RST_PIN 9
//Cria a instacia do RFID (mfrc522)
MFRC522 mfrc522(SS_PIN, RST_PIN);   

//Aqui colocamos as Tags que desejamos autorizar
String tagsCadastrada[2] ={"36 7B 36 9E","FF CC 8B 28"};

//------------Objeto do LCD + I2C
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

 //Pinos do LED RGB
 int ledVermelho =2;
 int ledVerde =3;
 int ledAzul =4;
 
 //Esta parte do Rele é apenas 1 exemplo de utilidade---------
 //neste caso precisaremos de fonte externa para o acionamento--------
 //decidi não colocar para não complicar muito o exemplo---------------
 //basta tirar o comentario para usar------------------
 int relay =7;
 
 
void setup() 
{
  // Inicia a serial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  //Inicia o LCD como 16 linhas e 2 colunas
//  lcd.begin(16,2);
  //inicia a conexão SPI
  SPI.begin();  
  // Inicia MFRC522  
  mfrc522.PCD_Init();  
  Serial.println();
  
  //Inicia os pinos do LED RGB como saida
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  
  //Metodo inicial (Menu)
  mensageminicial();
  
 
  
  //Esta parte do Rele é apenas 1 exemplo de utilidade---------
 //neste caso precisaremos de fonte externa para o acionamento--------
 //decidi não colocar para não complicar muito o exemplo---------------
 //basta tirar o comentario para usar------------------
  pinMode(relay, OUTPUT);
}
 
void loop() 
{

  //Aguarda proximidade do cartão / tag
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
   //Seleciona o cartão / tag
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  //String que armazenará o UID do cartão
  String conteudo= "";
  //variavel que coletará os bytes lidos
  byte letra;
  
  //dentro deste FOR, armazena byte a byte e 
  //concatena na variavel conteudo
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  //booleana que valida a tag lida
  //como autorizada ou não
  boolean tagVerificada = false;
  
//  //Limpa o LCD
//  lcd.clear();
//  //Seta o cursor para linha e coluna 0  
//  lcd.setCursor(0,0);
//  
  
  Serial.print("Leitura : ");
  
  //coloca o valor da variavel conteudo toda em Maisculo
  conteudo.toUpperCase();
  
  //verifica se a tag lida coincide com uma das tags 
  //cadastada no array
 for(int indice =0; indice < sizeof(tagsCadastrada); indice++){
  //if (conteudo.substring(1) == "24 B4 8B 19") //UID 1 
   if (conteudo.substring(1) == tagsCadastrada[0]) //UID 1
  {
   //Se sim imprime no LCD e na Serial
    Serial.println("Chaveiro RFID cadastrado. Acesso Liberado!");
      
    
//    lcd.print("Ola Thiago!");
//    lcd.setCursor(0,1);
//    lcd.println("Acesso Liberado!");
    
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
 
  //if (conteudo.substring(1) == "55 FC F9 0D") //UID 1
  
  //verifica se a tag lida coincide com uma das tags 
  //cadastada no array
  if (conteudo.substring(1) == tagsCadastrada[1]) //UID 1
  {
   
    //Se sim imprime no LCD e na Serial
    Serial.println("Cartao RFID cadastrado. Acesso Liberado!");
    
//    lcd.print("Oi Arduino e Android!");
//    lcd.setCursor(0,1);
//    lcd.println("Acesso Liberado!");
    
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
  
  //caso o conteudo não seja "" e a tag Verficada
  //esteja falsa.
  //Informa o usuario que não tem acesso
  if((tagVerificada == false)&&(conteudo != "")){
    
    //Se ambas condições forem verdadeira 
    //imprime no LCD e na Serial uma mensagem de negação ao usuario
    Serial.println("Usuario Desconhecido! ");
    Serial.println("Acesso Negado!!");
    
//    lcd.print("Usuario Negado!");
//    lcd.setCursor(0,1);
//    lcd.println("Acesso Negado!  ");
    
    //este metodo acende o led vermelho (nãp autorizado)
    //e matem o rele desligado 
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
  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Aproxime a sua");
//  lcd.setCursor(0,1);
//  lcd.print("tag p/ Leitura!");
  
  digitalWrite(ledAzul,LOW);
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, HIGH);
  
  //Esta parte do Rele é apenas 1 exemplo de utilidade---------
 //neste caso precisaremos de fonte externa para o acionamento--------
 //decidi não colocar para não complicar muito o exemplo---------------
 //basta tirar o comentario para usar------------------
  digitalWrite(relay, HIGH);
  Serial.println();


 
}

//Metodo chamado quando a tag é valida e cadastrada
void tagValida()
{
  digitalWrite(ledAzul,HIGH);
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, LOW);
  
  //Esta parte do Rele é apenas 1 exemplo de utilidade---------
 //neste caso precisaremos de fonte externa para o acionamento--------
 //decidi não colocar para não complicar muito o exemplo---------------
 //basta tirar o comentario para usar------------------
  digitalWrite(relay, LOW);

}

//Metodo chamado quando a tag invalida / desconhecida
void tagInvalida()
{
  digitalWrite(ledAzul,HIGH);
  digitalWrite(ledVermelho,  LOW);
  digitalWrite(ledVerde, HIGH);
  
  //Esta parte do Rele é apenas 1 exemplo de utilidade---------
 //neste caso precisaremos de fonte externa para o acionamento--------
 //decidi não colocar para não complicar muito o exemplo---------------
 //basta tirar o comentario para usar------------------
  digitalWrite(relay, HIGH);
}
