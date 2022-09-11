#pragma once
#include "omni.h"

class LineTracer {
    public:
    LineTracer(Omni& omni);
    void trace();

    private:
    Omni& _omni;
};
