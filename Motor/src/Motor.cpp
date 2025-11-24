#include "Motor.h"

// Constructor
Motor::Motor() : speed(0), isAttached(false), isStarted(false), movingForward(true) {
}

// Destructor
Motor::~Motor() {
    stop();
    Serial.println(F("Motor destroyed"));
}

// Attach motor to pins
void Motor::attach(int enablePin, int forwardPin, int backwardPin) {
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
    
    Serial.println(F("Motor attached successfully"));
}

// Toggle motor on/off
void Motor::toggle() {
    if (isStarted) {
        stop();
    } else {
        start();
    }
}

// Start motor with default settings
void Motor::start() {
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
    movingForward = true;

    digitalWrite(FORWARD, HIGH);
    digitalWrite(BACKWARD, LOW);
    analogWrite(ENABLE, speed);

    Serial.println(F("Motor started"));
    Serial.print(F("Speed: "));
    Serial.println(speed);
}

// Start motor with specific speed
void Motor::start(int initialSpeed) {
    if (!isAttached) {
        Serial.println(F("Error: Motor not attached"));
        return;
    }
    
    speed = constrain(initialSpeed, 0, 255);
    isStarted = true;
    movingForward = true;

    digitalWrite(FORWARD, HIGH);
    digitalWrite(BACKWARD, LOW);
    analogWrite(ENABLE, speed);

    Serial.print(F("Motor started at speed: "));
    Serial.println(speed);
}

// Move motor forward
void Motor::forward() {
    if (!isAttached) {
        Serial.println(F("Error: Motor not attached"));
        return;
    }
    
    if (!isStarted) {
        start();
        return;
    }
    
    movingForward = true;
    digitalWrite(FORWARD, HIGH);
    digitalWrite(BACKWARD, LOW);
    
    Serial.print(F("Moving forward at speed: "));
    Serial.println(speed);
}

// Move motor backward
void Motor::reverse() {
    if (!isAttached) {
        Serial.println(F("Error: Motor not attached"));
        return;
    }
    
    if (!isStarted) {
        start();
    }
    
    movingForward = false;
    digitalWrite(FORWARD, LOW);
    digitalWrite(BACKWARD, HIGH);
    
    Serial.print(F("Moving backward at speed: "));
    Serial.println(speed);
}

// Stop motor
void Motor::stop() {
    if (!isStarted) return;
    
    analogWrite(ENABLE, 0);
    digitalWrite(FORWARD, LOW);
    digitalWrite(BACKWARD, LOW);
    
    isStarted = false;
    speed = 0; // Reset speed to 0 when stopped
    
    Serial.println(F("Motor stopped"));
}

// Set motor speed (0-255)
void Motor::setSpeed(int newSpeed) {
    if (!isAttached) {
        Serial.println(F("Error: Motor not attached"));
        return;
    }
    
    speed = constrain(newSpeed, 0, 255);
    
    if (isStarted) {
        analogWrite(ENABLE, speed);
        Serial.print(F("Speed set to: "));
        Serial.println(speed);
    }
}

// Accelerate motor
void Motor::accelerate(int increment) {
    if (!isAttached || !isStarted) return;

    speed = constrain(speed + increment, 0, 255);
    analogWrite(ENABLE, speed);
    
    Serial.print(F("Accelerated to: "));
    Serial.println(speed);
}

// Decelerate motor
void Motor::brake(int decrement) {
    if (!isAttached || !isStarted) return;

    speed = constrain(speed - decrement, 0, 255);
    analogWrite(ENABLE, speed);
    
    Serial.print(F("Braking to: "));
    Serial.println(speed);
    
    // Auto-stop if speed reaches 0
    if (speed == 0) {
        stop();
    }
}

// Getters
int Motor::currentSpeed() const {
    return speed;
}

bool Motor::isRunning() const {
    return isStarted;
}

bool Motor::isReady() const {
    return isAttached;
}

bool Motor::isForward() const {
    return movingForward;
}
