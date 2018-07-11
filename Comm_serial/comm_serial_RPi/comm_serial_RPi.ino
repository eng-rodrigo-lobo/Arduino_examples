const int pino_led = 13;
char buf;
long baud = 115200;
int estado = 1;
 
void setup()
{
  //setup do LED
  pinMode(pino_led, OUTPUT); digitalWrite(pino_led, LOW);
  
  //inicia a comunicação serial
  Serial.begin(baud); Serial.println("****** Iniciando Monitoramento ******");
}
 
void loop()
{
  while (Serial.available() > 0)
  {
    buf = Serial.read();
    // Caso seja recebido o caracter 'o', muda o estado do led
    if (buf == 'o')
    {
      // Liga ou desliga o led da porta 11
      switchLED(estado);
      
      // Envia a resposta para o Raspberry
      Serial.print("Recebido! - Estado Led: ");
      
      if (estado == 1) { Serial.println("Ligado"); }
      else Serial.println("Desligado");

      // Inverte o estado do led
      estado = !estado; delay(500);
    }
    
  }
}

void switchLED(int state){ digitalWrite(pino_led, state); }
