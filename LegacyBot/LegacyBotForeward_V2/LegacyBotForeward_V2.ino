#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Adafruit_L3GD20.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

Adafruit_L3GD20 gyro;

int speedRight = 100;
int speedLeft = speedRight;
int msecPerFt = 50000 / speedRight;
int travel = 4000;  // feet
int travelTime = travel * msecPerFt;
int timeStop;
float rotation;
float krotation = .1;

const int OptPin = 2;  // the number of the pushbutton pin
bool OldOptState = 0;  // variable for reading the pushbutton status
bool OptState;
unsigned int OptTime;
unsigned int OldOptTime;
float RPM;
float ValidRPM = 0.;
const float kRPM = 60000.0 / 24.0;  // fraction of a turn between transitions
unsigned int count = 0;
const float countDist = 6.5 / 24;  // wheel circumfrence divided by counts per revolution
const float stopDistance = 18;
const unsigned int stopCount = int(stopDistance / countDist);


void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  pinMode(OptPin, INPUT);

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(speedRight);
  rightMotor->run(FORWARD);
  leftMotor->setSpeed(speedLeft);
  leftMotor->run(FORWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);

  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS)) {
    Serial.println("Oops ... unable to initialize the gyro. Check your wiring!");
    while (1)
      ;
  }
  timeStop = millis() + travelTime;
  OldOptTime = millis();
  Serial.println("Go");
}

void loop() {

  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);

  OptState = digitalRead(OptPin);
  if (OptState != OldOptState) {
    //   OptTime = millis();
    //   RPM = ValidRPM * kRPM / float(OptTime - OldOptTime);
    //   OldOptTime = OptTime;
    //   ValidRPM = 1.0;
    //   Serial.print("RPM: ");
    //   Serial.println(RPM);
    OldOptState = OptState;
    count = count + 1;
    Serial.print("count: ");
    Serial.println(count);
  }

  gyro.read();
  rotation = (int)gyro.data.z;
  if (rotation != 0) {
    speedLeft = speedLeft + int(rotation * krotation);
    speedLeft = constrain(speedLeft, 0, 255);
    leftMotor->setSpeed(speedLeft);
  }

  while (count >= stopCount) {
    Serial.println("Stop");
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
    while (1)
      ;
  }
}