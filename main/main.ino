#include "HorizontalDistanceSensor.h"
#include "VerticalDistanceSensor.h"
#include "Motor.h"

HorizontalDistanceSensor horizontalDistanceSensor(9, 10);
VerticalDistanceSensor verticalDistanceSensor(11, 12);
Motor motor(6);
int counter = 0;

void setup() {
  Serial.begin(9600);
  
  horizontalDistanceSensor.begin();
  verticalDistanceSensor.begin();
  motor.begin();
}

void loop() {
  // horizontalDistanceSensor.printReading();
  // verticalDistanceSensor.printReading();

  // Serial.println("--------------------");
  // delay(500);
}
