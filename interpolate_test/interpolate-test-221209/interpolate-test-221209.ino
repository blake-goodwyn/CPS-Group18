#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

//BIG LENGTH
#define L 250
#define arm_A 16
#define arm_B 15
#define arm_C 14
#define arm_D 13

//Arm Message Queues
int arm_A[L];
bool arm_A_flag;

int arm_B[L];
bool arm_B_flag;

int arm_C[L];
bool arm_C_flag;

int arm_D[L];
bool arm_D_flag;

int arm_E[L];
bool arm_E_flag;

int arm_F[L];
bool arm_F_flag;

//Test parameters
int duration = 1000; //ms
int startAngle = 0;
int endAngle = 180;

bool interpolateMotion(int startDeg, int endDeg, int armQueue[]){

  //Determine step size
  //Serial.println("Step Calc:");
  float step = (float(endDeg) - float(startDeg)) / (L-1);
  //Serial.println(step);
  //delay(10000);

  //populate array
  //Serial.println("Populat Array");
  for (int i = 0; i<L; i++){
    //Serial.println((i*step) + startDeg);
    armQueue[i] = (i*step) + startDeg;
    //Serial.println(armQueue[i]);
    //delay(25);
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
  arm_A_flag = interpolateMotion(startAngle, endAngle, arm_A);
  int i = 0;
  //Serial.print("arm A flag: ");
  //Serial.println(arm_A_flag);
  while(arm_A_flag){
    servo.setAngle(testMotor, arm_A[i]);
    Serial.print("Angle: ");
    Serial.println(arm_A[i]);
    delay(1000/L);
    i++;
    if (i>=L){
      arm_A_flag = 0;
    }
  }

  Serial.print(endAngle);
  Serial.print(", ");
  Serial.println(startAngle);
  arm_A_flag = interpolateMotion(endAngle, startAngle, arm_A);
  i = 0;
  while(arm_A_flag){
    servo.setAngle(testMotor, arm_A[i]);
    Serial.print("Angle: ");
    Serial.println(arm_A[i]);
    delay(1000/L);
    i++;
    if (i>=L){
      arm_A_flag = 0;
    }
  }
}