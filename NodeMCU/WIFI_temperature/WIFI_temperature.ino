
#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "spri";
const char* senha = "zarelhounido";

int ledPin = 13;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
  
  
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

  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type:text/html");
  cliente.println("");
  cliente.println("<!DOCTYPE HTML>");
  cliente.println("<html>"); 

  cliente.println("<br><br>");

  float u  = dht.readHumidity();
  float t = dht.readTemperature();

  if( isnan(t) || isnan(u) ){
    Serial.println("Falha de leitura");
  }
  else {
    Serial.print("Umidade: ");
    Serial.print(u);
    Serial.print(",");
    Serial.print("temperatura:");
    Serial.print(t);
  }

  cliente.print("Umidade: ");
  cliente.println(u);
  cliente.print(" %");
  cliente.println("<br><br>");
  cliente.print("Temperatura: ");
  cliente.println(t);
  cliente.print(" C");
  

  cliente.println("</html>");
  delay(1); 
}

