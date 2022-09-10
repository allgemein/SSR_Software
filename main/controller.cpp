#include "controller.h"

Controller::Controller(const char* addr) { PS4.begin(addr); }
void Controller::update() {}
