#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
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
    Motor();
    
    // Destructor
    ~Motor();

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
