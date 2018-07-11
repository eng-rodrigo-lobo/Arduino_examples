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
    Serial.begin(BAUD);
    Serial.println("Iniciando plot de dados do Multimedidor: ");

   //Comunica com o equipamento através de protcolo Modbus (slave ID 1) através da porta Serial (port 0)
   MTDIN2COM.begin(SLAVE_ID, Serial);

   // Callbacks allow us to configure the RS485 transceiver correctly
   MTDIN2COM.preTransmission(preTransmission);
   MTDIN2COM.postTransmission(postTransmission);
}


void loop() {

//      MTDIN2COM.preTransmission(preTransmission);
//      MTDIN2COM.postTransmission(postTransmission);
      
      uint8_t result;
      long  V1_n = 0.0;
      long  L1_n = 0.0;
      long  P1_n = 0.0;
      long  freq = 0.0;
      
for(int i=0;i<2;i++)
{
  switch(i)
  {
    case 0:
        // Ler 6 registradores começando por 0x0000)
        result = MTDIN2COM.readHoldingRegisters(0x0000, 6);
        
        V1_n = ( (MTDIN2COM.getResponseBuffer(0x00) << 32) | MTDIN2COM.getResponseBuffer(0x01)  );
        L1_n = ( (MTDIN2COM.getResponseBuffer(0x02) << 32) | MTDIN2COM.getResponseBuffer(0x03)  );
        P1_n = ( (MTDIN2COM.getResponseBuffer(0x04) << 32) | MTDIN2COM.getResponseBuffer(0x05)  );
        
        MTDIN2COM.clearResponseBuffer();
        
        
        if (result == MTDIN2COM.ku8MBSuccess)
        {
            Serial.println(" ");      
            Serial.println("**************************");
            Serial.print("V1_n: ");
            Serial.print(V1_n/10.0f);
            Serial.println(" V");
            Serial.println("**************************");
            Serial.println(" ");
            Serial.println("**************************");
            Serial.print("L1_n: ");
            Serial.print(L1_n);
            Serial.println(" mA");
            Serial.println("**************************");
            Serial.println(" ");
            Serial.println("**************************");
            Serial.print("P1_n: ");
            Serial.print(P1_n);
            Serial.println(" W");
            Serial.println("**************************");
            Serial.println(" ");
            
         }
      break;

      case 1:
//        MTDIN2COM.preTransmission(preTransmission);
//        MTDIN2COM.postTransmission(postTransmission);
        MTDIN2COM.clearResponseBuffer();
        MTDIN2COM.clearTransmitBuffer();
        result = MTDIN2COM.readHoldingRegisters(0x0028, 2);

        freq = ( (MTDIN2COM.getResponseBuffer(0x00) << 32) | MTDIN2COM.getResponseBuffer(0x01)  );
        MTDIN2COM.clearResponseBuffer();
        if (result == MTDIN2COM.ku8MBSuccess)
        {
            Serial.println(" ");      
            Serial.println("**************************");
            Serial.print("freq: ");
            Serial.print(freq/10.0f);
            Serial.println(" Hz");
            Serial.println("**************************");
            Serial.println(" ");
            
        }
      break;
      
  }//fim do switch

} //fim do for

} //Fim do código *************************************
