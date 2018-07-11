/* Controlando LEDs com os comandos do controle PS2 */

#include <PS2X_lib.h>  //for v1.6

/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        12  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        13  //17

#define LED_UP          2
#define LED_RIGHT       3
#define LED_DOWN        4
#define LED_LEFT        5

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 *  'true' activates the variables
 ******************************************************************/
#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0; byte type = 0; byte vibrate = 0;

void setup() {
  Serial.begin(57600);
  
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
  error = 0;

  type = 1;
  pinMode(LED_UP, OUTPUT)  ;  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);  pinMode(LED_LEFT, OUTPUT);

  digitalWrite(LED_UP,LOW)  ; digitalWrite(LED_RIGHT,LOW);
  digitalWrite(LED_DOWN,LOW); digitalWrite(LED_LEFT,LOW);
  
}

void loop() 
{
  controle();
}




// Controla LEDs na protoboard enquanto botões ou direcionais forem pressionados (pree
void controle()
{
  if(error == 1) //skip loop if no controller found
  return; 
  
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
  if (ps2x.Button(PSB_PAD_UP) || ps2x.Button(PSB_TRIANGLE))         //will be TRUE as long as button is pressed
  { 
    Serial.println("UP ou TRIANGULO pressionados"); digitalWrite(LED_UP,HIGH);
  } else digitalWrite(LED_UP,LOW);

  if (ps2x.Button(PSB_PAD_RIGHT) || ps2x.Button(PSB_CIRCLE))         //will be TRUE as long as button is pressed
  { 
    Serial.println("RIGHT ou CIRCULO pressionados"); digitalWrite(LED_RIGHT,HIGH);
  } else digitalWrite(LED_RIGHT,LOW);
  
  if (ps2x.Button(PSB_PAD_DOWN) || ps2x.Button(PSB_CROSS))         //will be TRUE as long as button is pressed
  { 
    Serial.println("DOWN ou X pressionados"); digitalWrite(LED_DOWN,HIGH);
  } else digitalWrite(LED_DOWN,LOW);

  if (ps2x.Button(PSB_PAD_LEFT) || ps2x.Button(PSB_SQUARE))         //will be TRUE as long as button is pressed
  { 
    Serial.println("LEFT ou QUADRADO pressionados"); digitalWrite(LED_LEFT,HIGH);
  } else digitalWrite(LED_LEFT,LOW);  

  delay(50);
}

