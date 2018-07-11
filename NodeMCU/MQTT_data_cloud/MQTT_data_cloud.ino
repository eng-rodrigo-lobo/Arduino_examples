/*
 
 PUBSUB MQTT library
 
 
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
  Code from Andreas Spiess
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

const int DHTPIN = D7;     // what digital pin we're connected to
const int LED_PIN = D1; 
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define ssid              "spri"
#define password          "zarelhounido"
#define SERVER            "io.adafruit.com"
#define SERVERPORT        1883
#define MQTT_USERNAME     "rodrigo_lobo"
#define MQTT_KEY          "751d01a7e9884b48acb28ddefe0557f4"
#define USERNAME          "rodrigo_lobo/"
#define PREAMBLE          "feeds/"
#define T_TEMP            "temperatura"
#define T_UMID            "umidade"
#define T_LUMINOSITY      "luminosity"
#define T_CLIENTSTATUS    "clientstatus"
#define T_COMMAND         "command"


unsigned long entry;
byte clientStatus, prevClientStatus = 99;
float umid, prevUmid = 0;
float tempC, prevTempC = 0;
char valueStr[5];

WiFiClient WiFiClient;
PubSubClient client(WiFiClient); // create MQTT object
DHT dht(DHTPIN, DHTTYPE);


//
void setup() {

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

  client.setServer(SERVER, SERVERPORT);
  client.setCallback(callback);
  dht.begin();
}

//
void loop() {
  //Serial.println("loop");
  yield();
  if (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("", MQTT_USERNAME, MQTT_KEY)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(USERNAME PREAMBLE T_COMMAND, 1);
      client.subscribe(USERNAME PREAMBLE "test", 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

  if (millis() - entry > 2000) {
    Serial.println("Measure");
    entry = millis();
    umid = dht.readHumidity();
    tempC = dht.readTemperature();
  }

  if (client.connected() && prevUmid != umid) {
    Serial.println("Publicar UMIDADE");
    String hi = (String)umid;
    hi.toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE T_UMID, valueStr);
    prevUmid = umid;
    delay(500);
  }

  if (client.connected() && prevTempC != tempC) {
    Serial.println("Publicar TEMPERATURA");
    String hi = (String)tempC;
    hi.toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE T_TEMP, valueStr);
    prevTempC = tempC;
    delay(500);
  }

  if (client.connected()&& prevClientStatus != clientStatus ) {
    Serial.println("Publish Status");

    String hi = (String)clientStatus;
    hi.toCharArray(valueStr, 2);
    client.publish(USERNAME PREAMBLE T_CLIENTSTATUS, valueStr);
    prevClientStatus = clientStatus;
  }
  client.loop();
}


//----------------------------------------------------------------------


void callback(char* topic, byte * data, unsigned int length) {
  // handle message arrived {

  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
  }
  Serial.println();
  if (data[1] == 'F')  {
    clientStatus = 0;
    digitalWrite(LED_PIN, LOW);
  } else {
    clientStatus = 1;
    digitalWrite(LED_PIN, HIGH);
  }
}

