#pragma once
#include "omni.h"

class LineTracer {
    public:
    LineTracer(Omni& omni);
    void trace();
    void reset();

    private:
    Omni& _omni;
    int _step = 0;
};
