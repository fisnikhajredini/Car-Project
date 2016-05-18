#include <Servo.h>


Servo steerServo; 
Servo driveServo;
int tempDrive = 0;
int steer;
int drive;
int drivePulse =0;
int steerPulse =0;
int State = 0;
String serialInput;
int test1;
int zero = 0;
int rcPin1 = 3;
int rcPin2 = 2;
volatile int RCDriveFlag = LOW;
volatile int RCSteerFlag = LOW;
// the setup routine runs once when you press reset:
void setup() {
  //Serial is the commands that we send through the Serial Monitor!
  Serial.begin(9600); // we initiate the serial
  //servo1 is the motor which accelerates 
    driveServo.attach(6);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
    driveServo.writeMicroseconds(1500);//we set the microspeeds to the average where the car doesnt move.. if its higher the car goes forward and vice versa
  
 
   steerServo.attach(5);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
   steerServo.write(90); // we set the angle of the tires to 90 which means that the tires will be in a straight position. 
  pinMode(rcPin1,INPUT);
  pinMode(rcPin2,INPUT);
  attachInterrupt(digitalPinToInterrupt(rcPin1),change1,RISING);

}

// the loop routine runs over and over again forever:
void loop() {
  
    if( RCDriveFlag == HIGH){   
      tempDrive = getDriveRCTime();
      
      if( tempDrive == 0){
        
        
        drive = 1500;
        steer = 90;
        
        zero++;
        
        if (zero >= 10){
          RCDriveFlag = LOW;
        Serial.println(zero);
        }
       
      }
      else{
  //    drive= tempDrive;
  //    steer=getSteerRCTime();
        drive = 1500;
        steer = 90;
        zero = 0;
      }
      steerServo.write(steer);
      driveServo.writeMicroseconds(drive);
      
      
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
    Serial.print(test1); // we print the result that we input without the first character.
  
  }
  

}
  

  
void change1() {
  RCDriveFlag = HIGH;
  
}

//void change2() {
//  RCSteerFlag = HIGH; 
//  
//
//}

 int getDriveRCTime(){
  
  drivePulse = pulseIn(3,HIGH,10000);
  return drivePulse ;
}
int getSteerRCTime(){
   steerPulse = pulseIn(2,HIGH,10000);
  return steerPulse;

}







