#pragma once
#include <Wire.h>

class Arm {
    public:
    Arm(int addr);
    void move(int y1, int y2);

    protected:
    int _addr;
    int _height;
    int _degree;
};
