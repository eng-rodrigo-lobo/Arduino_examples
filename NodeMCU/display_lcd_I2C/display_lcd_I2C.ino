#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2); //FUNÇÃO DO TIPO "LiquidCrystal_I2C"

void setup() {
  Serial.begin(115200);
  //Use predefined PINS consts
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.home();
  lcd.print("Hello, NodeMCU");
  delay(10000);
  lcd.clear();

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("   Funcionou!");
  lcd.setCursor(0, 1);
  lcd.print("* Hello World *");
  delay(1500);
  lcd.clear();
  delay(1500);
}
