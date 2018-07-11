
#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "spri";
const char* senha = "zarelhounido";

String apiKey = "TRF6QGI219VVR9QI";
const char *servidor_destino = "api.thingspeak.com";



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
  
}

void loop() {
  WiFiClient cliente;

 

  float u  = dht.readHumidity();
  float t = dht.readTemperature();

  if( isnan(t) || isnan(u) ){
    Serial.println("Falha de leitura");
  }

  if(cliente.connect(servidor_destino, 80)){
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    
    postStr += "&field2=";
    postStr += String(u);

    postStr += "\r\n\r\n";

    cliente.print("POST /update HTTP/1.1\n");
    cliente.print("Host:api.thingspeak.com\n");
    cliente.print("Connection:close\n");
    cliente.print("X-THINGSPEAKAPIKEY:"+apiKey+"\n");

    cliente.print("Content-Type: application/x-www-form-urlencoded\n");

    cliente.print("Content-Length:");
    cliente.print(postStr.length());
    cliente.print("\n\n");
    cliente.print(postStr);
    
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" C, umidade:");
    Serial.print(u);
    Serial.print(" %");
    Serial.println("Enviando dados para Thingspeak");
   
  }
  cliente.stop();
  Serial.println("Aguardando...");
  delay(20000); 
}

