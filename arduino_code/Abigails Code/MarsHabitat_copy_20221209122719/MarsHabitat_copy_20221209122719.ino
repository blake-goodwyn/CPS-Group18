/* 
Cyber Physcials 2022/23 GID/IDE
Mars Habitat 
By: Abigail Hoover, Blake Goodwyn, Richard Alexandre 

This script features connecting and checking both servos and hall effect senors. 
Gathering voltages of Hall Effect sensors and running it through wekinator then outputing
a specific state to move our habitat 
*/

// Libraries //
#include "definitions.h"
#include "PCA9685.h"

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

void arm_position (int arm, int endstates) {
   servo.setAngle(arm, endstate);
}

// define state 

switch (state) {
  case "360deg":
    arm_position(arm_A, crimp);
    arm_position(arm_B, crimp);
    arm_position(arm_C, normal);
    arm_position(arm_D, sloper);
    arm_position(arm_E, sloper);
    arm_position(arm_F, normal);
    break;
  case "60deg":
    arm_position(arm_A, normal);
    arm_position(arm_B, crimp);
    arm_position(arm_C, crimp);
    arm_position(arm_D, normal);
    arm_position(arm_E, sloper);
    arm_position(arm_F, sloper);
    break;
  case "120deg":
    arm_position(arm_A, sloper);
    arm_position(arm_B, normal);
    arm_position(arm_C, crimp);
    arm_position(arm_D, crimp);
    arm_position(arm_E, normal);
    arm_position(arm_F, sloper);
    break;
  case "180deg":
    arm_position(arm_A, sloper);
    arm_position(arm_B, sloper);
    arm_position(arm_C, normal);
    arm_position(arm_D, crimp);
    arm_position(arm_E, crimp);
    arm_position(arm_F, normal);
    break;
  case "240deg":
    arm_position(arm_A, normal);
    arm_position(arm_B, sloper);
    arm_position(arm_C, sloper);
    arm_position(arm_D, normal);
    arm_position(arm_E, crimp);
    arm_position(arm_F, crimp);
    break;
  case "300deg":
    arm_position(arm_A, crimp);
    arm_position(arm_B, normal);
    arm_position(arm_C, sloper);
    arm_position(arm_D, sloper);
    arm_position(arm_E, normal);
    arm_position(arm_F, crimp);
    break;
  default:
    arm_position(arm_A, normal);
    arm_position(arm_B, normal);
    arm_position(arm_C, normal);
    arm_position(arm_D, normal);
    arm_position(arm_E, normal);
    arm_position(arm_F, normal);
    break;
  }
}