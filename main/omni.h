#pragma once

#include "motor.h"

class Omni {
    public:
    Omni(Motor& motor1, Motor& motor2, Motor& motor3);
    void move(float vx, float vy, float vtheta);
    const float _k_motor1 = 1.2;
    const float _k_motor2 = 1.2;
    const float _k_motor3 = 1.2;

    private:
    const int _threshold = 20;
    int _vtheta = 0;

    Motor& _motor1;
    Motor& _motor2;
    Motor& _motor3;
};
