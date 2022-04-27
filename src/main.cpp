#include <Arduino.h>
#include <SoftRcPulseOut.h> 

SoftRcPulseOut servoControl1;
SoftRcPulseOut servoControl2;

#define servoPin1 PB2;           // Servo at Arduino digital
#define servoPin2 PB4;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 70;  // Servo target angle
int servo1Angle = 0;
int servo2Angle = 0;
const int servoDelay = 500;       // Servo delay time in ms
const int servoRefresh = 20;      // Servo refresh ms


#define prPin A2;       // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 700;   // Value of Photoresistor action

int launchStatus = 1;
bool switched = false;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  servoControl1.attach(servoPin1);  // Set Servo pin1
  servoControl2.attach(servoPin2);  // Set Servo pin2

  //Servo setup
  servoControl1.write(servoDefaultAngle); // Set servo to default position
  servoControl2.write(servoDefaultAngle); // Set servo to default position
  delay(500); // Delay after reset (waiting for position)
}

void loop() {
  prValue = analogRead(prPin); // Read pResistor

  if (prValue > prLaunch){
    if(launchStatus == 1){
      servo1Angle = servoTargetAngle;
    }else if(launchStatus == 2){
      servo2Angle = servoTargetAngle;
    }
    if(!switched){
      launchStatus = 2;
      switched = true;
    }
  } else {
    if(servo1Angle != servoDefaultAngle){
      servo1Angle = servoDefaultAngle;
    }
    if(servo2Angle != servoDefaultAngle){
      servo2Angle = servoDefaultAngle;
    }
    if(switched){
      launchStatus = 1;
      switched = false;
    }
  }
  
  servoControl1.write(servo1Angle);   // tell servo1 to go to position in variable 'servoAngle' 
  servoControl2.write(servo2Angle);   // tell servo2 to go to position in variable 'servoAngle' 
  delay(servoRefresh);                // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);         // generates the servo pulse
}