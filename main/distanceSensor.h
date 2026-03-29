#pragma once
#include <Arduino.h>

class Sensor {
  protected:
    int trigPin;
    int echoPin;

  public:
    Sensor(int trig, int echo);

    void begin();

    float readDistanceCm();

    virtual const char* getType() = 0;

    void printReading();
};