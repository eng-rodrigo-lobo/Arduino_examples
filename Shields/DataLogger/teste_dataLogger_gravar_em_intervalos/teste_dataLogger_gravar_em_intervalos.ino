//Programa: Datalogger com Arduino, modulo RTC DS1307 e cartao SD
//Alteracoes e adaptacoes: Rodrigo Lobo

/*
Pinagem do projeto:

Gravador microSD              Arduino
SCK  (3.3V)     ------------------>   pino 13 (5V)
MISO (5V)       ------------------>   pino 12 (5V)
MOSI (3.3V)     ------------------>   pino 11 (5V)
CS   (3.3V)     ------------------>   pino 4  (5V)

--------------------------------------------------------- 
--------------------------------------------------------- 

Módulo RTC DS1307             Arduino
SDA (5V)      ------------------>   pino A4 (5V)
SCL (5V)      ------------------>   pino A5 (5V)

*/

//***************************
//Bibliotecas
//***************************
#include "RTClib.h"
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
 
//***************************
//Variáveis globais
//***************************
const byte CS_PIN = 10;       // Pino CS de conexão do leitor de cartão SD

const byte hora_Log01 = 17;      // Hora de inicio da leitura no intervalo 01
const byte minINIT_Log01 = 40;   // Min de inicio da leitura no intervalo 01
const byte minFIM_Log01 = 59;    // Min de término da leitura no intervalo 01

const byte hora_Log02 = 18;      // Hora de inicio da leitura no intervalo 01
const byte minINIT_Log02 = 0;   // Min de inicio da leitura no intervalo 01
const byte minFIM_Log02 = 59;    // Min de término da leitura no intervalo 01




//***************************
//Construtores
//***************************
File logger;
RTC_DS1307 rtc;


void setup()
{
  Serial.begin(9600);
  Serial.println("Data logger");
  
  //Inicia o cartao SD
  setup_SD();
    
  //Inicia o real time clock
  setup_RTC();
 
 }


 //*************************** Loop principal do Arduino ***************************************************
 void loop(void)
{
      //Le as informacoes de data e hora
      DateTime now = rtc.now();

      switch (now.hour()){

        case(hora_Log01):
            
            if(now.minute() >= minINIT_Log01 && now.minute() < minFIM_Log01)
            {
              debug_serial_cartao_SD();
              grava_SD(logger);
              delay(1000);
            }
            break;

        case(hora_Log02):
            if(now.minute() >= minINIT_Log02 && now.minute() < minFIM_Log02)
            {
              debug_serial_cartao_SD();
              grava_SD(logger);
              delay(1000);
            }
            break;
        
        default:
          Serial.println("Fora do intervalo de gravacao!");
          break;
      
      
      }//Fim switch
      
       
}
//*************************** Loop principal do Arduino ***************************************************



//*************************************************************
//Funções para inicializar os módulos e realizar as leituras
//*************************************************************

//setup inicial do relógio
void setup_RTC(){
  
  //Verifica as condicoes do RTC
  if (!rtc.begin())
    {
    Serial.println("RTC nao encontrado!");
    while (1);
    }
  
  if (!rtc.isrunning())
    {
    Serial.println("RTC nao operante!");
    //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //A linha abaixo permite ajustar manualmente a data e hora do RTC
    //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   }

}

//setup inicial do módulo leitor SD
void setup_SD(){

  //pinMode(CS_PIN, OUTPUT);
 
  //Inicia o cartao SD
  Serial.println("Iniciando cartao SD...");
  if (!SD.begin(CS_PIN))
    {
    Serial.println("Falha na inicializacao do SD!");
    return;
    }
  Serial.println("Cartao SD iniciado. OK");
  Serial.println();
}


//Grava dados de hora no cartao SD
void grava_SD(File file)
{
  //Abre arquivo no SD para gravacao
  file = SD.open("stp_log.txt", FILE_WRITE);

  if (file)
  {
    Serial.print("arquivo txt foi aberto com sucesso! ");  
  }
  
  //Le as informacoes de data e hora
  DateTime now = rtc.now();
     
  //Grava os dados no cartao SD
  file.print("Data/hora: ");
  file.print(now.day() < 10 ? "0" : "");
  file.print(now.day(), DEC);
  file.print('/');
  file.print(now.month() < 10 ? "0" : "");
  file.print(now.month(), DEC);
  file.print('/');
  file.print(now.year(), DEC);
  file.print(' ');
  file.print("Hora: ");
  file.print(now.hour() < 10 ? "0" : "");
  file.print(now.hour(), DEC);
  file.print(':');
  file.print(now.minute() < 10 ? "0" : "");
  file.print(now.minute(), DEC);
  file.print(':');
  file.print(now.second() < 10 ? "0" : "");
  file.println(now.second(), DEC);
  
  //Fecha arquivo
  file.close();
  
}

//Mostra no prompt o que está sendo gravado no cartão SD
void debug_serial_cartao_SD()
{
  //Le as informacoes de data e hora
  DateTime now = rtc.now();
  
  //Grava os dados no cartao SD
  Serial.print("Data/hora: ");
  Serial.print(now.day() < 10 ? "0" : "");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month() < 10 ? "0" : "");
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour() < 10 ? "0" : "");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute() < 10 ? "0" : "");
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second() < 10 ? "0" : "");
  Serial.println(now.second(), DEC);
   
}
