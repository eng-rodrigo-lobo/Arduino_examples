#include <PS2X_lib.h>  //for v1.6

/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        12    
#define PS2_CMD        11  
#define PS2_SEL        10  
#define PS2_CLK        13  

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 *  'true' activates the variables
 ******************************************************************/
#define pressures   false
#define rumble      false



/* Parâmetros dos motores */
#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

//default motor speed
short usSpeed = 150;  
unsigned short usMotor_Status = BRAKE;

// create PS2 Controller Class
PS2X ps2x; 
int error = 0; byte type = 0; byte vibrate = 0;
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);  

  
  // **************************************************************************************************
  // testar desativar esses pinos, parecem inuteis ... (qnd aperto quadrado, aciona LED power do shield)
  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  // **************************************************************************************************

  Serial.begin(9600);              // Initiates the serial to do the monitoring

  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
   }
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("4. READ CURRENT");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();
  error = 0; type = 1;
}

void loop() 
{
  controle();
}


/***********************
  Função de controle
************************/

// Controla LEDs na protoboard enquanto botões ou direcionais forem pressionados (pree
void controle()
{
  if(error == 1) //skip loop if no controller found
  return;

  // Habilita os dois motores
  digitalWrite(EN_PIN_1, HIGH); digitalWrite(EN_PIN_2, HIGH);
  
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
  if (ps2x.Button(PSB_PAD_UP))         //will be TRUE as long as button is pressed
  { 
    Serial.println("UP pressionados: aumenta velocidade"); IncreaseSpeed();
  } 

  if (ps2x.Button(PSB_PAD_DOWN))         //will be TRUE as long as button is pressed
  { 
    Serial.println("DOWN pressionado: reduz velocidade"); DecreaseSpeed();
  } 

  if (ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println("Seta DIREITA pressionada: virar pra direita"); turnRight(); delay(50);
  }else Stop();

  if (ps2x.Button(PSB_PAD_LEFT))
  {
    Serial.println("Seta ESQUERDA pressionada: virar pra esquerda"); turnLeft(); delay(50);
  }else Stop();
  
  if (ps2x.Button(PSB_CROSS))         //will be TRUE as long as button is pressed
  { 
    Serial.println("X pressionado: marcha re"); Reverse(); delay(50);
  }else Stop(); 

  if (ps2x.Button(PSB_SQUARE))         //will be TRUE as long as button is pressed
  { 
    Serial.println("QUADRADO pressionado: anda pra frente"); Forward();
  } else Stop(); 

  delay(50);
}

/*=========================================================*/
void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
}

void Forward()
{
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
}

void turnLeft()
{
  Serial.println("Turning LEFT");
  //Motor1_Status = CW; Motor2_Status = CCW;
  motorGo(MOTOR_1, CW, usSpeed);
  motorGo(MOTOR_2, CCW, usSpeed);
}

void turnRight()
{
  Serial.println("Turning RIGHT");
  //Motor1_Status = CCW; Motor2_Status = CW;
  motorGo(MOTOR_1, CCW, usSpeed);
  motorGo(MOTOR_2, CW, usSpeed);
}

void Reverse()
{
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

//Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm);
  }
}


