#include <Wire.h>

#include "pin.h"
// #include "screw.h"

hw_timer_t *timer[2];
const int initial_delay = 1000;
const int acc = 10;
const int rpm = 120;
const int steps_per_rev = 200;
const int steps_per_cm = 100;  //計算して適切な値にする
const int frec = 1000000 / steps_per_rev * rpm;

const int pins[2][4] = {
    {pin::stepper1_A, pin::stepper1_B, pin::stepper1_C, pin::stepper1_D},
    {pin::stepper2_A, pin::stepper2_B, pin::stepper2_C, pin::stepper2_D}};

volatile int target_y[2] = {0, 0};
volatile int current_steps[2] = {0, 0};
volatile int current_delay[2] = {initial_delay, initial_delay};
volatile int current_ex[2] = {0, 0};

void IRAM_ATTR move(int num);
void IRAM_ATTR move1();
void IRAM_ATTR move2();

void setup() {
    Wire.begin(uint8_t(8), 21, 22);
    Serial.begin(115200);
    //タイマを作成，1usで1カウントされるように設定
    timer[0] = timerBegin(0, 80, true);
    timer[1] = timerBegin(1, 80, true);
    timerAttachInterrupt(timer[0], move1, true);
    timerAttachInterrupt(timer[1], move2, true);
}

void loop() {
    if (Serial.available()) {
        String s[2];
        s[0] = Serial.readStringUntil(',');
        s[1] = Serial.readStringUntil('\n');
        for (int i = 0; i < 2; i++) {
            target_y[i] = s[i].toInt();
        }
        move1();
        move2();
    }
    // Serial.println(current_steps[0]);
    // delay(1);
}

//割り込みで呼ぶ関数は引数を取れないため
void IRAM_ATTR move1() { move(0); }
void IRAM_ATTR move2() { move(1); }

void IRAM_ATTR move(int num) {
    int target_steps = target_y[num] * steps_per_cm;
    int delay = current_delay[num];  //[ms]

    if (target_steps == current_steps[num]) return;

    for (int i = 0; i < 4; i++) {
        if (i == current_ex[num])
            digitalWrite(pins[num][i], LOW);
        else
            digitalWrite(pins[num][i], HIGH);
    }

    //目標速度まで台形に加減速させるつもりで書いている
    if (target_steps > current_steps[num]) {
        //加速
        delay -= acc;
        //最大速度に制限
        delay = min(delay, frec);
        //現在位置を更新
        current_steps[num]++;
        //励磁の状態を更新(4まで行ったら0に戻る)
        current_ex[num] = (num >= 4 ? 0 : num + 1);
    } else {
        //逆転ver
        delay += acc;
        delay = max(delay, 0);
        current_steps[num]--;
        current_ex[num] = (num < 0 ? 4 : num - 1);
    }

    current_delay[num] = delay;

    //タイマを設定，有効化
    timerWrite(timer[num], 0);
    timerAlarmWrite(timer[num], delay, false);
    timerAlarmEnable(timer[num]);
}
