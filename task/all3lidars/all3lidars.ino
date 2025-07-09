#include <Wire.h>
#include <VL6180X.h>
#include <MPU6050_light.h>

// Create sensor instances
VL6180X sensor1;
VL6180X sensor2;
VL6180X sensor3;
MPU6050 mpu(Wire);

// Define ENABLE pins for LIDARs
const int sensor1_pin = A0;
const int sensor2_pin = A1;
const int sensor3_pin = A2;

unsigned long timer = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Set LIDAR enable pins as outputs and turn all off
  pinMode(sensor1_pin, OUTPUT);
  pinMode(sensor2_pin, OUTPUT);
  pinMode(sensor3_pin, OUTPUT);

  digitalWrite(sensor1_pin, LOW);
  digitalWrite(sensor2_pin, LOW);
  digitalWrite(sensor3_pin, LOW);
  delay(100);

  // Power on Sensor 1 and assign new address
  digitalWrite(sensor1_pin, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setTimeout(250);
  sensor1.setAddress(0x30);
  delay(50);

  // Power on Sensor 2 and assign new address
  digitalWrite(sensor2_pin, HIGH);
  delay(50);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setTimeout(250);
  sensor2.setAddress(0x31);
  delay(50);

  // Power on Sensor 3 and assign new address
  digitalWrite(sensor3_pin, HIGH);
  delay(50);
  sensor3.init();
  sensor3.configureDefault();
  sensor3.setTimeout(250);
  sensor3.setAddress(0x32);
  delay(50);

  // IMU Setup
  byte status = mpu.begin();
  if (status != 0) {
    Serial.print("MPU6050 init failed with code: ");
    Serial.println(status);
    while (1);
  }

  Serial.println("Calibrating IMU...");
  delay(1000);
  mpu.calcOffsets(true, true);
  Serial.println("IMU calibration done.");
}

void loop() {
  // Update IMU
  mpu.update();

  // Only output every 200ms
  if (millis() - timer > 200) {
    Serial.print("LEFT: ");
    Serial.print(sensor1.readRangeSingleMillimeters());
    if (sensor1.timeoutOccurred()) Serial.print(" TIMEOUT");

    Serial.print(" | FRONT: ");
    Serial.print(sensor2.readRangeSingleMillimeters());
    if (sensor2.timeoutOccurred()) Serial.print(" TIMEOUT");

    Serial.print(" | RIGHT: ");
    Serial.print(sensor3.readRangeSingleMillimeters());
    if (sensor3.timeoutOccurred()) Serial.print(" TIMEOUT");

    Serial.print(" | YAW: ");
    Serial.print(mpu.getAngleZ());
    Serial.println(" deg");

    timer = millis();
  }
}
