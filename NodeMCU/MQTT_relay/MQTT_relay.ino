
/*
  Este programa ira utilizar o módulo com 2 reles e o protocolo MQTT.
  Para realizar o teste deste programa será utlizado um aplicativo
  cliente MQTT chamado MQTT.fx e para Celular Android e IOS

  Neste exemplo será utilizado o broker www.cloudmqtt.com

  Autores: Norberto Hideaki Enomoto - norberto.enomoto@gmail.com
           Vitor Mazuco             - vitor.mazuco@gmail.com

  Data criação: 19/11/2016
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* SSID          = "TBDT";
const char* PASSWORD      = "12345678";

const char* MQTT_SERVER   = "m13.cloudmqtt.com";
const int   MQTT_PORT       =  15217;
const char* MQTT_USER     = "cirlkxnr";
const char* MQTT_PASSWORD = "_0RSONdKnnGa";
const char* MQTT_CLIENT   = "ESP8266-Client";

const char* TOPICO_ESCUTA  = "topicoEscuta";
const char* TOPICO_ENVIO   = "topicoEnvio";

// GPIO 4 (D3)
const int PIN_RELE_1 = D3;

WiFiClient espClient;
PubSubClient MQTT(espClient);


void reconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED)
     return;
     
  Serial.println("Conectando-se na rede: " + String(SSID));
  Serial.println("Aguarde");
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;

  for(int i = 0; i < length; i++) 
  {
     char c = (char)payload[i];
     msg += c;
  }
  
  Serial.print("Mensagem [");
  Serial.print(topic);
  Serial.print("]: " + msg);
  Serial.println();

  if (msg.equals("1")) {
    digitalWrite(PIN_RELE_1, LOW);
    MQTT.publish(TOPICO_ENVIO, "1");
  } 
  else if (msg.equals("0")){
    digitalWrite(PIN_RELE_1, HIGH);
    MQTT.publish(TOPICO_ENVIO, "0");
  }

}

void initMQTT() {
  MQTT.setServer(MQTT_SERVER, MQTT_PORT);
  MQTT.setCallback(callback);
}

// Função para conexão
void reconnectMQTT() {
    while (!MQTT.connected()) {
      Serial.print("Tentado conectar ao broker MQTT: " + String(MQTT_SERVER) + ":" + String(MQTT_PORT) + " :");
      if (MQTT.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("conectado");
        MQTT.publish(TOPICO_ENVIO, "Cliente conectado ao broker");
        MQTT.subscribe(TOPICO_ESCUTA);
      } 
      else {
        Serial.print("falha, rc=");
        Serial.print(MQTT.state());
        Serial.println(" tenta novamente após 5 segundos");
        delay(5000);
      }
    }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_RELE_1, OUTPUT);
  digitalWrite(PIN_RELE_1, HIGH);
  
  reconnectWiFi();
  initMQTT();
}


void loop() {
  reconnectWiFi();
  reconnectMQTT();
  MQTT.loop();
}

