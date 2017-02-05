/** RF24Mesh_Example_Node2NodeExtra.ino by TMRh20
  * 
  * This example sketch shows how to communicate between two (non-master) nodes using
  * RF24Mesh & RF24Network
  */
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include <printf.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9, 10);  // mysensors wiring 9=CE, 10=CSN/CS, 11=MOSI, 12=MISO, 13=SCK
RF24Network network(radio);
RF24Mesh mesh(radio,network);

/** 
 * User Configuration: 
 * nodeID - A unique identifier for each radio. Allows addressing to change dynamically
 * with physical changes to the mesh. (numbers 1-255 allowed)
 **/
#define nodeID 1

struct payload_t {
  unsigned long ms;
  unsigned long counter;
};

uint32_t displayTimer = 0;
void setup() {
    Serial.println(F("Initializing"));
  lcd.begin(16,2);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.printstr("Connecting");
  
  Serial.begin(115200);
  
  // Set the nodeID
  mesh.setNodeID(nodeID);  
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
}
void loop() {
  
  mesh.update();
  // Send to the master node every second
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();
    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&displayTimer, 'M', sizeof(displayTimer))) {
      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        lcd.printstr("Renew address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
        lcd.printstr("Send fail");
      }
    } else {
      Serial.print("Send OK: "); 
      Serial.println(displayTimer);
      lcd.printstr("Send ok");
    }
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
    lcd.printstr("Rcv packet");
    lcd.write(payload.counter);
    lcd.printstr(" at ");
    lcd.write(payload.ms);
  }
}
