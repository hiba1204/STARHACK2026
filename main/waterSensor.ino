#include <Arduino.h>
#include "waterSensor.h"

WaterLevelSensor::WaterLevelSensor(int pin, int threshold)
  : pin_(pin), threshold_(threshold) {
}

int WaterLevelSensor::begin() {
  pinMode(pin_, INPUT);
  return 1;
}

int WaterLevelSensor::readLevel() {
  long level = 0;

  for (int i = 0; i < 15; i++) {
    level += analogRead(pin_);
  }

  return level / 15;
}

int WaterLevelSensor::isSubmerged() {
  return readLevel() >= threshold_;
}