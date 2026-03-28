#pragma once
#include "DistanceSensor.h"

class VerticalDistanceSensor : public Sensor {
  public:
    VerticalDistanceSensor(int trig, int echo) : Sensor(trig, echo) {}

    const char* getType() override {
      return "Vertical";
    }
};