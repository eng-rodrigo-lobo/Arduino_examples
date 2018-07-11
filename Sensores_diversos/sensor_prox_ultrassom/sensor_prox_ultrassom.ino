//Autor: FILIPEFLOP
 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger  5
#define pino_echo     4
#define pino_relay    8
#define led           13 
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  pinMode(pino_relay, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(pino_relay, LOW);
  digitalWrite(led, HIGH);
}
 
void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  aciona_relay(cmMsec);
  delay(1000);
  
}

void aciona_relay(float cm)
{
    if (cm > 15)
    {
      digitalWrite(pino_relay, LOW);
      digitalWrite(led, LOW);
    }
    else 
    { digitalWrite(pino_relay, HIGH);
      digitalWrite(led, HIGH);
    }
}
