#include <Arduino.h>
// #include <SoftwareServo.h>
// #include <SimpleServo.h>
#include <SoftRcPulseOut.h> 


// SoftwareServo servoControl;    // Define servo control object
// SimpleServo servoControl;
SoftRcPulseOut servoControl;

const int servoPin = 4;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 70;  // Servo target angle
int servoAngle = 0;
const int servoDelay = 500;       // Servo delay time in ms
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = 3;        // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 700;   // Value of Photoresistor action

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  servoControl.attach(servoPin);  // Set Servo pin

  //Servo setup
  servoControl.write(servoDefaultAngle); // Set servo to default position
  delay(500); // Delay after reset (waiting for position)
}

void loop() {
  prValue = analogRead(prPin); // Read pResistor

  if (prValue > prLaunch){
    servoAngle = servoTargetAngle;
  } else {
    servoAngle = servoDefaultAngle;
  }
  
  servoControl.write(servoAngle);    // tell servo to go to position in variable 'pos' 
  delay(servoRefresh);               // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);        // generates the servo pulse
}