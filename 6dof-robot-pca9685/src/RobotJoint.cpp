#include "RobotJoint.hpp"
#include <Arduino.h>

RobotJoint::RobotJoint(uint8_t servo_num, uint16_t min, uint16_t max, Adafruit_PWMServoDriver* pwm) {
    this->_servo_num = servo_num;
    this->_min = min;
    this->_max = max;
    // Set the destination to out of bounds
    this->_destination = 0;
    this->_immediate_target = 0;
    this->_valid_destination = false;
    this->_valid_immediate_target = false;
    // Set the current based on which motor we're talking about
    switch (servo_num) {
        case 0:
            this->_current = max;
            break;
        case 1:
            this->_current = max;
            break;
        case 2:
            this->_current = max;
            break;
        case 3:
            this->_current = max;
            break;
        case 4:
            this->_current = (max - min) / 2;
            break;
        case 5:
            this->_current = (max - min) / 2;
            break;
        default:
            Serial.print("Invalid servo number: ");
            Serial.println(servo_num);
            break;
    }
    // Set the PCA9685 PWM driver
    this->_pwm = pwm;
}

void RobotJoint::setTargetAngle(uint16_t destination) {
    if (destination > this->_max || destination < this->_min) {
        Serial.print("Invalid destination ");
        Serial.print(destination);
        Serial.print(" for joint");
        Serial.println(this->_servo_num);
        this->_valid_destination = false;
        return;
    }
    this->_destination = destination;
    this->_valid_destination = true;
}

void RobotJoint::setImmediateTarget(uint16_t destination) {
    if (destination > this->_max || destination < this->_min) {
        Serial.print("Invalid destination ");
        Serial.print(destination);
        Serial.print(" for joint");
        Serial.println(this->_servo_num);
        this->_valid_immediate_target = false;
        return;
    }
    this->_immediate_target = destination;
    this->_valid_immediate_target = true;
}

void RobotJoint::propagate() {
    if (_valid_immediate_target) {
        _pwm->setPWM(this->_servo_num, 0, this->_immediate_target);
        this->_current = this->_immediate_target;
        this->_valid_immediate_target = false;
        Serial.print("Joint ");
        Serial.print(this->_servo_num);
        Serial.println("- imediate target reached");
        return;
    }
    if (_valid_destination) {
        _pwm->setPWM(this->_servo_num, 0, this->_current);
        if (this->_current == this->_destination) {
            Serial.print("Joint ");
            Serial.print(this->_servo_num);
            Serial.print(" reached destination ");
            Serial.println(this->_destination);
            _valid_destination = false;
            return;
        } else {
            if (this->_current < this->_destination) {
                ++this->_current;
            } else {
                --this->_current;
            }
            // Serial.print("Joint ");
            // Serial.print(this->_servo_num);
            // Serial.print(" - current pos: ");
            // Serial.println(this->_current);
        }
    }
}

/**
 * @brief Check if the joint is moving by checking if it has a valid destination or immediate target
 * 
 * @return true 
 * @return false 
 */
bool RobotJoint::isMoving() {
    return this->_valid_destination || this->_valid_immediate_target;
}