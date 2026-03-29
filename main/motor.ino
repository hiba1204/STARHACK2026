#include "motor.h"

Motor::Motor(uint8_t pin) : pin_(pin) {}

void Motor::begin() {
  pinMode(pin_, OUTPUT);
  analogWrite(pin_, 0);
}

void Motor::off() {
  analogWrite(pin_, 0);
}

void Motor::setIntensity(uint8_t value) {
  analogWrite(pin_, value);
}

void Motor::slow() {
  analogWrite(pin_, 80);
}

void Motor::medium() {
  analogWrite(pin_, 150);
}

void Motor::fast() {
  analogWrite(pin_, 255);
}

void Motor::updateFromDistance(long distance) {
  if (distance < 20)
    fast();     // danger proche
  
  else if (distance < 40)
    medium();   // attention
  
  else
    off();      // rien
}