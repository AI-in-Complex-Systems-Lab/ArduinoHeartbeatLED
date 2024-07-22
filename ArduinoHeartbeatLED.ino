#include "SevSeg.h"
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.  


SevSeg sevseg; //Initiate a seven segment controller object
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


//  Variables
int Signal; 
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 510;


void setup() {
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments, 0, 0, 1);
  sevseg.setBrightness(90);


  Serial.begin(115200);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}
void loop() {
  Signal = analogRead(PulseWire);

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  sevseg.setNumber(myBPM, -1);

  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
    Serial.print("♥ BPM: ");                        // Print phrase "BPM: " 
    Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}