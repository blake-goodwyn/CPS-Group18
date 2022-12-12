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


//Interpolate motions between start state and end state over set duration. Pushes interpolated motions to fixed array
void interpolateMotion(Arm arm, int startDeg, int endDeg) {

  //Determine step size
  float step = (float(endDeg) - float(startDeg)) / (L - 1);

#ifdef DEBUG
  Serial.print("Step size: ");
  Serial.println((i * step) + startDeg);
#endif

  //Populate array
  int arr[L];
  for (int i = 0; i < L; i++) {
    arr[i] = (i * step) + startDeg;
    
#ifdef DEBUG
    Serial.print("Array entry #");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(armArray[i]);
#endif

  }
  
  arm.setMove(&arr);
  arm.setFlag(1);
}

//TODO - Function to broadcast analog read pins
void broadcast() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.println(sensorValue);

  sensorValue = analogRead(A2);
  // print out the value you read:
  Serial.println(sensorValue);
}

//TODO - Function to interpret incoming signals from Wekinator
void stateTransition() {
  void;
}

//Conducts a test sweep during big loop function
void testSweep(bool direction) {

#ifdef DEBUG
  Serial.print(startAngle);
  Serial.print(", ");
  Serial.println(endAngle);
#endif

  if (direction == FORWARD) {
    int startAngle = sloper;
    int endAngle = crimp;
  } else if (direction == REVERSE) {
    int startAngle = crimp;
    int endAngle = sloper;
  }


  //Load Movement Arrays
  interpolateMotion(ArmA, startAngle, endAngle);
  interpolateMotion(ArmB, startAngle, endAngle);
  interpolateMotion(ArmC, startAngle, endAngle);
  interpolateMotion(ArmD, startAngle, endAngle);
  interpolateMotion(ArmE, startAngle, endAngle);
  interpolateMotion(ArmF, startAngle, endAngle);
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
  int c = 0;
  bool dir = FORWARD;
}

void loop() {

  //broadcast latest analog signals
  broadcast();

  //TEST SWEEP

  cFlag = ArmA.getFlag() | ArmB.getFlag() | ArmC.getFlag() | ArmD.getFlag() | ArmE.getFlag() | ArmF.getFlag();

  if (!(cFlag) && (dir == FORWARD)) {
    testSweep(FORWARD);
  } else if (!(cFlag) && (dir == REVERSE)) {
    testSweep(REVERSE);
  }

  //increment all designated arm positions
  if (cFlag) {

    if (ArmA.getFlag()) {
      servo.setAngle(ArmA.getPin(), ArmA.getMove[c]);
    }
    if (ArmB.getFlag()) {
      servo.setAngle(ArmB.getPin(), ArmB.getMove[c]);
    }
    if (ArmC.getFlag()) {
      servo.setAngle(ArmC.getPin(), ArmC.getMove[c]);
    }
    if (ArmA.getFlag()) {
      servo.setAngle(ArmD.getPin(), ArmD.getMove[c]);
    }
    if (ArmA.getFlag()) {
      servo.setAngle(ArmE.getPin(), ArmE.getMove[c]);
    }
    if (ArmA.getFlag()) {
      servo.setAngle(ArmF.getPin(), ArmF.getMove[c]);
    }

    c++;
    if (c >= L) {
      //set all move flags to FALSE
      ArmA.setFlag(0);
      
      //reset incrementor
      c = 0;

      //for test sweep
      dir != dir;
    }
  }
  delay(delayStep);
}