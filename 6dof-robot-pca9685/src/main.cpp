#include "RobotJoint.hpp"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685_module = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 400
#define SERVOMAX5 200
#define SERVO_FREQ 50

// Setup the robot joints
RobotJoint joints[5] = {
    RobotJoint(0, 170, 350, &pca9685_module),
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
  joints[0].setImmediateTarget(200);
  joints[1].setImmediateTarget(300);
  joints[2].setImmediateTarget(300);
  joints[3].setImmediateTarget(300);
  joints[4].setImmediateTarget(SERVOMAX5-50);
  // joints[5].setImmediateTarget(SERVOMAX-50);
}

// Define list of random targets for joint 0, between 170 and 350
uint16_t joint0_targets[5] = {300, 170, 250, 200, 350};
uint8_t joint0_target_index = 0;

// Define list of random targets for joint 3, between SERVOMIN and SERVOMAX
uint16_t joint3_targets[5] = {SERVOMIN, 300, 250, 200, SERVOMAX};
uint8_t joint3_target_index = 0;

void loop() {
  // Propagate the joints
  for (int i = 0; i < 5; i++) {
    joints[i].propagate();
  }

  // Check if joint 0 is done moving, then set new target
  if (!joints[0].isMoving()) {
    Serial.println("Setting new target for joint0");
    joints[0].setTargetAngle(joint0_targets[joint0_target_index]);
    joint0_target_index++;
    if (joint0_target_index > 4) {
      joint0_target_index = 0;
    }
  }

  // Check if joint 3 is done moving, then set new target
  if (!joints[3].isMoving()) {
    Serial.println("Setting new target for joint3");
    joints[3].setTargetAngle(joint3_targets[joint3_target_index]);
    joint3_target_index++;
    if (joint3_target_index > 4) {
      joint3_target_index = 0;
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