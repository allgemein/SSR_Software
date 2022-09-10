#include "motor.h"

Motor::Motor(int pwm, int dir) {
    _pwm = pwm;
    _dir = dir;

    ledcSetup(0, 20000, 8);

    ledcAttachPin(_pwm, 0);
    pinMode(_dir, OUTPUT);

    ledcWrite(0, 0);
    digitalWrite(_dir, LOW);
}

void Motor::setSpeed(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }

    if (speed >= 0) {
        ledcWrite(0, speed);
        digitalWrite(_dir, LOW);
    } else {
        ledcWrite(0, -speed);
        digitalWrite(_dir, HIGH);
    }
}
