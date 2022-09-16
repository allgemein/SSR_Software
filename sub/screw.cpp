// #include "screw.h"
//
// Screw::Screw(int ch, int A, int B, int C, int D)
//     : _frec(1000 / _rpm * _steps_per_rev) {
//     //タイマを作成，1msで1カウントされるように設定
//     timer = timerBegin(ch, getApbFrequency() / 1000, true);
//     //割り込みに関数を割り当てる
//     timerAttachInterrupt(timer, &Screw::wrapper, this, true);
// }
//
// static void IRAM_ATTR Screw::wrapper(Screw* ptr) { ptr->move(); }
//
// void IRAM_ATTR Screw::move() {
//     int target_steps = y * _steps_per_cm;
//     int delay = _current_delay;  //[ms]
//
//     if (target_steps == _steps_current) return;
//
//     //目標速度まで台形に加速させるつもりで書いている
//     if (target_steps > _steps_current) {
//         delay -= _acc;
//         delay = min(delay, 0);
//         _steps_current++;
//     } else {
//         delay += _acc;
//         delay = max(delay, _frec);
//         _steps_current--;
//     }
//
//     //タイマを設定，有効化
//     timerAlarmWrite(timer, delay, false);
//     timerAlarmEnable(timer);
// }
