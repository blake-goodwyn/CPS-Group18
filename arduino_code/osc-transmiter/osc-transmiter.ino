/*
   arduino-osc-transmitter sketch
   Takes in OSC wekinator output and transmits to main Arduino through auxiliary Arduino.
   written by Blake Goodwyn
   Forked from arduino-osc-blink script by Becky Stewart 2022
*/

// variable used for LED blink pattern
#define OUTPIN 5
#define tDelay 1000
int outVal = 0;
int MLstate = 0;

void setup() {
  Serial.begin(9600);  // initialise the serial communication

  pinMode(LED_BUILTIN, OUTPUT);
  // initialize analog pin as an output.
  pinMode(OUTPIN, OUTPUT);
}

void loop() {
  // wait for a message to arrive
  if (Serial.available()) {
    // save the message when it arrives
    MLstate = Serial.parseInt();
  }

  Serial.println(MLstate);

  switch (MLstate) {
    case 1: //North state
      outVal = 50;
      break;
    case 2: //West State
      outVal = 100;
      break;
    case 3: //South state
      outVal = 150;
      break;
    case 4: //East State
      outVal = 200;
      break;
    default: //no discernable state
      outVal = 0;
      break;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(OUTPIN, outVal);  // turn the LED on (HIGH is the voltage level)
  delay(tDelay/2);                   // wait for the delayed time
  digitalWrite(LED_BUILTIN, LOW);
  delay(tDelay/2);
}