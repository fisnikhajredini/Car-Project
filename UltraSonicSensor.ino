#include <SonarSRF08.h>

#define MAIN_08_ADDRESS (0xE6 >> 1)
#define US_08_FRONTRIGHT (0xE4 >> 1)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

SonarSRF08 usFront;
SonarSRF08 usFrontRight;
String reference;
char unit = 'c';
int sensorSoft;

void setup() {
  Serial.begin(9600);
  usFront.connect(MAIN_08_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER);
  usFrontRight.connect(US_08_FRONTRIGHT, GAIN_REGISTER, LOCATION_REGISTER);
  isConnected("SRF08 Front", usFront.getSoft());
  isConnected("SRF08 FrontRight", usFrontRight.getSoft());
  
}
 
void loop() {
  float sensorReading = 0;
  sensorReading = usFront.getRange(unit);
  distance("frontSensor", sensorReading);

  float sensorReadingFR = 0;
  sensorReadingFR = usFrontRight.getRange(unit);
  distance("frontRightSensor", sensorReadingFR);
}

void distance(String reference, int sensorReading) {
  Serial.print("Distance from " + reference + ": ");
  Serial.print(sensorReading);
  Serial.println(unit);
  delay(500);
}

void isConnected(String reference, int sensorSoft) {
  if (sensorSoft >= 0) {
    Serial.print("Sensor " + reference + "detected (");
    Serial.print(sensorSoft);
    Serial.println(")");
  }
  else {
    Serial.println("Sensor " + reference + " not detected");
  }
}
