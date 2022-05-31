#include <Arduino.h>
#include <Servo.h>

struct SRVconfig{
  int Number;
  bool Enabled;
  int Pin;
  int DefaultAngle;
  int TargetAngle;
  int CurrentAngle;
};

Servo ServoControl[5];

//Servo config
SRVconfig conf[5] ={
  {0,false, D5,0,180,0},
  {1,false, D6,0,180,0},
  {2,false, D7,160,0,160},
  {3,false, D2,160,0,160},
  {4,false, D4,0,180,0}
};     
SRVconfig SRVEnabled[5];   

const int servoRefresh = 20;      // Servo refresh ms

//Photoresistor config
const int prPin = A0;       
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 30;   // Value of Photoresistor action

//Load key
const int loadPin = D3;

//Config pins
int K[3] = {D0,D8,D1};

int launchStatus = 1;
bool actionDone = false;

bool serviceMode = false;

int SrvCount=5;
int SrvEnabled=0;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  Serial.begin(9600);

  //Load key setup
  pinMode(loadPin, INPUT_PULLUP);

  // Config switcher 
  for (int i=0;i<3;i++){
    pinMode(K[i],INPUT_PULLUP);
  }

  int K1Value = digitalRead(K[0]);
  int K2Value = digitalRead(K[1]);
  int K3Value = digitalRead(K[2]);


  if (K1Value==0){
    SRVEnabled[SrvEnabled]=conf[0];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
  }
  if (K2Value==0){
    SRVEnabled[SrvEnabled]=conf[1];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
    SRVEnabled[SrvEnabled]=conf[2];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
  }
  if (K3Value==0){
    SRVEnabled[SrvEnabled]=conf[3];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
    SRVEnabled[SrvEnabled]=conf[4];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
  }

  // Servo setup
  for (int i=0;i<SrvCount;i++){
    // if (conf[i].Enabled){
      ServoControl[i].attach(conf[i].Pin);
    // }
  }
  for (int i=0;i<SrvCount;i++){
      ServoControl[i].write(conf[i].DefaultAngle);
      delay(servoRefresh); 
  }
}

void loop() {
  int isLoad = digitalRead(loadPin);
  if (isLoad>0){
    prValue = analogRead(prPin); // Read pResistor
  }else{
    prValue=0;
  }

  // Serial.println(prValue);
  if (prValue < prLaunch){
    if(!actionDone){
      Serial.println(launchStatus);
      SRVEnabled[launchStatus-1].CurrentAngle = SRVEnabled[launchStatus-1].TargetAngle;
      actionDone = true;
    }
  } else {
    if(actionDone){
      for(int i=0;i<SrvEnabled;i++){
        SRVEnabled[i].CurrentAngle=SRVEnabled[i].DefaultAngle;
      }
      if (launchStatus==SrvEnabled){
        launchStatus = 1;
      }else{
        launchStatus++;
      }
    }
    actionDone = false;
  }
  
  for (int i=0;i<SrvEnabled;i++){
    // if (SRVEnabled[i].Enabled){
      ServoControl[SRVEnabled[i].Number].write(SRVEnabled[i].CurrentAngle);
      delay(servoRefresh);
    // }
  }     
}

