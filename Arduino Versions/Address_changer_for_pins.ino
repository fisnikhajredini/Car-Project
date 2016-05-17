/*
This code was found online and was used to change the address of a pin since 2 different SCL,SDA pins had the same address.
Credit iToby
http://forum.arduino.cc/index.php?topic=124333.0
*/

#include <Wire.h>

#define oldad (0xE6 >>1)
#define newad 0xE4

void setup() {

  Wire.begin();
  
  delay(100);

    Wire.beginTransmission(oldad);
    Wire.write(0x00);
    Wire.write(0xA0);
    Wire.endTransmission();
    delay(60);
    
    Wire.beginTransmission(oldad);
    Wire.write(0x00);
    Wire.write(0xAA);
    Wire.endTransmission();
    delay(60);
    
    Wire.beginTransmission(oldad);
    Wire.write(0x00);
    Wire.write(0xA5);
    Wire.endTransmission();
    delay(60);
    
    Wire.beginTransmission(oldad);
    Wire.write(0x00);
    Wire.write(newad);
    Wire.endTransmission();

}
  
void loop(){
}
