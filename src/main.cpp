#include <Arduino.h>
// #include <SoftwareServo.h>
// #include <SimpleServo.h>
#include <SoftRcPulseOut.h> 


// SoftwareServo servoControl;       // Define servo control object
// SimpleServo servoControl;
SoftRcPulseOut servoControl;

const int servoPin = 4;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 90; // Servo target angle
int servoAngle = 0;
int servoTmpAngle = 0;
const int servoDelay = 500;       // Servo delay time in ms
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = 5;        // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 700;   // Value of Photoresistor action

void setup() {
  pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);

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
    
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    if(servoAngle != servoTargetAngle){
      for(servoTmpAngle = 0; servoTmpAngle < servoTargetAngle; servoTmpAngle += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
          servoControl.write(servoTmpAngle);              // tell servo to go to position in variable 'pos' 
          delay(servoRefresh);        // waits 20ms for refresh period 
          SoftRcPulseOut::refresh(1);        // generates the servo pulse
      } 
    }
    servoAngle = servoTargetAngle;
  } else {
    
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    if(servoAngle != servoDefaultAngle){
      for(servoTmpAngle = servoTargetAngle; servoTmpAngle>=1; servoTmpAngle-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        servoControl.write(servoTmpAngle);              // tell servo to go to position in variable 'pos' 
        delay(servoRefresh);        // waits 20ms for for refresh period 
        SoftRcPulseOut::refresh(1);        // generates the servo pulse
      }
    }
    servoAngle = servoDefaultAngle;
  }
  

  // if(prValue > prLaunch){
  //   prValue = 0;
  // }else{
  //   prValue = 1000;
  // }
  // delay(5000);
    servoControl.write(servoAngle);              // tell servo to go to position in variable 'pos' 
    delay(servoRefresh);        // waits 20ms for for refresh period 
    SoftRcPulseOut::refresh(1);        // generates the servo pulse
  // servoControl.write(servoAngle);
  // if(servoAngle != servoTmpAngle){
  //   delay(servoDelay);
  // }
  // servoTmpAngle = servoAngle;

  // delay(1); // Idle
}