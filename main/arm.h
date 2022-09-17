#pragma once
#include <SoftwareSerial.h>

#define MYPORT_TX 21
#define MYPORT_RX 13

class Arm {
    public:
    Arm();
    SoftwareSerial SSerial;
    void move(int y1, int y2);
};
