#include <Arduino.h>
#include <Servo.h>

struct SRVconfig{
  int Number;
  bool Enabled;
  const int Pin;
  const int DefaultAngle;
  const int TargetAngle;
  int CurrentAngle;
};

Servo ServoControl[2];

//Servo config
SRVconfig conf[2] ={
  {0,false, D6,180,0,180},
  {1,false, D5,0,180,0}
};       

const int servoRefresh = 20;      // Servo refresh ms

//Photoresistor config
const int prPin = A0;       
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 22;   // Value of Photoresistor action

//Load key
const int loadPin = D3;

int launchStatus = 1;
bool actionDone = false;

int SrvCount=2;

void moveServo(int i, int angle){
  ServoControl[i].write(angle);
  delay(servoRefresh);
  
}

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  // Serial.begin(9600);

  //Load key setup
  pinMode(loadPin, INPUT_PULLUP);

  // Servo setup
  for (int i=0;i<SrvCount;i++){
     ServoControl[i].attach(conf[i].Pin);
  }

  for (int i=0;i<SrvCount;i++){
    moveServo(i,conf[i].DefaultAngle);
  }

}


void loop() {

  int isLoad = digitalRead(loadPin);

  if (isLoad>0){
    prValue = analogRead(prPin); // Read pResistor
  }else{
    prValue=0;
  }
  if (prValue < prLaunch){
    if(!actionDone){
      conf[launchStatus-1].CurrentAngle = conf[launchStatus-1].TargetAngle;
      actionDone = true;
    }
  } else {
    if(actionDone){
      for(int i=0;i<SrvCount;i++){
        conf[i].CurrentAngle=conf[i].DefaultAngle;
      }
      if (launchStatus==SrvCount){
        launchStatus = 1;
      }else{
        launchStatus++;
      }
    }
    actionDone = false;
  }
  for (int i=0;i<SrvCount;i++){
    moveServo(i,conf[i].CurrentAngle);
  }   
  delay(10);  
}

