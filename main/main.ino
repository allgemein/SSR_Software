#include "arm.h"
#include "controller.h"
#include "linetracer.h"
#include "motor.h"
#include "omni.h"
#include "pin.h"

void setup() {
    Serial.begin(115200);
    PS4.begin("1a:2b:3c:01:01:01");
}

// コントローラのペアリング先のMACアドレスを入れる
Controller ctl;

Motor motor1(0, pin::pwm1, pin::dir1);
Motor motor2(1, pin::pwm2, pin::dir2);
Motor motor3(2, pin::pwm3, pin::dir3);

Arm arm(8);

Omni omni(motor1, motor2, motor3);

LineTracer lt(omni);

void loop() {
    Serial.println("loop...");
    ctl.update();
    ctl.print();
    if (ctl.isAuto) {
        lt.trace();
    } else {
        // motor1.setSpeed(100);
        // motor2.setSpeed(100);
        // motor3.setSpeed(100);
        // delay(5000);
        // motor1.setSpeed(0);
        // motor2.setSpeed(0);
        // motor3.setSpeed(0);
        // delay(2000);
        omni.move(ctl.vx, ctl.vy, ctl.vTheta);
//        omni.move(127, 0, 0);
//        delay(5000);
//        omni.move(-127, 0, 0);
//        delay(5000);
//        omni.move(0, 127, 0);
//        delay(5000);
//        omni.move(0, -127, 0);
//        delay(5000);
        // arm.move(ctl.Height1, ctl.Height2);
    }
    delay(100);
}
