/*
    Essa programaÃ§Ã£o faz a conexÃ£o do
    ESP ao ponto de Wifi 
  
   Modificado em 11 de novembro de 2016
   por Vitor Mazuco (contato@vmzsolutions.com.br)
*/

// InclusÃ£o da biblioteca ESP8266WiFi
#include "ESP8266WiFi.h"  

// ConfiguraÃ§Ã£o do Wi-FI  
const char* ssid = "spri";  // SSID
const char* password = "zarelhounido";  // Senha 

void setup(void)  
{   
// ComeÃ§a o Serial   
Serial.begin(115200);  // na frequÃªncia em 115200 

// ConexÃ£o com o Wifi  
WiFi.begin(ssid, password);  
while (WiFi.status() != WL_CONNECTED) {  
delay(500);  
Serial.print(".");  
}  
Serial.println("");  
Serial.println("A conexao com a rede WiFi foi estabelecida!");  

// Mostra o endereÃ§o IP  
Serial.println("Seu endereco IP eh:");  
Serial.println(WiFi.localIP());

}  

void loop() {  

}  


