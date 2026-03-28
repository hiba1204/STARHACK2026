#include "HorizontalDistanceSensor.h"
#include "VerticalDistanceSensor.h"

HorizontalDistanceSensor horizontalDistanceSensor(9, 10);
VerticalDistanceSensor verticalDistanceSensor(11, 12);

void setup() {
  Serial.begin(9600);

  horizontalDistanceSensor.begin();
  verticalDistanceSensor.begin();
}

void loop() {
  horizontalDistanceSensor.printReading();
  verticalDistanceSensor.printReading();

  Serial.println("--------------------");
  delay(500);
}