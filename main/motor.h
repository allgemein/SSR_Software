#pragma once
#include <Arduino.h>

class Motor {
    public:
    Motor(int num, int pwm, int dir);
    void move(int distance);
    void setSpeed(int speed);

    protected:
    int _num;
    int _pwm;
    int _dir;
};
