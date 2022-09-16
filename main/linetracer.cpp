#include "linetracer.h"
#include "pin.h"

LineTracer::LineTracer(Omni &omni) : _omni(omni) { _step = 1; }

void LineTracer::trace()
{
  float rotate_speed = 1.0;
  float rotate_speed_low = 0.5;
  float forward_speed = -100.0;
  float rotate_degree = 30;
  int rotate_delay = 380;
  pinMode(pin::sensorR, INPUT);
  pinMode(pin::sensorC, INPUT);
  pinMode(pin::sensorL, INPUT);
  bool l = !digitalRead(pin::sensorR);
  bool c = !digitalRead(pin::sensorC);
  bool r = !digitalRead(pin::sensorL);
  Serial.print("r: ");
  Serial.print(r);
  Serial.print("c: ");
  Serial.print(c);
  Serial.print("l: ");
  Serial.print(l);
  Serial.print("\n");
  // 左センサーのみ
  // 左回転強
  if (!r && !c && l)
  {
    rotate_speed = -40.0;
  }

  // 左・中央センサー
  // 左回転弱
  else if (!r && c && l)
  {
    rotate_speed = -20.0;
  }

  // 右・中央センサー
  // 右回転弱
  else if (r && c && !l)
  {
    rotate_speed = 20.0;
  }

  // 右センサーのみ
  // 右回転強
  else if (r && !c && !l)
  {
    rotate_speed = 40.0;
  }
  else if (r && c && l)
  {
    forward_speed = 0.0;
    _step++;
    if (_step == 1)
    {
      _omni.move(0, -50, 0);
      delay(200);
    }
    else if (_step == 2)
    {
      _omni.move(0, 0, rotate_degree);
      delay(rotate_delay);
      _omni.move(0, -50, 0);
      delay(800);
    }
    else if (_step == 3)
    {
      _omni.move(0, 0, rotate_degree);
      delay(rotate_delay);
      _omni.move(0, -50, 0);
      delay(800);
    }
    else if (_step == 4)
    {
      _omni.move(0, 0, -rotate_degree);
      delay(rotate_delay);
      _omni.move(0, -50, 0);
      delay(800);
    }
    else if (_step == 5)
    {
      _omni.move(0, -50, 0);
      delay(1000);
    }
    else if (_step == 6)
    {
    }
  }
  _omni.move(rotate_speed, forward_speed, 0);
}
