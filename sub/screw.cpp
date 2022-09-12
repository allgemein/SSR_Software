#include "screw.h"

Screw::Screw(int A, int B, int C, int D)
    : Stepper::Stepper(steps_per_rev, A, C, B, D) {}

void Screw::move(int y) {
    step((y_current - y) * steps_per_cm);
    y_current = y;
}

int Screw::y() { return y_current; }
