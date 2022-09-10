#pragma once
#include <Wire.h>

class Arm {
    private:
    int height;
    int degree;
    int id;

    public:
    Arm(unsigned int id);
    void move(int vh);
};
