#include "motor.h"

Motor::Motor(uint8_t pin)
  : pin_(pin),
    pwm_(0),
    mode_(0),
    outputOn_(false),
    lastToggleMs_(0),
    onTimeMs_(0),
    offTimeMs_(0) {}

void Motor::begin() {
  pinMode(pin_, OUTPUT);
  analogWrite(pin_, 0);
}

void Motor::applyOutput(bool on) {
  outputOn_ = on;
  analogWrite(pin_, on ? pwm_ : 0);
}

void Motor::off() {
  pwm_ = 0;
  mode_ = 0;
  onTimeMs_ = 0;
  offTimeMs_ = 0;
  lastToggleMs_ = millis();
  applyOutput(false);
}

void Motor::setIntensity(uint8_t value) {
  pwm_ = value;
  if (outputOn_) {
    analogWrite(pin_, pwm_);
  }
}

void Motor::slow()   { setIntensity(35); }
void Motor::medium() { setIntensity(50); }
void Motor::fast()   { setIntensity(70); }

void Motor::setPulseProfile(uint8_t mode, uint8_t pwm, unsigned long onMs, unsigned long offMs, unsigned long now) {
  if (mode_ != mode) {
    mode_ = mode;
    pwm_ = pwm;
    onTimeMs_ = onMs;
    offTimeMs_ = offMs;
    lastToggleMs_ = now;
    applyOutput(true);
  } else {
    pwm_ = pwm;
  }
}

void Motor::updateFromDistance(long distance) {
  unsigned long now = millis();

  if (distance <= 0 || distance > 150) {
    off();
    return;
  }

  // Much slower and gentler vibration map
  if (distance <= 12) {
    setPulseProfile(6, 75, 0, 0, now);      // continuous only when extremely close
    applyOutput(true);
    return;
  } else if (distance <= 22) {
    setPulseProfile(5, 68, 70, 500, now);
  } else if (distance <= 35) {
    setPulseProfile(4, 60, 65, 900, now);
  } else if (distance <= 50) {
    setPulseProfile(3, 52, 55, 1400, now);
  } else if (distance <= 75) {
    setPulseProfile(2, 45, 45, 2200, now);
  } else {
    setPulseProfile(1, 38, 35, 3200, now);
  }

  if (outputOn_ && (now - lastToggleMs_ >= onTimeMs_)) {
    lastToggleMs_ = now;
    applyOutput(false);
  } else if (!outputOn_ && (now - lastToggleMs_ >= offTimeMs_)) {
    lastToggleMs_ = now;
    applyOutput(true);
  }
}

const char* Motor::getModeName() const {
  switch (mode_) {
    case 1: return "VERY_SLOW";
    case 2: return "SLOW";
    case 3: return "MEDIUM";
    case 4: return "FAST";
    case 5: return "VERY_FAST";
    case 6: return "CONTINUOUS";
    default: return "OFF";
  }
}

uint8_t Motor::getIntensity() const {
  return pwm_;
}