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