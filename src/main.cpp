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

Servo ServoControl[3];

//Servo config
SRVconfig conf[3] ={
  {0,false, D6,0,180,0},
  {1,false, D5,0,180,0},
  {2,false, D7,160,0,160}
};     
SRVconfig SRVEnabled[3];   

const int servoRefresh = 20;      // Servo refresh ms

//Photoresistor config
const int prPin = A0;       
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 14;   // Value of Photoresistor action

//Load key
const int loadPin = D3;

int launchStatus = 1;
bool actionDone = false;

bool serviceMode = false;

int SrvCount=3;
int SrvEnabled=0;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  Serial.begin(9600);

  //Load key setup
  pinMode(loadPin, INPUT_PULLUP);

    SRVEnabled[SrvEnabled]=conf[0];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;

    SRVEnabled[SrvEnabled]=conf[1];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;
    SRVEnabled[SrvEnabled]=conf[2];
    SRVEnabled[SrvEnabled].Enabled=true;
    SrvEnabled++;

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
      ServoControl[SRVEnabled[i].Number].write(SRVEnabled[i].CurrentAngle);
      delay(servoRefresh);
  }     
}

