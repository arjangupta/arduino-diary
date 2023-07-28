#include <Arduino.h>
#include <Servo.h>

byte servoPin = 9; // signal pin for the ESC.
byte potentiometerPin = A0; // analog input pin for the potentiometer.
Servo servo;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second.
  // Show welcome message in the serial monitor.
  Serial.println("Welcome to the Arduino BLDC ESC tester!");

  servo.attach(servoPin);
  servo.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.

  delay(7000); // delay to allow the ESC to recognize the stopped signal.
}

void loop() {

  int potVal = analogRead(potentiometerPin); // read input from potentiometer.

  // The potentiometer values can jump around suddenly at times. To deal with this, we
  // only update the PWM value if the potentiometer value has changed by at most 25. If it changes by more than 25,
  // we ignore the new value and clamp the PWM value to an increment of 25.
  static int lastPotVal = 0;
  if (abs(potVal - lastPotVal) > 25) {
    potVal = lastPotVal + (potVal > lastPotVal ? 25 : -25);
  }
  lastPotVal = potVal;

  // Show the potentiometer value in the serial monitor.
  Serial.print("Potentiometer value: ");
  Serial.println(potVal);

  int pwmVal = map(potVal,0, 1023, 1100, 1900); // maps potentiometer values to PWM value.

  servo.writeMicroseconds(pwmVal); // Send signal to ESC.
}