////////////////////////////////////////////////////////////////
//Importa Bibliotecas
////////////////////////////////////////////////////////////////
#include <IRremote.h>
//FIM///////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Define portas digitais
////////////////////////////////////////////////////////////////
//FIM///////////////////////////////////////////////////////////
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN); 
decode_results results;

void setup() 
{ 
  Serial.begin(9600);
  delay(300);
  irrecv.enableIRIn();
  Serial.println("Iniciado");
  delay(100);
}

void loop()
{
  lerIR();
  delay(1);
}

void lerIR()
{
  if (irrecv.decode(&results))
  { 
    dump(&results); 
    irrecv.resume();
  }
}

int line = 0;

void dump(decode_results *results)
{ 
  int count = results->rawlen;

  Serial.print("unsigned int raw["); 
  Serial.print(count, HEX); 
  Serial.print("] = {");
  for (int i = 1; i < count; i++)
  {
    line++;

    if ((i % 2) == 1)
    { 
      int primeiro = highByte(results->rawbuf[i]*USECPERTICK);
      int segundo = lowByte(results->rawbuf[i]*USECPERTICK);
      
      Serial.print(" ");
      Serial.print(primeiro, HEX);
      Serial.print(" ");
      Serial.print(segundo, HEX);
    } 
    else
    { 
      Serial.print(" ");
      Serial.print(highByte((int)results->rawbuf[i]*USECPERTICK), HEX);
      Serial.print(" ");
      Serial.print(lowByte((int)results->rawbuf[i]*USECPERTICK), HEX);
      
    }
    Serial.print("  ");
    
    if(line==20)
    {
      line=0;
      Serial.println();
    }        
  }

  Serial.println("};");
}
