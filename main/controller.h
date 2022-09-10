#pragma once
#include <PS4Controller.h>

class Controller {
    public:
    Controller(const char* addr);
    void update();
    float vx = 0;
    float vy = 0;
    float vtheta = 0;
    float vHeight1 = 0;
    float vHeight2 = 0;
    bool isAuto = false;

    protected:
    float px = 0;
    float py = 0;
    float ptheta = 0;
    float pHeight1 = 0;
    float pHeight2 = 0;
};
