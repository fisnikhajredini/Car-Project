#include <Servo.h>
#include <SonarSRF08.h>

#define US_08_FRONT (0xE6 >> 1)
#define US_08_FRONTRIGHT (0xE4 >> 1)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

Servo steerServo; 
Servo driveServo;
SonarSRF08 usFront;
SonarSRF08 usFrontRight;

String inputString;

int drive = 0;
int steer = 90;

volatile int control = LOW;

void setup() {
  
  //Attach steerServo to pin 6.
  steerServo.attach(6);
  
  //Attach driveServo to pin 5.
  driveServo.attach(5);

  //Is more or less a way to attach the sensors to pin. Also defines the range and frequency of reading data.
  usFront.connect(US_08_FRONT, GAIN_REGISTER, LOCATION_REGISTER);
  usFrontRight.connect(US_08_FRONTRIGHT, GAIN_REGISTER, LOCATION_REGISTER);
  
  //Initialize Serial-Communication
  Serial.begin(9600);
  
  //Using map instead. 0-1000 = LOW, 1000-2000 = HIGH
  drive = map(1500, 0, 1023, 1000, 2000);
  
  //Putting the car in neutral
  driveServo.writeMicroseconds(drive);
  steerServo.write(steer);
  
}

void loop() {
  //So we can panic turn off the car with the controller by turning it on.
  if(control == HIGH) {
    steer = 90;
    drive = map(1500, 0, 1023, 1000, 2000);

    steerServo.write(steer);
    driveServo.writeMicroseconds(drive);
  }

  //Checking all the Serial that is recieved and will start if the Serial is greater than 0.
  while(Serial.available() > 0) {

    //Value that will read in the Serial and put it in the inByte.
    char inByte = Serial.read();

    //Checks for spaces between the Serial. Can be changed and suited for specific projects. This one is just using space as a checker
    if(inByte == ' ') {
      break;
    }

    //Add each inByte to the inputString. 
    inputString = inputString + inByte; 
  }
  //Will only execute if the while loop above is made since otherwise the inputString length will be lesser than 0.
  if(inputString.length() > 1) {

    //Takes the String for inputString and change it to a Integer.
    steer = inputString.toInt();

    //steerServo will use the new Integer steer to steer.
    steerServo.write(steer);

    //drive
    drive = map(1585, 0, 1023, 1000, 2000);
    driveServo.writeMicroseconds(drive);
  }
  
}
