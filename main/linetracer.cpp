#include "linetracer.h"
#include "pin.h"

LineTracer::LineTracer(Omni &omni) : _omni(omni)
{
  _step = 0;
  pinMode(pin::sensorR, INPUT);
  pinMode(pin::sensorC, INPUT);
  pinMode(pin::sensorL, INPUT);
}

void LineTracer::trace()
{
  float slide_speed = 0.0;
  float forward_speed = -100.0;
  int rotate_delay = 380;
  bool r = !digitalRead(pin::sensorR);
  bool c = !digitalRead(pin::sensorC);
  bool l = !digitalRead(pin::sensorL);
  // 左センサーのみ
  // 左回転強
  if (!l && !c && r)
  {
    slide_speed = -40.0;
  }

  // 左・中央センサー
  // 左回転弱
  else if (!l && c && r)
  {
    slide_speed = -20.0;
  }

  // 右・中央センサー
  // 右回転弱
  else if (l && c && !r)
  {
    slide_speed = 20.0;
  }

  // 右センサーのみ
  // 右回転強
  else if (l && !c && !r)
  {
    slide_speed = 40.0;
  }
  // コーナー
  if (l && c && r)
  {
    _step++;
    forward_speed = 0.0;
    rotate_speed = 0.0;
    slide_speed = 0.0;
    if (_step == 1)
    {
      rotate_speed = 0.0;
    }
    else if (_step == 2)
    {
      rotate_speed = 30.0;
    }
    else if (_step == 3)
    {
      rotate_speed = 30.0;
    }
    else if (_step == 4)
    {
      rotate_speed = -30;
    }
    _omni.move(0, 0, rotate_speed);
    delay(380);
    _omni.move(0, -50, 0);
    delay(800);
  }
  _omni.move(slide_speed, forward_speed, 0);
}
void LineTracer::reset()
{
  _step = 0;
}
