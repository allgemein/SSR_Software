#include "linetracer.h"

LineTracer::LineTracer(Omni* omni) {
    _omni = omni;

}
void LineTracer::trace() {
    int rotate_speed = 10;
    // 左センサーのみ
    // 左回転強
    _omni.move(0, 0, rotate_speed);
    
    // 左・中央センサー
    // 左回転弱
    _omni.move(0, 0, rotate_speed/2);

    // 右・中央センサー
    // 右回転弱
    _omni.move(0, 0, -rotate_speed/2);

    // 右センサーのみ
    // 右回転強
    _omni.move(0, 0, -rotate_speed);

}
