#include <SD.h>
File dataFile;

Sd2Card SDcard;
SdVolume volume;

// Pino do Arduino conectado ao pino CS do modulo
const int chipSelect = 4;  
int contador = 0;

void setup()
{
  Serial.begin(9600);
  
  //Inicia a comunicacao com o modulo SD
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    return;
  }
  Serial.println("Cartao iniciado corretamente !");
}


void loop(void) {
    while(contador<=500){
    // Abre o arquivo arquivo.txt do cartao SD
    File dataFile = SD.open("arquivo.txt", FILE_WRITE);
    
            // Incrementa o contador e envia os dados para o
            // Serial monitor
            Serial.print("Contador : ");
            Serial.println(contador);

            
            // Grava os dados no arquivo
            if (dataFile) 
            {
              dataFile.print("Contador : ");
              dataFile.println(contador);
              dataFile.close();
            }  
            else 
            {
              // Mensagem de erro caso ocorra algum problema
              // na abertura do arquivo
              Serial.println("Erro ao abrir arquivo.txt !");
            } contador++;
    } 
}
