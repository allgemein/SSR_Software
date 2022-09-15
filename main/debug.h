#pragma once
#include "omni.h"
#include "motor.h"

class Debug {
    public:
    Debug(Motor& motor1, Motor& motor2, Motor& motor3, Omni& omni);
    void debug(bool check_motor, bool check_omni);

    private:
    Omni& _omni;

    Motor& _motor1;
    Motor& _motor2;
    Motor& _motor3;
};
