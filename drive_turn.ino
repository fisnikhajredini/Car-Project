#include <Servo.h>


Servo servo; 
Servo servo1;
String test;
int test1;
// the setup routine runs once when you press reset:
void setup() {
  //Serial is the commands that we send through the Serial Monitor!
  Serial.begin(9600); // we initiate the serial
  //servo1 is the motor which accelerates 
    servo1.attach(6);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
    servo1.writeMicroseconds(1500);//we set the microspeeds to the average where the car doesnt move.. if its higher the car goes forward and vice versa
  
 
   servo.attach(5);//we attach one of the motors to the digital pin 6 in arduino and name it servo1 so it will be different from the other motor
   servo.write(90); // we set the angle of the tires to 90 which means that the tires will be in a straight position. 
  
  

 
 
}

// the loop routine runs over and over again forever:
void loop() {
  
  
       
  if(Serial.available()){
    test=Serial.readString(); // Test becomes what we are sending to the serial monitor and it will be as a string, the serial reads it!
    if(test.charAt(0)== 'd'){ // we see if the first char of the string "test" is d (drive
       test.remove(0,1); // we remove the characters on the string from 0 to 1 which is only the 1st letter!
       test1 = test.toInt(); // we name the variable test1 and store the remainder of the test to it as an Integer so servo can write!
       servo1.writeMicroseconds(test1); // we write in microseconds from 1000 (full bacwards) to 2000 (full forward) with an medium of 1500.
      
    }
    if(test.charAt(0)== 't'){// we see if the first char of the string "test" is t (turn)
       test.remove(0,1); //we remove the characters on the string from 0 to 1 which is only the 1st letter!
       test1 = test.toInt();// we name the variable test1 and store the remainder of the test to it as an Integer so servo can write!
         servo.write(test1); // we write to servo with a degree ranging from 45 to 135 where 90 is the medium(tires straight) 
    }
    Serial.print(test1); // we print the result that we input without the first character.
  
  }
}
