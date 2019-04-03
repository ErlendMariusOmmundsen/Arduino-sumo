/*
  ProximitySensor
  
  Dette er et eksempel på hvordan du kan bruke en HC-SR04 ultralyd sensor med biblioteket NewPing for å måle avstand.
  Lengde (i centimeter) måles og skrives ut hver 50 ms.
  
  Kretsen:
    1 x HC-SR04 (ultralyd sensor)
  Oppkobling vises på wiki:
  https://www.ntnu.no/wiki/display/plab/3.+Ultralyd+-+HC-SR04
  
  Bibliotek
    - NewPing (Nedlasting: https://code.google.com/p/arduino-new-ping/downloads/list )
  
  
  This is an example on how you may use a HC-SR04 ultrasonic sensor with the library NewPing to detect distance.
  Distance (in centimetres) is measured and printed every 50 ms.
  
  Circuit
    1 x HC-SR04 (ultrasonic sensor)
  How to connect circuit can be seen here:
  https://www.ntnu.no/wiki/display/plab/3.+Ultralyd+-+HC-SR04
  
  Library
    - NewPing (Download: https://code.google.com/p/arduino-new-ping/downloads/list )
 */
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
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200

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
int angleConverter = 0.72;

const int servoPin = 6;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 


#define NUM_SENSORS 6
 

Pushbutton button(ZUMO_BUTTON); 

int degreesServo = 0;
int degreesStep = 15;

void setup() {
  sensors.init();
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90);
  button.waitForButton(); // start when button pressed
  myServo.write(65);
}

void stepServo() {
   myServo.write(degreesServo);
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
    degreesStep = -degreesStep;
    degreesServo = 180;
   } else if (degreesServo < 0) {
    degreesStep = -degreesStep;
    degreesServo = 0;
  }  
}

float sonarDistance() {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  //Serial.println(distance);
   return distance;
}

void borderCheck(){
   sensors.read(sensor_values);
   if (sensor_values[0] < QTR_THRESHOLD) {
     PLab_motors.backward(300, 10);
     PLab_motors.turnRight(300,155);
   } else if (sensor_values[5] < QTR_THRESHOLD) {
     PLab_motors.backward(300, 8);
     PLab_motors.turnLeft(300,155);
   }
}



void loop() {
   stepServo();
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
    delay(100);
  }
  else{
    motors.setSpeeds(200,200);
  }
  borderCheck();


}
