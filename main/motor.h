#pragma once
#include <Arduino.h>

class Motor {
    public:
    Motor(int pwm, int dir);
    void move(int distance);
    void setSpeed(int speed);

    protected:
    int _pwm;
    int _dir;
};
