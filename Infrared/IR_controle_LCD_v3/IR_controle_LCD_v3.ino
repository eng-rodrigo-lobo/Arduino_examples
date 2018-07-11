/*
  Display LCD + controle IR + timer (futuro)
- receber comandos do controle
- gravar 2 ou 3 horarios distintos (hora e min)
- acionar saidas de acordo com prog. horária

--> bibliotecas: New LiquidCrystal (I2C), IRRemote
*/

// Lista de comandos do mini controle remoto LG
#define  C_PWR  0x7887      //código IR botão PWR
#define  C_1    0xFFFF827D  //código IR botão 1
#define  C_2    0x42BD      //código IR botão 2
#define  C_3    0xFFFFC23D  //código IR botão 3
#define  C_4    0x22DD      //código IR botão 4
#define  C_5    0xFFFFA25D  //código IR botão 5
#define  C_6    0x629D      //código IR botão 6
#define  C_7    0xFFFFE21D  //código IR botão 7
#define  C_8    0x12ED      //código IR botão 8
#define  C_9    0xFFFF926D  //código IR botão 9
#define  C_0    0xFFFFD22D  //código IR botão 0
#define  C_UP   0xFFFFE817  //código IR botão UP
#define  C_DOWN 0x6897      //código IR botão DOWN
#define  C_SRC  0x33CC      //código IR botão SRC
#define  C_MENU 0x55AA      //código IR botão MENU
#define  C_NUM  0x748B      //código IR botão NUMBER #
#define  C_BAND 0xFFFF9A65  //código IR botão BAND
#define  C_DISP 0xFFFFC53A  //código IR botão DISP
//----------------------------------------------------------------------------------

// Flags de acionamento dos botões
byte flag_c_pwr = 0; byte flag_c_1    = 0; byte flag_c_2    = 0; byte flag_c_3 = 0; byte flag_c_4 = 0;
byte flag_c_5   = 0; byte flag_c_6    = 0; byte flag_c_7    = 0; byte flag_c_8 = 0; byte flag_c_9 = 0;
byte flag_c_0   = 0; byte flag_c_up   = 0; byte flag_c_down = 0; byte flag_c_src = 0; byte flag_c_menu = 0;
byte flag_c_num = 0; byte flag_c_band = 0; byte flag_c_disp = 0;

// Bibliotecas do projeto
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Constantes
int RECV_PIN = 6;
char setupMsg1[] = "Arduino";
char setupMsg2[] = "Controle IR";
char instrucaoGravar[] = "Num. + #:";
char checkTime1[] = "Formato invalido";
char checkTime2_H[] = "Hora > 0..23";
char checkTime2_M[] = "Min. > 0..59";
char finalProg[] = "Fim do programa!";

//Valores de horas e minutos a serem gravados
int hora_01 = 0;
int min_01  = 0;
int hora_02 = 0;
int min_02  = 0;
int outputNum = 0;    //Recebe os valores na função 'gravaNumero()'

// Variavel de estado do fluxo do programa
byte state = 0;

// Declaração de construtores do projeto
IRrecv irrecv(RECV_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
decode_results results;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); lcd.print(setupMsg1);
  lcd.setCursor(0, 1); lcd.print(setupMsg2);
  irrecv.enableIRIn(); // Start the receiver
  delay(500);
  state = 1;
}

void loop() {
  switch (state) {
    case 1: lcd.clear(); lcd.setCursor(0, 0); lcd.print(instrucaoGravar);
            lcd.setCursor(0, 1); lcd.print("Hora 1: "); gravaNumero(); hora_01 = outputNum; if(!checkHour(hora_01)){state=state;}else{state++;}; break;

    case 2: lcd.clear(); lcd.setCursor(0, 0); lcd.print(instrucaoGravar);
      lcd.setCursor(0, 1); lcd.print("Min. 1: "); gravaNumero(); min_01 = outputNum; if(!checkMin(min_01)){state=state;}else{state++;}; break;

    case 3: lcd.clear(); lcd.setCursor(0, 0); lcd.print(finalProg); lcd.setCursor(0, 1);
            lcd.print("1) "); if (hora_01 < 10) {lcd.print("0");} lcd.print(hora_01); lcd.print("h");
                              if (min_01  < 10) {lcd.print("0");} lcd.print(min_01); 
            Serial.println(hora_01+"h"+min_01); delay(5000); state=1;
    
  }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/***************** FUNÇÕES DO PROGRAMA ******************/

// Leitura do sensor IR
void leituraIR()
{
  if (irrecv.decode(&results)) {
    int codeIR = results.value;
    qualBotao(codeIR);
    irrecv.resume(); // Receive the next value
  }
}

// Analisa qual botão foi apertado
void qualBotao(int irInput)
{
  switch (irInput) {

    case C_PWR: flag_c_pwr  = 1; Serial.println("Botao PWR"); break;   case C_1:  flag_c_1 = 1; Serial.println("Botao 1"); break;
    case C_2:   flag_c_2    = 1; Serial.println("Botao 2")  ; break;   case C_3:  flag_c_3 = 1; Serial.println("Botao 3"); break;
    case C_4:   flag_c_4    = 1; Serial.println("Botao 4")  ; break;   case C_5:  flag_c_5 = 1; Serial.println("Botao 5"); break;
    case C_6:   flag_c_6    = 1; Serial.println("Botao 6")  ; break;   case C_7:  flag_c_7 = 1; Serial.println("Botao 7"); break;
    case C_8:   flag_c_8    = 1; Serial.println("Botao 8")  ; break;   case C_9:  flag_c_9 = 1; Serial.println("Botao 9"); break;
    case C_0:   flag_c_0    = 1; Serial.println("Botao 0")  ; break;   case C_UP: flag_c_up = 1; Serial.println("Botao UP"); break;
    case C_DOWN: flag_c_down = 1; Serial.println("Botao DOWN"); break; case C_SRC:  flag_c_src  = 1; Serial.println("Botao SRC"); break;
    case C_MENU: flag_c_menu = 1; Serial.println("Botao MENU"); break; case C_NUM:  flag_c_num  = 1; Serial.println("Botao NUM"); break;
    case C_BAND: flag_c_band = 1; Serial.println("Botao BAND"); break; case C_DISP: flag_c_disp = 1; Serial.println("Botao DISP"); break;
  }
}

// Imprimir os numeros no display
void gravaNumero()
{
  byte col = 8; // começa no 8 por conta do texto que vem antes na tela (Hora x: / Min. X:)
  byte i = 0; char inputNum[2] = "";
  //Enquanto o user não apertar # ou digitar 2 números
  while (flag_c_num == 0 && col < 10) {
    leituraIR();
           if (flag_c_1 == 1) {lcd.setCursor(col, 1); lcd.print("1"); inputNum[i] = '1'; col++; i++; flag_c_1 = 0;}
      else if (flag_c_2 == 1) {lcd.setCursor(col, 1); lcd.print("2"); inputNum[i] = '2'; col++; i++; flag_c_2 = 0;}
      else if (flag_c_3 == 1) {lcd.setCursor(col, 1); lcd.print("3"); inputNum[i] = '3'; col++; i++; flag_c_3 = 0;}
      else if (flag_c_4 == 1) {lcd.setCursor(col, 1); lcd.print("4"); inputNum[i] = '4'; col++; i++; flag_c_4 = 0;}
      else if (flag_c_5 == 1) {lcd.setCursor(col, 1); lcd.print("5"); inputNum[i] = '5'; col++; i++; flag_c_5 = 0;}
      else if (flag_c_6 == 1) {lcd.setCursor(col, 1); lcd.print("6"); inputNum[i] = '6'; col++; i++; flag_c_6 = 0;}
      else if (flag_c_7 == 1) {lcd.setCursor(col, 1); lcd.print("7"); inputNum[i] = '7'; col++; i++; flag_c_7 = 0;}
      else if (flag_c_8 == 1) {lcd.setCursor(col, 1); lcd.print("8"); inputNum[i] = '8'; col++; i++; flag_c_8 = 0;}
      else if (flag_c_9 == 1) {lcd.setCursor(col, 1); lcd.print("9"); inputNum[i] = '9'; col++; i++; flag_c_9 = 0;}
      else if (flag_c_0 == 1) {lcd.setCursor(col, 1); lcd.print("0"); inputNum[i] = '0'; col++; i++; flag_c_0 = 0;}
  }
  flag_c_num = 0;                               // resetando a flag num (caso user aperte 0..9 + #)
  outputNum = atoi(inputNum);                   // Converte a string inputNum num int outputNum
  lcd.setCursor(col, 1); lcd.print(" OK!");     // Mostra pro usuário na tela que a informação foi gravada com sucesso
  delay(500);                                   // Tempo suficiente pro usuário ler a mensagem acima
}

// Verifica se o user colocou hr < 24 e/ou min < 60
bool checkHour(int hour)
{
  bool hourOK = false;
  if (hour >= 24){lcd.clear(); lcd.setCursor(0, 0); lcd.print(checkTime1);
                  lcd.setCursor(0, 1); lcd.print(checkTime2_H); delay(2500); hourOK = false;}
                  else {hourOK = true;} //Se estiver OK avança
  return hourOK;
}

bool checkMin(int minute)
{
  bool minOK = false;
  if (minute >= 60){lcd.clear(); lcd.setCursor(0, 0); lcd.print(checkTime1);
                    lcd.setCursor(0, 1); lcd.print(checkTime2_M); delay(2500); minOK = false;}
                    else {minOK = true;} //Se estiver OK avança
  return minOK;
}










// Para referência, não devo usar
void dump(decode_results *results) {
  int val1 = results->value;
  Serial.println(val1, HEX);
}
