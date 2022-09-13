#include "omni.h"

Omni::Omni(Motor& motor1, Motor& motor2, Motor& motor3)
    : _motor1(motor1), _motor2(motor2), _motor3(motor3) {}
void Omni::move(float vx, float vy, float vtheta) {
    float r = 0.0;
    if (vx < _threshold) vx = 0;
    if (vy < _threshold) vy = 0;
    // motor1
    // vx + rvtheta
    float v1 = vx + r * vtheta;
    float speed1 = v1 * 2 * _k_motor1;
    _motor3.setSpeed(speed1);

    // motor2
    // -(1/2)vx + (√3/2)vy + rvtheta
    float v2 = -0.5 * vx + (1.73 / 2) * vy + r * vtheta;
    float speed2 = v2 * 2 * _k_motor2;
    _motor1.setSpeed(speed2);
    // motor2
    // -(1/2)vx - √3/2vy + rvtheta
    float v3 = -0.5 * vx - (1.73 / 2) * vy + r * vtheta;
    float speed3 = v3 * 2 * _k_motor3;
    _motor2.setSpeed(speed3);

    // Serial.println(v1);
    // Serial.println(v2);
    // Serial.println(v3);
}
