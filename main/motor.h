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

  const char* getModeName() const;
  uint8_t getIntensity() const;

private:
  uint8_t pin_;
  uint8_t pwm_;
  uint8_t mode_;
  bool outputOn_;
  unsigned long lastToggleMs_;
  unsigned long onTimeMs_;
  unsigned long offTimeMs_;

  void applyOutput(bool on);
  void setPulseProfile(uint8_t mode, uint8_t pwm, unsigned long onMs, unsigned long offMs, unsigned long now);
};