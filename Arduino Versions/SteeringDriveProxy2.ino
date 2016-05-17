#include <Servo.h>

Servo steerServo; 
Servo driveServo;

String inputStringSteer;
String inputString;
char inByte;
char inByteSteer;

int drive = 1500;
int steer = 90;

void setup() {
  
  //Attach Servos to right pins.
  driveServo.attach(6);
  steerServo.attach(5);
 
  //Initialize Serial-Communication
  Serial.begin(56700);

  driveServo.writeMicroseconds(drive);
  steerServo.write(steer);
  
}

void loop() {
  
  //Checking all the Serial that is recieved and will start if the Serial is greater than 0.
  while(Serial.available() > 0) {

    //Value that will read in the Serial and put it in the inByte.
    inByte = Serial.read();
  
    //Checks for spaces between the Serial. Can be changed and suited for specific projects. This one is just using space as a checker
    if(inByte == ' ') {
      break;
    }

    if(inByte == ';') {
      while(Serial.available() > 0) {
        inByteSteer = Serial.read();
        if(inByteSteer == ' ') {
          break;
        }

        inputStringSteer += inByteSteer;
      }
    }

    //Add each inByte to the inputString. 
    inputString = inputString + inByte; 
  }
  //Will only execute if the while loop above is made since otherwise the inputString length will be lesser than 0.
  if(inputString.length() > 1) {

    drive = inputString.toInt();

    driveServo.writeMicroseconds(drive);
    

  }
  if(inputStringSteer.length() > 1) {
    //Takes the String for inputString and change it to a Integer.
    steer = inputStringSteer.toInt();

    //steerServo will use the new Integer steer to steer.
    steerServo.write(steer);

  }
  //Restoring the original value to inputString.

  inputString = "";
  inputStringSteer = "";
  
  //This should clean the buffer. 
  Serial.flush();
  delay(10);
  
}
