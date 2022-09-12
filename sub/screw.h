#pragma once
#include <Stepper.h>

#include "Arduino.h"

class Screw : public Stepper {
    public:
    Screw(int A, int B, int C, int D);
    void move();
    int y = 0;

    protected:
    int _y_current = 0;
    const int _steps_per_rev = 200;
    const int _steps_per_cm = 10;  //計算して適切な値にする
};
