#include <AFMotor.h>
#include "Ultrasonic.h"
#define triger A0
#define echo A1

AF_DCMotor motorRight(1, MOTOR12_64KHZ);  // create motor #2, 64KHz pwm
AF_DCMotor motorLeft(2, MOTOR12_64KHZ);   // create motor #2, 64KHz pwm
Ultrasonic ultrasonic(triger, echo);

int distance0;
int distance;
int rotMsec;
float msecPerDeg;
int msecPerFt = 1000;

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  motorRight.setSpeed(50);  // set the speed to 200/255
  motorLeft.setSpeed(51);   // set the speed to 200/255
}

void loop() {
// get range to the wall
  distance0 = ultrasonic.Ranging(CM); 
// rotate away from the wall
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(1000);
  rotMsec = 1000;  // set initial rotation time

  distance = ultrasonic.Ranging(CM); // get first distance reading for while loop
  while ((distance - distance0) > 5) {  // stay in loop until facing the wall again
    motorRight.run(FORWARD);
    motorLeft.run(BACKWARD);
    delay(50);
    rotMsec = rotMsec + 50;  // accumulated rotation time 
    distance = ultrasonic.Ranging(CM); 
  }
  msecPerDeg = float(rotMsec) / 360.; // set reciprocal of rotation rate (milliseconds per degree)

  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(int(90. * msecPerDeg));


  motorRight.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);      // turn it on going forward
  delay(4 * msecPerFt);
  
  motorRight.run(FORWARD);      // turn it on going forward
  motorLeft.run(BACKWARD);      // turn it on going forward
  delay(180 * msecPerDeg);

  motorRight.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);      // turn it on going forward
  delay(4 * msecPerFt);
  
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  delay(int(90. * msecPerDeg));

  motorRight.run(RELEASE);  // stopped
  motorLeft.run(RELEASE);   // stopped
  delay(5000);
}