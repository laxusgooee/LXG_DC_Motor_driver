#include "LXG_DC_Motor_driver.h"

// Constructor
LXG_Motor::LXG_Motor()
    : speed(0), isAttached(false), isStarted(false), movingForward(true) {}

// Destructor
LXG_Motor::~LXG_Motor() { stop(); }

// Attach motor to pins
void LXG_Motor::attach(int enablePin, int forwardPin, int backwardPin) {
  if (isAttached) {
    Serial.println(F("Motor already attached"));
    return;
  }

  ENABLE = enablePin;
  FORWARD = forwardPin;
  BACKWARD = backwardPin;

  pinMode(ENABLE, OUTPUT);
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);

  // Initialize all pins to LOW
  analogWrite(ENABLE, 0);
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);

  isAttached = true;
}

// Toggle motor on/off
void LXG_Motor::toggle() {
  if (isStarted) {
    stop();
  } else {
    start();
  }
}

// Start motor with default settings
void LXG_Motor::start() {
  if (!isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (isStarted) {
    Serial.println(F("Motor already running"));
    return;
  }

  speed = 255;
  isStarted = true;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, speed);
}

// Start motor with specific speed
void LXG_Motor::start(int initialSpeed) {
  if (!isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  speed = constrain(initialSpeed, 0, 255);
  isStarted = true;

  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  analogWrite(ENABLE, speed);
}

// Move motor forward
void LXG_Motor::forward() {
  if (!isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (!isStarted) {
    Serial.println(F("Error: Motor not started. Call start() first."));
    return;
  }

  movingForward = true;
  digitalWrite(FORWARD, HIGH);
  digitalWrite(BACKWARD, LOW);
}

// Move motor backward
void LXG_Motor::reverse() {
  if (!isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  if (!isStarted) {
    Serial.println(F("Error: Motor not started. Call start() first."));
    return;
  }

  movingForward = false;
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, HIGH);
}

// Stop motor
void LXG_Motor::stop() {
  if (!isStarted)
    return;

  analogWrite(ENABLE, 0);
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);

  isStarted = false;
  speed = 0; // Reset speed to 0 when stopped
}

// Set motor speed (0-255)
void LXG_Motor::setSpeed(int newSpeed) {
  if (!isAttached) {
    Serial.println(F("Error: Motor not attached"));
    return;
  }

  speed = constrain(newSpeed, 0, 255);

  if (isStarted) {
    analogWrite(ENABLE, speed);
  }
}

// Accelerate motor
void LXG_Motor::accelerate(int increment) {
  if (!isAttached || !isStarted)
    return;

  speed = constrain(speed + increment, 0, 255);
  analogWrite(ENABLE, speed);
}

// Decelerate motor
void LXG_Motor::brake(int decrement) {
  if (!isAttached || !isStarted)
    return;

  speed = constrain(speed - decrement, 0, 255);
  analogWrite(ENABLE, speed);

  // Auto-stop if speed reaches 0
  if (speed == 0) {
    stop();
  }
}

// Getters
int LXG_Motor::currentSpeed() const { return speed; }

bool LXG_Motor::isRunning() const { return isStarted; }

bool LXG_Motor::isReady() const { return isAttached; }

bool LXG_Motor::isForward() const { return movingForward; }
