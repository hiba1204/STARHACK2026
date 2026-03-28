#pragma once
#include "distanceSensor.h"

class HorizontalDistanceSensor : public Sensor {
  public:
    HorizontalDistanceSensor(int trig, int echo) : Sensor(trig, echo) {}

    const char* getType() override;
};
