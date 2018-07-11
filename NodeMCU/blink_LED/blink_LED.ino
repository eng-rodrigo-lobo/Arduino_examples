/* Exemplo Pisca LED para NodeMCU */

int LED_AZUL = 16; //led integrado na placa
int LED_EXT  = D1; //led externo ligado na porta D7

void setup() {
  // Define o pino 13 como saida
  pinMode(LED_EXT, OUTPUT); //led externo
  pinMode(LED_AZUL, OUTPUT); //led embarcado azul
  Serial.begin(9600);
}
 
void loop() {
  digitalWrite(LED_EXT, HIGH);   // Acende o Led externo
  delay(1000);                   // Aguarda 1 segundo
  digitalWrite(LED_AZUL, HIGH);
  Serial.println("Led ON");// Acende o Led externo
  delay(1000);                   // Aguarda 1 segundo
  
  digitalWrite(LED_EXT, LOW);    // Apaga o Led
  delay(1000);                  // Aguarda 1 segundo
  digitalWrite(LED_AZUL, LOW);
  Serial.println("Led OFF");  // Apaga o Led
  delay(1000);                  // Aguarda 1 segundo
}
