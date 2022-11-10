#include <Arduino.h>

// MANUAL WAY
// #define servoPin 8

// void setup() {
//   pinMode(servoPin, OUTPUT);
// }

// void loop() {
//   // A pulse each 20 ms
//   digitalWrite(servoPin, HIGH);
//   // Pule durations: 600 - 0 deg; 1450 - 90 deg; 2300 - 180 deg
//   delayMicroseconds(600); // Duration of the pulse in microseconds
//   digitalWrite(servoPin, LOW);
//   delayMicroseconds(18550); // Remaining duration of the pulse in low (total should be 20ms)
// }

#include <Servo.h>

Servo robot_servo1;

void setup() {
  robot_servo1.attach(8,600,2300);
}

void loop() {
  robot_servo1.write(0); // go to angle 0
  delay(1000);

  robot_servo1.write(90); // go to angle 90
  delay(1000);
}