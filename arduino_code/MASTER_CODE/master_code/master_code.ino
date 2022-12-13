#include "PCA9685.h"
#include <Wire.h>
#include "definitions.h"

/* Overview of function structure (run this by Abigail)

1. Boot up
2. Set up one-time software objects
3. Send analog signals from hall effect sensors to Wekinator
4. Interpret return signal from Wekinator
5. Transition to state as needed 

*/

//Instantiate Arm objects
Arm ArmA(arm_A_pin, sloper);
Arm ArmB(arm_B_pin, sloper);
Arm ArmC(arm_C_pin, sloper);
Arm ArmD(arm_D_pin, sloper);
Arm ArmE(arm_E_pin, sloper);
Arm ArmF(arm_F_pin, sloper);

//ServoDriver object contains all the code to drive the servos
ServoDriver servo;

//State signal from wekinator
char MLstate;

//Other variables
int c;  //global incrementor
bool cFlag = 0;
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

void armPosition(Arm *arm, int endState) {
  if(arm->getState() != endState){
    interpolateMotion(arm, arm->getState(), endState);
  }
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
  Serial.print(sensorValue);

  sensorValue = analogRead(A2);
  // print out the value you read:
  #ifdef DEBUG
  Serial.println("A2 Value:");
  delay(DEBUG_delay);
  #endif
  Serial.print(", ");
  Serial.println(sensorValue);
}

void receive(){
  int val;
  if (Serial.available()) 
  { // If data is available to read,
    val = Serial.parseInt(); // read it and store it in val
  }
  Serial.println(val);
  if(0 < val < 7){
    Serial.println("Blink!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}

//TODO - Function to interpret incoming signals from Wekinator
void stateTransition(char state) {
  
  switch(state){
    case '1':
    #ifdef DEBUG
      Serial.println("Case: threeSixty");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, crimp);
      armPosition(&ArmB, crimp);
      armPosition(&ArmC, normal);
      armPosition(&ArmD, sloper);
      armPosition(&ArmE, sloper);
      armPosition(&ArmF, normal);
      break;
  case '2':
    #ifdef DEBUG
      Serial.println("Case: sixty");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, normal);
      armPosition(&ArmB, crimp);
      armPosition(&ArmC, crimp);
      armPosition(&ArmD, normal);
      armPosition(&ArmE, sloper);
      armPosition(&ArmF, sloper);
      break;
  case '3':
    #ifdef DEBUG
      Serial.println("Case: oneTwenty");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, sloper);
      armPosition(&ArmB, normal);
      armPosition(&ArmC, crimp);
      armPosition(&ArmD, crimp);
      armPosition(&ArmE, normal);
      armPosition(&ArmF, sloper);
      break;
  case '4':
    #ifdef DEBUG
      Serial.println("Case: oneEighty");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, sloper);
      armPosition(&ArmB, sloper);
      armPosition(&ArmC, normal);
      armPosition(&ArmD, crimp);
      armPosition(&ArmE, crimp);
      armPosition(&ArmF, normal);
      break;
  case '5':
    #ifdef DEBUG
      Serial.println("Case: twoForty");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, normal);
      armPosition(&ArmB, sloper);
      armPosition(&ArmC, sloper);
      armPosition(&ArmD, normal);
      armPosition(&ArmE, crimp);
      armPosition(&ArmF, crimp);
      break;
  case '6': 
    #ifdef DEBUG
      Serial.println("Case: threeHundred");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, crimp);
      armPosition(&ArmB, normal);
      armPosition(&ArmC, sloper);
      armPosition(&ArmD, sloper);
      armPosition(&ArmE, normal);
      armPosition(&ArmF, crimp);
      break;
  case '7':
    #ifdef DEBUG
      Serial.println("Case: defDirection");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, normal);
      armPosition(&ArmB, normal);
      armPosition(&ArmC, normal);
      armPosition(&ArmD, normal);
      armPosition(&ArmE, normal);
      armPosition(&ArmF, normal);
      break;
  }

}

void setup() {

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Serial.begin(9600);
  servo.init(0x7f);
  // uncomment this line if you need to use a special servo
  // servo.setServoPulseRange(600,2400,180);
  #ifdef DEBUG
  Serial.println("");
  Serial.println("");
  Serial.println("--- SETUP START ---");
  delay(DEBUG_delay);
  #endif

  //Set up transmit port

  //set up global incrementor
  #ifdef DEBUG
  Serial.println("Default Positions");
  delay(DEBUG_delay);
  #endif
  stateTransition('7');
  establishContact();
  pinMode(LED_BUILTIN, OUTPUT); // Set pin as OUTPUT
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

  //read latest signals
  receive();

  #ifdef DUMMY_INPUT
  //transition between states
  if(cFlag == 0){
    #ifdef DUMMY_INPUT
    Serial.println("Dummy serial input...");
    delay(DEBUG_delay);
    while (Serial.available() == 0){
      void;
    }
    habDir inState;
    MLstate = Serial.parseInt();
    switch(MLstate){
      case 1:
        inState = threeSixty;
        break;
      case 2:
        inState = sixty;
        break;
      case 3:
        inState = oneTwenty;
        break;
      case 4:
        inState = oneEighty;
        break;
      case 5:
        inState = twoForty;
        break;
      case 6:
        inState = threeHundred;
        break;
      case 7:
        inState = defDirection;
        break;
    }
    #endif
    #ifdef DEBUG
    Serial.println("State Transition...");
    delay(DEBUG_delay);
    #endif
    stateTransition(inState);
  };
  #else
  if (Serial.available() > 0) { // If data is available to read,
    MLstate = Serial.read(); // read it and store it in val
    stateTransition(MLstate);
    #ifdef DEBUG
    Serial.println("State transition!");
    #endif
    delay(100);
  } 
  #endif

  //increment all designated arm positions
  cFlag = ArmA.getFlag() || ArmB.getFlag() || ArmC.getFlag() || ArmD.getFlag() || ArmE.getFlag() || ArmF.getFlag();
  if (cFlag) {
    #ifdef DEBUG
    Serial.print("Increment: ");
    Serial.println(c);
    delay(DEBUG_delay);
    #endif

    if (ArmA.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm A Move: ");
      Serial.println(ArmA.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmA.getPin(), ArmA.getMove(c));
    }
    if (ArmB.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm B Move: ");
      Serial.println(ArmB.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmB.getPin(), ArmB.getMove(c));
    }
    if (ArmC.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm C Move: ");
      Serial.println(ArmC.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmC.getPin(), ArmC.getMove(c));
    }
    if (ArmD.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm D Move: ");
      Serial.println(ArmD.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmD.getPin(), ArmD.getMove(c));
    }
    if (ArmE.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm E Move: ");
      Serial.println(ArmE.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmE.getPin(), ArmE.getMove(c));
    }
    if (ArmF.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm F Move: ");
      Serial.println(ArmF.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmF.getPin(), ArmF.getMove(c));
    }

    c++;
    if (c >= L) {

      
      #ifdef DEBUG
      Serial.println("// End of Movement //");
      delay(DEBUG_delay);
      #endif

      //store current state in Arm objects
      ArmA.setState(ArmA.getMove(c-1));
      ArmB.setState(ArmB.getMove(c-1));
      ArmC.setState(ArmC.getMove(c-1));
      ArmD.setState(ArmD.getMove(c-1));
      ArmE.setState(ArmE.getMove(c-1));
      ArmF.setState(ArmF.getMove(c-1));

      //set all move flags to FALSE
      ArmA.setFlag(0);
      ArmB.setFlag(0);
      ArmC.setFlag(0);
      ArmD.setFlag(0);
      ArmE.setFlag(0);
      ArmF.setFlag(0);

      //reset incrementor
      c = 0;
    }
  }
  delay(delayStep);
  #ifdef DEBUG
  Serial.println("--- LOOP END ---");
  delay(DEBUG_delay); 
  #endif
}