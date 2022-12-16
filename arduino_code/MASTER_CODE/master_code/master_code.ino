/*  CPS GROUP 18 MASTER MOTION CODE
    Written by Blake Goodwyn, Abigail Hoover, and Richard Alexandre
    This Arduino script facilitates the core functions of the CPS project outcome, ASH, the Adjustable Space Hut.
    Core functions include:
    - Instantiating and managing software objects associated with mechanical arms
    - Encoding state machine model of structure and its transitions
    - Facilitating smoothed movement of mechanical arms per state machine transitions
    - Sending analog signals from Hall Effect sensors to Wekinator machine learning model
    - Decoding Wekinator machine learning model into state transitions
*/

#include "PCA9685.h"
#include <Wire.h>
#include "definitions.h"

/* Overview of function structure

SET_UP
1. Boot up
2. Set up one-time software objects

LOOP
3. Send analog signals from hall effect sensors to Wekinator
4. Interpret return signal from Wekinator
5. Transition to state and facilitate motion as needed 

*/

// --------------------------------------------------------

// -- INITIALIZATION --

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
int cur_MLstate = -1; //current ML state
int new_MLstate = -1; //new ML state

//Other variables
int c;                //global counter
bool cFlag = 0;       //motion flag

int timer1 = millis();
int timer2 = millis();

// --------------------------------------------------------

// FUNCTION DEFINITIONS

//Interpolate motions between start state and end state over set duration. Pushes interpolated motions to fixed array
void interpolateMotion(Arm *arm, int startDeg, int endDeg) {

  //Determine step size
  float step = (float(endDeg) - float(startDeg)) / (L - 1);

  //Populate array
  for (int i = 0; i < L; i++) {
    arm->setMove(((i * step) + startDeg), i);
  }
  #ifdef DEBUG
  Serial.println("Set Flag...");
  delay(DEBUG_delay);
  #endif
  arm->setFlag(1);
}

//Function to set arm position to defined angle
void armPosition(Arm *arm, int endState) {
  if(arm->getState() != endState){
    interpolateMotion(arm, arm->getState(), endState);
  }
}

//Function to broadcast analog read pins
void broadcast() {
  // read the input on analog pin 1:
  int sensorValue = analogRead(A1);
  Serial.print(sensorValue);

  sensorValue = analogRead(A2);
  Serial.print(", ");
  Serial.println(sensorValue);
}

//Function to receive and filter out incoming Wekinator messages
int receive(){
  
  String val;
  timer1 = millis();
  
  while (Serial.available() <= 0){
    
    //buffer statement
    Serial.println("waiting...");

    //timer condition to prevent hang up on broadcast calls
    timer2 = millis();
    if((timer2-timer1)>1000){
      return -1;
    }

  }
  val = Serial.readString(); // read it and store it in val
  
  #ifdef DEBUG
  //print received message
  Serial.print("<receive>: ");
  Serial.println(val);
  #endif
  
  //filter out Wekinator messages
  if(val.substring(0,2) == "RM"){
    
    #ifdef DEBUG
    Serial.println("Pass check");
    #endif

    int state = (val.substring(3)).toInt();

    #ifdef DEBUG
    Serial.println("State Transition!");
    Serial.println(state);
    #endif

    return state;

  }else{

    return -1;

  }
}

//Function to initialize serial contact with Processing script
void establishContact() {
  
  while (Serial.available() <= 0) {
    Serial.println("A");   // send a capital A as generic single-char confirmation
    delay(300);
  }
}

//Function to encode state machine transitions as interpreted by incoming signals from Wekinator
void stateTransition(int state) {
  
  switch(state){
    case 1:
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
  case 2:
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
  case 3:
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
  case 4:
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
  case 5:
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
  case 6: 
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
  case 7:
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
  case 8:
    #ifdef DEBUG
      Serial.println("Case: defDirection");
      delay(DEBUG_delay);
    #endif
      armPosition(&ArmA, crimp);
      armPosition(&ArmB, crimp);
      armPosition(&ArmC, crimp);
      armPosition(&ArmD, crimp);
      armPosition(&ArmE, crimp);
      armPosition(&ArmF, crimp);
      break;
  }
}

// --------------------------------------------------------

// ONE-TIME SETUP

void setup() {

  // spin up I2C bus for motor shield comms.
  Wire.begin();
  
  // spin up serial bus
  Serial.begin(9600);
  
  //initialize servo comms.
  servo.init(0x7f);

  #ifdef DEBUG
  Serial.println("");
  Serial.println("");
  Serial.println("--- SETUP START ---");
  delay(DEBUG_delay);
  #endif

  //move arms from sloper position (initialized) to default positions
  #ifdef DEBUG
  Serial.println("Default Positions");
  delay(DEBUG_delay);
  #endif

  cur_MLstate = 7;
  stateTransition(cur_MLstate);

  //reach out to Processing to establish common Serial connection
  #ifndef DUMMY_INPUT
  establishContact();
  #endif
}

// --------------------------------------------------------

// MASTER LOOP FUNCTION

void loop() {
  
  #ifdef DEBUG
  Serial.println("--- LOOP START ---");
  delay(DEBUG_delay);
  #endif

  #ifdef DEBUG
  Serial.println("Broadcast...");
  delay(DEBUG_delay);
  #endif

  // LOOP STEP 1 - Broadcast latest analog signals
  broadcast();

  // LOOP STEP 2 - Queue up motion if valid transition is provided
  #ifdef DUMMY_INPUT

  // dummy input branch for testing state transitions without machine learning input
  if(cFlag == 0){
    #ifdef DEBUG
    Serial.println("Dummy serial input...");
    delay(DEBUG_delay);
    #endif
    while (Serial.available() == 0){
      void;
    }
    new_MLstate = Serial.parseInt();
    #ifdef DEBUG
    Serial.print("MLstate: ");
    Serial.println(int(new_MLstate));
    #endif
    stateTransition(new_MLstate);
  };
  #else

  // branch for real-time state transitions
  if (cFlag == 0){
    #ifndef TRAIN //if defined, provides no state transitions but outputs signals for training
    new_MLstate = receive();
    if((new_MLstate != -1) && (new_MLstate != cur_MLstate)){
      stateTransition(new_MLstate);
      cur_MLstate = new_MLstate;
      #ifdef DEBUG
      Serial.print("State: ");
      Serial.println(cur_MLstate);
      #endif
    }
    #endif
  }
  #endif

  // LOOP STEP 3 - increment all designated arm positions per loaded motion profiles
  
  // define global motion flag
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
      servo.setAngle(ArmA.getPin(), ArmA.getMove(c)+A_OFFSET);
    }
    if (ArmB.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm B Move: ");
      Serial.println(ArmB.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmB.getPin(), ArmB.getMove(c)+B_OFFSET);
    }
    if (ArmC.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm C Move: ");
      Serial.println(ArmC.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmC.getPin(), ArmC.getMove(c)+C_OFFSET);
    }
    if (ArmD.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm D Move: ");
      Serial.println(ArmD.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmD.getPin(), ArmD.getMove(c)+D_OFFSET);
    }
    if (ArmE.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm E Move: ");
      Serial.println(ArmE.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmE.getPin(), ArmE.getMove(c)+E_OFFSET);
    }
    if (ArmF.getFlag()) {
      #ifdef DEBUG
      Serial.print("Arm F Move: ");
      Serial.println(ArmF.getMove(c));
      delay(DEBUG_delay);
      #endif
      servo.setAngle(ArmF.getPin(), ArmF.getMove(c)+F_OFFSET);
    }

    c++;            //increment global counter
    if (c >= L) {   //if global counter reaches end of arrays

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

      //reset global counter
      c = 0;
    }
  }
  delay(delayStep);
  #ifdef DEBUG
  Serial.println("--- LOOP END ---");
  delay(DEBUG_delay); 
  #endif
}