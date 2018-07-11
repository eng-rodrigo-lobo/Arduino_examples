//Programa para leitura do medidor de energia PM210 da Schneider

#include <ModbusMaster.h>
#include<SoftwareSerial.h>

// Definindo Pino Enable comm
#define MAX485_DE_RE 2

// Definindo parâmetros de comunicação
#define BAUD      9600
#define SLAVE_ID  1

//Iniciar objeto ModbusMaster
ModbusMaster PM210;
SoftwareSerial RS485(8, 9);

void preTransmission()
{
digitalWrite(MAX485_DE_RE, 1);
}

void postTransmission()
{
digitalWrite(MAX485_DE_RE, 0);
}

void setup() {
    
    // Init in receive mode
    pinMode(MAX485_DE_RE, OUTPUT);
    digitalWrite(MAX485_DE_RE, 0);
    
    //Iniciar comunicação serial Serial port 0 Rx/Tx (pinos 0 e 1), com baud rate 19200:
    Serial.begin(19200);
    Serial.println("Iniciando plot de dados do Multimedidor: ");

    //Inicia a leitura via softwareserial
    RS485.begin(BAUD); 
    
   //Comunica com o equipamento através de protcolo Modbus (slave ID 1) através da porta SoftSerial
   PM210.begin(SLAVE_ID, RS485);

   // Callbacks allow us to configure the RS485 transceiver correctly
   PM210.preTransmission(preTransmission);
   PM210.postTransmission(postTransmission);
}


void loop() {
   
      uint8_t result;
      //float result;
      long  V1_n = 0.0;
      long  V2_n = 0.0;
      long  V3_n = 0.0;
      long  freq = 0.0;
      
        // Ler 6 registradores começando por 0x1019)
        //result = PM210.readHoldingRegisters(1059, 2);
        result = PM210.readInputRegisters(1059, 2);
                
        freq = ( (PM210.getResponseBuffer(0x00) << 16) | PM210.getResponseBuffer(0x01)  );
        
        if (result == PM210.ku8MBSuccess)
        {
            Serial.println(" ");      
            Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            Serial.print("freq: ");
            Serial.print(freq/10.0f);
            Serial.println(" Hz");
            Serial.println(PM210.getResponseBuffer(0x00), HEX);
            Serial.println(PM210.getResponseBuffer(0x01), HEX);
            Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
            Serial.println(" ");
            
        }

} //Fim do código *************************************
