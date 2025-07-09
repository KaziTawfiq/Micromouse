#include "Motor.hpp"

#define LEFT_PWM 9
#define LEFT_DIR 10
#define RIGHT_PWM 11
#define RIGHT_DIR 12

mtrn3100::Motor leftMotor(LEFT_PWM, LEFT_DIR);
mtrn3100::Motor rightMotor(RIGHT_PWM, RIGHT_DIR);

int pwmSpeed = 200;
unsigned long startTime;
bool motorsStarted = false;
bool motorsStopped = false;

void setup() {
    Serial.begin(9600);
    startTime = millis();
    Serial.println("Waiting 3 seconds...");
}

void loop() {
    unsigned long currentTime = millis();

    // Wait 3 seconds before starting motors
    if (!motorsStarted && currentTime - startTime >= 3000) {
        leftMotor.setPWM(175);        // Start left motor
        rightMotor.setPWM(175);  // Start right motor
        Serial.println("Motors started.");
        motorsStarted = true;
        startTime = currentTime; // reset timer to track 5s run
    }

    // After motors have started, stop them after 5 seconds
    if (motorsStarted && !motorsStopped && currentTime - startTime >= 800) {
        leftMotor.setPWM(0);
        rightMotor.setPWM(0);
        Serial.println("Motors stopped.");
        motorsStopped = true;
    }
}
