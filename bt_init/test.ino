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

  Serial.print("Setting new name for device to PLab_");
  Serial.println(BTName);

  btSerial.write(ATCommand);
  btSerial.write(BTName);
  btSerial.write(0x0D); btSerial.write(0x0A);
  delay(100);
  // put your main code here, to run repeatedly:

}
