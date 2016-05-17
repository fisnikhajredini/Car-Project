#include <Servo.h>
#include <SonarSRF08.h>

#define MAIN_08_ADDRESS (0xE6 >> 1)
#define US_08_FRONTRIGHT (0xE4 >> 1)
#define GAIN_REGISTER 0x31
#define LOCATION_REGISTER 0x8C

Servo steerServo; 
Servo driveServo;
SonarSRF08 usFront;
SonarSRF08 usFrontRight;

int tempDrive ;
int steer;
int drive;
int drivePulse =0;
int steerPulse =0;
int State = 0;
String serialInput;
int test1;
int zero = 0;
int steerRC;
int driveRC;
int tempSteer;
int rcPin1 = 2;
int rcPin2 = 3;
int fixedTempDrive;
String reference;
char unit = 'c';
int sensorSoft;
volatile int RCDriveFlag = LOW;
volatile int RCSteerFlag = LOW;

// the setup routine runs once when you press reset:
void setup() {
  //Serial is the commands that we send through the Serial Monitor!
  Serial.begin(9600); // we initiate the serial
  //servo1 is the motor which accelerates 
  driveServo.attach(6);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
  driveServo.writeMicroseconds(1500);//we set the microspeeds to the average where the car doesnt move.. if its higher the car goes forward and vice versa
  usFront.connect(MAIN_08_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER);
  usFrontRight.connect(US_08_FRONTRIGHT, GAIN_REGISTER, LOCATION_REGISTER);
  isConnected("SRF08 Front", usFront.getSoft());
  isConnected("SRF08 FrontRight", usFrontRight.getSoft());
 
  steerServo.attach(5);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
  steerServo.write(90); // we set the angle of the tires to 90 which means that the tires will be in a straight position. 
  pinMode(rcPin1,INPUT);
  pinMode(rcPin2,INPUT);
  attachInterrupt(digitalPinToInterrupt(rcPin2),change1,RISING);
  

}

// the loop routine runs over and over again forever
void loop() {
  float sensorReading = 0;
  sensorReading = usFront.getRange(unit);
  distance("frontSensor", sensorReading);

  float sensorReadingFR = 0;
  sensorReadingFR = usFrontRight.getRange(unit);
  distance("frontRightSensor", sensorReadingFR);
  
    if( RCDriveFlag == HIGH){   
      tempDrive = getDriveRCTime();
      tempSteer = getSteerRCTime();
      //Serial.println(tempDrive);
      if (tempDrive >0){
        driveRC = tempDrive;
        driveServo.writeMicroseconds(driveRC);
      }
      if (tempSteer>0){
        Serial.println(steerRC);
        steerRC=tempSteer;
      if (steerRC>1550){
        steerRC= steerRC+150;
        steerServo.write(steerRC);
        
      }
        
      else if(steerRC<1450){
        steerRC = steerRC-150;
        steerServo.write(steerRC);
      }
        
      else { steerServo.write(1500);
      }
      }
      if(tempDrive == 0){
        
        
        drive = 1500;
        steer = 90;
        
        zero++;
        //Serial.println(zero);
       
      //  Serial.println(getDriveRCTime);
        
        if (zero >= 10){
          
          RCDriveFlag = LOW;
          zero =0;
          
        }
      } 
      
      else{
  //    drive= tempDrive;
  //    steer=getSteerRCTime();
        drive = 1500;
        steer = 90;

        
       // driveServo.writeMicroseconds(drive);
        steerServo.write(steer);
      }
      
      
    }else if(Serial.available()){
        
      
        serialInput=Serial.readString(); // Test becomes what we are sending to the serial monitor and it will be as a string, the serial reads it!
        
        if(serialInput.charAt(0)== 'd'){ // we see if the first char of the string "test" is d (drive
            serialInput.remove(0,1); // we remove the characters on the string from 0 to 1 which is only the 1st letter!
            drive = serialInput.toInt(); // we name the variable test1 and store the remainder of the test to it as an Integer so servo can write!
            driveServo.writeMicroseconds(drive); // we write in microseconds from 1000 (full bacwards) to 2000 (full forward) with an medium of 1500.
      }
      
        if(serialInput.charAt(0)== 't'){// we see if the first char of the string "test" is t (turn)
            serialInput.remove(0,1); //we remove the characters on the string from 0 to 1 which is only the 1st letter!
            steer = serialInput.toInt();// we name the variable test1 and store the remainder of the test to it as an Integer so servo can write!
            steerServo.write(steer); // we write to servo with a degree ranging from 45 to 135 where 90 is the medium(tires straight) 
            
      }
   // Serial.print(test1); // we print the result that we input without the first character.
  
  }
  

}
  

  
void change1() {
  RCDriveFlag = HIGH;
  
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
int getDriveRCTime(){  
  drivePulse = pulseIn(2,HIGH,10000);
  //Serial.println(drivePulse);
  
  return drivePulse;
}

int getSteerRCTime(){
  steerPulse = pulseIn(3,HIGH,10000);
  return steerPulse;

}

