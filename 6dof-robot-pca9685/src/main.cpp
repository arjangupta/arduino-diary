#include "RobotJoint.hpp"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685_module = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 400
#define SERVOMAX5 200
#define SERVO_FREQ 50
#define USMIN 600
#define USMAX 2400

// Setup the robot joints
RobotJoint joints[5] = {
    RobotJoint(0, SERVOMIN, SERVOMAX, &pca9685_module),
    RobotJoint(1, SERVOMIN, SERVOMAX, &pca9685_module),
    RobotJoint(2, SERVOMIN, SERVOMAX, &pca9685_module),
    RobotJoint(3, SERVOMIN, SERVOMAX, &pca9685_module),
    RobotJoint(4, SERVOMIN, SERVOMAX5, &pca9685_module)
};

void setup() {
  Serial.begin(9600);
  Serial.println("6 DoF robot controller");

  pca9685_module.begin();
  pca9685_module.setOscillatorFrequency(27000000);
  pca9685_module.setPWMFreq(SERVO_FREQ);  // Analog servos run at this freq

  delay(10);


  // Setup destination angles
  joint1.setImmediateTarget(SERVOMAX-50);
  joint2.setImmediateTarget(SERVOMAX-75);
  joint3.setImmediateTarget(SERVOMAX-100);
}

// our servo # counter
uint8_t gripper_rotator_servo_num = 4;

void loop() {
  Serial.println("Looping");

  // Drive each servo one at a time using setpca9685_module()
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX5; pulselen++) {
    pca9685_module.setpca9685_module(gripper_rotator_servo_num, 0, pulselen+100);
    pca9685_module.setpca9685_module(gripper_rotator_servo_num+1, 0, pulselen);
    delay(10);
  }
  Serial.println("Reached max position");
  delay(100);

  for (uint16_t pulselen = SERVOMAX5; pulselen > SERVOMIN; pulselen--) {
    pca9685_module.setpca9685_module(gripper_rotator_servo_num, 0, pulselen+100);
    pca9685_module.setpca9685_module(gripper_rotator_servo_num+1, 0, pulselen);
    delay(10);
  }
  Serial.println("Reached min position");
  delay(100);
}