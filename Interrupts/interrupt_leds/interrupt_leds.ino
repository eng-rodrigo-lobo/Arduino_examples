/*
  Exemplo de uso de interrupções

  LED 01 vai piscar em f = 0.5 Hz
  LED 02 vai acender quando o botão for pressionado

*/

// Estado do LED 02 (alterado pela interrupção)
volatile byte led2state = LOW;

// Valores dos pinos de entrada dos LEDs
const int led1 = 8;
const int led2 = 9;

const int button = 2;

void setup() {
  // Set dos LEDs para saída
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  Serial.begin(9600);

  // Set do botão para entrada, acionando o pull-up resistor
  pinMode(button, INPUT_PULLUP);
  
  // Configurando a interrupção
  attachInterrupt(digitalPinToInterrupt(button), turn_led2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  delay(500);
  
}

void turn_led2(){
  led2state = !led2state;
  digitalWrite(led2, led2state);
}
