#include "waterSensor.h"

WaterLevelSensor::WaterLevelSensor(int pin) : pin_(pin) {
}

int WaterLevelSensor::begin() {
  pinMode(pin_, INPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Système StarHack : Prêt !");
  return 1;
}

int WaterLevelSensor::readLevel() {
  long level = 0;

  for (int i = 0 ; i < 15 ; i++) {
    level += analogRead(pin_);
  }

  return level / 15;
}

int WaterLevelSensor::isSubmerged() {
  return readLevel() >= 50;
}
