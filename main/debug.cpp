#include "debug.h"

Debug::Debug(Motor& motor1, Motor& motor2, Motor& motor3, Omni& omni)
    : _motor1(motor1), _motor2(motor2), _motor3(motor3), _omni(omni) {}

void Debug::debug(bool check_motor, bool check_omni) {
    if (check_motor) {
        //         モーター1正転
        Serial.println("13-A");
        _motor1.setSpeed(100);
        _motor3.setSpeed(100);
        delay(2000);
        _motor1.setSpeed(0);
        _motor3.setSpeed(0);
        delay(2000);
        // モーター1逆転
        Serial.println("13-B");
        _motor1.setSpeed(-100);
        _motor3.setSpeed(-100);
        delay(2000);
        _motor1.setSpeed(0);
        _motor3.setSpeed(0);
        delay(2000);
        Serial.println("1-A");
        _motor1.setSpeed(100);
        delay(2000);
        // モーター1逆転
        Serial.println("1-B");
        _motor1.setSpeed(-100);
        delay(2000);
        _motor1.setSpeed(0);
        // // モーター2正転
        // Serial.println("2-A");
        // _motor2.setSpeed(100);
        // delay(2000);
        // // モーター2逆転
        // Serial.println("2-B");
        // _motor2.setSpeed(-100);
        // delay(2000);
        // _motor2.setSpeed(0);
        // // モーター3正転
        Serial.println("3-A");
        _motor3.setSpeed(100);
        delay(2000);
        _motor3.setSpeed(0);
        // モーター3逆転
        Serial.println("3-B");
        _motor3.setSpeed(-100);
        delay(2000);
        _motor3.setSpeed(0);
    }
    if (check_omni) {
        // 前進
        _omni.move(0, 100.0f, 0);
        delay(2000);
        // 後進
        _omni.move(0, -100.0f, 0);
        delay(2000);
        delay(2000);
        // 右
        _omni.move(100.0f, 0.0f, 0.0f);
        delay(2000);
        _omni.move(0.0f, 0.0f, 0.0f);
        delay(2000);
        // 左
        _omni.move(-100.0f, 0.0f, 0.0f);
        delay(2000);
        _omni.move(0.0f, 0.0f, 0.0f);
        delay(2000);
        // 時計回り
        _omni.move(0, 0, 100);
        delay(2000);
        // 反時計回り
        _omni.move(0, 0, 100);
        delay(2000);
    }
}
