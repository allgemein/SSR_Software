#pragma once
#include <PS4Controller.h>

class Controller {
    public:
    Controller();
    void update();
    void print();
    int vx = 0;
    int vy = 0;
    int vTheta = 0;
    int Height1 = 0;
    int Height2 = 0;
    bool isAuto = false;

    protected:
    int px = 0;
    int py = 0;
    int pTheta = 0;
    int pHeight1 = 0;
    int pHeight2 = 0;
    const float kTheta = 1;
    const float kHeight = 1;
};
