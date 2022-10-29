#include "arm.h"

Arm::Arm() {
    pinMode(5, OUTPUT);
    pinMode(16, OUTPUT);
    digitalWrite(16, LOW);
    digitalWrite(5, LOW);
}
void Arm::move(int y1, int y2) {
    // char cmd[64];
    // sprintf(cmd, "%2d,%2d\n", y1, y2);
    // Serial2.println(cmd);
    switch (y1) {
        case 1:
            digitalWrite(16, HIGH);
            digitalWrite(5, LOW);
        case -1:
            digitalWrite(16, LOW);
            digitalWrite(5, HIGH);
        default:
            digitalWrite(16, LOW);
            digitalWrite(5, LOW);
    }
}
