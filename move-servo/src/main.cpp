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
  robot_servo1.attach(8,525,2050);
}

void loop() {
  for (size_t i = 0; i < 180; i++)
  {
    robot_servo1.write(i); // go to angle i
    delay(3);
  }
  for (size_t i = 0; i < 180; i++)
  {
    robot_servo1.write(180 - i); // go to angle i
    delay(3);
  }
}