#include <Wire.h>

#include "pin.h"
#include "screw.h"

Screw s1(pin::stepper1_A, pin::stepper1_B, pin::stepper1_C, pin::stepper1_D);
Screw s2(pin::stepper2_A, pin::stepper2_B, pin::stepper2_C, pin::stepper2_D);

void setup() {
    Wire.begin(8);
    Serial.begin(115200);
    Wire.onReceive(onReceive);
}

void loop() {
    Serial.print(s1.y());
    Serial.print(", ");
    Serial.println(s2.y());
    delay(500);
}

void onReceive(int num_bytes) {
    String s_h1, s_h2;
    while (Wire.available()) {
        s_h1 = Wire.readStringUntil(',');
        s_h2 = Wire.readStringUntil('\n');
    }
    int h1, h2;
    h1 = s_h1.toInt();
    h2 = s_h2.toInt();
    s1.move(h1);
    s2.move(h2);
}
