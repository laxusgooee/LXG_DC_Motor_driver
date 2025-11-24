#ifndef LXG_DC_MOTOR_DRIVER_H
#define LXG_DC_MOTOR_DRIVER_H

#include "Arduino.h"

class LXG_Motor {
private:
  int speed;
  int ENABLE;
  int FORWARD;
  int BACKWARD;
  bool isAttached;
  bool isStarted;
  bool movingForward; // Track current direction

public:
  // Constructor
  LXG_Motor();

  // Destructor
  ~LXG_Motor();

  // Attach motor to pins
  void attach(int enablePin, int forwardPin, int backwardPin);

  // Toggle motor on/off
  void toggle();

  // Start motor with default settings
  void start();

  // Start motor with specific speed
  void start(int initialSpeed);

  // Move motor forward
  void forward();

  // Move motor backward
  void reverse();

  // Stop motor
  void stop();

  // Set motor speed (0-255)
  void setSpeed(int newSpeed);

  // Accelerate motor
  void accelerate(int increment = 25);

  // Decelerate motor
  void brake(int decrement = 25);

  // Getters
  int currentSpeed() const;

  bool isRunning() const;

  bool isReady() const;

  bool isForward() const;
};

#endif
