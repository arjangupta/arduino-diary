// This class defines a joint of the 6 DoF robot arm

#ifndef ROBOTJOINT_HPP

#define ROBOTJOINT_HPP

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

class RobotJoint {

public:
    RobotJoint(uint8_t servo_num, uint16_t min, uint16_t max, Adafruit_PWMServoDriver* pwm);
    void setTargetAngle(uint16_t destination);
    void setImmediateTarget(uint16_t destination);
    bool isMoving();
    void propagate();
private:
    uint8_t _servo_num;
    uint16_t _min;
    uint16_t _max;
    uint16_t _destination;
    uint16_t _immediate_target;
    uint16_t _current;
    bool _valid_destination;
    bool _valid_immediate_target;
    Adafruit_PWMServoDriver* _pwm;
};

#endif // ROBOTJOINT_HPP