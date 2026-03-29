#pragma once
#include <Arduino.h>

class Motor {
public:
  Motor(uint8_t pin);

  void begin();
  void off();

  void setIntensity(uint8_t value); 
  void slow();
  void medium();
  void fast();

  void updateFromDistance(long distance);

private:
  uint8_t pin_;
};