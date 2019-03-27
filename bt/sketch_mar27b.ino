#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

#define txPin 2
#define rxPin 3

char BTName[] = "tobiako";
char ATCommand[] = "AT+NAMEPLab_";

PLabBTSerial btSerial(txPin, rxPin);
void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {

 while(btSerial.available()){
  char c = btSerial.read();
  Serial.write(c);
 }while(Serial.available()){
  char c = Serial.read();
  btSerial.write(c);
 }
  // put your main code here, to run repeatedly:

}
