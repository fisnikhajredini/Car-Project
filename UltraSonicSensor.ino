#include <SonarSRF08.h>
#include <SonarSRF.h>
#include <SonarSRF02.h>



#define MAIN_08_ADDRESS (0x70)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

SonarSRF08 usFront;
SonarSRF08 usFrontRight;

char unit = 'c';
int usFrontr;
int usFrontRightr;

void setup() {
  Serial.begin(9600);
  usFront.connect(MAIN_08_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER);
  isConnected("SRF08", usFront.getSoft());
  
}

 
 void loop()
 {
  float sensorReading = 0;
  sensorReading = usFront.getRange(unit);
  distance("sensor", sensorReading);
 }

 void distance(String reference, int sensorReading) {
  Serial.print("Distance from " + reference + ": ");
  Serial.print(sensorReading);
  Serial.println(unit);
 }

void isConnected(String reference, int sensorSoft) {
  if (sensorSoft >= 0) {
    Serial.print("Sensor " + reference + "connected (");
    Serial.print(sensorSoft);
    Serial.println(")");
  }
  else {
    Serial.println("Sensor " + reference + " not detected");
  }
}

