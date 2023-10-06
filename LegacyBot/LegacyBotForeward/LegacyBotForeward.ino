#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_L3GD20.h>

AF_DCMotor motorRight(1, MOTOR12_64KHZ);  // create motor #2, 64KHz pwm
AF_DCMotor motorLeft(2, MOTOR12_64KHZ);   // create motor #2, 64KHz pwm

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

  motorRight.setSpeed(speedRight);  // set the speed to 200/255
  motorLeft.setSpeed(speedLeft);    // set the speed to 200/255

  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
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

  motorRight.run(FORWARD);  // turn it on going forward
  motorLeft.run(FORWARD);

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
    motorLeft.setSpeed(speedLeft);
  }

  while (count >= stopCount) {
    Serial.println("Stop");
    motorRight.run(RELEASE);  // stopped
    motorLeft.run(RELEASE);   // stopped
    while (1)
      ;
  }
}