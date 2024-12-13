/*
This tab has everything to do with the Servo Motor.
*/

//Importing the servo library
#include <Servo.h>
Servo servo;

//Setting the servor pins and interval movement
const byte servoPin = 3;
const byte servoMin = 0;
const byte servoMax = 180;
const int railRoadGateMoveInterval = 50;

byte servoPosition = 0;
unsigned long gatePreviousMillis = 0L;

//getter for the servo positions min, max, and the current. 
byte getServoMax() {
  return servoMax;
}

byte getServoMin() {
  return servoMin;
}

byte getPosServo() {
  return servoPosition;
}

//sets up the servo
void servoSetup() {
  servo.attach(servoPin);
  servo.write(servoMin);
  servoPosition = servoMin;
}

// function to move the servo motor.
void moveServo(byte newPosition) {

  servoPosition = newPosition;
  if (servoPosition < servoMin) {
    servoPosition = servoMin;
  }
  if (servoPosition > servoMax) {
    servoPosition = servoMax;
  }
  servo.write(newPosition);
}
//moves the servo slow.
void moveServoSlowly(byte newPosition){
  if(timerControl(gatePreviousMillis,railRoadGateMoveInterval)){
    moveServo(newPosition);
    gatePreviousMillis=millis();
  }
}


