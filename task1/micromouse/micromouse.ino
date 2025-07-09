#include "Encoder.hpp"
#include "Motor.hpp"

#define MOT1PWM 9
#define MOT1DIR 10
#define MOT2PWM 11
#define MOT2DIR 12

#define EN1_A 2
#define EN1_B 4
#define EN2_A 3
#define EN2_B 5

mtrn3100::Motor leftMotor(MOT1PWM, MOT1DIR);
mtrn3100::Motor rightMotor(MOT2PWM, MOT2DIR);

mtrn3100::Encoder leftEncoder(EN1_A, EN1_B);
mtrn3100::Encoder rightEncoder(EN2_A, EN2_B);

const int pwmSpeed = 150;         // speed 0–255
const float targetRotations = 5;  // stop after 5 rotations
const int ticksPerRev = 360;      // ticks per full wheel turn

void setup() {
  Serial.begin(9600);
  delay(1000);  // give serial monitor time
  leftMotor.setPWM(pwmSpeed);
  rightMotor.setPWM(pwmSpeed);
}

void loop() {
  long leftTicks = leftEncoder.getTicks();
  long rightTicks = rightEncoder.getTicks();

  float leftRevs = leftTicks / (float)ticksPerRev;
  float rightRevs = rightTicks / (float)ticksPerRev;

  Serial.print("Left revs: "); Serial.print(leftRevs);
  Serial.print(" | Right revs: "); Serial.println(rightRevs);

  if (leftRevs >= targetRotations) {
    leftMotor.setPWM(0);
  }

  if (rightRevs >= targetRotations) {
    rightMotor.setPWM(0);
  }

  delay(100);
}
