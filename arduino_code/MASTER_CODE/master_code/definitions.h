/*  DEFINITIONS.h
    This is a header file containing relevant constants and definitions for operation of the master_code.ino script
*/

#ifndef definitions_h
#define definitions_h
#define DEBUG_delay 50

//DEBUGGING DEFINITIONS
//#define DEBUG
#undef DEBUG

#undef TEST_SWEEP       //test sweep tag
//#define DUMMY_INPUT   //dummy input tag
//#define TRAIN

// BIG LENGTH 
// Defines the resolution of the arm movements
#ifdef DEBUG
  #define L 15
#else if
  #define L 50
#endif
//**this is a tradeoff between motion resolution AND file size (more res, more size)

//Motion Parameters
int duration = 500; //ms
int delayStep = duration/L;

// Arms Pin Positions on Motor Shield
#define arm_A_pin 2
#define arm_B_pin 16
#define arm_C_pin 9
#define arm_D_pin 12
#define arm_E_pin 5
#define arm_F_pin 4

// Arm States
#define sloper 90
#define crimp 200
#define normal 150

// Arm Position Trimming
#define A_OFFSET -10
#define B_OFFSET 0
#define C_OFFSET 0
#define D_OFFSET 0
#define E_OFFSET 35
#define F_OFFSET -10

//Class definition for mechanical arm object
class Arm
{
  public:
    Arm::Arm(int pin, int state);
    int getState();
    void setState(int state);
    int getPin();
    int getMove(int i);
    void setMove(int val, int i);
    bool getFlag();
    void setFlag(bool flag);

  private:
    int _curState;
    int _pinPosition;
    int _moveArray[L];
    bool _moveFlag;
};

//Object instantiation function
Arm::Arm(int pin, int state){
  
  _curState = state;
  _pinPosition = pin;
  _moveFlag = 0;
  for(int i = 0; i < L; i++){
    _moveArray[i] = _curState;
  }

}

//getter function for Arm pin position on motor shield
int Arm::getPin(){
  return _pinPosition;
}

//getter function for current stored Arm position
int Arm::getState(){
  return _curState;
}

//setter function for current stored Arm position
void Arm::setState(int state){
  _curState = state;
}

//getter function for motion flag
bool Arm::getFlag(){
  return _moveFlag;
}

//setter function for motion flag
void Arm::setFlag(bool flag){
  _moveFlag = flag;
};

//getter function for element of motion array
int Arm::getMove(int i){
  return _moveArray[i];
};

//setter function for element of motion array
void Arm::setMove(int val, int i){
  _moveArray[i] = val;
}

#endif
