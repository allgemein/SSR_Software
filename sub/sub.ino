#include <Wire.h>

#include "pin.h"
#include "screw.h"

Screw s1(pin::stepper1_A, pin::stepper1_B, pin::stepper1_C, pin::stepper1_D);
Screw s2(pin::stepper2_A, pin::stepper2_B, pin::stepper2_C, pin::stepper2_D);

void setup() {
    Wire.begin(uint8_t(8), 21, 22);
    Serial.begin(115200);
    Wire.onReceive(onReceive);
}

void loop() {
    s1.move();
    s2.move();
    delay(100);
}

void onReceive(int num_bytes) {
    String s_y1, s_y2;
    while (Wire.available()) {
        s_y1 = Wire.readStringUntil(',');
        s_y2 = Wire.readStringUntil('\n');
    }
    s1.y = s_y1.toInt();
    s2.y = s_y2.toInt();
}
