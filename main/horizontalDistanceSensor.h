#pragma once
#include "DistanceSensor.h"

class HorizontalDistanceSensor : public Sensor {
  public:
    HorizontalDistanceSensor(int trig, int echo) : Sensor(trig, echo) {}

    const char* getType() override {
      return "Horizontal";
    }
};