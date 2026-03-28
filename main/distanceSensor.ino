#include "distanceSensor.h"

Sensor::Sensor(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;
}

void Sensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float Sensor::readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2.0;
}

void Sensor::printReading() {
  float distance = readDistanceCm();

  Serial.print(getType());
  Serial.print(" distance: ");

  if (distance < 0) {
    Serial.println("No reading");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}
