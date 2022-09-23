#include "arm.h"

Arm::Arm()
{ // SSerial.begin(115200); }
}
void Arm::move(int y1, int y2)
{
    char cmd[64];
    sprintf(cmd, "%2d,%2d\n", y1, y2);
    // SSerial.write(cmd);
}
