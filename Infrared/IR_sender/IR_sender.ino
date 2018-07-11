#include <IRremote.h>

IRsend sender;
int go =0;
char nByte[4];
int byteCounter = 0;
String comm;
unsigned int Volume_UP[68]    = {9000, 4450, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 550, 600, 550, 550, 600, 550, 550, 600, 1650, 550, 1700, 550, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 550, 600, 1700, 550, 550, 550, 600, 550, 550, 600, 550, 550, 550, 600, 550, 550, 1700, 550, 600, 550, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 1700, 550};
unsigned int Volume_DOWN[68]  = {9050, 4400, 650, 500, 600, 500, 650, 1600, 650, 500, 600, 500, 650, 500, 600, 550, 600, 500, 650, 1600, 600, 1650, 600, 550, 600, 1650, 600, 1600, 650, 1600, 650, 1600, 650, 1600, 600, 1600, 650, 1650, 600, 500, 650, 500, 600, 550, 600, 500, 650, 450, 650, 500, 650, 500, 600, 550, 600, 1600, 650, 1600, 650, 1600, 650, 1600, 600, 1650, 600, 1650, 600};

void clearVar(){
for (int a=0;a<15;a++){
nByte[a] = 0;
}
}

void setup(){
Serial.begin(9600);
clearVar();
}

void loop(){
if (Serial.available() > 0){
//nByte[4] = Serial.read();
go = 1;
//byteCounter++;
}
else if (go == 1){
comm = nByte;
if (Serial.read() == "up"){
Serial.println("Aumentar volume TV");
sender.sendRaw(Volume_UP,68,38);//buffer,lenght,KHz
}
else if (Serial.read() == "down"){
Serial.println("Diminuir volume TV");
sender.sendRaw(Volume_DOWN,68,38);//buffer,lenght,KHz
}
else{
Serial.println(nByte);
//Serial.println(go);
}

go = 0;
byteCounter = 0;
clearVar();
}
}
