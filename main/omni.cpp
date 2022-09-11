#include "omni.h"

Omni::Omni(Motor& motor1, Motor& motor2, Motor& motor3)
    : _motor1(motor1), _motor2(motor2), _motor3(motor3) {}
void Omni::move(float vx, float vy, float vtheta) {
    float r = 1.0;
    // motor1
    // vx + rvtheta
    float v1 = vx + r * vtheta;
    _motor1.setSpeed(v1 * 256);
    // motor2
    // -(1/2)vx + (√3/2)vy + rvtheta
    float v2 = -(1 / 2) * vx + (1.73 / 2) * vy + r * vtheta;
    _motor2.setSpeed(v2 * 256);
    // motor2
    // -(1/2)vx - √3/2vy + rvtheta
    float v3 = -(1 / 2) * vx - (1.73 / 2) * vy + r * vtheta;
    _motor3.setSpeed(v3 * 256);
}
