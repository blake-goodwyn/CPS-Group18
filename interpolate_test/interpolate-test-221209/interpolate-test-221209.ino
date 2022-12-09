#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

//BIG LENGTH
#define L 250 //this is a tradeoff between motion resolution AND file size

//Arms!
#define arm_A 16
#define arm_B 14
#define arm_C 13
#define arm_D 11
#define arm_E 0
#define arm_F 0

//Arm Message Queues
int arm_A_q[L];
bool arm_A_flag;

int arm_B_q[L];
bool arm_B_flag;

int arm_C_q[L];
bool arm_C_flag;

int arm_D_q[L];
bool arm_D_flag;

int arm_E_q[L];
bool arm_E_flag;

int arm_F_q[L];
bool arm_F_flag;

//Test parameters
int duration = 3000; //ms
int startAngle = 0;
int endAngle = 180;
int delayStep = duration/L;

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

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Serial.begin(9600);
    servo.init(0x7f);
    // uncomment this line if you need to use a special servo
    // servo.setServoPulseRange(600,2400,180);
}

void loop(){

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