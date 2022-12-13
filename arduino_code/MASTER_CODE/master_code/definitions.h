//Defintions.h

#ifndef definitions_h
#define definitions_h
#define DEBUG_delay 50

//#define DEBUG
#undef DEBUG
#undef TEST_SWEEP
//#define DUMMY_INPUT

// --Arms Pin Positions on Motor Shield--
#define arm_A_pin 15
#define arm_B_pin 3
#define arm_C_pin 13
#define arm_D_pin 2
#define arm_E_pin 6
#define arm_F_pin 0

// --ML Transmit Pin--
#define ML_PIN A7

enum habDir{
  threeSixty,
  sixty,
  oneTwenty,
  oneEighty,
  twoForty,
  threeHundred,
  defDirection
};

//--Arm States--
#define sloper 60
#define crimp 150
#define normal 100

//--BIG LENGTH -- 
//Defines the resolution of the arm movements
#ifdef DEBUG
  #define L 25
#else if
  #define L 250
#endif
//**this is a tradeoff between motion resolution AND file size (more res, more size)

#define FORWARD 1
#define REVERSE 0

//Motion Parameters
int duration = 1000; //ms
int delayStep = duration/L;

class Arm
{
  public:
    Arm::Arm(int pin, int state);
    int getPin();
    int getState();
    void setState(int state);
    bool getFlag();
    void setFlag(bool flag);
    void position(int endState);
    int getMove(int i);
    void setMove(int val, int i);

  private:
    int _curState;
    int _pinPosition;
    int _moveArray[L];
    bool _moveFlag;
};

Arm::Arm(int pin, int state){
  
  _curState = state;
  _pinPosition = pin;
  _moveFlag = 0;
  for(int i = 0; i < L; i++){
    _moveArray[i] = _curState;
  }
}

int Arm::getPin(){
  return _pinPosition;
}

int Arm::getState(){
  return _curState;
}

void Arm::setState(int state){
  _curState = state;
}

bool Arm::getFlag(){
  return _moveFlag;
}

void Arm::setFlag(bool flag){
  _moveFlag = flag;
};

int Arm::getMove(int i){
  return _moveArray[i];
};


void Arm::setMove(int val, int i){
  _moveArray[i] = val;
}

#endif