#pragma once

#include "motor.h"

class Omni {
    public:
    Omni(Motor* motor1, Motor* motor2, Motor* motor3);
    void move(float vx, float vy, float vtheta);

    private:
    Motor* _motor1;
    Motor* _motor2;
    Motor* _motor3;
};
