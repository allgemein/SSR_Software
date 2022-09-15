#include <Wire.h>

#include "pin.h"
// #include "screw.h"

hw_timer_t *timer[2];
const int initial_delay = 20;
const int acc = 5;
const int rpm = 120;
const int steps_per_rev = 200;
const int steps_per_cm = 10;  //計算して適切な値にする
const int frec = 1000 / steps_per_rev * rpm;

int target_y[2] = {0, 0};
int current_steps[2] = {0, 0};
int current_delay[2] = {initial_delay, initial_delay};

void IRAM_ATTR move(int num);
void IRAM_ATTR move1();
void IRAM_ATTR move2();

void setup() {
    Wire.begin(uint8_t(8), 21, 22);
    Serial.begin(115200);
    //タイマを作成，1msで1カウントされるように設定
    timer[0] = timerBegin(0, getApbFrequency() / 1000, true);
    timer[1] = timerBegin(1, getApbFrequency() / 1000, true);
    timerAttachInterrupt(timer[0], move1, true);
    timerAttachInterrupt(timer[1], move2, true);
}

void loop() {
    if (Wire.available()) {
        String s[2];
        s[0] = Wire.readStringUntil(',');
        s[1] = Wire.readStringUntil('\n');
        for (int i = 0; i < 2; i++) {
            target_y[i] = s[i].toInt();
        }
        move1();
        move2();
    }
    Serial.println(target_y[0]);
    delay(10);
}

void IRAM_ATTR move1() { move(0); }
void IRAM_ATTR move2() { move(1); }

void IRAM_ATTR move(int num) {
    int target_steps = target_y[num] * steps_per_cm;
    int delay = current_delay[num];  //[ms]

    if (target_steps == current_steps[num]) return;

    //目標速度まで台形に加速させるつもりで書いている
    if (target_steps > current_steps[num]) {
        delay -= acc;
        delay = min(delay, frec);
        current_steps[num]++;
    } else {
        delay += acc;
        delay = max(delay, 0);
        current_steps[num]--;
    }

    current_delay[num] = delay;

    //タイマを設定，有効化
    timerAlarmWrite(timer[num], delay, false);
    timerAlarmEnable(timer[num]);
}
