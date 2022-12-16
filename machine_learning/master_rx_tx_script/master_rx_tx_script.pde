import controlP5.*;
import java.util.*;
import oscP5.*;
import netP5.*;
import processing.serial.*; //import the Serial library

Serial myPort;  //the Serial port object
String serVal;
boolean gettingData = false;
int numFeatures = 0;
String featureString = "";

int timer1;
int timer2;

//Objects for sending OSC
OscP5 oscP5;
NetAddress dest;

//message queue
ArrayList<Integer> outMessages = new ArrayList<Integer>();

// since we're doing serial handshaking, 
// we need to check if we've heard from the microcontroller
boolean firstContact = false;
int arduinoMessage = -1;

void setup() {
  size(200, 200);
  
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('\n');
  
  timer1 = millis();
  timer2 = millis();
  
  //Set up OSC:
  oscP5 = new OscP5(this, 12000); //This port isn't important (we're not receiving OSC)
  dest = new NetAddress("127.0.0.1",6448); //Send to port 6448
}

void draw() {
  //we can leave the draw method empty, 
  //because all our programming happens in the serialEvent (see below)
}

void sendFeatures(String[] s) {
  OscMessage msg = new OscMessage("/wek/inputs");
  StringBuilder sb = new StringBuilder();
  try {
    for (int i = 0; i < s.length; i++) {
      float f = Float.parseFloat(s[i]); 
      msg.add(f);
      sb.append(String.format("%.2f", f)).append(" ");
    }
    oscP5.send(msg, dest);
    featureString = sb.toString();
    //println("Feature string:", featureString);
  } catch (Exception ex) {
     println("Encountered exception parsing string: " + ex); 
  }
}

void serialEvent( Serial myPort) {
  
  //put the incoming data into a String - 
  //the '\n' is our end delimiter indicating the end of a complete packet
  serVal = myPort.readStringUntil('\n');
  
  //make sure our data isn't empty before continuing
  if (serVal != null) {
    //trim whitespace and formatting characters (like carriage return)
    serVal = trim(serVal);
    if (serVal != "0\n"){
      String[] a = split(serVal, ',');  //a new array (called 'a') that stores values into separate cells (separated by commas specified in your Arduino program)
      numFeatures = a.length;
      if(numFeatures > 1){
        sendFeatures(a);
      }
    }

  //look for our 'A' string to start the handshake
  //if it's there, clear the buffer, and send a request for data
  if (firstContact == false) {
    if (serVal.equals("A")) {
      myPort.clear();
      firstContact = true;
      myPort.write("A");
      println("contact");
    }
  }
  else { //if we've already established contact, keep getting and parsing data
    println(serVal);

    }
  }
}

void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */

  if (theOscMessage.checkAddrPattern("/wek/outputs")==true) {
    /* check if the typetag is the right one. */
    if (theOscMessage.checkTypetag("f")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      float firstValue = theOscMessage.get(0).floatValue();
      //print("### received an osc message /test with typetag f.");
      //println(" values: "+firstValue);

      

      updateArduino((int)firstValue);
      delay(25);
      return;
    }
  }
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
}

// send a new message to the Arduino
void updateArduino(int newMessage) {
  // check that the message is different from the last one sent
  // if so then update the message
  if (arduinoMessage != newMessage){
    arduinoMessage = newMessage;
    // print for debugging convenience
    
    timer2 = millis();
    //println("Timer2: ", timer2);
    if ((timer2 - timer1) > 1000){
      String outStr = "RM:" + str(arduinoMessage) + "\n";
      println("Sending the following to Arduino:", outStr);
      // send the message to the Arduino
      myPort.write(outStr);
      timer1 = millis();
      timer2 = timer1;
    }
  }
}
