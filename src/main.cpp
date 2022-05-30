#include <Arduino.h>
#include <Servo.h>

Servo servoControl1;
Servo servoControl2;
Servo servoControl3;
Servo servoControl4;
Servo servoControl5;

//Servo config
const int servoPin1 = D5;  
const int servo1DefaultAngle = 0;   
const int servo1TargetAngle = 180;          
const int servoPin2 = D6;
const int servo2DefaultAngle = 0;   
const int servo2TargetAngle = 180;
const int servoPin3 = D7;
const int servo3DefaultAngle = 160;   
const int servo3TargetAngle = 0;
const int servoPin4 = D2;
const int servo4DefaultAngle = 160;   
const int servo4TargetAngle = 0;
const int servoPin5 = D4;
const int servo5DefaultAngle = 0;   
const int servo5TargetAngle = 180;


int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;
const int servoRefresh = 20;      // Servo refresh ms

//Photoresistor config
const int prPin = A0;       
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 30;   // Value of Photoresistor action

//Load key
const int loadPin = D3;

//Config pins
const int K1 = TX;
const int K2 = RX;
const int K3 = D1;

int launchStatus = 1;
bool actionDone = false;

bool inited = false;

bool serviceMode = false;

void servoOpen(){
    servoControl1.write(servo1TargetAngle);   
    delay(servoRefresh); 
    servoControl2.write(servo2TargetAngle);  
    delay(servoRefresh);       
    servoControl3.write(servo3TargetAngle);  
    delay(servoRefresh);  
    servoControl4.write(servo4TargetAngle);  
    delay(servoRefresh);  
    servoControl5.write(servo5TargetAngle);  
    delay(servoRefresh);
}

void servoClose(){
    servoControl1.write(servo1DefaultAngle);   
    delay(servoRefresh); 
    servoControl2.write(servo2DefaultAngle);  
    delay(servoRefresh);       
    servoControl3.write(servo3DefaultAngle);  
    delay(servoRefresh);  
    servoControl4.write(servo4DefaultAngle);  
    delay(servoRefresh);  
    servoControl5.write(servo5DefaultAngle);  
    delay(servoRefresh);
}

void servoSetup(){
  // Servo setup
  servoControl1.attach(servoPin1);
  servoControl2.attach(servoPin2); 
  servoControl3.attach(servoPin3); 
  servoControl4.attach(servoPin4); 
  servoControl5.attach(servoPin5); 
  if(!inited){
    servoClose();
    inited = true;
  }
}

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  Serial.begin(9600);

  //Load key setup
  pinMode(loadPin, INPUT_PULLUP);

  //Config switcher 
  pinMode(K1,INPUT_PULLUP);
  pinMode(K2,INPUT_PULLUP);
  pinMode(K3,INPUT_PULLUP);

  // Servo setup
  servoSetup();

}

void loop() {

  int isLoad = digitalRead(loadPin);
  if (isLoad>0){
    prValue = analogRead(prPin); // Read pResistor
  }else{
    prValue=0;
  }

  int K1Value = digitalRead(K1);
  int K2Value = digitalRead(K2);
  int K3Value = digitalRead(K3);
  
  // Serial.println(prValue);
  if (prValue < prLaunch){
    if(!actionDone){
      if(launchStatus == 1){
        servo1Angle = servo1TargetAngle;
      }else if(launchStatus == 2){
        servo2Angle = servo2TargetAngle;
      }else if(launchStatus == 3){
        servo3Angle = servo3TargetAngle;
      }else if(launchStatus == 4){
        servo4Angle = servo4TargetAngle;
      }else if(launchStatus == 5){
        servo5Angle = servo5TargetAngle;
      }
      actionDone = true;
    }
  } else {
    if(actionDone){
      servo1Angle = servo1DefaultAngle;
      servo2Angle = servo2DefaultAngle;
      servo3Angle = servo3DefaultAngle;
      servo4Angle = servo4DefaultAngle;
      servo5Angle = servo5DefaultAngle;

      if(launchStatus == 1){
        launchStatus = 2;
      }else if(launchStatus == 2){
        launchStatus = 3;
      }else if(launchStatus == 3){
        launchStatus = 4;
      }else if(launchStatus == 4){
        launchStatus = 5;
      }else if(launchStatus == 5){
        launchStatus = 1;
      }
    }
    
    actionDone = false;
  }
  
  servoControl1.write(servo1Angle);   
  delay(servoRefresh); 
  servoControl2.write(servo2Angle);  
  delay(servoRefresh);       
  servoControl3.write(servo3Angle);  
  delay(servoRefresh);  
  servoControl4.write(servo4Angle);  
  delay(servoRefresh);  
  servoControl5.write(servo5Angle);  
  delay(servoRefresh);   
       
}

