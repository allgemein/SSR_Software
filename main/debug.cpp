#include "debug.h"
    
Debug::Debug(Motor& motor1, Motor& motor2, Motor& motor3, Omni& omni) 
    :  _motor1(motor1), _motor2(motor2), _motor3(motor3), _omni(omni) {}

void Debug::debug(bool check_omni, bool check_motor) {
    if (check_omni){
        delay(2000);
        // 前進
        _omni(100, 0, 0);
        delay(2000);
        // 後進
        _omni(-100, 0, 0);
        delay(2000);
        // 右
        _omni(0, 100, 0);
        delay(2000);
        // 左
        _omni(0, -100, 0);
        delay(2000);
        // 時計回り
        _omni(0, 0, 1)
        delay(2000);        
        // 反時計回り
        _omni(0, 0, 1)
        delay(2000);
    }
    if (check_motor){
        // モーター1正転
        _motor1.setSpeed(100);
        delay(2000);
        // モーター1逆転
        _motor1.setSpeed(-100);
        delay(2000);
        // モーター2正転
        _motor2.setSpeed(100);
        delay(2000);
        // モーター2逆転
        _motor2.setSpeed(-100);
        delay(2000);
        // モーター3正転
        _motor3.setSpeed(100);
        delay(2000);
        // モーター3逆転
        _motor3.setSpeed(-100);
        delay(2000);
    }
}
