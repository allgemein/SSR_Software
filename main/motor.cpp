#include "motor.h"

Motor::Motor(int num, int pwm, int dir) {
    _num = num;
    _pwm = pwm;
    _dir = dir;

    ledcSetup(_num, 20000, 8);

    ledcAttachPin(_pwm, _num);
    pinMode(_dir, OUTPUT);

    ledcWrite(_num, 0);
    digitalWrite(_dir, LOW);
}

void Motor::setSpeed(int speed) {
    if (speed > 255) {
        speed = 255;
    } else if (speed < -255) {
        speed = -255;
    }

    if (speed >= 0) {
        ledcWrite(_num, speed);
        digitalWrite(_dir, LOW);
    } else {
        ledcWrite(_num, -speed);
        digitalWrite(_dir, HIGH);
    }
}
