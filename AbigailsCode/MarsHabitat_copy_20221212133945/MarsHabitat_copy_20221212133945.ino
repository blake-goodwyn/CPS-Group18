/* 
Cyber Physcials 2022/23 GID/IDE
Mars Habitat 
By: Abigail Hoover, Blake Goodwyn, Richard Alexandre 

This script features connecting and checking both servos and hall effect senors. 
Gathering voltages of Hall Effect sensors and running it through wekinator then outputing
a specific state to move our habitat 
*/

// Libraries //
#include <definitions.h>

// Properties // 
char ssid[] = "yourNetwork"; // your network SSID (name) 
char pass[] = "12345678"; // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status


void setup() {
  // initialise serial:
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  int sensorValue = analogRead(A2);
  Serial.println(sensorValue);
  int sensorValue = analogRead(A3);
  Serial.println(sensorValue);
  delay(1);  // delay in between reads for stability
}

// Turns values into OSC and send to wekinator 
// Get state from wekinator 

// Servo Cases //
void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For
    // example 'a' = 97, 'b' = 98, and so forth:

arm.position(int arm, int endstate) 
  // to do move arm position 

  //
switch (state) {
  case "360deg":
    ArmA.position(crimp)
    ArmB.position(crimp)
    ArmC.position(normal)
    ArmD.position(sloper)
    ArmE.position(sloper)
    ArmF.position(normal)
    break;
  case "60deg":
    ArmA.position(normal)
    ArmB.position(crimp)
    ArmC.position(crimp)
    ArmD.position(normal)
    ArmE.position(sloper)
    ArmF.position(sloper)
    break;
  case "120deg":
    ArmA.position(sloper)
    ArmB.position(normal)
    ArmC.position(crimp)
    ArmD.position(crimp)
    ArmE.position(normal)
    ArmF.position(sloper)
    break;
  case "180deg":
    ArmA.position(sloper)
    ArmB.position(sloper)
    ArmC.position(normal)
    ArmD.position(crimp)
    ArmE.position(crimp)
    ArmF.position(normal)
    break;
  case "240deg":
    ArmA.position(normal)
    ArmB.position(sloper)
    ArmC.position(sloper)
    ArmD.position(normal)
    ArmE.position(crimp)
    ArmF.position(crimp)
    break;
  case "300deg": 
    ArmA.position(crimp)
    ArmB.position(normal)
    ArmC.position(sloper)
    ArmD.position(sloper)
    ArmE.position(normal)
    ArmF.position(crimp)
    break;
  default:
    ArmA.position(normal)
    ArmB.position(normal)
    ArmC.position(normal)
    ArmD.position(normal)
    ArmE.position(normal)
    ArmF.position(normal)
    break;
  }
}