#include <SoftwareSerial.h>
#include <Wire.h>

#include "pin.h"
// #include "screw.h"
#define MYPORT_TX 21
#define MYPORT_RX 13

const int delay_us = 5000;
const int steps_per_rev = 200;
const int steps_per_cm = (10 / 2) * steps_per_rev;  //ピッチは2mm

const int pins[2][4] = {
    {pin::stepper1_A, pin::stepper1_C, pin::stepper1_B, pin::stepper1_D},
    {pin::stepper2_A, pin::stepper2_C, pin::stepper2_B, pin::stepper2_D}};

const bool pulse[4][4] = {
    {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}};

int target_y[2] = {0, 0};
int current_steps[2] = {0, 0};
int current_ex[2] = {0, 0};

const bool debug = false;

SoftwareSerial SSerial;

void setup() {
    //通信開始
    Wire.begin(uint8_t(8), 21, 22);
    Serial.begin(115200);
    SSerial.begin(115200);

    //出力ピンを設定
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++) pinMode(pins[i][j], OUTPUT);
}

void loop() {
    if (debug) {
        if (Serial.available()) {
            String s[3];
            bool is_cclockwise = false;
            s[0] = Serial.readStringUntil(',');
            s[1] = Serial.readStringUntil(',');
            s[2] = Serial.readStringUntil('\n');
            int motor_num = s[0].toInt();
            int delay_us = s[1].toInt();
            int times = s[2].toInt();
            if (times < 0) {
                is_cclockwise = true;
                times = -times;
            }
            for (int i = 0; i < times; i++) {
                for (int j = 0; j < 4; j++) {
                    int step = j;
                    if (is_cclockwise) step = 3 - j;
                    for (int k = 0; k < 4; k++) {
                        if (pulse[step][k]) {
                            digitalWrite(pins[motor_num][k], HIGH);
                            Serial.print("1 ");
                        } else {
                            digitalWrite(pins[motor_num][k], LOW);
                            Serial.print("0 ");
                        }
                    }
                    Serial.println();
                    delayMicroseconds(delay_us);
                }
            }
        }
    } else {
        if (SSerial.available()) {  //データがあったら読み取り
            String s[2];
            s[0] = Wire.readStringUntil(',');   //モータ1の位置[cm]
            s[1] = Wire.readStringUntil('\n');  //モータ2
            Serial.print(s[0]);
            Serial.println(s[1]);
            for (int motor_num = 0; motor_num < 2; motor_num++) {
                target_y[motor_num] = s[motor_num].toInt();  //数値に変換
            }
        }

        //(ほぼ)特定周期ごとにパルスを出して回す
        for (int motor_num = 0; motor_num < 2; motor_num++) {
            // cmからステップ数に変換
            int target_steps = target_y[motor_num] * steps_per_cm;

            //目標に達していたら処理しない
            if (target_steps == current_steps[motor_num]) continue;

            //パルスを出力
            for (int pin = 0; pin < 4; pin++) {
                if (pulse[current_ex[motor_num]][pin]) {
                    digitalWrite(pins[motor_num][pin], HIGH);
                } else {
                    digitalWrite(pins[motor_num][pin], LOW);
                }
            }

            if (target_steps > current_steps[motor_num]) {  //正転
                //現在位置を更新
                current_steps[motor_num]++;
                //励磁の状態を更新(4まで行ったら0に戻る)
                current_ex[motor_num] = (motor_num >= 4 ? 0 : motor_num + 1);
            } else {  //逆転
                current_steps[motor_num]--;
                current_ex[motor_num] = (motor_num < 0 ? 4 : motor_num - 1);
            }

            //周期ぶん待つ
            delayMicroseconds(delay_us);
        }
    }
}
