//Programa para leitura do medidor de energia MTDIN2COM da GE

#include <ModbusMaster.h>

// Definindo Pino Enable comm
#define MAX485_DE_RE 2

// Definindo parâmetros de comunicação
#define BAUD      9600
#define SLAVE_ID  1

//Iniciar objeto ModbusMaster
ModbusMaster MTDIN2COM;

void preTransmission()
{
digitalWrite(MAX485_DE_RE, 1);
}

void postTransmission()
{
digitalWrite(MAX485_DE_RE, 0);
}

void setup() {

    pinMode(MAX485_DE_RE, OUTPUT);

    // Init in receive mode
    digitalWrite(MAX485_DE_RE, 0);
    
    //Iniciar comunicação serial Serial port 0 Rx/Tx (pinos 0 e 1), com baud rate 9600:
    Serial.begin(9600);

   //Comunica com o equipamento através de protcolo Modbus (slave ID 1) através da porta Serial (port 0)
   MTDIN2COM.begin(1, Serial);

   // Callbacks allow us to configure the RS485 transceiver correctly
   MTDIN2COM.preTransmission(preTransmission);
   MTDIN2COM.postTransmission(postTransmission);
}


void loop() {

      uint32_t result;
      static uint32_t i;
      uint8_t j;
      uint16_t data[6];
      i++;

      // slave: read (6) 16-bit registers starting at register 2 to RX buffer
      result = MTDIN2COM.readHoldingRegisters(0, 6);
      
      // do something with data if read is successful
      float V1_n = ( (MTDIN2COM.getResponseBuffer(0x00) << 16) || MTDIN2COM.getResponseBuffer(0x01)  )/10.0f;
      float L1_n = ( (MTDIN2COM.getResponseBuffer(0x02) << 16) || MTDIN2COM.getResponseBuffer(0x03)  )/10.0f;
      float P1_n = ( (MTDIN2COM.getResponseBuffer(0x04) << 16) || MTDIN2COM.getResponseBuffer(0x05)  )/10.0f;
      float freq = ( (MTDIN2COM.getResponseBuffer(0x28) << 16) || MTDIN2COM.getResponseBuffer(0x29)  )/10.0f;
            
      if (result == MTDIN2COM.ku8MBSuccess)
      {
      Serial.println("**************************");
      Serial.print("Reg 00: ");
      //Serial.println(MTDIN2COM.getResponseBuffer(0x00), HEX);
//      Serial.print("Reg 01: ");
//      Serial.println(MTDIN2COM.getResponseBuffer(0x01), HEX);
//      Serial.print("V1-N: ");
//      Serial.println(V1_n);
//      Serial.print("L1-N: ");
//      Serial.println(L1_n);
//      Serial.print("P1-N: ");
//      Serial.println(P1_n);
//      Serial.print("Frequencia: ");
//      Serial.println(freq);
      Serial.println("**************************");

      }
//      // Ler 48 registradores começando por 0x0000)
//      result = MTDIN2COM.readHoldingRegisters(0x0000, 48);
     
     // delay(1000);
       
//Fim do código *************************************
}
