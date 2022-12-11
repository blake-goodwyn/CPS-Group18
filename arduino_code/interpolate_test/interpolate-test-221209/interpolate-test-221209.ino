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

ServoDriver servo;

//Interpolate motions between start state and end state over set duration. Pushes interpolated motions to fixed array
bool interpolateMotion(int startDeg, int endDeg, int armQueue[]){

  //Determine step size
  float step = (float(endDeg) - float(startDeg)) / (L-1);

  //Populate array
  for (int i = 0; i<L; i++){
    //Serial.println((i*step) + startDeg);
    armQueue[i] = (i*step) + startDeg;
    //Serial.println(armQueue[i]);
  }

  return 1;
}

//TODO - Function to broadcast analog read pins
void broadcast(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.println(sensorValue);

  sensorValue = analogRead(A2);
  // print out the value you read:
  Serial.println(sensorValue);
}

//TODO - Function to interpret incoming signals from Wekinator
void stateTransition(){
  void;
}

void testSweep(){
  
  Serial.print(startAngle);
  Serial.print(", ");
  Serial.println(endAngle);
  arm_A_flag = interpolateMotion(startAngle, endAngle, arm_A_q);
  arm_B_flag = interpolateMotion(startAngle, endAngle, arm_B_q);
  arm_C_flag = interpolateMotion(startAngle, endAngle, arm_C_q);
  arm_D_flag = interpolateMotion(startAngle, endAngle, arm_D_q);
  int i = 0;
  //Serial.print("arm A flag: ");
  //Serial.println(arm_A_flag);
  while(arm_A_flag | arm_B_flag | arm_C_flag | arm_D_flag){
    
    if(arm_A_flag){
      servo.setAngle(arm_A, arm_A_q[i]);
      //Serial.print("Angle: ");
      //Serial.println(arm_A_q[i]);
    }
    if(arm_B_flag){
      servo.setAngle(arm_B, arm_B_q[i]);
    }
    
    if(arm_C_flag){
      servo.setAngle(arm_C, arm_C_q[i]);
    }
    
    if(arm_D_flag){
      servo.setAngle(arm_D, arm_D_q[i]);
    }

    delay(delayStep);
    i++;
    if (i>=L){
      arm_A_flag = 0;
      arm_B_flag = 0;
      arm_C_flag = 0;
      arm_D_flag = 0;
    }
  }

  Serial.print(endAngle);
  Serial.print(", ");
  Serial.println(startAngle);
  arm_A_flag = interpolateMotion(endAngle, startAngle, arm_A_q);
  arm_B_flag = interpolateMotion(endAngle, startAngle, arm_B_q);
  arm_C_flag = interpolateMotion(endAngle, startAngle, arm_C_q);
  arm_D_flag = interpolateMotion(endAngle, startAngle, arm_D_q);
  i = 0;
  while(arm_A_flag | arm_B_flag | arm_C_flag | arm_D_flag){
    
    if(arm_A_flag){
      servo.setAngle(arm_A, arm_A_q[i]);
      //Serial.print("Angle: ");
      //Serial.println(arm_A_q[i]);
    }
    if(arm_B_flag){
      servo.setAngle(arm_B, arm_B_q[i]);
    }
    
    if(arm_C_flag){
      servo.setAngle(arm_C, arm_C_q[i]);
    }
    
    if(arm_D_flag){
      servo.setAngle(arm_D, arm_D_q[i]);
    }

    delay(delayStep);
    i++;
    if (i>=L){
      arm_A_flag = 0;
      arm_B_flag = 0;
      arm_C_flag = 0;
      arm_D_flag = 0;
    }
  }
}

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Serial.begin(9600);
    servo.init(0x7f);
    // uncomment this line if you need to use a special servo
    // servo.setServoPulseRange(600,2400,180);

    //Set up transmit port

}

void loop(){

  //broadcast latest analog signals
  broadcast();

  testSweep();
  
}