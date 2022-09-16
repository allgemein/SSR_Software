#include "controller.h"

Controller::Controller() {
    _timer = timerBegin(0, 80, true);
    timerAttachInterrupt(_timer, &change_accept_flag, true);
    accept_circle_button = true;
}

volatile bool Controller::accept_circle_button;

void Controller::update() {
    if (!PS4.isConnected()) {
        Serial.println("Not Connected to controller");
    }

    if (PS4.Up()) {
        if (PS4.Cross())
            Height1 = 30;
        else
            Height2 = 30;
    }
    if (PS4.Down()) {
        if (PS4.Cross())
            Height1 = 0;
        else
            Height2 = 0;
    }

    vTheta = 0;

    if (PS4.L1()) vTheta = -1;
    if (PS4.R1()) vTheta = 1;

    if (PS4.Circle()) {
        if (accept_circle_button) {
            isAuto = !isAuto;
            accept_circle_button = false;
            timerAlarmWrite(_timer, 1000000, false);
            timerWrite(_timer, 0);
            timerAlarmEnable(_timer);
        }
    }

    if (PS4.LStickY()) {
        if (PS4.L2()) Height1 += kHeight * PS4.LStickY();
        if (PS4.R2()) Height1 += kHeight * PS4.LStickY();
    }

    vx = vy = 0;

    if (PS4.RStickX()) {
        vx = PS4.RStickX();
    }
    if (PS4.RStickY()) {
        vy = PS4.RStickY();
    }
}

void Controller::print() {
    Serial.print("vx: ");
    Serial.print(vx);
    Serial.print(", vy: ");
    Serial.print(vy);
    Serial.print(", vTheta: ");
    Serial.print(vTheta);
    Serial.print(", Height1: ");
    Serial.print(Height1);
    Serial.print(", Height2: ");
    Serial.println(Height2);
}

void IRAM_ATTR Controller::change_accept_flag() { accept_circle_button = true; }
