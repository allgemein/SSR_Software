#include "arm.h"
#include "controller.h"
#include "linetracer.h"
#include "motor.h"
#include "omni.h"
#include "pin.h"

void setup() {}

// コントローラのペアリング先のMACアドレスを入れる
Controller ctl("1a:2b:3c:01:01:01");

Motor motor1(pin::pwm1, pin::dir1);
Motor motor2(pin::pwm2, pin::dir2);
Motor motor3(pin::pwm3, pin::dir3);

Arm arm1(0);
Arm arm2(1);

Omni omni(&motor1, &motor2, &motor3);

LineTracer lt(&omni);

void loop() {
    ctl.update();
    if (ctl.isAuto) {
        lt.trace();
    } else {
        omni.move(ctl.vx, ctl.vy, ctl.vtheta);
        arm1.move(ctl.vHeight1);
        arm2.move(ctl.vHeight2);
    }
}
