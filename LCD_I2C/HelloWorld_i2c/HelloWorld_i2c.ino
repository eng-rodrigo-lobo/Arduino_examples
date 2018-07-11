/*
            Arduino UNO          Arduino MEGA
  pino SDA    ---> A4             ---> 20
  pino SCL    ---> A5             ---> 21
  
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char str1[] = "arduino";
char str2[] = "Hello World!";

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}
 
void loop()
{
  lcd.setCursor(0, 0); lcd.print(str1);
  //lcd.setCursor(0, 1); lcd.print(str2);
  Serial.println(str1);Serial.println(str2);delay(1000);
}
