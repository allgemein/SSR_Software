#include "arm.h"

Arm::Arm(int addr) {
    Wire.begin();
    _addr = addr;
}
void Arm::move(int y1, int y2) {
    Wire.beginTransmission(_addr);
    char cmd[64];
    sprintf(cmd, "%2d,%2d\n", y1, y2);
    Wire.write(cmd);
    Wire.endTransmission();
}
