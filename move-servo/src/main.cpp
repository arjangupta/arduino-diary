#include <Arduino.h>

#define servoPin 9

void setup() {
  pinMode(servoPin, OUTPUT);
}

void loop() {
  // A pulse each 20 ms
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(1450); // Duration of the pulse in microseconds
  digitalWrite(servoPin, LOW);
  delayMicroseconds(18550); // Remaining duration of the pulse in low (total should be 20ms)
}