# LXG_DC_Motor_driver

A simple and efficient Arduino library to control DC motors using an H-bridge or similar driver.

## Features

- **Easy Control**: Simple methods to start, stop, forward, and reverse.
- **Speed Control**: Set speed (PWM) and accelerate/decelerate smoothly.
- **State Tracking**: Query current speed, direction, and running state.
- **Lightweight**: Minimal overhead.

## Installation

### Via Arduino Library Manager
1. Open Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries...**.
3. Search for `LXG_DC_Motor_driver`.
4. Click **Install**.

### Manual Installation
1. Download the latest release as a ZIP file.
2. Open Arduino IDE.
3. Go to **Sketch** > **Include Library** > **Add .ZIP Library...**.
4. Select the downloaded ZIP file.

## Usage

### Wiring
Connect your motor driver (e.g., L298N) to the Arduino:
- **Enable Pin**: Connect to a PWM-capable pin (e.g., 9).
- **Forward Pin**: Connect to a digital pin (e.g., 8).
- **Backward Pin**: Connect to a digital pin (e.g., 7).

### Example Code

```cpp
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
  myMotor.start(); // Starts at full speed (255) by default
}

void loop() {
  // Move forward
  myMotor.forward();
  delay(2000);
  
  // Stop
  myMotor.stop();
  delay(1000);
  
  // Move backward at half speed
  myMotor.reverse();
  myMotor.setSpeed(128);
  delay(2000);
  
  // Stop
  myMotor.stop();
  delay(1000);
}
```

## API Reference

- `void attach(int enablePin, int forwardPin, int backwardPin)`: Initialize the motor.
- `void start(int initialSpeed = 255)`: Start the motor.
- `void stop()`: Stop the motor.
- `void forward()`: Set direction to forward.
- `void reverse()`: Set direction to backward.
- `void setSpeed(int speed)`: Set speed (0-255).
- `void accelerate(int increment = 25)`: Increase speed.
- `void brake(int decrement = 25)`: Decrease speed.
- `int currentSpeed()`: Get current speed.
- `bool isRunning()`: Check if motor is running.
- `bool isForward()`: Check if direction is forward.

## License

This project is open source.
