#pragma once

namespace pin {
const int dir1 = 17;  // GPIOの仕様上だめだったので変えた。J3
const int dir2 = 12;  // J8
const int dir3 = 26;  // J7
const int pwm1 = 18;
const int pwm2 = 27;
const int pwm3 = 14;
// 12 27 motor2
// 26 14 motor3
// 17 18 motor1
//const int dir1 = 12;  // GPIOの仕様上だめだったので変えた。J3
//const int dir2 = 26;  // J8
//const int dir3 = 17;  // J7
//const int pwm1 = 27;
//const int pwm2 = 14;
//const int pwm3 = 18;

const int sensorR = 34;
const int sensorC = 32;
const int sensorL = 25;
const int inL = 25;
const int inC = 32;
const int inR = 34;
}  // namespace pin
