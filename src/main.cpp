#include <Arduino.h>
// #include <SoftwareServo.h>
#include <SimpleServo.h>

// SoftwareServo servoControl;       // Define servo control object
SimpleServo servoControl;
const int servoPin = 4;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 120; // Servo target angle
const int servoDelay = 500;       // Servo delay time in ms

const int prPin = 5;        // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 800;   // Value of Photoresistor action

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  servoControl.attach(servoPin);  // Set Servo pin

  //Servo setup
  // delay(500); // Delay before reset
  servoControl.write(servoDefaultAngle); // Set servo to default position
  delay(500); // Delay after reset (waiting for position)
}

void loop() {
  prValue = analogRead(prPin); // Read pResistor

  if (prValue < prLaunch){
      servoControl.write(servoTargetAngle);
      delay(servoDelay);
  } else {
      servoControl.write(servoDefaultAngle);
      delay(servoDelay);
  }

  delay(1); // Idle
}