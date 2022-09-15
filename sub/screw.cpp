#include "screw.h"

Screw::Screw(int A, int B, int C, int D)
    : Stepper::Stepper(_steps_per_rev, A, C, B, D) {}

void Screw::move() {
    if (y == _y_current) return;
    step((_y_current - y) * _steps_per_cm);
    _y_current = y;
    Serial.println(y);
}
