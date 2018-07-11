/*                  Mapa de chaveamento dos motores usando ponte H
 *       Motor A
 *       In1  |   In2   |       Efeito     
 *    -------------------------------------- 
 *        0V  |   0V    |   Motor desligado
 *        0V  |   5V    |   Sentido 1
 *        5V  |   0V    |   Sentido 2
 *        5V  |   5V    |   Freia o motor
 *       
 *       EnA(PWM):  sem o jumper, é possível controlar a velocidade
 *                  através de uma saída PWM (0 a 255)
 *                  
 *   >>>> NÃO ESQUECER DE JUMPEAR O GND DA FONTE 12V PARA O GND DO ARDUINO <<<<
 *        SENÃO O MOTOR NÃO RODA
*/


//------------------------ Parâmetros variáveis e constantes ------------------------
//parâmetros do LED
const int LED = 13; 

//parâmetros do motor
const int in1 = 7, in2 = 8, controle_motor = 9;
int velocidade_motor = 255;

//parâmetros da comunicação
char buf;
long baud = 115200;

 
void setup()
{
  //setup do LED
  pinMode(LED, OUTPUT); digitalWrite(LED, LOW);

  //setup do motor
  pinMode(in1,OUTPUT); pinMode(in2,OUTPUT); pinMode(controle_motor,OUTPUT);

  //inicia a comunicação serial
  Serial.begin(baud); Serial.println("****** Iniciando Monitoramento ******");
}

//------------------------ Laço principal do programa ------------------------
void loop()
{
  serial_comm_loop();
}

//------------------------ Funções do programa ------------------------
//verifica se há comandos vindo da porta serial e executa se for o caso
void serial_comm_loop()
{
  while (Serial.available() > 0)
  {
    buf = Serial.read();
    
    switch (buf)
    {
      case 'L':
        // Liga o LED e aciona o motor
        ligaLED(); ligaMotor();
      
        // Envia a resposta para o Raspberry
        Serial.println("********************************************");
        Serial.println("Recebido! - LED: on - Motor GIRANDO ");
      break;

      case 'D':
        // Liga o LED e aciona o motor
        desligaLED(); desligaMotor();
      
        // Envia a resposta para o Raspberry
        Serial.println("********************************************");
        Serial.println("Recebido! - LED: off - Motor PARADO ");
      break;
    }    
  }
}


//liga o LED
void ligaLED()    { digitalWrite(LED, HIGH); }


//desliga o LED
void desligaLED() { digitalWrite(LED, LOW); }


//aciona o motor
void ligaMotor()
{
  //Sentido (o cooler só gira nessa config)
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  //Serial.println("in1 = HIGH, in2 = LOW .... Motor LIGADO");Serial.println("-------------------"); 
  analogWrite(controle_motor, velocidade_motor);
}


//desliga o motor
void desligaMotor()
{
  //Sentido (o cooler só gira nessa config)
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  //Serial.println("in1 = LOW, in2 = LOW .... Motor PARADO");Serial.println("-------------------"); 
  analogWrite(controle_motor, 0);
}






//while (Serial.available() > 0)
//  {
//    buf = Serial.read();
//    
//    if(buf == 'l')
//    {
//        // Liga o LED e aciona o motor
//        ligaLED(); ligaMotor();
//      
//        // Envia a resposta para o Raspberry
//        Serial.println("Recebido! - LED: on - Motor GIRANDO ");
//    }
//    if(buf == 'd')
//    { 
//        // Liga o LED e aciona o motor
//        desligaLED(); desligaMotor();
//      
//        // Envia a resposta para o Raspberry
//        Serial.println("Recebido! - LED: off - Motor PARADO ");
//    }
//  }
