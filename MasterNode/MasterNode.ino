#include <LiquidCrystal_I2C.h>

#include <IRLib.h>
#include <IRLibMatch.h>
#include <IRLibRData.h>
#include <IRLibTimer.h>
#include <RF24Network.h>
#include <RF24.h>           // see http://tmrh20.github.io/RF24/classRF24.html
#include <RF24Mesh.h>       // see https://tmrh20.github.io/RF24Mesh/RF24Mesh_Example_Master_8ino-example.html

//Include eeprom.h for AVR (Uno, Nano) etc. except ATTiny
//#include <EEPROM.h>

//#include "protocol.h"
//#include "commands.h"

uint32_t displayTimer = 0;

/***** Configure the chosen CE,CS pins *****/
RF24 radio(9, 10); // mysensors wiring 9=CE, 10=CSN/CS, 11=MOSI, 12=MISO, 13=SCK
RF24Network network(radio);
RF24Mesh mesh(radio,network);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("Start Master");
  
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  Serial.println(mesh.getNodeID());

  // Connect to the mesh
  mesh.begin();
}

void loop() {    
  // Call mesh.update to keep the network updated
  mesh.update();
  
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
  
  // Check for incoming data from the sensors
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    
    uint32_t dat=0;
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'M': network.read(header,&dat,sizeof(dat)); Serial.println(dat); break;
      default: network.read(header,0,0); Serial.println(header.type);break;
    }
  }
  
  if(millis() - displayTimer > 5000){
    displayTimer = millis();
    Serial.println(" ");
    Serial.println(F("********Assigned Addresses********"));
     for(int i=0; i<mesh.addrListTop; i++){
       Serial.print("NodeID: ");
       Serial.print(mesh.addrList[i].nodeID);
       Serial.print(" RF24Network Address: 0");
       Serial.println(mesh.addrList[i].address,OCT);
     }
    Serial.println(F("**********************************"));
  }
}
