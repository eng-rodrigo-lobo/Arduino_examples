#include <SimpleModbusMaster.h>

/*
   The example will use packet1 to read a register from address 0 (the adc ch0 value)
   from the arduino slave (id=1). It will then use this value to adjust the brightness
   of an led on pin 9 using PWM.
   It will then use packet2 to write a register (its own adc ch0 value) to address 1 
   on the arduino slave (id=1) adjusting the brightness of an led on pin 9 using PWM.
*/

//////////////////// Port information ///////////////////
#define baud 9600
#define timeout 100
#define polling 100 // the scan rate
#define retry_count 10
#define SERIAL_8N1 0x06

// used to toggle the receive/transmit pin on the driver
//SoftwareSerial pins 
#define TxEnablePin 2


// The total amount of available memory on the master to store data
#define TOTAL_NO_OF_REGISTERS 13

// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.
enum
{
  PACKET1,
  PACKET2,
  TOTAL_NO_OF_PACKETS // leave this last entry
};

// Create an array of Packets to be configured
Packet packets[TOTAL_NO_OF_PACKETS];

// Masters register array
unsigned int regs[TOTAL_NO_OF_REGISTERS];

void setup()
{
  // Initialize each packet
/*void modbus_construct(Packet *_packet, unsigned char id, unsigned char function, 
                        unsigned int address, unsigned int data, unsigned int local_start_address)
{
  _packet->id = id;
  _packet->function = function;
  _packet->address = address;
  _packet->data = data;
  _packet->local_start_address = local_start_address;
  _packet->connection = 1;
}*/
  Serial.begin(19200);
    
  modbus_construct(&packets[PACKET1], 1, READ_HOLDING_REGISTERS, 0, 1, 0); //Tensão L1-N - reg 00
  //modbus_construct(&packets[PACKET2], 1, READ_HOLDING_REGISTERS, 1, 1, 1); //Tensão L1-N - reg 01
  
  // Initialize the Modbus Finite State Machine
  modbus_configure(&Serial, baud, SERIAL_8N1, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);

}

void loop()
{
  modbus_update();

  //float V1_n = ( (regs[0] << 16) || regs[1] )/10.0f;

  Serial.println("DEBUG");
  Serial.print("requests: ");
  Serial.println(packets[PACKET1].requests);
  Serial.print("successful_requests: ");
  Serial.println(packets[PACKET1].successful_requests);
  Serial.print("failed_requests: ");
  Serial.println(packets[PACKET1].failed_requests);
  Serial.print("exception_errors: ");
  Serial.println(packets[PACKET1].exception_errors);
  Serial.print("connection: ");
  Serial.println(packets[PACKET1].connection);
  Serial.print("regs[0]: ");
  Serial.println(regs[0], HEX);
 // Serial.println(" V");
  Serial.println("************************");
  delay(100);
}
