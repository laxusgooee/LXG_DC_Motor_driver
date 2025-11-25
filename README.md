# LXG_DC_Motor_driver

A simple and efficient Arduino library to control DC motors using an H-bridge or similar motor driver.

## Features

- **Simple Control**: Intuitive methods to start, stop, move forward, and reverse.
- **Speed Control**: Set speed via PWM, accelerate, and decelerate.
- **State Tracking**: Easily query the motor's current speed, direction, and running state.
- **Lightweight**: Minimal memory and processing overhead.

## Installation

### Via Arduino Library Manager
1. Open the Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries...**.
3. Search for `LXG_DC_Motor_driver`.
4. Click **Install**.

### Manual Installation
1. Download the latest release ZIP file from the repository.
2. Open the Arduino IDE.
3. Go to **Sketch** > **Include Library** > **Add .ZIP Library...**.
4. Select the downloaded ZIP file.

## Usage

### Wiring
Connect your motor driver (e.g., L298N) to your Arduino:
- **Enable Pin**: Connect to a PWM-capable pin (e.g., `~9`).
- **Forward Pin**: Connect to any digital pin (e.g., `8`).
- **Backward Pin**: Connect to any digital pin (e.g., `7`).

### Example Code

```cpp
#include <LXG_DC_Motor_driver.h>

// Define motor control pins
const int ENABLE_PIN = 9;
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 7;

// Create a motor instance
LXG_Motor myMotor;

void setup() {
  Serial.begin(9600);
  
  // Attach the motor to its control pins
  myMotor.attach(ENABLE_PIN, FORWARD_PIN, BACKWARD_PIN);
  
  // Start the motor (enables it but does not move it yet)
  // Think of this as turning the key in a car
  myMotor.start(); 
}

void loop() {
  Serial.println("Moving forward at full speed...");
  myMotor.setSpeed(255); // Set to max speed
  myMotor.forward();
  delay(2000);
  
  Serial.println("Braking...");
  myMotor.brake(100); // Reduce speed
  delay(500);
  Serial.println("Braking...");
  myMotor.brake(100); // Reduce speed further
  delay(500);
  
  Serial.println("Stopping.");
  myMotor.stop();
  delay(2000);
  
  Serial.println("Starting and moving in reverse at half speed...");
  myMotor.start(128); // Start motor at half speed
  myMotor.reverse();
  delay(2000);

  Serial.println("Accelerating...");
  myMotor.accelerate(50);
  delay(500);
  Serial.println("Accelerating...");
  myMotor.accelerate(50);
  delay(500);

  Serial.println("Stopping.");
  myMotor.stop();
  delay(2000);
}
```

## API Reference

### Setup
- `LXG_Motor()`
  The constructor. Creates a new motor object.

- `void attach(int enablePin, int forwardPin, int backwardPin)`
  Attaches the motor to the specified control pins. Must be called before any other methods.

### Core Control
- `void start()`
  Enables the motor at full speed (255). Does not cause movement until `forward()` or `reverse()` is called.

- `void start(int initialSpeed)`
  Enables the motor at a specific speed (0-255).

- `void stop()`
  Stops all motor activity and disables it. Resets speed to 0.

- `void toggle()`
  Toggles the motor's state between started and stopped.

### Movement
- `void forward()`
  Sets the motor's direction to forward. The motor must be started to move.

- `void reverse()`
  Sets the motor's direction to backward.

- `void setSpeed(int newSpeed)`
  Sets the motor's speed (0-255).

- `void accelerate(int increment = 25)`
  Increases the motor's current speed by a given amount.

- `void brake(int decrement = 25)`
  Decreases the motor's current speed by a given amount. If speed reaches 0, the motor stops.

### State Queries
- `int speed() const`
  Returns the current speed (0-255).

- `bool isReady() const`
  Returns `true` if the motor has been attached to pins.

- `bool isRunning() const`
  Returns `true` if the motor is started (enabled).

- `bool isMoving() const`
  Returns `true` if the motor is actively moving forward or backward.

- `bool isMovingForward() const`
  Returns `true` if the motor is moving forward.

- `bool isReversing() const`
  Returns `true` if the motor is moving backward.

## License

This project is open source and available under the MIT License.
