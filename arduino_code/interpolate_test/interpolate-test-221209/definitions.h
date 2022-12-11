//Defintions.h

//BIG LENGTH
#define L 250 //this is a tradeoff between motion resolution AND file size

//Arms!
#define arm_A 10
#define arm_B 0
#define arm_C 0
#define arm_D 0
#define arm_E 0
#define arm_F 0

//move flags
bool arm_A_flag;
bool arm_B_flag;
bool arm_C_flag;
bool arm_D_flag;
bool arm_E_flag;
bool arm_F_flag;

//Arm Message Queues
int arm_A_q[L];
int arm_B_q[L];
int arm_C_q[L];
int arm_D_q[L];
int arm_E_q[L];
int arm_F_q[L];

//Test parameters
int duration = 2000; //ms
int startAngle = 79;
int endAngle = 172;
int delayStep = duration/L;