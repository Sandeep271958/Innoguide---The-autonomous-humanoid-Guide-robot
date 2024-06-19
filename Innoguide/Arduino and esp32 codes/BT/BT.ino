#include <BluetoothSerial.h>
BluetoothSerial btSerial;

// Motor pins
const int PWM1 = 2; // PWM pin for motor 1
const int DIR1 = 4; // Direction pin for motor 1
const int PWM2 = 3; // PWM pin for motor 2
const int DIR2 = 5; // Direction pin for motor 2

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize Bluetooth
  btSerial.begin("ESP32_BT"); // Set Bluetooth name
  
  // Set motor control pins as outputs
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  // Stop motors initially
  stopMotors();
}

void loop() {
  if (btSerial.available()) {
    char command = btSerial.read();
    switch (command) {
      case 'F': // Forward
        moveForward();
        break;
      case 'B': // Backward
        moveBackward();
        break;
      case 'L': // Left
        turnLeft();
        break;
      case 'R': // Right
        turnRight();
        break;
      case 'S': // Stop
        stopMotors();
        break;
      default:
        break;
    }
  }
}

void moveForward() {
  digitalWrite(DIR1, HIGH);
  analogWrite(PWM1, 200);

  digitalWrite(DIR2, HIGH);
  analogWrite(PWM2, 200);
}

void moveBackward() {
  digitalWrite(DIR1, LOW);
  analogWrite(PWM1, 200);

  digitalWrite(DIR2, LOW);
  analogWrite(PWM2, 200);
}

void turnLeft() {
  digitalWrite(DIR1, LOW);
  analogWrite(PWM1, 25);

  digitalWrite(DIR2, HIGH);
  analogWrite(PWM2, 25);
}

void turnRight() {
  digitalWrite(DIR1, HIGH);
  analogWrite(PWM1, 25);

  digitalWrite(DIR2, LOW);
  analogWrite(PWM2, 25);
}

void stopMotors() {
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}
