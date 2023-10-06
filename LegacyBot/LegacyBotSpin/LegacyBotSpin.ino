#include <AFMotor.h>

AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motorRight.setSpeed(100);     // set the speed to 200/255
  motorLeft.setSpeed(106);     // set the speed to 200/255
}

void loop() {
  Serial.print("tick");
  
  motorRight.run(FORWARD);      // turn it on going forward
  motorLeft.run(BACKWARD);      // turn it on going forward
  delay(1073);
  
  Serial.print("tack");
  motorRight.run(RELEASE);      // stopped
  motorLeft.run(RELEASE);      // stopped
  delay(5000);
}