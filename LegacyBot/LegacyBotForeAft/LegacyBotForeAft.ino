#include <AFMotor.h>

AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motorRight.setSpeed(200);     // set the speed to 200/255
  motorLeft.setSpeed(200);     // set the speed to 200/255
}

void loop() {
  Serial.print("tick");
  
  motorRight.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);      // turn it on going forward
  delay(1000);

  Serial.print("tock");
  motorRight.run(BACKWARD);     // the other way
  motorLeft.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack");
  motorRight.run(RELEASE);      // stopped
  motorLeft.run(RELEASE);      // stopped
  delay(1000);
}