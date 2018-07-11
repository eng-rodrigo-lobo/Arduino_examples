#include <ESP8266WiFi.h>

const char* ssid = "spri";
const char* senha = "zarelhounido";

/* Pinos da ESP8266
 * Quando o NODEMCU é escolhido como placa, as variáveis D0...D10 já estão configuradas
 * basta us=a-las no código, não precisa declarar novamente
   D0   = 16;
   D1   =  5;
   D2   =  4;
   D3   =  0;
   D4   =  2;
   D5   = 14;
   D6   = 12;
   D7   = 13;
   D8   = 15;
   D9   =  3;
   D10  =  1;
*/

int ledPin = D7;
int ledPin2 = D6;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
  
  Serial.print("Conectando a rede:");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  server.begin();
  Serial.println("Servidor Iniciado");

  Serial.print("Use esta URL:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

int status = LOW;
int status2 = LOW; 

void loop() {
  WiFiClient cliente = server.available();
  if(!cliente){
    return;
  }
  Serial.println("Novo cliente");
  while(!cliente.available()){
    delay(1);
  }
  String requisicao = cliente.readStringUntil('\r');
  Serial.println(requisicao);
  cliente.flush();

  if( requisicao.indexOf("/LED=ON") !=-1){
    status = HIGH;  
  }  
  if(requisicao.indexOf("/LED=OFF") != -1){
   status = LOW;
  }   

  if( requisicao.indexOf("/LED2=ON") !=-1){
    status2 = HIGH;  
  }  
  if(requisicao.indexOf("/LED2=OFF") != -1){
   status2 = LOW;
  }  
  
  Serial.print("status:");
  Serial.println(status);
  digitalWrite(ledPin, status);
  digitalWrite(ledPin2, status2);

  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type:text/html");
  cliente.println("");
  cliente.println("<!DOCTYPE HTML>");
  cliente.println("<html>"); 

  cliente.println("<br><br>");
  cliente.println("<a href=\"/LED=ON\"\"><button> Ligar </button></a>");
  cliente.println("<a href=\"/LED=OFF\"\"><button> Desligar </button></a><br/>");

  cliente.println("<br><br>");
  cliente.println("<a href=\"/LED2=ON\"\"><button> Ligar2 </button></a>");
  cliente.println("<a href=\"/LED2=OFF\"\"><button> Desligar2 </button></a><br/>");


  
  cliente.println("</html>");
  delay(1); 
}

