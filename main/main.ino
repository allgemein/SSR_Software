#include "arm.h"
#include "controller.h"
#include "debug.h"
#include "linetracer.h"
#include "motor.h"
#include "omni.h"
#include "pin.h"

void setup()
{
    Serial.begin(115200);
    PS4.begin("1a:2b:3c:01:01:01");
}

// コントローラのペアリング先のMACアドレスを入れる
Controller ctl;

Motor motor1(0, pin::pwm1, pin::dir1);
Motor motor2(1, pin::pwm2, pin::dir2);
Motor motor3(2, pin::pwm3, pin::dir3);

Arm arm();

Omni omni(motor1, motor2, motor3);

LineTracer lt(omni);
Debug debug(motor1, motor2, motor3, omni);
void loop()
{
    //    Serial.println("loop...");
    ctl.update();
    //    ctl.print();

    //    debug.debug(true, false);
    if (ctl.isAuto)
    {
        lt.trace();
        //         debug.debug(false, true);
    }
    else
    {
        omni.move(-ctl.vx, -ctl.vy, ctl.vTheta);
        arm.move(ctl.Height1, ctl.Height2);
    }
    delay(10);
}
