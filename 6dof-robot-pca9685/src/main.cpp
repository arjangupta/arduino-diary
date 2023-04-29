#include "RobotJoint.hpp"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685_module = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 400
#define SERVOMAX5 200
#define SERVO_FREQ 50

// Setup the robot joints
RobotJoint joints[5] = {
    RobotJoint(0, SERVOMIN+150, SERVOMAX-100, &pca9685_module),
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

  // Recommended delay before setting the first servo
  delay(10);

  // Setup destination angles
  joints[1].setImmediateTarget(SERVOMAX-50);
  joints[2].setImmediateTarget(SERVOMAX-75);
  joints[3].setImmediateTarget(SERVOMAX-100);
  joints[4].setImmediateTarget(SERVOMAX5-50);
  // joints[]
}

// Define list of targets for joint 0
uint16_t joint0_targets[5] = {200, 300, 200, 350, 220};
uint8_t joint0_target_index = 0;

void loop() {
  // Propagate the joints
  for (int i = 0; i < 5; i++) {
    joints[i].propagate();
  }

  // Check if robot is done moving, then set new target
  if (!joints[0].isMoving()) {
    Serial.println("Setting new target for joint0");
    joints[0].setTargetAngle(joint0_targets[joint0_target_index]);
    joint0_target_index++;
    if (joint0_target_index > 4) {
      joint0_target_index = 0;
    }
  }
  
  // Loop over joints array and check if any joints are moving
  bool any_joints_moving = false;
  for (int i = 0; i < 5; i++) {
    if (joints[i].isMoving()) {
      any_joints_moving = true;
    }
  }

  if (!any_joints_moving) {
    Serial.println("All joints are done moving");
    delay(1000);
  }
  else
  {
    delay(10);
  }
}