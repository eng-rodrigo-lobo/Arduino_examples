/**************************************************************/
/* Código teste para acionamento de LED na porta D7 (GPIO 13) */
/* quando o reed switch na porta D1 (GPIO 05)é fechado.       */
/**************************************************************/

// Contantes que representam os pinos do switch e do LED
const int reed_switch = 5;
const int led_pin = 13;

// variável ledState armazena estado do LED
int led_state = LOW;
int reed_state;            

void setup() {

  // Iniciando a porta serial a um baud rate de 115200:
  Serial.begin(115200);
  Serial.println("****************************");
  Serial.println("     Programa iniciado.");
  Serial.println("****************************");
  
  // Setando o pino do LED como output:
  pinMode(led_pin, OUTPUT);

  // Setando o pino do reed switch como input:
  pinMode(reed_switch, INPUT);

}

void loop() {
  
  reed_state = digitalRead(reed_switch);
  
  if (reed_state == true){
    led_state = HIGH;
    digitalWrite(led_pin, led_state);
    Serial.println("Reed switch FECHADO! ");
    Serial.println(reed_state);
    }
    else {
      led_state = LOW;
      digitalWrite(led_pin, led_state);
      Serial.println("Reed switch ABERTO! ");
      Serial.println(reed_state);
    }

}
