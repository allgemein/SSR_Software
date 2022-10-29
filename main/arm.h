#pragma once
#include <HardwareSerial.h>

class Arm {
    public:
    Arm();
    void move(int y1, int y2);
};
