#include <Servo.h>
#include <SonarSRF08.h>

#define MAIN_08_ADDRESS (0xE6 >> 1)
#define US_08_FRONTRIGHT (0xE4 >> 1)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

Servo steerServo; 
Servo driveServo;
SonarSRF08 USFC;
SonarSRF08 USFR;

String inputString;
String inputStringSteer;

char inByte;
char inByteSteer;

int IRFR = A5;
int IRRR = A4;
int IRRC = A3;
int zero = 0;
int rcPin1 = 2;
int rcPin2 = 3;
int drive = 1500;
int steer = 90;

float sensorReading = 0;

volatile int rcInteruppt = LOW;

void setup() {
  
  //Attach Servos to right pins.
  driveServo.attach(6);
  steerServo.attach(5);
 
  //Initialize Serial-Communication
  Serial.begin(56700);

  driveServo.writeMicroseconds(drive);
  steerServo.write(steer);

  USFC.connect(MAIN_08_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER);
  USFR.connect(US_08_FRONTRIGHT, GAIN_REGISTER, LOCATION_REGISTER);

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
    sensorReading = USFC.getRange();
    distance("USFC", sensorReading);

    sensorReading = USFR.getRange();
    distance("USFR", sensorReading);

    sensorReading = analogRead(IRFR);
    distance("IRFR", sensorReading);

    sensorReading = analogRead(IRRR);
    distance("IRRR", sensorReading);

    sensorReading = analogRead(IRRC);
    distance("IRRC", sensorReading);
  
  //This is where the arduino will recieve messages from the proxy.
  
  //Checking all the Serial that is recieved and will start if the Serial is greater than 0.
    while(Serial.available() > 0) {
  
      //Value that will read in the Serial and put it in the inByte.
      inByte = Serial.read();
    
      //Checks for spaces between the Serial. Can be changed and suited for specific projects. This one is just using space as a checker
      if(inByte == ' ') {
        break;
      }
      //This if statement will take the other part of the string that we recieved from the proxy
      if(inByte == ':') {
        inByteSteer = Serial.read();
        inByteSteer++;
        if(inByteSteer == ' '){
          break;
        }
        inputStringSteer += inByteSteer;
      }
      //Add each inByte to the inputString. 
      inputString += inByte; 
    }
    //Will only execute if the while loop above is made since otherwise the inputString length will be lesser than 0.
    //Need to test with only inputString.length running both driving and steering commands.
    if(inputString.length() > 1) {
      
      drive = inputString.toInt();
      
      driveServo.writeMicroseconds(drive);
    }
    if(inputStringSteer.length() > 1){

      steer = inputStringSteer.toInt();
      
      steerServo.write(steer);
    }
  }
  //Restoring the original value to inputString.

  inputString = "";
  inputStringSteer = "";
  
  //This should clean the buffer. 
  Serial.flush();
  delay(10);
  
}

void change() {
  rcInteruppt = HIGH;
}

void distance(String reference, int sensorReading) { 
  Serial.print(reference + ":");
  Serial.write(sensorReading);
  delay(10);
}

