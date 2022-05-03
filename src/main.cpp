#include <Arduino.h>
#include <SoftRcPulseOut.h> 

SoftRcPulseOut servoControl1;
SoftRcPulseOut servoControl2;

const int servoPin1 = PB2;           // Servo Left
const int servoPin2 = PB4;           // Servo Right
const int servo1DefaultAngle = 70;   // Servo Left default angle
const int servo1TargetAngle = 0;     // Servo Left target angle
const int servo2DefaultAngle = 0;    // Servo Right default angle
const int servo2TargetAngle = 70;    // Servo Right target angle
int servo1Angle = 0;
int servo2Angle = 0;
const int servoDelay = 500;       // Servo delay time in ms
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = A3;       // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 300;   // Value of Photoresistor action

int launchStatus = 1;
bool actionDone = false;

void setup() {
  // Photoresistor setup
  // pinMode(0, OUTPUT);
  // pinMode(1, OUTPUT);

  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  servoControl1.attach(servoPin1);  // Set Servo pin1
  servoControl2.attach(servoPin2);  // Set Servo pin2

  //Servo setup
  servoControl1.write(-70); // Set servo to default position
  servoControl2.write(70); // Set servo to default position
  delay(500); // Delay after reset (waiting for position)
}

void loop() {
  prValue = analogRead(prPin); // Read pResistor

  if (prValue < prLaunch){
    // digitalWrite(0, HIGH);
    // digitalWrite(1, HIGH);

    if(!actionDone){
      if(launchStatus == 1){
        servo1Angle = servo1TargetAngle;
      }else if(launchStatus == 2){
        servo2Angle = servo2TargetAngle;
      }
      actionDone = true;
    }
  } else {
    // digitalWrite(0, LOW);
    // digitalWrite(1, LOW);

    if(actionDone){
      servo1Angle = servo1DefaultAngle;
      servo2Angle = servo2DefaultAngle;

      if(launchStatus == 1){
        launchStatus = 2;
      }else if(launchStatus == 2){
        launchStatus = 1;
      }
    }
    
    actionDone = false;
  }
  
  servoControl1.write(servo1Angle);   // tell servo1 to go to position in variable 'servoAngle' 
  servoControl2.write(servo2Angle);   // tell servo2 to go to position in variable 'servoAngle' 
  delay(servoRefresh);                // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);         // generates the servo pulse
}