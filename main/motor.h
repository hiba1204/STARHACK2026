#pragma once
#include <Arduino.h>
#include <Servo.h>

class Motor {
public:
  Motor(uint8_t pin);
  
  void begin();
  void on();
  void off();
  void slowVibration();
  void normalVibration();
  void fastVibration();

private:
  uint8_t pin_;
  Servo servo_;
}