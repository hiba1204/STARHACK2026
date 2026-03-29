#include "Motor.h"

Motor::Motor(uint8_t pin) : pin_(pin) {}

void Motor::begin() {
  servo_.attach(pin_);
}

void Motor::on() {
  servo_.write(100);
}

void Motor::off() {
  servo_.write(90); 
}

void Motor::slowVibration() {
  servo_.write(85);
  delay(100);
  servo_.write(95);
  delay(100);
}

void Motor::normalVibration() {
  servo_.write(80);
  delay(60);
  servo_.write(100);
  delay(200);
}

void Motor::fastVibration() {
  servo_.write(70);
  delay(30);
  servo_.write(110);
  delay(30);
}