#pragma once
#include <Stepper.h>

class Screw : public Stepper {
    public:
    Screw(int A, int B, int C, int D);
    void move(int y);
    int y();

    protected:
    int y_current = 0;
    const int steps_per_rev = 200;
    const int steps_per_cm = 10;  //計算して適切な値にする
};
