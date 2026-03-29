#include "distanceSensor.h"

float SOUND_WAVE_TRIP_SPEED = 0.0343f / 2.0f;

Sensor::Sensor(int trig, int echo) {
  trigPin = trig;
  echoPin = echo;
}

void Sensor::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

float Sensor::readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);

  if (duration == 0) return -1.0f;

  float distance = duration * SOUND_WAVE_TRIP_SPEED;

  if (distance < 2.0f || distance > 400.0f) {
    return -1.0f;
  }

  return distance;
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