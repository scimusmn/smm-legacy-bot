
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
}

void loop() {
  Serial.print("tick");
  
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  delay(500);

  Serial.print("tock");
  
  rightMotor->run(BACKWARD);
  leftMotor->run(BACKWARD);
  delay(500);
  
  Serial.print("tack");
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
  delay(1000);
}