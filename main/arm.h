#pragma once
#include <SoftwareSerial.h>

#define MYPORT_TX 23
#define MYPORT_RX 22

class Arm {
    public:
    Arm();
    //SoftwareSerial SSerial;
    void move(int y1, int y2);
};
