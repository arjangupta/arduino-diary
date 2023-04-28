#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 200
#define SERVOMAX 400
#define SERVO_FREQ 50
#define USMIN 600
#define USMAX 2400

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at this freq

  delay(10);

  // 10 second countdown
  // for (uint8_t i = 0; i < 10; i++) {
  //   // Show starting in seconds
  //   Serial.print("Starting in "); Serial.println(10 - i);
  //   delay(1000);
  // }

}

// our servo # counter
uint8_t servonum = 4;

void loop() {

  pwm.setPWM(1, 0, SERVOMAX-50);
  pwm.setPWM(2, 0, SERVOMAX-75);
  pwm.setPWM(3, 0, SERVOMAX-100);
  
  
  // Drive each servo one at a time using setPWM()
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(50);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(50);
  }

  // servonum++;
  // if (servonum > 5) servonum = 0; // Testing the first 6 servo channels
}