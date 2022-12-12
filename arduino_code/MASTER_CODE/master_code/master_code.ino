#include "PCA9685.h"
#include <Wire.h>
#include "definitions.h"

/* Overview of function structure (run this by Abigail)

1. Boot up
2. Safety checks on all components
3. Set up one-time software objects
4. Send analog signals from hall effect sensors to Wekinator
5. Interpret return signal from Wekinator
6. Transition state as needed 

*/

//Arm objects
Arm ArmA(arm_A_pin, defState);
Arm ArmB(arm_B_pin, defState);
Arm ArmC(arm_C_pin, defState);
Arm ArmD(arm_D_pin, defState);
Arm ArmE(arm_E_pin, defState);
Arm ArmF(arm_F_pin, defState);

//ServoDriver object contains all the code to drive the servos
ServoDriver servo;

//State signal from wekinator
int MLstate;

//Other variables
int c; //global incrementor
bool cFlag;
bool dir;

//Interpolate motions between start state and end state over set duration. Pushes interpolated motions to fixed array
void interpolateMotion(Arm *arm, int startDeg, int endDeg) {

  //Determine step size
  float step = (float(endDeg) - float(startDeg)) / (L - 1);

/*
#ifdef DEBUG
  Serial.print("Step size: ");
  Serial.println(step);
#endif
*/

  //Populate array
  for (int i = 0; i < L; i++) {
    arm->setMove(((i * step) + startDeg), i);

/* 
#ifdef DEBUG
    Serial.print("Array entry #");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(arm.getMove(i));
#endif
*/

  }
#ifdef DEBUG
  Serial.println("Set Flag...");
  delay(DEBUG_delay);
#endif
  arm->setFlag(1);
}

//TODO - Function to broadcast analog read pins
void broadcast() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
#ifdef DEBUG
  Serial.println("A1 Value:");
  delay(DEBUG_delay);
#endif
  Serial.println(sensorValue);

  sensorValue = analogRead(A2);
  // print out the value you read:
#ifdef DEBUG
  Serial.println("A2 Value:");
  delay(DEBUG_delay);
#endif
  Serial.println(sensorValue);
}

//TODO - interpret incoming signals
int receive(){
  while(Serial.available() == 0){
  }
  return Serial.parseInt();
}

//TODO - Function to interpret incoming signals from Wekinator
void stateTransition(int state) {
  void;
}

//Conducts a test sweep during big loop function
void testSweep(bool direction) {

int startAngle;
int endAngle;

  if (direction == FORWARD) {
    startAngle = sloper;
    endAngle = crimp;
  } else if (direction == REVERSE) {
    startAngle = crimp;
    endAngle = sloper;
  }

#ifdef DEBUG
  Serial.print(startAngle);
  Serial.print(", ");
  Serial.println(endAngle);
#endif

  //Load Movement Arrays
  interpolateMotion(&ArmA, startAngle, endAngle);
  interpolateMotion(&ArmB, startAngle, endAngle);
  interpolateMotion(&ArmC, startAngle, endAngle);
  interpolateMotion(&ArmD, startAngle, endAngle);
  interpolateMotion(&ArmE, startAngle, endAngle);
  interpolateMotion(&ArmF, startAngle, endAngle);
}

void setup() {

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Serial.begin(9600);
  servo.init(0x7f);
  // uncomment this line if you need to use a special servo
  // servo.setServoPulseRange(600,2400,180);

  //Set up transmit port

  //set up global incrementor
  c = 0;
  dir = FORWARD;

}

void loop() {
#ifdef DEBUG
  Serial.println("--- LOOP START ---");
  delay(DEBUG_delay);
#endif

#ifdef DEBUG
  Serial.println("Broadcast...");
  delay(DEBUG_delay);
#endif

  //broadcast latest analog signals
  broadcast();

  /* TODO
  //receive incoming state signal
  MLstate = receive();
  */

#ifdef DEBUG
  Serial.println("State Transition...");
  delay(DEBUG_delay);
#endif

  //transition between states
  stateTransition(MLstate);

  //TEST SWEEP

#ifdef DEBUG
  Serial.println("Test Sweep...");
#endif
  cFlag = ArmA.getFlag() || ArmB.getFlag() || ArmC.getFlag() || ArmD.getFlag() || ArmE.getFlag() || ArmF.getFlag();
#ifdef DEBUG
  Serial.print("flag: ");
  Serial.println(cFlag);
  delay(DEBUG_delay);
#endif

  if (!cFlag && (dir == FORWARD)) {
#ifdef DEBUG
  Serial.println("TEST SWEEP FORWARD");
  delay(DEBUG_delay);
#endif
    testSweep(FORWARD);
  } else if (!cFlag && (dir == REVERSE)) {
#ifdef DEBUG
  Serial.println("TEST SWEEP REVERSE");
  delay(DEBUG_delay);
#endif
    testSweep(REVERSE);
  }

  //increment all designated arm positions
  if (cFlag) {
#ifdef DEBUG
  Serial.print("Increment: ");
  Serial.println(c);
  delay(DEBUG_delay);
#endif

    if (ArmA.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm A Move");
  Serial.println(ArmA.getMove(c));
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmA.getPin(), ArmA.getMove(c));
    }
    if (ArmB.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm B Move");
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmB.getPin(), ArmB.getMove(c));
    }
    if (ArmC.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm C Move");
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmC.getPin(), ArmC.getMove(c));
    }
    if (ArmD.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm D Move");
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmD.getPin(), ArmD.getMove(c));
    }
    if (ArmE.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm E Move");
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmE.getPin(), ArmE.getMove(c));
    }
    if (ArmF.getFlag()) {
#ifdef DEBUG
  Serial.println("Arm F Move");
  delay(DEBUG_delay);
#endif
      servo.setAngle(ArmF.getPin(), ArmF.getMove(c));
    }

    c++;
    if (c >= L) {
      //set all move flags to FALSE
      ArmA.setFlag(0);
      ArmB.setFlag(0);
      ArmC.setFlag(0);
      ArmD.setFlag(0);
      ArmE.setFlag(0);
      ArmF.setFlag(0);
      
      //reset incrementor
      c = 0;

      //for test sweep
      dir = !dir;
    }
  }
  delay(delayStep);
#ifdef DEBUG
  Serial.println("--- LOOP END ---");
  delay(DEBUG_delay);
#endif
}