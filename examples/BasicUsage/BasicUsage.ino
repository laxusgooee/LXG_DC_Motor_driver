#include <LXG_DC_Motor_driver.h>

// Define pins
const int ENABLE_PIN = 9;
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 7;

// Create motor instance
LXG_Motor myMotor;

void setup() {
  Serial.begin(9600);

  // Attach motor to pins
  myMotor.attach(ENABLE_PIN, FORWARD_PIN, BACKWARD_PIN);

  // Start motor
  myMotor.start();
}

void loop() {
  // Accelerate
  for (int i = 0; i < 10; i++) {
    myMotor.accelerate();
    delay(500);
  }

  delay(1000);

  // Decelerate
  for (int i = 0; i < 10; i++) {
    myMotor.brake();
    delay(500);
  }

  delay(1000);

  // Reverse direction
  myMotor.reverse();
  myMotor.setSpeed(150);

  delay(2000);

  // Stop
  myMotor.stop();

  delay(2000);

  // Start forward again
  myMotor.forward();
  myMotor.setSpeed(200);

  delay(2000);
}
