#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 200
#define SERVOMAX 400
#define SERVO_FREQ 50
#define USMIN 600
#define USMAX 2400

void setup() {
  Serial.begin(9600);
  Serial.println("6 DoF robot controller");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at this freq

  delay(10);
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
    // pwm.setPWM(servonum+1, 0, pulselen);
    delay(10);
  }
  Serial.println("Reached max position");
  delay(100);

  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    // pwm.setPWM(servonum+1, 0, pulselen);
    delay(10);
  }
  Serial.println("Reached min position");
  delay(100);
}