#include <Arduino.h>
// #include <SoftRcPulseOut.h> 
#include <Servo.h>

Servo  servoControl1;
Servo servoControl2;

const int servoPin1 = 5;           // Servo Left
const int servoPin2 = 4;           // Servo Right
const int servo1DefaultAngle = 0;   // Servo Left default angle
const int servo1TargetAngle = 90;     // Servo Left target angle
const int servo2DefaultAngle = 90;    // Servo Right default angle
const int servo2TargetAngle = 0;    // Servo Right target angle
int servo1Angle = 0;
int servo2Angle = 0;
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = A0;       // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 30;   // Value of Photoresistor action

// const int load1 = 7;       // Photoresistor at Arduino analog pin A0
// const int load2 = 8;       // Photoresistor at Arduino analog pin A0

int launchStatus = 1;
bool actionDone = false;

bool inited = false;

// int i = 0;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  // pinMode(load1, OUTPUT);          // Set PhotoResistor pin
  // pinMode(load2, OUTPUT);          // Set PhotoResistor pin
  Serial.begin(9600);
  // Servo setup
  servoControl1.attach(servoPin1);  // Set Servo pin1
  servoControl2.attach(servoPin2);  // Set Servo pin2
  
}

void loop() {
  // i++;
  if(!inited){
    servo1Angle = servo1DefaultAngle;
    servo2Angle = servo2DefaultAngle;
    inited = true;
  }

  prValue = analogRead(prPin); // Read pResistor
  Serial.println(prValue);
  if (prValue < prLaunch){
    if(!actionDone){
      if(launchStatus == 1){
        servo1Angle = servo1TargetAngle;
      }else if(launchStatus == 2){
        servo2Angle = servo2TargetAngle;
      }
      actionDone = true;
    }
  } else {
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
  delay(15); 
  servoControl2.write(servo2Angle);   // tell servo2 to go to position in variable 'servoAngle' 
  delay(15); 
  delay(servoRefresh);                // waits 20ms for for refresh period 
  // SoftRcPulseOut::refresh(1);         // generates the servo pulse
  // delay(200);

  // // if (i>5){
  //   digitalWrite(load1,HIGH);
  //   digitalWrite(load2,HIGH);
  //   delay(100);
  //   digitalWrite(load1,LOW);
  //   digitalWrite(load2,LOW);
  //   i = 0;
  // // }
  
}