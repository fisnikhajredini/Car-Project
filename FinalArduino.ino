#include <Servo.h>
#include <SonarSRF08.h>

#define MAIN_08_ADDRESS (0xE6 >> 1)
#define US_08_FRONTRIGHT (0xE4 >> 1)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

Servo steerServo; 
Servo driveServo;
SonarSRF08 USC;
SonarSRF08 USR;

String inputString;

char inByte;

int IRFR = A5;
int IRRR = A4;
int IRRC = A3;
int zero = 0;
int rcPin1 = 2;
int rcPin2 = 3;
int drive = 1500; 
int steer = 90;

float sensorReading = 0;
float analogReading = 0;

volatile int rcInteruppt = LOW;

void setup() {
  
  //Attach Servos to right pins.
  driveServo.attach(6);
  steerServo.attach(5);
 
  //Initialize Serial-Communication
  Serial.begin(57600);

  driveServo.writeMicroseconds(drive);
  steerServo.write(steer);

  USC.connect(MAIN_08_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER);
  USR.connect(US_08_FRONTRIGHT, GAIN_REGISTER, LOCATION_REGISTER);

  pinMode(rcPin1,INPUT);
  pinMode(rcPin2,INPUT);
  attachInterrupt(digitalPinToInterrupt(rcPin2),change,RISING);
  
}

void loop() {
  //Interuppt when the controller turns on.
  if(rcInteruppt == HIGH) {
    drive = 1500;
    steer = 90;
    driveServo.writeMicroseconds(drive);
    steerServo.write(steer);
    zero++;
    if(zero >= 10) {
      rcInteruppt = LOW;
      zero = 0;
    }
  }
  else {
  //This is where the arduino will send sensor data to the proxy

   
    sensorReading = USC.getRange();
    distance("USC", sensorReading);

    sensorReading = USR.getRange();
    distance("USR", sensorReading);

    analogReading = analogRead(IRFR);
    irDistance("IRFR", analogReading);

    analogReading = analogRead(IRRR);
    irDistance("IRRR", analogReading);

    analogReading = analogRead(IRRC);
    irDistance("IRRC", analogReading);
    Serial.print(",");
  
  //This is where the arduino will recieve messages from the proxy.
  
  //Checking all the Serial that is recieved and will start if the Serial is greater than 0.
   while(Serial.available() > 0) {
      
      inByte = Serial.read();

      inputString +=inByte;
      
      int indexOne = inputString.indexOf("=");
      int indexTwo = inputString.indexOf("=", indexOne + 1);
      int indexThree = inputString.indexOf(";");
      int indexFour = inputString.indexOf(";", indexThree + 1);

      if(inputString.substring(0, indexOne) == "speed" && inputString.substring(indexThree +1, indexTwo) == "angle") {
        drive = inputString.substring(indexOne + 1, indexThree).toInt();
        steer = inputString.substring(indexTwo +1, indexFour).toInt();
        Serial.flush();
      }
      
      
   }  
    //Will only execute if the while loop above is made since otherwise the inputString length will be lesser than 0.
    //Need to test with only inputString.length running both driving and steering commands.
    if(inputString.length() >1 ) {
      
      driveServo.writeMicroseconds(drive);

      steerServo.write(steer);
    }
    
    //Will only execute if the while loop above is made since otherwise the inputString length will be lesser than 0.
    //Need to test with only inputString.length running both driving and steering commands.
   
  }
  //Restoring the original value to inputString.

  inputString = "";
  
  //This should clean the buffer. 
  Serial.flush();
  delay(10);
  
}

void change() {
  rcInteruppt = HIGH;
}

void distance(String reference, double sensorReading) { 
  Serial.print(reference + ":");
  Serial.print(sensorReading);
  Serial.print(";");
  delay(10);
}

void irDistance(String reference, int analogReading) {
  if(analogReading > 60) {
  Serial.print(reference + ":");
  Serial.print(analogReading);
  Serial.print(";");
  delay(10);

  }
  else {
    analogReading = -1;
    Serial.print(reference + ":");
    Serial.print(analogReading);
    Serial.print(";");
    delay(10);    
  } 
}
