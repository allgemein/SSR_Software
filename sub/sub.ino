#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#include "pin.h"
// #include "screw.h"

int delay_us = 4000;
const int steps_per_rev = 200;
const int steps_per_cm = (10 / 2) * steps_per_rev;  //ピッチは2mm

const int pins[2][4] = {
    {pin::stepper1_A, pin::stepper1_C, pin::stepper1_B, pin::stepper1_D},
    {pin::stepper2_A, pin::stepper2_C, pin::stepper2_B, pin::stepper2_D}};

const bool pulse[4][4] = {
    {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}};

float target_y[2] = {0, 0};
int current_steps[2] = {0, 0};
int current_ex[2] = {0, 0};

void move(int motor_num, int delay_us, int times);
const int num_pixels = 20;
const float speed = 0.2;

Adafruit_NeoPixel LED1(num_pixels, 25, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel LED2(num_pixels, 27, NEO_GRB + NEO_KHZ800);
const bool debug = true;

void setup() {
    //通信開始
    Serial.begin(115200);
    // Serial2.begin(9600, SERIAL_8N1, 17, 18);
    pinMode(18, INPUT);
    pinMode(17, INPUT);

    //出力ピンを設定
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++) pinMode(pins[i][j], OUTPUT);
    pinMode(0, INPUT);
    Serial.println("setup");
    LED1.clear();
    LED2.clear();
    // pinMode(8, INPUT);
}

// bool flag = true;

void loop() {
    // Serial.println("loop");
    // if (digitalRead(0) == HIGH) {
    //     if (flag) {
    //         move(0, 1500, 400);
    //     } else {
    //         move(0, 1500, -400);
    //     }
    //     flag = !flag;
    // }
    // }
    // else {
    // }
    // if (Serial.available()) {
    //     Serial.println("rec");
    //     String s[3];
    //     s[0] = Serial.readStringUntil(',');
    //     s[1] = Serial.readStringUntil(',');   //モータ1の位置[cm]
    //     s[2] = Serial.readStringUntil('\n');  //モータ2
    //     Serial.println(s[2]);
    //     move(s[0].toInt(), s[1].toInt(), s[2].toInt());
    // }
    if (Serial.available()) {  //データがあったら読み取り
        String s[3];
        s[0] = Serial.readStringUntil(',');   //モータ1の位置[cm]
        s[1] = Serial.readStringUntil('\n');  //モータ2の位置[cm]
        // s[2] = SSerial.readStringUntil('\n');  //回転速度
        Serial.println("rec");
        Serial.print(s[0]);
        Serial.println(s[1]);
        delay_us = s[2].toInt();
        for (int motor_num = 0; motor_num < 2; motor_num++) {
            target_y[motor_num] = s[motor_num].toInt();
            //数値に変換
        }
    }
    int dir1 = digitalRead(18);
    int dir2 = digitalRead(17);
    if (dir1) target_y[0] += speed;
    if (dir2) target_y[0] -= speed;

    //(ほぼ) 特定周期ごとにパルスを出して回す
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
            current_ex[motor_num] =
                (current_ex[motor_num] >= 4 ? 0 : current_ex[motor_num] + 1);
        } else {  //逆転
            current_steps[motor_num]--;
            current_ex[motor_num] =
                (current_ex[motor_num] <= 0 ? 4 : current_ex[motor_num] - 1);
        }
    }
    for (int i = 0; i < num_pixels; i++) {
        LED1.setPixelColor(i, LED1.Color(80, 20, 0));
        LED2.setPixelColor(i, LED2.Color(0, 80, 20));
    }

    LED1.show();
    LED2.show();
    //周期ぶん待つ
    delayMicroseconds(delay_us);
}

void move(int motor_num, int delay_us, int times) {
    bool is_cclockwise = false;
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
                } else {
                    digitalWrite(pins[motor_num][k], LOW);
                }
            }
            // Serial.println(j);
            delayMicroseconds(delay_us);
        }
    }
}
