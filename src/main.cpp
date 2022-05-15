#include <Arduino.h>
// #include <SoftwareServo.h>
// #include <SimpleServo.h>
#include <SoftRcPulseOut.h> 


// SoftwareServo servoControl;    // Define servo control object
// SimpleServo servoControl;
SoftRcPulseOut servoControl;

const int servoPin = 10;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 70;  // Servo target angle
int servoAngle = 0;
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = 22;        // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 100;   // Value of Photoresistor action

bool inited = false;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  //Servo setup
  servoControl.attach(servoPin);  // Set Servo pin
}

void loop() {
  Serial.begin(9600);
  if(!inited){
    servoAngle = servoDefaultAngle;
    inited = true;
  }

  prValue = analogRead(prPin); // Read pResistor
  Serial.println(prValue);
  if (prValue < prLaunch){
      servoAngle = servoTargetAngle;
  } else {
      servoAngle = servoDefaultAngle;
  }
  
  servoControl.write(servoAngle);    // tell servo to go to position in variable 'servoAngle' 
  delay(servoRefresh);               // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);        // generates the servo pulse
}