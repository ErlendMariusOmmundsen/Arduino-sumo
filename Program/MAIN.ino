#include <NewPing.h>
#include <NewServo.h>
#include <ZumoMotors.h>
#include <PLab_ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

 
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1800 // 

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

ZumoMotors motors;
PLab_ZumoMotors PLab_motors;


const int ledPin=A4;

const int echoPin = A1;
const int triggerPin = A0;
const int maxDistance = 50;
int change = 0;
int program = 0;
int angleConverter = 0.72;

const int servoPin = 6;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 


#define NUM_SENSORS 6
 

Pushbutton button(ZUMO_BUTTON); 

int degreesServo = 0;
int degreesStepSnD = 15;
int degreesStepTor = 15;



void setup() {
  sensors.init();
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90);
  button.waitForButton(); // start when button pressed
  myServo.write(65);
}

void stepServoSnD() {
   myServo.write(degreesServo);
   degreesServo = degreesServo + degreesStepSnD;
   if (degreesServo > 180) {
    degreesStepSnD = -degreesStepSnD;
    degreesServo = 180;
   } else if (degreesServo < 0) {
    degreesStepSnD = -degreesStepSnD;
    degreesServo = 0;
  }  
}

void stepServoTor() {
   degreesServo = degreesServo + degreesStepTor;
   myServo.write(65);
}

float sonarDistance() {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  //Serial.println(distance);
   return distance;
}


void borderCheckSnD(){
   sensors.read(sensor_values);
   if (sensor_values[0] < QTR_THRESHOLD) {
     PLab_motors.backward(300, 10);
     PLab_motors.turnRight(300,155);
   } else if (sensor_values[5] < QTR_THRESHOLD) {
     PLab_motors.backward(300, 8);
     PLab_motors.turnLeft(300,155);
   }
}

void borderCheckTor(){
   sensors.read(sensor_values);
   if (sensor_values[0] < QTR_THRESHOLD) {
     PLab_motors.backward(400, 20);
   } else if (sensor_values[5] < QTR_THRESHOLD) {
     PLab_motors.backward(400, 20);
   }
}





void loop() {

  if(program == 1){
   int distance = sonarDistance();
   Serial.println(distance);
   if(distance == 0){
    stepServoTor();
    
    //PLab_motors.turnLeft(400, 45);
    if(change == 0){
      motors.setSpeeds(300, -300);
    }
    else{
      motors.setSpeeds(-300, 300);
    }
   }
   else{
      motors.setSpeeds(400, 400);
      if(change == 0){
        change++;
      }
      else if(change == 1){
        change--;
      }
   }
   
   borderCheckTor();
    
  }

  else{
    stepServoSnD();
    int distance = sonarDistance();
    Serial.println(degreesServo);
   
    if(distance != 0){
    if(degreesServo < 90 && degreesServo > 0){
      PLab_motors.turnRight(400,90 - degreesServo);
    }
    else if(degreesServo > 90 && degreesServo < 180){
      PLab_motors.turnLeft(400,(degreesServo - 90));
    }
    degreesServo = 65;
    motors.setSpeeds(400,400);
    delay(50);
    }
    else{
      motors.setSpeeds(200,200);
    }
    borderCheckSnD();
    }















  

}
